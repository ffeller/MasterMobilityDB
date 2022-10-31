#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "dbutil.h"

PG_FUNCTION_INFO_V1(aspect_type_create);

#define TABLE_NAME "aspect_type"

Datum 
aspect_type_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID, INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int new_aspect_type_id;
    
    char sql[200]; 
    sprintf(sql, "insert into %s.aspect_type(aspect_type_id, description, super_type_id) \
        values(nextval('%s.seq_aspect_type'), $1, $2) \
        returning aspect_type_id", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    new_aspect_type_id = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, true);
    pfree(values);
    PG_RETURN_INT32(new_aspect_type_id);
}

PG_FUNCTION_INFO_V1(aspect_type_create_many);

Datum 
aspect_type_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID, INT4ARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200]; 
    sprintf(sql, "insert into %s.aspect_type(aspect_type_id, description, super_type_id) \
        values(nextval('%s.seq_aspect_type'), unnest($1), unnest($2))", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_type_update);

Datum 
aspect_type_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200]; 
    sprintf(sql, "update %s.aspect_type \
        set description = $2, \
            super_type_id = $3 \
        where aspect_type_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_type_delete);

Datum 
aspect_type_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200]; 
    sprintf(sql, "delete from %s.aspect_type \
        where aspect_type_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}
