#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "mastermobilitydb.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(moving_object_create);

Datum 
moving_object_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,INT4OID};
    SPIPlanPtr stmt; 
    Datum values[2];
    bool isnull;
    int new_mo_id, ret, proc;
    
    char * op = "insert";
    char * table = "master.point";

    char * sql = 
        "insert into master.point(point_id, p_order, mat_id) \
        values(nextval('master.seq_point'), $1, $2) \
        returning point_id";

    SPI_connect();

    stmt = SPI_prepare(sql, 1, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    values[0] = PG_GETARG_DATUM(0);
    values[1] = PG_GETARG_DATUM(1);

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

PG_FUNCTION_INFO_V1(moving_object_update);

Datum 
moving_object_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,INT4OID,INT4OID};
    SPIPlanPtr stmt;
    Datum values[3];
    int ret, proc;
    char * op = "update";
    char * table = "master.point";

    char * sql = 
        "update master.point \
        set description = $2, \
            mo_type_id = $3 \
        where point_id = $1";

    SPI_connect();

    stmt = SPI_prepare(sql, 3, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    values[0] = PG_GETARG_DATUM(0);
    values[1] = PG_GETARG_DATUM(1);
    values[2] = PG_GETARG_DATUM(2);

    ret = SPI_execp(stmt, values, " ", 0);
    if (ret < 0) {
        elog(ERROR, ERR_MMDB_002, op, table);
    }
    proc = SPI_processed;

    SPI_freeplan(stmt);
    SPI_finish();

    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(moving_object_delete);

Datum 
moving_object_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    SPIPlanPtr stmt;
    Datum values[1];
    int ret, proc;
    char * op = "delete";
    char * table = "master.point";

    char * sql = 
        "delete from master.point \
        where point_id = $1";

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
