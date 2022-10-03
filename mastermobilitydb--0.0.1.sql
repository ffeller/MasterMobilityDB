CREATE OR REPLACE FUNCTION
mo_type_create(varchar) RETURNS int AS '$libdir/mo_type.so','mo_type_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_update(int, varchar) RETURNS int AS '$libdir/mo_type.so','mo_type_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_delete(int) RETURNS int AS '$libdir/mo_type.so','mo_type_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_type_create(varchar, int) RETURNS int AS '$libdir/aspect_type.so','aspect_type_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_type_update(int, varchar, int) RETURNS int AS '$libdir/aspect_type.so','aspect_type_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_type_delete(int) RETURNS int AS '$libdir/aspect_type.so','aspect_type_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_create(varchar, int) RETURNS int AS '$libdir/moving_object.so','moving_object_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_update(int, varchar, int) RETURNS int AS '$libdir/moving_object.so','moving_object_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_delete(int) RETURNS int AS '$libdir/moving_object.so','moving_object_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_create(varchar, int) RETURNS int AS '$libdir/point.so','point_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_update(int, varchar, int) RETURNS int AS '$libdir/point.so','point_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_delete(int) RETURNS int AS '$libdir/point.so','point_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_create(varchar, int) RETURNS int AS '$libdir/point.so','point_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_update(int, varchar, int) RETURNS int AS '$libdir/point.so','point_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_delete(int) RETURNS int AS '$libdir/point.so','point_delete'
LANGUAGE C STRICT;
