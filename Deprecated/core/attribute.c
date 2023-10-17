#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "db/dbutil.h"

#define TABLE_NAME "attribute"

PG_FUNCTION_INFO_V1(attribute_create);

Datum 
attribute_create(PG_FUNCTION_ARGS)
{
    int new_attribute_id;
    char sql[SQL_LENGTH]; 
    sprintf(sql, 
        "insert into %s.attribute(attribute_id, name, \
        aspect_type_id, data_type_id) \
        values(nextval('%s.seq_attribute'), $1, $2, $3) \
        returning attribute_id",
        SCHEMA_NAME, SCHEMA_NAME);

    new_attribute_id = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, true);
    PG_RETURN_INT32(new_attribute_id);
}

PG_FUNCTION_INFO_V1(attribute_create_many);

Datum 
attribute_create_many(PG_FUNCTION_ARGS)
{
    int proc;
    char sql[SQL_LENGTH]; 
    sprintf(sql, 
        "insert into %s.attribute(attribute_id, name, aspect_type_id, data_type_id) \
        values(nextval('%s.seq_attribute'), unnest($1), unnest($2), unnest($3))",
        SCHEMA_NAME,SCHEMA_NAME);

    proc = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, false);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(attribute_update);

Datum 
attribute_update(PG_FUNCTION_ARGS)
{
    int proc;
    char sql[SQL_LENGTH]; 
    sprintf(sql, "update %s.attribute \
        set name = $2, aspect_type_id = $3, data_type_id = $4 \
        where attribute_id = $1", SCHEMA_NAME);

    proc = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, false);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(attribute_delete);

Datum 
attribute_delete(PG_FUNCTION_ARGS)
{
    int proc;
    char sql[SQL_LENGTH]; 
    sprintf(sql, "delete from %s.attribute \
        where attribute_id = $1", SCHEMA_NAME);

    proc = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, false);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(attribute_find_by_id);

Datum
attribute_find_by_id(PG_FUNCTION_ARGS) {
    HeapTuple tuple;
    char sql[SQL_LENGTH];
    sprintf(sql, 
        "select attribute_id, name, aspect_type_id, data_type_id \
        from %s.attribute \
        where attribute_id = $1", 
        SCHEMA_NAME);

    tuple = run_sql_query_tuple_args(fcinfo, TABLE_NAME, sql); 

    if (tuple != NULL) {
        PG_RETURN_DATUM(HeapTupleGetDatum(tuple));
    } else {
        PG_RETURN_NULL();
    }
}

PG_FUNCTION_INFO_V1(attribute_count);

Datum
attribute_count(PG_FUNCTION_ARGS) {
    Datum ret;
    char sql[SQL_LENGTH];
    sprintf(sql, 
        "select count(*) as cnt from %s.attribute", SCHEMA_NAME);

    ret = run_sql_query_single(TABLE_NAME, sql, NULL, 0, NULL, NULL);

    PG_RETURN_INT32(DatumGetInt32(ret));
}

PG_FUNCTION_INFO_V1(attribute_find_all);

Datum
attribute_find_all(PG_FUNCTION_ARGS)
{
    FuncCallContext     *funcctx;
    TupleDesc            tupdesc;
    Portal               curs;
    int                  proc;

    if (SRF_IS_FIRSTCALL())
    {
        MemoryContext   oldcontext;
        Portal          auxcurs;

        char sql[SQL_LENGTH];
        sprintf(sql, 
        "select attribute_id, name, aspect_type_id, data_type_id \
        from %s.attribute",
        SCHEMA_NAME);
        
        funcctx = SRF_FIRSTCALL_INIT();
        oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);
        if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE) {
            ereport(ERROR,
                    (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
                     errmsg("function returning record called in context "
                            "that cannot accept type record")));
        }
        tupdesc = BlessTupleDesc(tupdesc);
        funcctx->tuple_desc = tupdesc;

        SPI_connect();
        auxcurs = open_cursor(TABLE_NAME, sql, NULL, 0, NULL, NULL);
        funcctx->user_fctx = auxcurs;

        MemoryContextSwitchTo(oldcontext);
    }

    funcctx = SRF_PERCALL_SETUP();

    tupdesc = funcctx->tuple_desc;
    curs = funcctx->user_fctx;

    SPI_cursor_fetch(curs, true, 1);
    proc = SPI_processed;
    if (proc > 0) 
    {
        HeapTuple    tuple;
        Datum        result;

        tuple = ret_tuple(SPI_tuptable, tupdesc);
        result = HeapTupleGetDatum(tuple);

        SRF_RETURN_NEXT(funcctx, result);
    }
    else    
    {
        SPI_cursor_close(curs);
        SPI_finish();
        SRF_RETURN_DONE(funcctx);
    }
}

PG_FUNCTION_INFO_V1(attribute_find_by_name);

Datum
attribute_find_by_name(PG_FUNCTION_ARGS) {
    HeapTuple tuple;
    char sql[SQL_LENGTH];
    sprintf(sql, 
        "select attribute_id, name, aspect_type_id, data_type_id \
        from %s.attribute \
        where name = $1", 
        SCHEMA_NAME);

    tuple = run_sql_query_tuple_args(fcinfo, TABLE_NAME, sql); 

    if (tuple != NULL) {
        PG_RETURN_DATUM(HeapTupleGetDatum(tuple));
    } else {
        PG_RETURN_NULL();
    }
}

