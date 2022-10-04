#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "mastermobilitydb.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(mo_relationship_create);

Datum 
mo_relationship_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID,TIMESTAMPOID,TIMESTAMPOID,INT4OID,INT4OID};
    SPIPlanPtr stmt; 
    Datum values[5];
    bool isnull;
    int new_mo_id, ret, proc;
    
    char * op = "insert";
    char * table = "master.mo_relationship";

    char * sql = 
        "insert into master.mo_relationship(mor_id, description, start_time, \
        end_time, mo_target, mo_source) \
        values(nextval('master.seq_mo_relationship'), $1, $2, $3, $4, $5) \
        returning mo_id";

    SPI_connect();

    stmt = SPI_prepare(sql, 5, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    values[0] = PG_GETARG_DATUM(0);
    values[1] = PG_GETARG_DATUM(1);
    values[2] = PG_GETARG_DATUM(2);
    values[3] = PG_GETARG_DATUM(3);
    values[4] = PG_GETARG_DATUM(4);

    ret = SPI_execp(stmt, values, " ", 1);
    if (ret < 0) {
        elog(ERROR, ERR_MMDB_002, op, table);
    }
    proc = SPI_processed;

    if (proc > 0) {
        new_mo_id = DatumGetInt32(SPI_getbinval(SPI_tuptable->vals[0],
                                    SPI_tuptable->tupdesc,
                                    1,
                                    &isnull));
    } else {
        elog(ERROR, ERR_MMDB_003, op, table);
        new_mo_id = 0;
    }

    SPI_freeplan(stmt);
    SPI_finish();

    PG_RETURN_INT32(new_mo_id);
}

PG_FUNCTION_INFO_V1(mo_relationship_update);

Datum 
mo_relationship_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID,TIMESTAMPOID,TIMESTAMPOID,INT4OID,INT4OID};
    SPIPlanPtr stmt;
    Datum values[6];
    int ret, proc;
    char * op = "update";
    char * table = "master.mo_relationship";

    char * sql = 
        "update master.mo_relationship \
        set description = $2, start_time = $3, end_time = $4, mo_target = $5, 
            mo_source = $6 \
        where mor_id = $1";

    SPI_connect();

    stmt = SPI_prepare(sql, 6, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    values[0] = PG_GETARG_DATUM(0);
    values[1] = PG_GETARG_DATUM(1);
    values[2] = PG_GETARG_DATUM(2);
    values[3] = PG_GETARG_DATUM(3);
    values[4] = PG_GETARG_DATUM(4);
    values[5] = PG_GETARG_DATUM(5);

    ret = SPI_execp(stmt, values, " ", 0);
    if (ret < 0) {
        elog(ERROR, ERR_MMDB_002, op, table);
    }
    proc = SPI_processed;

    SPI_freeplan(stmt);
    SPI_finish();

    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_relationship_delete);

Datum 
mo_relationship_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    SPIPlanPtr stmt;
    Datum values[1];
    int ret, proc;
    char * op = "delete";
    char * table = "master.mo_relationship";

    char * sql = 
        "delete from master.mo_relationship \
        where mor_id = $1";

    SPI_connect();

    stmt = SPI_prepare(sql, 1, types);
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
