--aspect_attribute
CREATE OR REPLACE FUNCTION
aspect_attribute_create(integer, integer, varchar, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_attribute_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_attribute_create_many(integer[], integer[], varchar[], integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_attribute_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_attribute_update(integer, integer, varchar, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_attribute_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_attribute_delete(integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_attribute_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--aspect_type
CREATE OR REPLACE FUNCTION
aspect_type_create(varchar, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_type_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_type_create_many(varchar[], integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_type_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_type_update(integer, varchar, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_type_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_type_delete(integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_type_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--aspect
CREATE OR REPLACE FUNCTION
aspect_create(varchar, integer, integer, timestamp, integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_create_many(varchar[], integer[], integer[], timestamp[], integer[], integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_update(integer, varchar, integer, integer, timestamp, integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_delete(integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--attribute
CREATE OR REPLACE FUNCTION
attribute_create(varchar, integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','attribute_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
attribute_create_many(varchar[], integer[], integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','attribute_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
attribute_update(integer, varchar, integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','attribute_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
attribute_delete(integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','attribute_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--mat_aspect
CREATE OR REPLACE FUNCTION
mat_aspect_create(integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_aspect_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_aspect_create_many(integer[], integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_aspect_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_aspect_delete(integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_aspect_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--mat
CREATE OR REPLACE FUNCTION
mat_create(varchar) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_create_many(varchar[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_update(integer, varchar) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_delete(integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--mo_aspect
CREATE OR REPLACE FUNCTION
mo_aspect_create(integer, integer, timestamp, timestamp) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_aspect_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_aspect_create_many(integer[], integer[], timestamp[], timestamp[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_aspect_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_aspect_update(integer, integer, timestamp, timestamp) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_aspect_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_aspect_delete(integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_aspect_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--mo_relationship
CREATE OR REPLACE FUNCTION
mo_relationship_create(varchar, timestamp, timestamp, integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_relationship_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_relationship_create_many(varchar[], timestamp[], timestamp[], integer[],
  integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_relationship_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_relationship_update(integer, varchar) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_relationship_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_relationship_delete(integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_relationship_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--mo_type
CREATE OR REPLACE FUNCTION
mo_type_create(varchar) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_type_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_create_many(varchar[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_type_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_update(integer, varchar) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_type_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_delete(integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_type_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_find_by_id(in integer, out integer, out varchar) 
RETURNS record 
AS 'MODULE_PATHNAME','mo_type_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_find_all(out integer, out varchar) 
RETURNS setof record 
AS 'MODULE_PATHNAME','mo_type_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_type_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--mor_aspect
CREATE OR REPLACE FUNCTION
mor_aspect_create(integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mor_aspect_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mor_aspect_create_many(integer[], integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mor_aspect_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mor_aspect_delete(integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mor_aspect_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--moving_object
CREATE OR REPLACE FUNCTION
moving_object_create(varchar, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','moving_object_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_create_many(varchar[], integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','moving_object_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_update(integer, varchar, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','moving_object_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_delete(integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','moving_object_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--point
CREATE OR REPLACE FUNCTION
point_create(varchar, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_create_many(varchar[], integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_update(integer, varchar, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_delete(integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--point_aspect
CREATE OR REPLACE FUNCTION
point_aspect_create(integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_aspect_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_aspect_create_many(integer[], integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_aspect_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_aspect_delete(integer, integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_aspect_delete'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------
