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
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt; 
    Datum * values = malloc(sizeof(Datum) * argcount);
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
    free(values);

    PG_RETURN_INT32(new_mo_id);
}

PG_FUNCTION_INFO_V1(mo_relationship_create_many);

Datum 
mo_relationship_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID,TIMESTAMPARRAYOID,TIMESTAMPARRAYOID,INT4ARRAYOID,INT4ARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt; 
    Datum * values = malloc(sizeof(Datum) * argcount);
    int ret, proc;
    
    char * op = "insert";
    char * table = "master.mo_relationship";

    char * sql = 
        "insert into master.mo_relationship(mor_id, description, start_time, \
        end_time, mo_target, mo_source) \
        values(nextval('master.seq_mo_relationship'), unnest($1), unnest($2), \
            unnest($3), unnest($4), unnest($5))";

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

PG_FUNCTION_INFO_V1(mo_relationship_update);

Datum 
mo_relationship_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID,TIMESTAMPOID,TIMESTAMPOID,INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt;
    Datum * values = malloc(sizeof(Datum) * argcount);
    int ret, proc;
    char * op = "update";
    char * table = "master.mo_relationship";

    char * sql = 
        "update master.mo_relationship \
        set description = $2, start_time = $3, end_time = $4, mo_target = $5, \
            mo_source = $6 \
        where mor_id = $1";

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

PG_FUNCTION_INFO_V1(mo_relationship_delete);

Datum 
mo_relationship_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    SPIPlanPtr stmt;
    Datum * values = malloc(sizeof(Datum) * argcount);
    int ret, proc;
    char * op = "delete";
    char * table = "master.mo_relationship";

    char * sql = 
        "delete from master.mo_relationship \
        where mor_id = $1";

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
