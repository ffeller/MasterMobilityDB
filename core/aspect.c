#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

#include "dbutil.h"

#define TABLE_NAME "aspect"

PG_FUNCTION_INFO_V1(aspect_create);

Datum 
aspect_create(PG_FUNCTION_ARGS)
{
    int argcount = PG_NARGS();
    Oid *types = palloc(sizeof(Oid) * argcount);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    int new_aspect_id;

    char sql[200]; 
    sprintf(sql, "insert into %s.aspect(aspect_id, description, x, y, t, \
            space_time, aspect_type_id) \
        values(nextval('%s.seq_aspect'), $1, $2, $3, $4, $5, $6) \
        returning aspect_id", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        types[i] = get_fn_expr_argtype(fcinfo->flinfo, i);
        if (PG_ARGISNULL(i)) {
            values[i] =  (Datum) 0;
            nulls[i] = 'n';
        } else {
            values[i] = PG_GETARG_DATUM(i);
            nulls[i] = ' ';
        }
    }

    new_aspect_id = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, nulls, true);
    pfree(values);
    pfree(nulls);
    pfree(types);
    PG_RETURN_INT32(new_aspect_id);
}

PG_FUNCTION_INFO_V1(aspect_create_many);

Datum 
aspect_create_many(PG_FUNCTION_ARGS)
{
    int argcount = PG_NARGS();
    Oid *types = palloc(sizeof(Oid) * argcount);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    int proc;
    
    char sql[200]; 
    sprintf(sql, "insert into %s.aspect(aspect_id, description, x, y, t, \
            space_time, aspect_type_id) \
        values(nextval('%s.seq_aspect'), unnest($1), unnest($2), \
            unnest($3), unnest($4), unnest($5), unnest($6))", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        types[i] = get_fn_expr_argtype(fcinfo->flinfo, i);
        if (PG_ARGISNULL(i)) {
            values[i] =  (Datum) 0;
            nulls[i] = 'n';
        } else {
            values[i] = PG_GETARG_DATUM(i);
            nulls[i] = ' ';
        }
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, nulls, false);
    pfree(values);
    pfree(nulls);
    pfree(types);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_update);

Datum 
aspect_update(PG_FUNCTION_ARGS)
{
    int argcount = PG_NARGS();
    Oid *types = palloc(sizeof(Oid) * argcount);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    int proc;

    char sql[200]; 
    sprintf(sql, "update %s.aspect \
        set description = $2, x = $3, y = $4, t = $5, space_time = $6, \
            aspect_type_id = $7 \
        where aspect_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        types[i] = get_fn_expr_argtype(fcinfo->flinfo, i);
        if (PG_ARGISNULL(i)) {
            values[i] =  (Datum) 0;
            nulls[i] = 'n';
        } else {
            values[i] = PG_GETARG_DATUM(i);
            nulls[i] = ' ';
        }
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, nulls, false);
    pfree(values);
    pfree(nulls);
    pfree(types);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_delete);

Datum 
aspect_delete(PG_FUNCTION_ARGS)
{
    int argcount = PG_NARGS();
    Oid *types = palloc(sizeof(Oid) * argcount);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    int proc;

    char sql[200]; 
    sprintf(sql, "delete from %s.aspect \
        where aspect_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        types[i] = get_fn_expr_argtype(fcinfo->flinfo, i);
        if (PG_ARGISNULL(i)) {
            values[i] =  (Datum) 0;
            nulls[i] = 'n';
        } else {
            values[i] = PG_GETARG_DATUM(i);
            nulls[i] = ' ';
        }
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, nulls, false);
    pfree(values);
    pfree(nulls);
    pfree(types);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(aspect_find_by_id);

Datum
aspect_find_by_id(PG_FUNCTION_ARGS) {
    int argcount = PG_NARGS();
    Oid *types = palloc(sizeof(Oid) * argcount);
    Datum *values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    HeapTuple tuple;
    TupleDesc tupdesc;

    char sql[200];
    sprintf(sql, 
        "select aspect_id, description, x, y, t, \
            space_time, aspect_id \
        from %s.aspect \
        where aspect_id = $1", 
        SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        types[i] = get_fn_expr_argtype(fcinfo->flinfo, i);
        if (PG_ARGISNULL(i)) {
            values[i] =  (Datum) 0;
            nulls[i] = 'n';
        } else {
            values[i] = PG_GETARG_DATUM(i);
            nulls[i] = ' ';
        }
    }

    if (get_call_result_type(fcinfo, NULL, &tupdesc) != TYPEFUNC_COMPOSITE) {
        ereport(ERROR,
                (errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
                    errmsg("function returning record called in context "
                        "that cannot accept type record")));
    }

    tuple = run_sql_query_tuple(TABLE_NAME, sql, types, argcount, values, nulls, tupdesc);
    pfree(values);
    pfree(nulls);
    pfree(types);

    if (tuple != NULL) {
        PG_RETURN_DATUM(HeapTupleGetDatum(tuple));
    } else {
        PG_RETURN_NULL();
    }
}

PG_FUNCTION_INFO_V1(aspect_count);

Datum
aspect_count(PG_FUNCTION_ARGS) {
    Datum ret;
    char sql[200];
    sprintf(sql, 
        "select count(*) as cnt from %s.aspect", SCHEMA_NAME);

    ret = run_sql_query_single(TABLE_NAME, sql, NULL, 0, NULL, NULL);

    PG_RETURN_INT32(DatumGetInt32(ret));
}

PG_FUNCTION_INFO_V1(aspect_find_all);

Datum
aspect_find_all(PG_FUNCTION_ARGS)
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
        "select aspect_id, description, x, y, t, \
            space_time, aspect_id \
        from %s.aspect",
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

