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
    char *nulls = palloc(sizeof(char) * argcount);
    
    char sql[200];
    int new_mor_id;
    
    sprintf(sql, 
        "insert into %s.mo_relationship(mor_id, description, start_time, \
        end_time, mo_target, mo_source) \
        values(nextval('%s.seq_mo_relationship'), $1, $2, $3, $4, $5) \
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

    new_mor_id = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, nulls, true);
    pfree(values);
    pfree(nulls);
    PG_RETURN_INT32(new_mor_id);
}

PG_FUNCTION_INFO_V1(mo_relationship_create_many);

Datum 
mo_relationship_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID,TIMESTAMPARRAYOID,TIMESTAMPARRAYOID,INT4ARRAYOID,INT4ARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, 
        "insert into %s.mo_relationship(mor_id, description, start_time, \
        end_time, mo_target, mo_source) \
        values(nextval('%s.seq_mo_relationship'), unnest($1), unnest($2), \
            unnest($3), unnest($4), unnest($5))", SCHEMA_NAME, SCHEMA_NAME);

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

PG_FUNCTION_INFO_V1(mo_relationship_update);

Datum 
mo_relationship_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID,TIMESTAMPOID,TIMESTAMPOID,INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, 
        "update %s.mo_relationship \
        set description = $2, start_time = $3, end_time = $4, mo_target = $5, \
            mo_source = $6 \
        where mor_id = $1", SCHEMA_NAME);

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

PG_FUNCTION_INFO_V1(mo_relationship_delete);

Datum 
mo_relationship_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "delete from %s.mo_relationship \
        where mor_id = $1", SCHEMA_NAME);

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

PG_FUNCTION_INFO_V1(mo_relationship_find_by_id);

Datum
mo_relationship_find_by_id(PG_FUNCTION_ARGS) {
    Oid types[] = {INT4OID,VARCHAROID,TIMESTAMPOID,TIMESTAMPOID,INT4OID,INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum *values = palloc(sizeof(Datum) * argcount);
    char *nulls = palloc(sizeof(char) * argcount);
    HeapTuple tuple;
    TupleDesc tupdesc;

    char sql[200];
    sprintf(sql, 
        "select mor_id, description, start_time, \
        end_time, mo_target, mo_source \
        from %s.mo_relationship \
        where mor_id = $1", 
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

PG_FUNCTION_INFO_V1(mo_relationship_count);

Datum
mo_relationship_count(PG_FUNCTION_ARGS) {
    Datum ret;
    char sql[200];
    sprintf(sql, 
        "select count(*) as cnt from %s.mo_relationship", SCHEMA_NAME);

    ret = run_sql_query_single(TABLE_NAME, sql, NULL, 0, NULL, NULL);

    PG_RETURN_INT32(DatumGetInt32(ret));
}

PG_FUNCTION_INFO_V1(mo_relationship_find_all);

Datum
mo_relationship_find_all(PG_FUNCTION_ARGS)
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
            "select mor_id, description, start_time, \
            end_time, mo_target, mo_source \
            from %s.mo_relationship",
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

