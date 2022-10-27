#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "dbutil.h"

#define TABLE_NAME "mo_relationship"

PG_FUNCTION_INFO_V1(mo_relationship_create);

Datum 
mo_relationship_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID,TIMESTAMPOID,TIMESTAMPOID,INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    
    char sql[200];
    int new_mor_id;
    
    sprintf(sql, 
        "insert into %s.mo_relationship(mor_id, description, start_time, \
        end_time, mo_target, mo_source) \
        values(nextval('%s.seq_mo_relationship'), $1, $2, $3, $4, $5) \
        returning mo_id", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    new_mor_id = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, true);
    pfree(values);
    PG_RETURN_INT32(new_mor_id);
}

PG_FUNCTION_INFO_V1(mo_relationship_create_many);

Datum 
mo_relationship_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID,TIMESTAMPARRAYOID,TIMESTAMPARRAYOID,INT4ARRAYOID,INT4ARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, 
        "insert into %s.mo_relationship(mor_id, description, start_time, \
        end_time, mo_target, mo_source) \
        values(nextval('%s.seq_mo_relationship'), unnest($1), unnest($2), \
            unnest($3), unnest($4), unnest($5))", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_relationship_update);

Datum 
mo_relationship_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID,TIMESTAMPOID,TIMESTAMPOID,INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, 
        "update %s.mo_relationship \
        set description = $2, start_time = $3, end_time = $4, mo_target = $5, \
            mo_source = $6 \
        where mor_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_relationship_delete);

Datum 
mo_relationship_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "delete from %s.mo_relationship \
        where mor_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}
