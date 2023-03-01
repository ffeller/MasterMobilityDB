#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"
#include "funcapi.h"
#include "utils/lsyscache.h"
 
#include "dbutil.h"

char *str_lower(char *str){
  int i = 0;
  static char ret[SQL_LENGTH];
  
  while (str[i]) {
    ret[i] = tolower(str[i]);
    i++;
  }
  ret[i] = '\0';

  return ret;
}

char *operation(char *sql) {
  char tokens[SQL_LENGTH];
  char *token; 
  char *op;

  strcpy(tokens, sql);
  token = strtok(tokens, " ");
  while (strcasecmp(token,"select") 
    && strcasecmp(token,"insert")
    && strcasecmp(token,"update") 
    && strcasecmp(token,"delete")
    && token != NULL) {
    token = strtok(NULL, " ");
  }

  if (token == NULL) {
    strcpy(op, "unknown operation");
  } else {
    op = str_lower(token);
  }

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
      elog(WARNING, ERR_MMDB_003, op, SCHEMA_NAME, table);
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

Datum * run_sql_cmd_new(
  char *table,
  char *sql,
  Oid *types,
  int argcount, 
  Datum *values,
  char *nulls,
  uint64 *n
) {
  Datum *elems;
  SPIPlanPtr stmt; 
  bool isnull;
  Datum newid;
  int ret; 
  uint64 proc;
  SPITupleTable *tuptable;
  char *op = operation(sql);

  if (SPI_connect() != SPI_OK_CONNECT) {
    elog(ERROR, ERR_MMDB_004, op, SCHEMA_NAME, table);
  }

  stmt = SPI_prepare(sql, argcount, types);
  if (!stmt) {
    elog(ERROR, ERR_MMDB_001, op, SCHEMA_NAME, table);
  }

  if (SPI_keepplan(stmt) != 0) {
    elog(ERROR, ERR_MMDB_005, op, SCHEMA_NAME, table);
  }

  ret = SPI_execp(stmt, values, nulls, 0);
  if (ret < 0) {
    elog(ERROR, ERR_MMDB_002, op, SCHEMA_NAME, table);
  }
  proc = SPI_processed;

  if (proc == 0) {
    elog(WARNING, ERR_MMDB_003, op, SCHEMA_NAME, table);
  }

  tuptable = SPI_tuptable;
  *n = tuptable->numvals;
  elems = (Datum *) palloc(*n * sizeof(Datum));

  for (int i = 0; i < *n; i++) {
    newid = SPI_getbinval(tuptable->vals[i],
                                tuptable->tupdesc,
                                1,
                                &isnull);
    elems[i] = newid;
  }

  if (SPI_finish() != SPI_OK_FINISH) {
    elog(ERROR, ERR_MMDB_006, op, SCHEMA_NAME, table);
  }

  return elems;
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

Datum * run_sql_cmd_args_new(
    PG_FUNCTION_ARGS, 
    char *table_name, 
    char *sql,
    uint64 *n
) {
    Datum *newids;
    int argcount = PG_NARGS();
    Oid *types = (Oid *) palloc(sizeof(Oid) * argcount);
    Datum *values = (Datum *) palloc(sizeof(Datum) * argcount);
    char *nulls = (char *) palloc(sizeof(char) * argcount);

    prepare_arrays(fcinfo, argcount, types, values, nulls);
    
    newids = run_sql_cmd_new(table_name, sql, types, argcount, values, nulls, n);
    pfree(values);
    pfree(nulls);
    pfree(types);

    return newids;
}

int run_sql_cmd_args(
    PG_FUNCTION_ARGS, 
    char *table_name, 
    char *sql, 
    bool retid
) {
    int argcount = PG_NARGS();
    Oid * types = (Oid *) palloc(sizeof(Oid) * argcount);
    Datum * values = (Datum *) palloc(sizeof(Datum) * argcount);
    char * nulls = (char *) palloc(sizeof(char) * argcount);
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
    Oid * types = (Oid *) palloc(sizeof(Oid) * argcount);
    Datum * values = (Datum *) palloc(sizeof(Datum) * argcount);
    char * nulls = (char *) palloc(sizeof(char) * argcount);
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

ArrayType * make_pg_array(
    Datum *carray, 
    uint64 nelems
) {
    ArrayType *result;
    Oid       elemtype = INT4OID;
    int16     typlen;
    bool      typbyval;
    char      typalign;

    get_typlenbyvalalign(elemtype, &typlen, &typbyval, &typalign);    
    result = construct_array(carray, nelems, INT4OID, typlen, typbyval, typalign);

    return result;
}

char * temp_table (char *schema_name, char *table_name) {
  char sql[SQL_LENGTH];
  char tmpname[50];
  
  strcpy(tmpname, "tmp_");
  strcat(tmpname, table_name);

   sprintf(sql,
      "create temp table %s as \
          select description, x, y, t, space_time, aspect_type_id \
          from %s.%s limit 0", tmpname, schema_name, table_name);

run_sql_cmd(table_name, sql, types, argcount, values, nulls, retid);

}

char * get_table_non_pk_columns(char *table_name, int *attr_qty) {
    char sql[SQL_LENGTH];
    
    sprintf(sql, 
       "select column_name from pg_arr where table_name = '%s' and column_name not in (select column_name from information_schema.key_column_usage where table_name = '%s');", table_name, table_name);
    SPI_connect();
    int result = SPI_exec(query, 0);
    
    if (result < 0) {
        elog(ERROR, "Query failed: %s", SPI_result_code_string(result));
        SPI_finish();
        PG_RETURN_NULL();
    }
    
    int num_rows = SPI_processed;
    
    for (int i = 0; i < num_rows; i++) {
        char *column_name = SPI_getvalue(result, i, 1);
        char *data_type = SPI_getvalue(result, i, 2);
        char *is_nullable = SPI_getvalue(result, i, 3);
        
        printf("%s\t%s\t%s\n", column_name, data_type, is_nullable);
    }
    
    SPI_finish();
    PG_RETURN_NULL();
}
