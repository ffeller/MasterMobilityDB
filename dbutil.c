#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

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

