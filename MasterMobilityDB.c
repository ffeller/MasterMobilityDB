#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"
#include "executor/spi.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(MoTypeCreate);

Datum
MoTypeCreate(PG_FUNCTION_ARGS)
{
    text * description = PG_GETARG_TEXT_PP(1);
    Oid types[] = {TEXTOID};
    SPIPlanPtr stmt;
    Datum values[1];
    bool isnull;
    int new_mo_type_id, ret, proc;
    char * op = "insert";
    char * table = "master.mo_type";
    char * msg;

    char * sql = 
        "insert into master.mo_type(mo_type_id, description) \
        values(nextval(seq_mo_type), ?) \
        returning mo_type_id";

    SPI_connect();

    stmt = SPI_prepare(sql, 1, types);
    if (!stmt) {
        sprintf(msg, "Failure when preparing %s on table %s", op, table);
        elog(ERROR, msg);
    }

    values[0] = description;

    ret = SPI_execp(stmt, values, " ", 1);
    if (ret < 0) {
        sprintf(msg, "Failure when executing %s on table %s", op, table);
        elog(ERROR, msg);
    }
    proc = SPI_processed;

    if (proc > 0) {
        new_mo_type_id = DatumGetInt32(SPI_getbinval(SPI_tuptable->vals[0],
                                    SPI_tuptable->tupdesc,
                                    1,
                                    &isnull));
    } else {
        sprintf(msg, "%s on table %s affected no rows", op, table);
        elog(ERROR, msg);
        new_mo_type_id = 0;
    }

    SPI_freeplan(stmt);
    SPI_finish();

    PG_RETURN_INT32(new_mo_type_id);
}
