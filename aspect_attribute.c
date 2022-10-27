#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "dbutil.h"

#define TABLE_NAME "aspect_attribute"
 
PG_FUNCTION_INFO_V1(aspect_attribute_create);

Datum 
aspect_attribute_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,INT4OID,VARCHAROID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum *values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "insert into %s.aspect_attribute(aspect_id, attribute_id, value, data_type_id) \
        values($1, $2, $3, $4)", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_attribute_create_many);

Datum 
aspect_attribute_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4ARRAYOID,INT4ARRAYOID,VARCHARARRAYOID,INT4ARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum *values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "insert into %s.aspect_attribute(aspect_attribute_id, value, data_type) \
        values(unnest($1), unnest($2), unnest($3), unnest($4))", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);

    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_attribute_update);

Datum 
aspect_attribute_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,INT4OID,VARCHAROID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum *values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200];
    sprintf(sql, "update %s.aspect_attribute \
        set value = $2, \
            data_type_id = $4 \
        where aspect_id = $1 and \
            attribute_id = $2", SCHEMA_NAME);

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_attribute_delete);

Datum 
aspect_attribute_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum *values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200]; 
    sprintf(sql, "delete from %s.aspect_attribute \
        where aspect_id = $1 and \
            attribute_id = $2", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}
