#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"
#include "funcapi.h"

#include <string.h>

#include "dbutil.h"

#define TABLE_NAME "mo_type"

PG_FUNCTION_INFO_V1(mo_type_create);

Datum 
mo_type_create(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHAROID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    
    char sql[200];
    int new_mo_type_id;
    
    sprintf(sql, "insert into %s.mo_type(mo_type_id, description) \
        values(nextval('%s.seq_mo_type'), $1) \
        returning mo_type_id", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    new_mo_type_id = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, true);
    pfree(values);
    PG_RETURN_INT32(new_mo_type_id);
}

PG_FUNCTION_INFO_V1(mo_type_create_many);
 
Datum 
mo_type_create_many(PG_FUNCTION_ARGS)
{
    Oid types[] = {VARCHARARRAYOID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    
    char sql[200];
    sprintf(sql, "insert into %s.mo_type(mo_type_id, description) \
        values(nextval('%s.seq_mo_type'), unnest($1))", SCHEMA_NAME, SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_type_update);

Datum 
mo_type_update(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID,VARCHAROID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200];
    sprintf(sql, "update %s.mo_type \
        set description = $2 \
        where mo_type_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_type_delete);

Datum 
mo_type_delete(PG_FUNCTION_ARGS)
{
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;

    char sql[200];
    sprintf(sql, "delete from %s.mo_type \
        where mo_type_id = $1", SCHEMA_NAME);

    for (int i = 0; i < argcount; i++) {
        values[i] = PG_GETARG_DATUM(i);
    }

    proc = run_sql_cmd(TABLE_NAME, sql, types, argcount, values, false);
    pfree(values);
    PG_RETURN_INT32(proc);
}

PG_FUNCTION_INFO_V1(mo_type_find_by_id);

Datum
mo_type_find_by_id(PG_FUNCTION_ARGS) {
    Oid types[] = {INT4OID};
    int argcount = sizeof(types)/sizeof(types[0]);
    Datum * values = palloc(sizeof(Datum) * argcount);
    int proc;
    SPITupleTable *tuptable;
    HeapTuple tuple;
    char sql[200];
    SPIPlanPtr stmt; 
    Datum ret;
    char op[10]; 
    Portal curs;
    char *table = TABLE_NAME;
    char curname[20];
    
    strcpy(curname, "c_");
    strcat(curname, table);

    sprintf(sql, 
        "select mo_type_id, description from %s.mo_type \
        where mo_type_id = $1", SCHEMA_NAME);

    strcpy(op, operation(sql));

    SPI_connect();

    stmt = SPI_prepare(sql, argcount, types);
    if (!stmt) {
        elog(ERROR, ERR_MMDB_001, op, SCHEMA_NAME, table);
    }

    SPI_keepplan(stmt);

    curs = SPI_cursor_open(curname, stmt, values, " ", true);
    SPI_cursor_fetch(curs, true, 1);
    
    proc = SPI_processed;

    if (SPI_tuptable != NULL) {
        tuptable = SPI_tuptable;
        tuple = tuptable->vals[0];
        ret = HeapTupleGetDatum(tuple);
        SPI_finish();
        PG_RETURN_DATUM(ret);
    } else {
        elog(WARNING, ERR_MMDB_003, op, SCHEMA_NAME, table);
        SPI_finish();
        PG_RETURN_NULL();
    }
}
