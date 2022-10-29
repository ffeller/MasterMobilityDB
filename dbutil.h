#include "funcapi.h"

#define SCHEMA_NAME "master"

#define ERR_MMDB_001 "Failure when preparing %s on table %s.%s"
#define ERR_MMDB_002 "Failure when executing %s on table %s.%s"
#define ERR_MMDB_003 "%s on table %s.%s affected no rows"

char *str_lower(char *);
char *operation(char *);

Portal open_cursor(char *, char *, int, Oid *, Datum *);
int run_sql_cmd(char *, char *, Oid *, int, Datum *, bool);
HeapTuple run_sql_query(char *, char *, Oid *, int, Datum *, TupleDesc);
