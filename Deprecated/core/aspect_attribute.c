#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "db/dbutil.h"

#define TABLE_NAME "aspect_attribute"
 
PG_FUNCTION_INFO_V1(aspect_attribute_create);

Datum 
aspect_attribute_create(PG_FUNCTION_ARGS)
{
    int proc;
    char sql[200];
    sprintf(sql, "insert into %s.aspect_attribute(aspect_id, attribute_id, value, data_type_id) \
        values($1, $2, $3, $4)", SCHEMA_NAME);

    proc = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, false);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_attribute_create_many);

Datum 
aspect_attribute_create_many(PG_FUNCTION_ARGS)
{
    int proc;
    char sql[200];
    sprintf(sql, "insert into %s.aspect_attribute(aspect_id, attribute_id, value, data_type_id) \
        values(unnest($1), $2, unnest($3), $4)", SCHEMA_NAME);

    proc = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, false);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_attribute_update);

Datum 
aspect_attribute_update(PG_FUNCTION_ARGS)
{
    int proc;
    char sql[200];
    sprintf(sql, "update %s.aspect_attribute \
        set value = $3, \
            data_type_id = $4 \
        where aspect_id = $1 and \
            attribute_id = $2", SCHEMA_NAME);

    proc = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, false);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_attribute_delete);

Datum 
aspect_attribute_delete(PG_FUNCTION_ARGS)
{
    int proc;
    char sql[200]; 
    sprintf(sql, "delete from %s.aspect_attribute \
        where aspect_id = $1 and \
            attribute_id = $2", SCHEMA_NAME);

    proc = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, false);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_attribute_find_by_id);

Datum
aspect_attribute_find_by_id(PG_FUNCTION_ARGS) {
    HeapTuple tuple;
    char sql[200];
    sprintf(sql, 
        "select aspect_id, attribute_id, value, data_type_id \
        from %s.aspect_attribute \
        where aspect_id = $1 and attribute_id = $2", 
        SCHEMA_NAME);

    tuple = run_sql_query_tuple_args(fcinfo, TABLE_NAME, sql); 

    if (tuple != NULL) {
        PG_RETURN_DATUM(HeapTupleGetDatum(tuple));
    } else {
        PG_RETURN_NULL();
    }
}

PG_FUNCTION_INFO_V1(aspect_attribute_count);

Datum
aspect_attribute_count(PG_FUNCTION_ARGS) {
    Datum ret;
    char sql[200];
    sprintf(sql, 
        "select count(*) as cnt from %s.aspect_attribute", SCHEMA_NAME);

    ret = run_sql_query_single(TABLE_NAME, sql, NULL, 0, NULL, NULL);

    PG_RETURN_INT32(DatumGetInt32(ret));
}

PG_FUNCTION_INFO_V1(aspect_attribute_find_all);

Datum
aspect_attribute_find_all(PG_FUNCTION_ARGS)
{
    FuncCallContext     *funcctx;
    TupleDesc            tupdesc;
    Portal               curs;
    int                  proc;

    if (SRF_IS_FIRSTCALL())
    {
        MemoryContext   oldcontext;
        Portal          auxcurs;

        char sql[200];
        sprintf(sql, 
        "select aspect_id, attribute_id, value, data_type_id \
        from %s.aspect_attribute",
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

