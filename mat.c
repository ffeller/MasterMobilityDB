#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "mastermobilitydb.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(mat_create);
 
Datum 
mat_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID};
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt; 
    Datum * values = malloc(sizeof(Datum) * argcount);
    bool isnull;
    int new_mat_id, ret, proc;
    
    char * op = "insert";
    char * table = "master.mat";

    char * sql = 
        "insert into master.mat(mat_id, description) \
        values(nextval('master.seq_mat'), $1) \
        returning mat_id";

    SPI_connect();

    stmt = SPI_prepare(sql, argcount, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, table);
    }

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    ret = SPI_execp(stmt, values, " ", 1);
    if (ret < 0) {
        elog(ERROR, ERR_MMDB_002, op, table);
    }
    proc = SPI_processed;

    if (proc > 0) {
        new_mat_id = DatumGetInt32(SPI_getbinval(SPI_tuptable->vals[0],
                                    SPI_tuptable->tupdesc,
                                    1,
                                    &isnull));
    } else {
        elog(ERROR, ERR_MMDB_003, op, table);
        new_mat_id = 0;
    }

    SPI_freeplan(stmt);
    SPI_finish();
    free(values);

    PG_RETURN_INT32(new_mat_id);
}

PG_FUNCTION_INFO_V1(mat_create_many);
 
Datum 
mat_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt; 
    Datum * values = malloc(sizeof(Datum) * argcount);
    int ret, proc;
    
    char * op = "insert";
    char * table = "master.mat";

    char * sql = 
        "insert into master.mat(mat_id, description) \
        values(nextval('master.seq_mat'), unnest($1))";

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

PG_FUNCTION_INFO_V1(mat_update);

Datum 
mat_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID};
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt;
    Datum * values = malloc(sizeof(Datum) * argcount);
    int ret, proc;
    char * op = "update";
    char * table = "master.mat";

    char * sql = 
        "update master.mat \
        set description = $2 \
        where mat_id = $1";

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

PG_FUNCTION_INFO_V1(mat_delete);

Datum 
mat_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt;
    Datum * values = malloc(sizeof(Datum) * argcount);
    int ret, proc;
    char * op = "delete";
    char * table = "master.mat";

    char * sql = 
        "delete from master.mat \
        where mat_id = $1";

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
