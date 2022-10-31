#include "funcapi.h"

#define SCHEMA_NAME "master"

#define ERR_MMDB_001 "Failure when preparing %s on table %s.%s"
#define ERR_MMDB_002 "Failure when executing %s on table %s.%s"
#define ERR_MMDB_003 "%s on table %s.%s affected no rows"

char *str_lower(char *);
char *operation(char *);

Portal open_cursor(char *, char *, Oid *, int, Datum *);
int run_sql_cmd(char *, char *, Oid *, int, Datum *, bool);
HeapTuple run_sql_query_tuple(char *, char *, Oid *, int , Datum *, TupleDesc);
Datum run_sql_query_single(char *, char *, Oid *, int, Datum *);
HeapTuple ret_tuple(SPITupleTable *, TupleDesc);
