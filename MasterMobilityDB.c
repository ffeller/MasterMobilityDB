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
    Datum values[1];

    char * sql = 
        "insert into master.mo_type(mo_type_id, description) \
        values(nextval(seq_mo_type), ?) \
        returning mo_type_id";
     
    SPIPlanPtr stmt = SPI_prepare(sql, 1, types);
    if (!stmt) {
        elog(ERROR, sprintf("Failure when preparing %s on table %s", "insert", "master.mo_type"));
    }

    values[0] = description;

    int ret = SPI_execp(stmt, values, " ", 1);
    if (ret < 0) {
        elog(ERROR, sprintf("Failure when executing %s on table %s", "insert", "master.mo_type"));
    }

    if SPI_processed > 0 {
        
    }
}
