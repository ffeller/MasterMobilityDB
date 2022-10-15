#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "mastermobilitydb.h"

PG_FUNCTION_INFO_V1(mo_aspect_create);
 
Datum 
mo_aspect_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,INT4OID,TIMESTAMPOID,TIMESTAMPOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt; 
    Datum * values = malloc(sizeof(Datum) * argcount);
    int ret, proc;
    
    char * op = "insert";
    char * table = "master.mo_aspect";

    char * sql = 
        "insert into master.mo_aspect(mo_id, aspect_id, start_time, end_time) \
        values($1, $2, $3, $4)";

    SPI_connect();

    stmt = SPI_prepare(sql, argcount, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    ret = SPI_execp(stmt, values, " ", 0);
    if (ret < 0) {
        elog(ERROR, ERR_MMDB_002, op, table);
    }
    proc = SPI_processed;

    if (proc == 0) {
        elog(ERROR, ERR_MMDB_003, op, table);
    }

    SPI_freeplan(stmt);
    SPI_finish();
    free(values);

    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_aspect_create_many);
 
Datum 
mo_aspect_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4ARRAYOID,INT4ARRAYOID,TIMESTAMPARRAYOID,TIMESTAMPARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt; 
    Datum * values = malloc(sizeof(Datum) * argcount);
    int ret, proc;
    
    char * op = "insert";
    char * table = "master.mo_aspect";

    char * sql = 
        "insert into master.mo_aspect(mo_id, aspect_id) \
        values(unnest($1), unnest($2), unnest($3), unnest($4))";

    SPI_connect();

    stmt = SPI_prepare(sql, argcount, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    ret = SPI_execp(stmt, values, " ", 0);
    if (ret < 0) {
        elog(ERROR, ERR_MMDB_002, op, table);
    }
    proc = SPI_processed;

    if (proc == 0) {
        elog(ERROR, ERR_MMDB_003, op, table);
    }

    SPI_freeplan(stmt);
    SPI_finish();
    free(values);

    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_aspect_update);

Datum 
mo_aspect_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,INT4OID,TIMESTAMPOID,TIMESTAMPOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt;
    Datum * values = malloc(sizeof(Datum) * argcount);
    int ret, proc;
    char * op = "update";
    char * table = "master.mo_aspect";

    char * sql = 
        "update master.mo_aspect \
        set start_time = $3, end_time = $4 \
        where mo_id = $1 and aspect_id = $2";

    SPI_connect();

    stmt = SPI_prepare(sql, argcount, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    ret = SPI_execp(stmt, values, " ", 0);
    if (ret < 0) {
        elog(ERROR, ERR_MMDB_002, op, table);
    }
    proc = SPI_processed;

    SPI_freeplan(stmt);
    SPI_finish();
    free(values);

    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_aspect_delete);

Datum 
mo_aspect_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt;
    Datum * values = malloc(sizeof(Datum) * argcount);
    int ret, proc;
    char * op = "delete";
    char * table = "master.mo_aspect";

    char * sql = 
        "delete from master.mo_aspect \
        where mo_id = $1 and aspect_id = $2";

    SPI_connect();

    stmt = SPI_prepare(sql, argcount, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    ret = SPI_execp(stmt, values, " ", 0);
    if (ret < 0) {
        elog(ERROR, ERR_MMDB_002, op, table);
    }
    proc = SPI_processed;

    SPI_freeplan(stmt);
    SPI_finish();
    free(values);

    PG_RETURN_INT32(proc);
}
