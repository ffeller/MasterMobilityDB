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
    char *nulls = palloc(sizeof(char) * argcount);
    
    char sql[200];
    int new_mo_id;

    sprintf(sql, "insert into %s.moving_object(mo_id, description, mo_type_id) \
        values(nextval('%s.seq_moving_object'), $1, $2) \
        returning mo_id", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        if (PG_ARGISNULL(i)) {
            values[i] =  (Datum) NULL;
            nulls[i] = 'n';
        } else {
            values[i] = PG_GETARG_DATUM(i);
            nulls[i] = ' ';
        }
    }

    new_mo_id = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, nulls, true);
    pfree(values);
    pfree(nulls);
    PG_RETURN_INT32(new_mo_id);
}

PG_FUNCTION_INFO_V1(moving_object_create_many);

Datum 
moving_object_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID, INT4ARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "insert into %s.moving_object(mo_id, description, mo_type_id) \
        values(nextval('%s.seq_moving_object'), unnest($1), unnest($2))", 
        SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        if (PG_ARGISNULL(i)) {
            values[i] =  (Datum) NULL;
            nulls[i] = 'n';
        } else {
            values[i] = PG_GETARG_DATUM(i);
            nulls[i] = ' ';
        }
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, nulls, false);
    pfree(values);
    pfree(nulls);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(moving_object_update);

Datum 
moving_object_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "update %s.moving_object \
        set description = $2, \
            mo_type_id = $3 \
        where mo_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
        nulls[i] = PG_ARGISNULL(i) ? 'n' : ' ';
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, nulls, false);
    pfree(values);
    pfree(nulls);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(moving_object_delete);

Datum 
moving_object_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "delete from %s.moving_object \
        where mo_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        if (PG_ARGISNULL(i)) {
            values[i] =  (Datum) NULL;
            nulls[i] = 'n';
        } else {
            values[i] = PG_GETARG_DATUM(i);
            nulls[i] = ' ';
        }
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, nulls, false);
    pfree(values);
    pfree(nulls);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(moving_object_find_by_id);

Datum
moving_object_find_by_id(PG_FUNCTION_ARGS) {
    Oid types[] = {INT4OID,VARCHAROID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum *values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    HeapTuple tuple;
    TupleDesc tupdesc;

    char sql[200];
    sprintf(sql, 
        "select mo_id, description, mo_type_id \
        from %s.moving_object \
        where mo_id = $1", 
        SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        if (PG_ARGISNULL(i)) {
            values[i] =  (Datum) NULL;
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

    if (tuple != NULL) {
        PG_RETURN_DATUM(HeapTupleGetDatum(tuple));
    } else {
        PG_RETURN_NULL();
    }
}

PG_FUNCTION_INFO_V1(moving_object_count);

Datum
moving_object_count(PG_FUNCTION_ARGS) {
    Datum ret;
    char sql[200];
    sprintf(sql, 
        "select count(*) as cnt from %s.moving_object", SCHEMA_NAME);

    ret = run_sql_query_single(TABLE_NAME, sql, NULL, 0, NULL, NULL);

    PG_RETURN_INT32(DatumGetInt32(ret));
}

PG_FUNCTION_INFO_V1(moving_object_find_all);

Datum
moving_object_find_all(PG_FUNCTION_ARGS)
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
        "select mo_id, description, mo_type_id \
        from %s.moving_object",
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

