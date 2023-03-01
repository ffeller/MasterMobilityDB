#include "funcapi.h"

#define SCHEMA_NAME "master"

#define ERR_MMDB_001 "Failure when preparing %s on table %s.%s"
#define ERR_MMDB_002 "Failure when executing %s on table %s.%s"
#define ERR_MMDB_003 "%s on table %s.%s affected no rows"

char *str_lower(char *);
char *operation(char *);

Portal open_cursor(char *, char *, Oid *, int, Datum *, char *);
int run_sql_cmd(char *, char *, Oid *, int, Datum *, char *, bool);
HeapTuple run_sql_query_tuple(char *, char *, Oid *, int , Datum *, char *, TupleDesc);
Datum run_sql_query_single(char *, char *, Oid *, int, Datum *, char *);
HeapTuple ret_tuple(SPITupleTable *, TupleDesc);
int run_sql_cmd_args(PG_FUNCTION_ARGS, char *, char *, bool);
void prepare_arrays(PG_FUNCTION_ARGS, int, Oid *, Datum *, char *);
HeapTuple run_sql_query_tuple_args(PG_FUNCTION_ARGS, char *, char *);
