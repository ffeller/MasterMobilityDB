CREATE OR REPLACE FUNCTION
mo_type_create(varchar) RETURNS int AS '$libdir/mo_type.so','mo_type_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_update(int, varchar) RETURNS int AS '$libdir/mo_type.so','mo_type_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_delete(int) RETURNS int AS '$libdir/mo_type.so','mo_type_delete'
LANGUAGE C STRICT;
