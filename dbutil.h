#include "funcapi.h"
#include "utils/array.h"

#define SCHEMA_NAME "master"
#define SQL_LENGTH 400
#define OBJ_LENGTH 30
#define BATCH_SIZE 10000

#define ERR_MMDB_001 "Failure preparing %s on table %s.%s"
#define ERR_MMDB_002 "Failure executing %s on table %s.%s"
#define ERR_MMDB_003 "%s on table %s.%s affected no rows"
#define ERR_MMDB_004 "Failure connecting to SPI manager on %s on table %s.%s"
#define ERR_MMDB_005 "Failure saving %s on table %s.%s"
#define ERR_MMDB_006 "Failure disconnecting from SPI manager on %s on table %s.%s"
#define ERR_MMDB_007 "Failure getting results from %s on table %s.%s"
#define ERR_MMDB_008 "SPI_connect() must be called first"

typedef struct {
  char schema[OBJ_LENGTH];
  char table[OBJ_LENGTH];
  char attribute[OBJ_LENGTH];
  char datatype[OBJ_LENGTH];
  bool required;
  bool pkey;
} typ_table_s;

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
Datum * run_sql_cmd_new(char *, char *, Oid *, int, Datum *, char *, uint64 *);
Datum * run_sql_cmd_args_new(PG_FUNCTION_ARGS, char *, char *, uint64 *);
ArrayType * make_pg_array(Datum *, uint64);
typ_table_s * get_table_structure(char *, char *);
