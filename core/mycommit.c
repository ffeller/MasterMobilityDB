#include "postgres.h"
#include "executor/spi.h"
#include "utils/builtins.h"

PG_FUNCTION_INFO_V1(my_commit);

Datum my_commit(PG_FUNCTION_ARGS)
{
    SPIExecuteOptions execopts;

    SPI_connect_ext(SPI_OPT_NONATOMIC);

    memset(&execopts, 0, sizeof(execopts));
    execopts.params = NULL;
    execopts.read_only = false;
    execopts.allow_nonatomic = true;
    execopts.must_return_tuples = false;
    execopts.tcount = 0;
    execopts.dest = NULL;
    execopts.owner = NULL;

    /* Execute some SQL commands */
    SPI_execute_extended("UPDATE master.attribute SET name = 'done'", &execopts);

    /* Commit the transaction */
    SPI_commit();

    SPI_finish();

    PG_RETURN_NULL();
}

PG_FUNCTION_INFO_V1(my_commit2);

Datum my_commit2(PG_FUNCTION_ARGS)
{
    int ret;
    SPI_connect();

    /* Execute some SQL commands */
    ret = SPI_execute("UPDATE master.attribute SET name = 'done'", false, 0);
    if (ret != SPI_OK_UPDATE) {
        elog(ERROR, "Failed to update mytable: %d", ret);
    }

    /* Commit the transaction */
    ret = SPI_execute("COMMIT", false, 0);
    if (ret != SPI_OK_UTILITY) {
        elog(ERROR, "Failed to commit transaction: %d", ret);
    }

    SPI_finish();

    PG_RETURN_NULL();
}
