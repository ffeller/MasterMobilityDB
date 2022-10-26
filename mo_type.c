#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "dbutil.h"

#define TABLE_NAME "mo_type"

PG_FUNCTION_INFO_V1(mo_type_create);

Datum 
mo_type_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    
    char sql[200];
    int new_mo_type_id;
    
    sprintf(sql, "insert into %s.mo_type(mo_type_id, description) \
        values(nextval('%s.seq_mo_type'), $1) \
        returning mo_type_id", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    new_mo_type_id = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, true);
    pfree(values);
    PG_RETURN_INT32(new_mo_type_id);
}

PG_FUNCTION_INFO_V1(mo_type_create_many);
 
Datum 
mo_type_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "insert into %s.mo_type(mo_type_id, description) \
        values(nextval('%s.seq_mo_type'), unnest($1))", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_type_update);

Datum 
mo_type_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200];
    sprintf(sql, "update %s.mo_type \
        set description = $2 \
        where mo_type_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_type_delete);

Datum 
mo_type_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200];
    sprintf(sql, "delete from %s.mo_type \
        where mo_type_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}
