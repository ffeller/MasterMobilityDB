#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "dbutil.h"

#define TABLE_NAME "aspect"

PG_FUNCTION_INFO_V1(aspect_create);

Datum 
aspect_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID,INT4OID,INT4OID,TIMESTAMPOID,INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int new_aspect_id;

    char sql[200]; 
    sprintf(sql, "insert into %s.aspect(aspect_id, description, x, y, t, \
            space_time, aspect_type_id) \
        values(nextval('%s.seq_aspect'), $1, $2, $3, $4, $5, $6) \
        returning aspect_id", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    pfree(values);
    new_aspect_id = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, true);
    PG_RETURN_INT32(new_aspect_id);
}

PG_FUNCTION_INFO_V1(aspect_create_many);

Datum 
aspect_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID,INT4ARRAYOID,INT4ARRAYOID,
        TIMESTAMPARRAYOID,INT4ARRAYOID,INT4ARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200]; 
    sprintf(sql, "insert into %s.aspect(aspect_id, description, x, y, t, \
            space_time, aspect_type_id) \
        values(nextval('%s.seq_aspect'), unnest($1), unnest($2), \
            unnest($3), unnest($4), unnest($5), unnest($6))", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_update);

Datum 
aspect_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID,INT4OID,INT4OID,TIMESTAMPOID,INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200]; 
    sprintf(sql, "update %s.aspect \
        set description = $2, x = $3, y = $4, t = $5, space_time = $6, \
            aspect_type_id = $7 \
        where aspect_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_delete);

Datum 
aspect_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200]; 
    sprintf(sql, "delete from %s.aspect \
        where aspect_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

