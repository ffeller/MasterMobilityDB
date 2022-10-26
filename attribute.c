#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "dbutil.h"

#define TABLE_NAME "attribute"

PG_FUNCTION_INFO_V1(attribute_create);

Datum 
attribute_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID,INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int new_attribute_id;
    
    char sql[200]; 
    sprintf(sql, "insert into %s.attribute( \
        attribute_id, name, aspect_type_id, data_type_id) \
        values(nextval('%s.seq_attribute'), $1, $2, $3)",
        SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    new_attribute_id = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, true);
    pfree(values);

    PG_RETURN_INT32(new_attribute_id);
}

PG_FUNCTION_INFO_V1(attribute_create_many);

Datum 
attribute_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID,INT4ARRAYOID,INT4ARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200]; 
    sprintf(sql, "insert into %s.attribute(attribute_id, value, data_type) \
        values(nextval('%s.seq_attribute'), unnest($1), unnest($2), unnest($3))",
        SCHEMA_NAME,SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);

    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(attribute_update);

Datum 
attribute_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID,INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200]; 
    sprintf(sql, "update %s.attribute \
        set name = $2, aspect_type_id = $3, data_type_id = $4 \
        where attribute_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(attribute_delete);

Datum 
attribute_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200]; 
    sprintf(sql, "delete from %s.attribute \
        where attribute_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}
