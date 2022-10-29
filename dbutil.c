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
    int argcount, 
    Oid *types,
    Datum *values)
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
    curs = SPI_cursor_open(curname, stmt, values, " ", true);

    return(curs);
}

int run_sql_cmd(
  char *table,
  char *sql,
  Oid *types,
  int argcount,
  Datum *values,
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

  ret = SPI_execp(stmt, values, " ", (retid)?1:0);
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

HeapTuple run_sql_query(
    char *table,
    char *sql,
    Oid *types,
    int argcount,
    Datum *srcvalues,
    TupleDesc tupdesc
) {
    Datum *values;
    bool *nulls, isnull;
    TupleDesc srctupdesc, auxtupdesc;
    int colcount;
    SPITupleTable *srctuptable;
    HeapTuple tuple, srctuple;
    SPIPlanPtr stmt; 
    char op[10], curname[20]; 
    Portal curs;

    strcpy(curname, "c_");
    strcat(curname, table);

    strcpy(op, operation(sql));

    SPI_connect();

    stmt = SPI_prepare(sql, argcount, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, SCHEMA_NAME, table);
    }

    SPI_keepplan(stmt);

    curs = SPI_cursor_open(curname, stmt, srcvalues, " ", true);
    SPI_cursor_fetch(curs, true, 1);

    if (SPI_tuptable != NULL) {
        srctuptable = SPI_tuptable;
        srctupdesc = srctuptable->tupdesc;
        srctuple = srctuptable->vals[0];
        colcount = srctupdesc->natts;

        values = (Datum *) palloc(sizeof(Datum) * colcount);
        nulls = (bool *) palloc(sizeof(bool) * colcount);
        for (int i = 1; i <= colcount; i++) {
            values[i-1] = SPI_getbinval(srctuple, srctupdesc, i, &isnull);
            nulls[i-1] = isnull;
        }

        auxtupdesc = BlessTupleDesc(tupdesc);
        tuple = heap_form_tuple(auxtupdesc, values, nulls);
        
        pfree(values);
        pfree(nulls);
        SPI_cursor_close(curs);
        SPI_finish();
        
        return tuple;
    } else {
        elog(WARNING, ERR_MMDB_003, op, SCHEMA_NAME, table);
        SPI_cursor_close(curs);
        SPI_finish();
        return NULL;
    }
}

