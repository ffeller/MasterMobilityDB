#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "dbutil.h"

#define TABLE_NAME "moving_object"

PG_FUNCTION_INFO_V1(moving_object_create);

Datum 
moving_object_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID, INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    
    char sql[200];
    int new_mo_id;

    sprintf(sql, "insert into %s.moving_object(mo_id, description, mo_type_id) \
        values(nextval('%s.seq_moving_object'), $1, $2) \
        returning mo_id", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    new_mo_id = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, true);
    pfree(values);
    PG_RETURN_INT32(new_mo_id);
}

PG_FUNCTION_INFO_V1(moving_object_create_many);

Datum 
moving_object_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID, INT4ARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "insert into %s.moving_object(mo_id, description, mo_type_id) \
        values(nextval('%s.seq_moving_object'), unnest($1), unnest($2))", 
        SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(moving_object_update);

Datum 
moving_object_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "update %s.moving_object \
        set description = $2, \
            mo_type_id = $3 \
        where mo_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(moving_object_delete);

Datum 
moving_object_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "delete from %s.moving_object \
        where mo_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}
