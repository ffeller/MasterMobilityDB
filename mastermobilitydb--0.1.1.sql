--aspect_attribute
CREATE OR REPLACE FUNCTION
aspect_attribute_create(
  in aspect_id integer, 
  in attribute_id integer, 
  in data_value varchar, 
  in data_type integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_attribute_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_attribute_create_many(
  in aspect_id_array integer[], 
  in attribute_id_array integer[], 
  in data_value_array varchar[], 
  in data_type_array integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_attribute_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_attribute_update(
  in key_id_1 integer, 
  in key_id_2 integer, 
  in data_valye varchar, 
  in data_type integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_attribute_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_attribute_delete(
  in key_id_1 integer, 
  in key_id_2 integer)
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_attribute_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_attribute_find_by_id(
  in key_id_1 integer, 
  in key_id_2 integer,
  out aspect_id integer, 
  out attribute_id integer, 
  out value varchar, 
  out data_type integer) 
RETURNS record 
AS 'MODULE_PATHNAME','aspect_attribute_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_attribute_find_all(
  out aspect_id integer, 
  out attribute_id integer, 
  out value varchar, 
  out data_type integer) 
RETURNS setof record 
AS 'MODULE_PATHNAME','aspect_attribute_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_attribute_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_attribute_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--aspect_type
CREATE OR REPLACE FUNCTION
aspect_type_create(
  in description varchar, 
  in super_type_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_type_create'
LANGUAGE C;

CREATE OR REPLACE FUNCTION
aspect_type_create_many(
  in description_array varchar[], 
  in super_type_id_array integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_type_create_many'
LANGUAGE C;

CREATE OR REPLACE FUNCTION
aspect_type_update(
  in key_id_1 integer, 
  in description varchar, 
  in super_type_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_type_update'
LANGUAGE C;

CREATE OR REPLACE FUNCTION
aspect_type_delete(
  in key_id_1 integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_type_delete'
LANGUAGE C;

CREATE OR REPLACE FUNCTION
aspect_type_find_by_id(
  in key_id_1 integer, 
  out aspect_type_id integer, 
  out description varchar, 
  out super_type_id integer) 
RETURNS record 
AS 'MODULE_PATHNAME','aspect_type_find_by_id'
LANGUAGE C;

CREATE OR REPLACE FUNCTION
aspect_type_find_all(
  out aspect_type_id integer, 
  out description varchar, 
  out super_type_id integer) 
RETURNS setof record 
AS 'MODULE_PATHNAME','aspect_type_find_all'
LANGUAGE C;

CREATE OR REPLACE FUNCTION
aspect_type_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_type_count'
LANGUAGE C;
-------------------------------------------------------------------------------

--aspect
CREATE OR REPLACE FUNCTION
aspect_create(
  in description varchar, 
  in x integer, 
  in y integer, 
  in t timestamp, 
  in space_time integer, 
  in aspect_type_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_create_many(
  in description_array varchar[], 
  in x_array integer[], 
  in y_array integer[], 
  in t_array timestamp[], 
  in space_time_array integer[], 
  in aspect_type_id_array integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_update(
  in id_key_1 integer, 
  in description varchar, 
  in x integer, 
  in y integer, 
  in t timestamp, 
  in space_time integer, 
  in aspect_type_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_delete(
  in id_key_1 integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_find_by_id(
  in id_key_1 integer, 
  out aspect_id integer, 
  out description varchar, 
  out x integer, 
  out y integer, 
  out t timestamp, 
  out space_time integer, 
  out aspect_type_id integer) 
RETURNS record 
AS 'MODULE_PATHNAME','aspect_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_find_all(
  out aspect_id integer, 
  out description varchar, 
  out x integer, 
  out y integer, 
  out t timestamp, 
  out space_time integer, 
  out aspect_type_id integer) 
RETURNS setof record 
AS 'MODULE_PATHNAME','aspect_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
aspect_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','aspect_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--attribute
CREATE OR REPLACE FUNCTION
attribute_create(
  in name varchar,
  in data_type integer,
  in aspect_type_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','attribute_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
attribute_create_many(
  in name_array varchar[],
  in data_type_array integer[],
  in aspect_type_id_array integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','attribute_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
attribute_update(
  in id_key_1 integer, 
  in name varchar,
  in data_type integer,
  in aspect_type_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','attribute_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
attribute_delete(
  in id_key_1 integer)
RETURNS integer 
AS 'MODULE_PATHNAME','attribute_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
attribute_find_by_id(
  in id_key_1 integer,
  out attribute_id integer, 
  out name varchar,
  out data_type integer,
  out aspect_type_id integer) 
RETURNS record 
AS 'MODULE_PATHNAME','attribute_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
attribute_find_all(
  out attribute_id integer, 
  out name varchar,
  out data_type integer,
  out aspect_type_id integer) 
RETURNS setof record 
AS 'MODULE_PATHNAME','attribute_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
attribute_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','attribute_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--mat_aspect
CREATE OR REPLACE FUNCTION
mat_aspect_create(
  in mat_id integer, 
  in aspect_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_aspect_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_aspect_create_many(
  in mat_id_array integer[], 
  in aspect_id_array integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_aspect_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_aspect_delete(
  in key_id_1 integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_aspect_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_aspect_find_by_id(
  in key_id_1 integer, 
  out mat_id integer, 
  out aspect_id integer) 
RETURNS record 
AS 'MODULE_PATHNAME','mat_aspect_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_aspect_find_all(
  out mat_id integer, 
  out aspect_id integer) 
RETURNS setof record 
AS 'MODULE_PATHNAME','mat_aspect_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_aspect_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_aspect_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--mat
CREATE OR REPLACE FUNCTION
mat_create(
  in description varchar) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_create_many(
  in description_array varchar[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_update(
  in key_id_1 integer, 
  in description varchar) 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_delete(
  in key_id_1 integer)
RETURNS integer 
AS 'MODULE_PATHNAME','mat_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_find_by_id(
  in key_id_1 integer, 
  out mat_id integer, 
  out description varchar) 
RETURNS record 
AS 'MODULE_PATHNAME','mat_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_find_all(
  out mat_id integer, 
  out description varchar) 
RETURNS setof record 
AS 'MODULE_PATHNAME','mat_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mat_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','mat_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--mo_aspect
CREATE OR REPLACE FUNCTION
mo_aspect_create(
  in mo_id integer,
  in aspect_id integer, 
  in start_time timestamp,
  in end_time timestamp) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_aspect_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_aspect_create_many(
  in mo_id_array integer[],
  in aspect_id_array integer[], 
  in start_time_array timestamp[],
  in end_time_array timestamp[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_aspect_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_aspect_update(
  in mo_id integer, 
  in aspect_id integer, 
  in start_time timestamp,
  in end_time timestamp) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_aspect_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_aspect_delete(
  in mo_id integer, 
  in aspect_id integer)
RETURNS integer 
AS 'MODULE_PATHNAME','mo_aspect_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_aspect_find_by_id(
  in key_id_1 integer, 
  in key_id_2 integer,
  out mo_id integer, 
  out aspect_id integer, 
  out start_time timestamp,
  out end_time timestamp) 
RETURNS record 
AS 'MODULE_PATHNAME','mo_aspect_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_aspect_find_all(
  out mo_id integer, 
  out aspect_id integer, 
  out start_time timestamp,
  out end_time timestamp) 
RETURNS setof record 
AS 'MODULE_PATHNAME','mo_aspect_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_aspect_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_aspect_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--mo_relationship
CREATE OR REPLACE FUNCTION
mo_relationship_create(
  in description varchar,
  in start_time timestamp,
  in end_time timestamp,
  in mo_target integer,
  in mo_source integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_relationship_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_relationship_create_many(
  in description_array varchar[],
  in start_time_array timestamp[],
  in end_time_array timestamp[],
  in mo_target_array integer[],
  in mo_source_array integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_relationship_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_relationship_update(
  in key_id_1 integer, 
  in description_array varchar[],
  in start_time_array timestamp[],
  in end_time_array timestamp[],
  in mo_target_array integer[],
  in mo_source_array integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_relationship_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_relationship_delete(
  in key_id_1 integer)
RETURNS integer 
AS 'MODULE_PATHNAME','mo_relationship_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_relationship_find_by_id(
  in key_id_1 integer, 
  out mor_id integer,
  out description_array varchar[],
  out start_time_array timestamp[],
  out end_time_array timestamp[],
  out mo_target_array integer[],
  out mo_source_array integer[]) 
RETURNS record 
AS 'MODULE_PATHNAME','mo_relationship_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_relationship_find_all(
  out mor_id integer,
  out description_array varchar[],
  out start_time_array timestamp[],
  out end_time_array timestamp[],
  out mo_target_array integer[],
  out mo_source_array integer[]) 
RETURNS setof record 
AS 'MODULE_PATHNAME','mo_relationship_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_relationship_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_relationship_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--mo_type
CREATE OR REPLACE FUNCTION
mo_type_create(
  in description varchar) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_type_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_create_many(
  in description_array varchar[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_type_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_update(
  in mo_type_id integer, 
  in description varchar) 
RETURNS integer 
AS 'MODULE_PATHNAME','mo_type_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_delete(
  in mo_type_id integer)
RETURNS integer 
AS 'MODULE_PATHNAME','mo_type_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_find_by_id(
  in key_id_1 integer, 
  out mo_type_id integer, 
  out description varchar) 
RETURNS record 
AS 'MODULE_PATHNAME','mo_type_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mo_type_find_all(
  out mo_type_id integer, 
  out description varchar) 
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
mor_aspect_create(
  in mor_id integer, 
  in aspect_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mor_aspect_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mor_aspect_create_many(
  in mor_id_array integer[], 
  in aspect_id_array integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','mor_aspect_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mor_aspect_delete(
  in mor_id integer, 
  in aspect_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','mor_aspect_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mor_aspect_find_by_id(
  in key_id_1 integer, 
  in key_id_2 integer, 
  out mor_id integer, 
  out aspect_id integer) 
RETURNS record 
AS 'MODULE_PATHNAME','mor_aspect_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mor_aspect_find_all(
  out mor_id integer, 
  out aspect_id integer) 
RETURNS setof record 
AS 'MODULE_PATHNAME','mor_aspect_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
mor_aspect_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','mor_aspect_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--moving_object
CREATE OR REPLACE FUNCTION
moving_object_create(
  in description varchar,
  in mo_type_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','moving_object_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_create_many(
  in description_array varchar[],
  in mo_type_id_array integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','moving_object_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_update(
  in mo_id integer, 
  in description varchar,
  in mo_type_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','moving_object_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_delete(
  in mo_id integer)
RETURNS integer 
AS 'MODULE_PATHNAME','moving_object_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_find_by_id(
  in key_id_1 integer, 
  out mo_id integer, 
  out description varchar,
  out mo_type_id integer) 
RETURNS record 
AS 'MODULE_PATHNAME','moving_object_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_find_all(
  out mo_id integer, 
  out description varchar,
  out mo_type_id integer) 
RETURNS setof record 
AS 'MODULE_PATHNAME','moving_object_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
moving_object_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','moving_object_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--point
CREATE OR REPLACE FUNCTION
point_create(
  in p_order integer, 
  in mat_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_create_many(
  in p_order_array integer[], 
  in mat_id_array integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_update(
  in point_id integer, 
  in p_order integer,
  in mat_id integer)
RETURNS integer 
AS 'MODULE_PATHNAME','point_update'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_delete(
  in point_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_find_by_id(
  in key_id_1 integer, 
  out point_id integer, 
  out p_order integer,
  out mat_id integer)
RETURNS record 
AS 'MODULE_PATHNAME','point_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_find_all(
  out point_id integer, 
  out p_order integer,
  out mat_id integer)
RETURNS setof record 
AS 'MODULE_PATHNAME','point_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','point_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------

--point_aspect
CREATE OR REPLACE FUNCTION
point_aspect_create(
  in point_id integer, 
  in aspect_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_aspect_create'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_aspect_create_many(
  in point_id_array integer[], 
  in aspect_id_array integer[]) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_aspect_create_many'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_aspect_delete(
  in point_id integer, 
  in aspect_id integer) 
RETURNS integer 
AS 'MODULE_PATHNAME','point_aspect_delete'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_aspect_find_by_id(
  in key_id_1 integer, 
  in key_id_2 integer, 
  out point_id integer, 
  out aspect_id integer) 
RETURNS record 
AS 'MODULE_PATHNAME','point_aspect_find_by_id'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_aspect_find_all(
  out point_id integer, 
  out aspect_id integer) 
RETURNS setof record 
AS 'MODULE_PATHNAME','point_aspect_find_all'
LANGUAGE C STRICT;

CREATE OR REPLACE FUNCTION
point_aspect_count() 
RETURNS integer 
AS 'MODULE_PATHNAME','point_aspect_count'
LANGUAGE C STRICT;
-------------------------------------------------------------------------------
