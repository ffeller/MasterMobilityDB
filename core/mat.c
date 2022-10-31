#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "dbutil.h"

#define TABLE_NAME "mat"

PG_FUNCTION_INFO_V1(mat_create);
 
Datum 
mat_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    
    char sql[200];
    int new_mat_id;

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    new_mat_id = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, true);
    pfree(values);

    PG_RETURN_INT32(new_mat_id);
}

PG_FUNCTION_INFO_V1(mat_create_many);
 
Datum 
mat_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "insert into %s.mat(mat_id, description) \
        values(nextval('%s.seq_mat'), unnest($1))", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mat_update);

Datum 
mat_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "update %s.mat \
        set description = $2 \
        where mat_id = $1", SCHEMA_NAME);

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mat_delete);

Datum 
mat_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "delete from %s.mat \
        where mat_id = $1", SCHEMA_NAME);

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}
