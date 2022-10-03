#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "mastermobilitydb.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(mo_type_create);
 
Datum 
mo_type_create(PG_FUNCTION_ARGS)
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

PG_FUNCTION_INFO_V1(mo_type_update);

Datum 
mo_type_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID};
    SPIPlanPtr stmt;
    Datum values[2];
    int ret, proc;
    char * op = "update";
    char * table = "master.mo_type";

    char * sql = 
        "update master.mo_type \
        set description = $2 \
        where mo_type_id = $1";

    SPI_connect();

    stmt = SPI_prepare(sql, 2, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    values[0] = PG_GETARG_DATUM(0);
    values[1] = PG_GETARG_DATUM(1);

    ret = SPI_execp(stmt, values, " ", 0);
    if (ret < 0) {
        elog(ERROR, ERR_MMDB_002, op, table);
    }
    proc = SPI_processed;

    SPI_freeplan(stmt);
    SPI_finish();

    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_type_delete);

Datum 
mo_type_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    SPIPlanPtr stmt;
    Datum values[1];
    int ret, proc;
    char * op = "delete";
    char * table = "master.mo_type";

    char * sql = 
        "delete from master.mo_type \
        where mo_type_id = $1";

    SPI_connect();

    stmt = SPI_prepare(sql, 2, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    values[0] = PG_GETARG_DATUM(0);

    ret = SPI_execp(stmt, values, " ", 0);
    if (ret < 0) {
        elog(ERROR, ERR_MMDB_002, op, table);
    }
    proc = SPI_processed;

    SPI_freeplan(stmt);
    SPI_finish();

    PG_RETURN_INT32(proc);
}
