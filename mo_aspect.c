#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "dbutil.h"

#define TABLE_NAME "mo_aspect"

PG_FUNCTION_INFO_V1(mo_aspect_create);
 
Datum 
mo_aspect_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,INT4OID,TIMESTAMPOID,TIMESTAMPOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum *values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "insert into %s.mo_aspect(mo_id, aspect_id, start_time, end_time) \
        values($1, $2, $3, $4)", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_aspect_create_many);
 
Datum 
mo_aspect_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4ARRAYOID,INT4ARRAYOID,TIMESTAMPARRAYOID,TIMESTAMPARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum *values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "insert into %s.mo_aspect(mo_id, aspect_id, start_time, end_time) \
        values(unnest($1), unnest($2), unnest($3), unnest($4))", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_aspect_update);

Datum 
mo_aspect_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,INT4OID,TIMESTAMPOID,TIMESTAMPOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum *values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "update %s.mo_aspect \
        set start_time = $3, end_time = $4 \
        where mo_id = $1 and aspect_id = $2", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_aspect_delete);

Datum 
mo_aspect_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum *values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "delete from %s.mo_aspect \
        where mo_id = $1 and aspect_id = $2", SCHEMA_NAME);

    SPI_connect();

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}
