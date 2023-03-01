#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "dbutil.h"

#define TABLE_NAME "aspect_type"

PG_FUNCTION_INFO_V1(aspect_type_create);

Datum 
aspect_type_create(PG_FUNCTION_ARGS)
{
    int new_aspect_type_id;
    char sql[200]; 
    sprintf(sql, "insert into %s.aspect_type(aspect_type_id, description, super_type_id) \
        values(nextval('%s.seq_aspect_type'), $1, $2) \
        returning aspect_type_id", SCHEMA_NAME, SCHEMA_NAME);

    new_aspect_type_id = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, true);
    PG_RETURN_INT32(new_aspect_type_id);
}

PG_FUNCTION_INFO_V1(aspect_type_create_many);

Datum 
aspect_type_create_many(PG_FUNCTION_ARGS)
{
    int proc;
    char sql[200]; 
    sprintf(sql, "insert into %s.aspect_type(aspect_type_id, description, super_type_id) \
        values(nextval('%s.seq_aspect_type'), unnest($1), unnest($2))", SCHEMA_NAME, SCHEMA_NAME);

    proc = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, false);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_type_update);

Datum 
aspect_type_update(PG_FUNCTION_ARGS)
{
    int proc;
    char sql[200]; 
    sprintf(sql, "update %s.aspect_type \
        set description = $2, \
            super_type_id = $3 \
        where aspect_type_id = $1", SCHEMA_NAME);

    proc = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, false);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_type_delete);

Datum 
aspect_type_delete(PG_FUNCTION_ARGS)
{
    int proc;
    char sql[200]; 
    sprintf(sql, "delete from %s.aspect_type \
        where aspect_type_id = $1", SCHEMA_NAME);

    proc = run_sql_cmd_args(fcinfo, TABLE_NAME, sql, false);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_type_find_by_id);

Datum
aspect_type_find_by_id(PG_FUNCTION_ARGS) {
    HeapTuple tuple;

    char sql[200];
    sprintf(sql, 
        "select aspect_type_id, description, super_type_id \
        from %s.aspect_type \
        where aspect_type_id = $1", 
        SCHEMA_NAME);

    tuple = run_sql_query_tuple_args(fcinfo, TABLE_NAME, sql); 

    if (tuple != NULL) {
        PG_RETURN_DATUM(HeapTupleGetDatum(tuple));
    } else {
        PG_RETURN_NULL();
    }
}

PG_FUNCTION_INFO_V1(aspect_type_count);

Datum
aspect_type_count(PG_FUNCTION_ARGS) {
    Datum ret;
    char sql[200];
    sprintf(sql, 
        "select count(*) as cnt from %s.aspect_type", SCHEMA_NAME);

    ret = run_sql_query_single(TABLE_NAME, sql, NULL, 0, NULL, NULL);

    PG_RETURN_INT32(DatumGetInt32(ret));
}

PG_FUNCTION_INFO_V1(aspect_type_find_all);

Datum
aspect_type_find_all(PG_FUNCTION_ARGS)
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
        "select aspect_type_id, description, super_type_id \
        from %s.aspect_type",
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
    } else {
        SPI_cursor_close(curs);
        SPI_finish();
        SRF_RETURN_DONE(funcctx);
    }
}
