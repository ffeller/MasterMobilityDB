#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "mastermobilitydb.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(aspect_type_create);

Datum 
aspect_type_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID, INT4OID};
    SPIPlanPtr stmt; 
    Datum values[2];
    bool isnull;
    int new_aspect_type_id, ret, proc;
    
    char * op = "insert";
    char * table = "master.aspect_type";

    char * sql = 
        "insert into master.aspect_type(aspect_type_id, description, super_type_id) \
        values(nextval('master.seq_aspect_type'), $1, $2) \
        returning aspect_type_id";

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
        new_aspect_type_id = DatumGetInt32(SPI_getbinval(SPI_tuptable->vals[0],
                                    SPI_tuptable->tupdesc,
                                    1,
                                    &isnull));
    } else {
        elog(ERROR, ERR_MMDB_003, op, table);
        new_aspect_type_id = 0;
    }

    SPI_freeplan(stmt);
    SPI_finish();

    PG_RETURN_INT32(new_aspect_type_id);
}

PG_FUNCTION_INFO_V1(aspect_type_update);

Datum 
aspect_type_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID,INT4OID};
    SPIPlanPtr stmt;
    Datum values[3];
    int ret, proc;
    char * op = "update";
    char * table = "master.aspect_type";

    char * sql = 
        "update master.aspect_type \
        set description = $2, \
            super_type_id = $3 \
        where aspect_type_id = $1";

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

PG_FUNCTION_INFO_V1(aspect_type_delete);

Datum 
aspect_type_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    SPIPlanPtr stmt;
    Datum values[1];
    int ret, proc;
    char * op = "delete";
    char * table = "master.aspect_type";

    char * sql = 
        "delete from master.aspect_type \
        where aspect_type_id = $1";

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