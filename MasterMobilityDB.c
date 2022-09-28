#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#define ERR_MMDB_001 "Failure when preparing %s on table %s"
#define ERR_MMDB_002 "Failure when executing %s on table %s"
#define ERR_MMDB_003 "%s on table %s affected no rows"
 
PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(fteste);

Datum 
fteste(PG_FUNCTION_ARGS)
{
    elog(INFO, "passo 0"); 
    PG_RETURN_INT32(1);
}

PG_FUNCTION_INFO_V1(MoTypeCreate);

Datum 
MoTypeCreate(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID};
    SPIPlanPtr stmt;
    Datum values[1];
    bool isnull;
    int new_mo_type_id, ret, proc;
    char * op = "insert";
    char * table = "master.mo_type";

    char * sql = 
        "insert into master.mo_type(mo_type_id, description) \
        values(nextval('master.seq_mo_type'), $1) \
        returning mo_type_id";

    elog(INFO, "passo 0");
    
    SPI_connect();

    stmt = SPI_prepare(sql, 1, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    values[0] = PG_GETARG_DATUM(0);

    ret = SPI_execp(stmt, values, " ", 1);
    if (ret < 0) {
        elog(ERROR, ERR_MMDB_002, op, table);
    }
    proc = SPI_processed;

    if (proc > 0) {
        new_mo_type_id = DatumGetInt32(SPI_getbinval(SPI_tuptable->vals[0],
                                    SPI_tuptable->tupdesc,
                                    1,
                                    &isnull));
    } else {
        elog(ERROR, ERR_MMDB_003, op, table);
        new_mo_type_id = 0;
    }

    SPI_freeplan(stmt);
    SPI_finish();

    PG_RETURN_INT32(new_mo_type_id);
}
