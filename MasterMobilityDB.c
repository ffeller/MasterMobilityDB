#include "postgres.h"
#include "pg_config.h"
#include "fmgr.h"

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(MoTypeCreate);

Datum
MoTypeCreate(PG_FUNCTION_ARGS)
{
int32 moTypeId = PG_GETARG_INT32(0);
text* description = PG_GETARG_TEXT_PP(1);

PG_RETURN_INT32(arg1 + arg2);
}
