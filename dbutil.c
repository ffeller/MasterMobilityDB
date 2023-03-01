#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"
#include "funcapi.h"

#include "dbutil.h"

char *str_lower(char *str){
  int i = 0;
  static char ret[200];
  
  while (str[i]) {
    ret[i] = tolower(str[i]);
    i++;
  }
  ret[i] = '\0';

  return ret;
}

char *operation(char *sql) {
  char tokens[200];
  char *token; 
  char *op;

  strcpy(tokens, sql);
  token = strtok(tokens, " ");
  op = str_lower(token);

  return op;
}

Portal open_cursor(
    char *table,
    char *sql, 
    Oid *types,
    int argcount, 
    Datum *values,
    char *nulls)
{
    SPIPlanPtr stmt;
    char op[10], curname[20]; 
    Portal curs;

    strcpy(curname, "c_");
    strcat(curname, table);

    strcpy(op, operation(sql));

    stmt = SPI_prepare(sql, argcount, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, SCHEMA_NAME, table);
    }
    SPI_keepplan(stmt);
    curs = SPI_cursor_open(curname, stmt, values, nulls, true);

    return(curs);
}

int run_sql_cmd(
  char *table,
  char *sql,
  Oid *types,
  int argcount,
  Datum *values,
  char *nulls,
  bool retid
) {
  SPIPlanPtr stmt; 
  bool isnull;
  int newid = 0;
  int ret, proc;
  char *op = operation(sql);

  SPI_connect();

  stmt = SPI_prepare(sql, argcount, types);
  if (!stmt) {
      elog(ERROR, ERR_MMDB_001, op, SCHEMA_NAME, table);
  }

  SPI_keepplan(stmt);

  ret = SPI_execp(stmt, values, nulls, (retid)?1:0);
  if (ret < 0) {
      elog(ERROR, ERR_MMDB_002, op, SCHEMA_NAME, table);
  }
  proc = SPI_processed;

  if (proc == 0) {
      elog(ERROR, ERR_MMDB_003, op, SCHEMA_NAME, table);
  } else {
    if (retid) {
      newid = DatumGetInt32(SPI_getbinval(SPI_tuptable->vals[0],
                                  SPI_tuptable->tupdesc,
                                  1,
                                  &isnull));
    }
  }

  if (retid) {
      ret = newid;
  } else {
      ret = proc;
  }

  SPI_finish();

  return ret;
}

HeapTuple ret_tuple(
    SPITupleTable *srctuptable,
    TupleDesc tupdesc
) {
    Datum *values;
    TupleDesc auxtupdesc, srctupdesc;
    HeapTuple tuple, srctuple;
    int colcount;
    bool isnull, *nulls;

    srctupdesc = srctuptable->tupdesc;
    srctuple = srctuptable->vals[0];
    colcount = srctupdesc->natts;

    values = (Datum *) palloc(sizeof(Datum) * colcount);
    nulls = (bool *) palloc(sizeof(bool) * colcount);
    for (int i = 1; i <= colcount; i++) {
        // elog(INFO, "%s=%s", SPI_fname(srctupdesc, i), SPI_getvalue(srctuple, srctupdesc, i));
        values[i-1] = SPI_getbinval(srctuple, srctupdesc, i, &isnull);
        nulls[i-1] = isnull;
    }

    auxtupdesc = BlessTupleDesc(tupdesc);
    tuple = heap_form_tuple(auxtupdesc, values, nulls);
    
    pfree(values);
    pfree(nulls);

    return tuple;
}

HeapTuple run_sql_query_tuple(
    char *table,
    char *sql,
    Oid *types,
    int argcount,
    Datum *values,
    char *nulls,
    TupleDesc tupdesc
) {
    int proc;
    char op[10]; 
    Portal curs;
    HeapTuple tuple;

    SPI_connect();
    curs = open_cursor(table, sql, types, argcount, values, nulls);
    SPI_cursor_fetch(curs, true, 1);
    proc = SPI_processed;
    if (proc > 0) {
        tuple = ret_tuple(SPI_tuptable, tupdesc);
        SPI_cursor_close(curs);
        SPI_finish();

        return tuple;
    } else {
        strcpy(op, operation(sql));
        elog(WARNING, ERR_MMDB_003, op, SCHEMA_NAME, table);
        SPI_cursor_close(curs);
        SPI_finish();

        return NULL;
    }
}
 
Datum run_sql_query_single(
    char *table,
    char *sql,
    Oid *types,
    int argcount,
    Datum *values,
    char *nulls
) {
    int proc;
    char op[10]; 
    Portal curs;
    bool isnull;
    Datum ret;

    SPI_connect();
    curs = open_cursor(table, sql, types, argcount, values, nulls);
    SPI_cursor_fetch(curs, true, 1);
    proc = SPI_processed;
    if (proc > 0) {
        ret = SPI_getbinval(SPI_tuptable->vals[0],
                                  SPI_tuptable->tupdesc,
                                  1,
                                  &isnull);
        SPI_cursor_close(curs);
        SPI_finish();

        return ret;
    } else {
        strcpy(op, operation(sql));
        elog(WARNING, ERR_MMDB_003, op, SCHEMA_NAME, table);
        SPI_cursor_close(curs);
        SPI_finish();

        return (Datum) NULL;
    }
}

void prepare_arrays(
    PG_FUNCTION_ARGS, 
    int argcount, 
    Oid * types, 
    Datum * values, 
    char * nulls
) {
    for (int i = 0; i < argcount; i++) {
        types[i] = get_fn_expr_argtype(fcinfo->flinfo, i);
        if (PG_ARGISNULL(i)) {
            values[i] =  (Datum) 0;
            nulls[i] = 'n';
        } else {
            values[i] = PG_GETARG_DATUM(i);
            nulls[i] = ' ';
        }
    }
}

int run_sql_cmd_args(
    PG_FUNCTION_ARGS, 
    char * table_name, 
    char * sql, 
    bool retid
) {
    int argcount = PG_NARGS();
    Oid * types = palloc(sizeof(Oid) * argcount);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char * nulls = palloc(sizeof(char) * argcount);
    int new_id;

    prepare_arrays(fcinfo, argcount, types, values, nulls);
    
    new_id = run_sql_cmd(table_name, sql, types, argcount, values, nulls, retid);
    pfree(values);
    pfree(nulls);
    pfree(types);
    return new_id;
}

HeapTuple run_sql_query_tuple_args(
    PG_FUNCTION_ARGS, 
    char * table_name, 
    char * sql
) {
    int argcount = PG_NARGS();
    Oid * types = palloc(sizeof(Oid) * argcount);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char * nulls = palloc(sizeof(char) * argcount);
    HeapTuple tuple;
    TupleDesc tupdesc;

    prepare_arrays(fcinfo, argcount, types, values, nulls);
    
    if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE) {
        ereport(ERROR,
                (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
                    errmsg("function returning record called in context "
                        "that cannot accept type record")));
    }

    tuple = run_sql_query_tuple(table_name, sql, types, argcount, values, nulls, tupdesc);
    pfree(values);
    pfree(nulls);
    pfree(types);

    return tuple;
}

