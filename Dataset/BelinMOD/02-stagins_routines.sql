set search_path to master, public;

create or replace procedure staging.load_mos_from_cars()  
language plpgsql as
$body$
declare
	car_mot			mo_type_typ;
	text_type		data_type_typ;
	car_asp			aspect_type_typ;
	licence_att	attribute_typ;
	car_type_att		attribute_typ;
	model_att		attribute_typ;
	ts					timestamp default now();

	limit_rows	integer default 10000;
	start_row		integer default 0;
	processed		integer default 1;

	c_car cursor for
		select c.car_id, c.licence, c.type, c.model  
		from staging.car c;
begin
	--Creates if not exists the Car moving object type
	car_mot := mo_type_find_by_name('Vehicle');
	if car_mot is null then
		car_mot.description := 'Vehicle';
		call mo_type_create(car_mot);
	end if;

	--Creates if not exists the Car aspect type
	car_asp := aspect_type_find_by_name('Vehicle');
	if car_asp is null then
		car_asp.description := 'Vehicle';
		call aspect_type_create(car_asp);
	end if;

	--Create if not exists the Text data type
	text_type := data_type_find_by_name('Text');
	if text_type is null then
		text_type.data_type_name := 'Text';
		call data_type_create(text_type);
	end if;

	--Creates if not exists the licence attribute
	licence_att := attribute_find_by_name('licence');
	if licence_att is null then
		licence_att.name := 'licence';
		licence_att.aspect_type_id := car_asp.aspect_type_id;
		licence_att.data_type_id := text_type.data_type_id;
		call attribute_create(licence_att);
	end if;

	--Creates if not exists the type attribute
	car_type_att := attribute_find_by_name('type');
	if car_type_att is null then
		car_type_att.name := 'type';
		car_type_att.aspect_type_id := car_asp.aspect_type_id;
		car_type_att.data_type_id := text_type.data_type_id;
		call attribute_create(car_type_att);
	end if;

	--Creates if not exists the model attribute
	model_att := attribute_find_by_name('model');
	if model_att is null then
		model_att.name := 'model';
		model_att.aspect_type_id := car_asp.aspect_type_id;
		model_att.data_type_id := text_type.data_type_id;
		call attribute_create(model_att);
	end if;

	call util.disable_indexes('master','moving_object');
	call util.disable_fks('master','moving_object');

	call util.disable_indexes('master','aspect_attribute');
	call util.disable_fks('master','aspect_attribute');

	call util.disable_indexes('master','aspect');
	call util.disable_fks('master','aspect');

  --Iterate through the cursor to locate trips' cars
	open c_car;
	while processed > 0 loop
		declare
			car_a							moving_object_typ[10000];
			aspect_a					aspect_typ[10000];
		
			aspect_licence_a	aspect_attribute_typ[10000];
			aspect_type_a			aspect_attribute_typ[10000];
			aspect_model_a		aspect_attribute_typ[10000];
		
		  car_aspect_a			mo_aspect_typ[10000];
		
			licence_a					text[10000];
			car_type_a						text[10000];
			model_a						text[10000];
			aspect_id_a				integer[10000];
		
			i 								integer default 0;
		
			car_id						staging.car.car_id%type;
		  licence						staging.car.licence%type;
		 	type							staging.car.type%type;
		 	model							staging.car.model%type;
		begin
			fetch next from c_car
			into car_id, licence, type, model;
		
			--Create moving objects in batches of 10000 records
			while i < limit_rows and found loop
				i 						:= i + 1;
				car_a[i] 			:= row(null, car_id, car_mot.mo_type_id);
				aspect_a[i] 	:= row(null, car_id, null, null, ts, 2, car_asp.aspect_type_id);
				licence_a[i]	:= licence;
				car_type_a[i]			:= type;
				model_a[i]		:= model;
												
				fetch next from c_car 
				into car_id, licence, type, model;
			end loop;
		
			processed := i;
		
			if processed > 0 then
				call moving_object_create_many(car_a);
				call aspect_create_many(aspect_a);
				
				select array_agg(row(c.mo_id, a.aspect_id, ts, null))
				into car_aspect_a
				from unnest(car_a) c
					inner join unnest(aspect_a) a using (description);
				
				call mo_aspect_create_many(car_aspect_a);
			
				select array_agg(r.aspect_id)
				into aspect_id_a
				from unnest(aspect_a) r;

				select array_agg(row(r.aspect_id, r.attribute_id, r.licence,
					r.text_type))
				into aspect_licence_a
				from (
					select unnest(aspect_id_a) aspect_id, 
						licence_att.attribute_id attribute_id, 
						unnest(licence_a) licence, 
						text_type.data_type_id text_type) r;
			
				call aspect_attribute_create_many(aspect_licence_a);
			
				select array_agg(row(r.aspect_id, r.attribute_id, r.type,
					r.text_type))
				into aspect_type_a
				from (
					select unnest(aspect_id_a) aspect_id, 
						car_type_att.attribute_id attribute_id, 
						unnest(car_type_a) type, 
						text_type.data_type_id text_type) r;
					
				call aspect_attribute_create_many(aspect_type_a);

				select array_agg(row(r.aspect_id, r.attribute_id, r.model,
					r.text_type))
				into aspect_model_a
				from (
					select unnest(aspect_id_a) aspect_id, 
						model_att.attribute_id attribute_id, 
						unnest(model_a) model, 
						text_type.data_type_id text_type) r;
					
				call aspect_attribute_create_many(aspect_model_a);

				
				start_row := start_row + processed;
				raise notice '% processed records.', start_row;
			end if;			
		end;
	end loop;

	close c_car;

	call util.enable_indexes('master','moving_object');
	call util.enable_fks('master','moving_object');
	call util.enable_indexes('master','aspect_attribute');
	call util.enable_fks('master','aspect_attribute');
	call util.enable_indexes('master','aspect');
	call util.enable_fks('master','aspect');
end;
$body$;

comment on procedure staging.load_mos_from_cars() 
is 'Creates moving objects from trips'' cars';

create or replace procedure staging.load_aspects_from_regions() 
language plpgsql as
$body$
declare
	region_asp 			master.aspect_type_typ;
	text_type				master.data_type_typ;
	region_geom_att	master.attribute_typ default null;

	ts							timestamp default now();
	
	limit_rows			integer default 10000;
	start_row				integer default 0;
	processed				integer default 1;

	c_region cursor for
		WITH RegionsSegs AS (
		  SELECT ri.Region_Id, ri.Seg_No,
		    ST_Transform(ST_SetSRID(St_MakeLine(ST_MakePoint(ri.X_Start, ri.Y_Start), 
		    ST_MakePoint(ri.X_End, ri.Y_End)), 4326), 5676) AS Geom
		  FROM staging.regions_input ri  )
		select region_id, st_x(st_centroid(geom)) latitude, 
			st_y(st_centroid(geom)) longitude, st_astext(geom) geom 
		from (  
			SELECT Region_Id, 
				ST_Polygon(ST_LineMerge(ST_Union(Geom ORDER BY Seg_No)), 5676) AS Geom
			FROM RegionsSegs
			GROUP BY Region_Id
		) reg;
begin
	--Create if not exists the region aspect type
	region_asp := aspect_type_find_by_name('region');
	if region_asp is null then
		region_asp.description := 'region';
		call aspect_type_create(region_asp);
	end if;

	--Create if not exists the Text data type
	text_type := data_type_find_by_name('Text');
	if text_type is null then
		text_type.data_type_name := 'Text';
		call master.data_type_create(text_type);
	end if;

	--Create if not exists the region_geom attribute
	region_geom_att := master.attribute_find_by_name('region_geom');
	if region_geom_att is null then
		region_geom_att.name := 'region_geom';
		region_geom_att.data_type_id := text_type.data_type_id;
		call master.attribute_create(region_geom_att);
	end if;

	call util.disable_fks('master','aspect');
	call util.disable_indexes('master','aspect');
	call util.disable_fks('master','aspect_attribute');
	call util.disable_indexes('master','aspect_attribute');

	open c_region;

	while processed > 0 loop
		declare
			aspect_a							aspect_typ[10000];
			region_geom_a					text[10000];
			aspect_region_geom_a	master.aspect_attribute_typ[10000];
			aspect_id_a						integer[10000];
		
			i											integer default 0;
		
			region_id							integer;
			latitude							double precision;
			longitude							double precision;
			region_geom						text;
		begin
			--Iterate through the region cursor to populate the ascpets and attributes
			fetch next from c_region into 
				region_id, latitude, longitude, region_geom;
	
			while i < limit_rows and found loop
				i := i + 1;
			
				aspect_a[i] := row(null, region_id, latitude, longitude, 
					ts, 1, region_asp.aspect_type_id);
				
				region_geom_a[i] := region_geom;
			
				fetch next from c_region into 
					region_id, latitude, longitude, region_geom;
			end loop;

			processed := i;
		
			--Associate the each region (aspect) with its attributes in batches of 10000
			if processed > 0 then					
				call aspect_create_many(aspect_a);
				
				select array_agg(r.aspect_id)
				into aspect_id_a
				from unnest(aspect_a) r;
			
				select array_agg(row(r.aspect_id, r.attribute_id, r.region_geom,
					r.text_type))
				into aspect_region_geom_a
				from (
					select unnest(aspect_id_a) aspect_id, 
						region_geom_att.attribute_id attribute_id, 
						unnest(region_geom_a) region_geom, 
						text_type.data_type_id text_type) r;
				
				call master.aspect_attribute_create_many(aspect_region_geom_a);
				start_row := start_row + processed;
				raise notice '% processed records.', start_row;
			end if;
		end;
	end loop;

	close c_region;

	call util.enable_fks('master','aspect');
	call util.enable_indexes('master','aspect');
	call util.enable_fks('master','aspect_attribute');
	call util.enable_indexes('master','aspect_attribute');
end;
$body$;

comment on procedure staging.load_aspects_from_regions()
is 'Creates aspects and attributes from regions';

create or replace procedure staging.load_aspects_from_instants() 
language plpgsql as
$body$
declare
	instant_asp 		aspect_type_typ;
begin
	instant_asp := aspect_type_find_by_name('instant');
	if instant_asp is null then
		instant_asp.description := 'instant';
		call aspect_type_create(instant_asp);
	end if;

	insert into master.aspect(aspect_id, description, t, space_time, aspect_type_id)
	select nextval('aspect_seq'), i.instant_id, i.instant, 2, instant_asp.aspect_type_id
	from staging.instants i;
end;
$body$;

create or replace procedure staging.load_aspects_from_pois() 
language plpgsql as
$body$
declare
	poi_asp 		aspect_type_typ;

	ts					timestamp default now();
	
	limit_rows	integer default 10000;
	start_row		integer default 0;
	processed		integer default 1;

	c_poi cursor for
		select p.point_id, p.pos_x, p.pos_y
		from staging.points p;
begin
	--Create if not exists the POI aspect type
	poi_asp := aspect_type_find_by_name('POI');
	if poi_asp is null then
		poi_asp.description := 'POI';
		call aspect_type_create(poi_asp);
	end if;
	
	call util.disable_fks('master','aspect');
	call util.disable_indexes('master','aspect');

	open c_poi;

	while processed > 0 loop
		declare
			aspect_a	aspect_typ[10000];
		
			i					integer default 0;
		
			poi_id		integer;
			latitude	double precision;
			longitude	double precision;
		begin
			--Iterate through the POI cursor to populate the ascpets and attributes
			fetch next from c_poi into 
				poi_id, latitude, longitude;
	
			while i < limit_rows and found loop
				i := i + 1;
			
				aspect_a[i] := row(null, poi_id, latitude, longitude, 
					ts, 1, poi_asp.aspect_type_id);
				
				fetch next from c_poi into 
					poi_id, latitude, longitude;
			end loop;

			processed := i;
		
			--Associate the each POI (aspect) with its attributes in batches of 10000
			if processed > 0 then					
				call aspect_create_many(aspect_a);
				
				start_row := start_row + processed;
				raise notice '% processed records.', start_row;
			end if;
		end;
	end loop;

	close c_poi;

	call util.enable_fks('master','aspect');
	call util.enable_indexes('master','aspect');
end;
$body$;

comment on procedure staging.load_aspects_from_pois()
is 'Creates aspects and attributes from POIs';

create or replace procedure staging.load_mats_from_trips()  
language plpgsql as
$body$
declare
	limit_rows	integer default 10000;
	start_row		integer default 0;
	processed		integer default 1;

	start_date	date;
	end_date		date;

	--Find trips, with respective cars (moving object)  
	c_trip cursor for
		with trips (car_id, trip_id, x , y, t) as (
			select ti.car_id, ti.trip_id, ti.x_start , ti.y_start, ti.t_start
			from staging.trips_input ti 
		),
		trajs (car_id, trip_id, mat_date, traj) as (
			select ti.car_id, ti.trip_id, min(ti.t) mat_date,
					tgeompoint_seq(
						array_agg(
							tgeompoint_inst(
								ST_Transform(ST_SetSRID(
									ST_MakePoint(ti.x, ti.y), 4326), 5676)
									, ti.t
							)
							order by ti.t asc
						)
					) traj
			from trips ti 
			group by ti.car_id, ti.trip_id)
		select mo.mo_id, tr.trip_id, tr.mat_date, tr.traj
		from trajs tr
			inner join moving_object mo on
				mo.description = tr.car_id::text;
begin
	select min(date(ti.t_start)), max(date(ti.t_start))
	into start_date, end_date
	from staging.trips_input ti ;

	call util.create_partitions_by_date(
		'master', 'mat', start_date, end_date, 'mat_date', 'day');

	call util.disable_fks('master','mat');
	call util.disable_indexes('master','mat');

	open c_trip;

	while processed > 0 loop
		declare
			mat_a						mat_typ[10000];
			point_a					point_typ[10000];
			i 							integer default 0;
			mo_id						mat.mo_id%type;
			raw_trajectory	mat.raw_trajectory%type;
			mat_date				mat.mat_date%type;
			trip_id					staging.trips_input.trip_id%type;
		begin
			--Load multiple aspect trajectories in batches of 10000 records
			loop
				fetch next from c_trip
				into mo_id, trip_id, mat_date, raw_trajectory;
			
				exit when not found;
			
				i := i + 1;
				mat_a[i] := row(null, trip_id, mo_id, raw_trajectory, 
				trajectory(raw_trajectory), mat_date);
			
				exit when i >= limit_rows;
			end loop;

			processed := i;

			if processed > 0 then					
				call mat_create_many(mat_a);

				start_row := start_row + processed;
				raise notice '% processed records.', start_row;
			end if;			
		end;
	end loop;

	close c_trip;

	call util.enable_indexes('master', 'mat');
	call util.enable_fks('master', 'mat');
end;
$body$;

comment on procedure staging.load_mats_from_trips()
is 'Create trajectories from cars'' trips';

create or replace procedure staging.load_points_from_trips()  
language plpgsql as
$body$
declare
	limit_rows	integer default 10000;
	start_row		integer default 0;
	processed		integer default 1;

	start_date	date;
	end_date		date;

	declare c_trip cursor for
		with poi as (
			SELECT p.aspect_id,
					ST_Transform(ST_SetSRID(ST_MakePoint(p.x, p.y), 4326), 5676) AS geom
			from aspect_type aty
				join aspect P using(aspect_type_id)
			where aty.description = 'POI'
		)
		SELECT  
			case when length(t.raw_trajectory) > 0 then 
				trunc((ST_NPoints(t.trajectory_geom) - 1) 
					* ST_LineLocatePoint(t.trajectory_geom, poi.geom))	
			else 1 end p_order,
			t.mat_id,
			startTimestamp(atValue(T.raw_trajectory, poi.geom)) t,
			poi.aspect_id
		from poi
			join mat T on
				ST_Contains(T.trajectory_geom, 
					poi.geom);
begin
	select min(date(mat_date)), max(date(mat_date + interval '1 day'))
	into start_date, end_date
	from master.mat ti ;

	call util.create_partitions_by_date(
		'master', 'point', start_date, end_date, 't', 'day');
	
	call util.disable_fks('master','point');
	call util.disable_indexes('master','point');
	call util.disable_fks('master','point_aspect');
	call util.disable_indexes('master','point_aspect');

	open c_trip;

	while processed > 0 loop
		declare
			point_a					point_typ[10000];
			i 							integer default 0;
			mat_id					point.mat_id%type;
			p_order					point.p_order%type;
			t								point.t%type;
			aspect_id				integer;
			aspect_id_a			integer[10000];
			point_id_a			integer[10000];
			point_aspect_a	point_aspect_typ[10000];
		begin
			--Load multiple aspect trajectories in batches of 10000 records
			loop 
				fetch next from c_trip 
				into p_order, mat_id, t, aspect_id;
			
				exit when not found;
			
				i := i + 1;
				point_a[i] := row(null, p_order, mat_id, t);
				aspect_id_a[i] := aspect_id;
			
				exit when i >= limit_rows;
			end loop;

			processed := i;

			if processed > 0 then					
				call point_create_many(point_a);
			
				select array_agg(r.point_id)
				into point_id_a
				from unnest(point_a) r;
			
				select array_agg(row(r.point_id, r.aspect_id))
				into point_aspect_a
				from (
					select unnest(point_id_a) point_id, 
						unnest(aspect_id_a) aspect_id
				) r;

				call point_aspect_create_many(point_aspect_a);
			
				start_row := start_row + processed;
			
				raise notice '% processed records.', start_row;
			end if;			
		end;
	end loop;

	close c_trip;

	call util.enable_indexes('master', 'point');
	call util.enable_fks('master', 'point');
	call util.enable_fks('master','point_aspect');
	call util.enable_indexes('master','point_aspect');

end;
$body$;

comment on procedure staging.load_points_from_trips()
is 'Create anotated points from vehicles'' trips';

create or replace procedure staging.load_points_from_regions()  
language plpgsql as
$body$
declare
	limit_rows	integer default 10000;
	start_row		integer default 0;
	processed		integer default 1;

	start_date	date;
	end_date		date;

	declare c_trip cursor for
		with region as (
		SELECT P.aspect_id , 
				ST_SetSRID(st_geomfromtext(aa.value) , 5676) AS geom
		from aspect_type aty
			join aspect P using(aspect_type_id)
			join aspect_attribute aa using(aspect_id)
			join "attribute" a using(attribute_id)
		where aty.description = 'region'
			and a."name" = 'region_geom'),
		inter as (	
		SELECT t.mat_id, region.aspect_id, 
			startTimestamp(atGeometry(T.raw_trajectory, region.geom)) AS t_start,
			endTimestamp(atGeometry(T.raw_trajectory, region.geom)) AS t_end,
			startValue(atGeometry(T.raw_trajectory, region.geom)) AS p_start,
			endValue(atGeometry(T.raw_trajectory, region.geom)) AS p_end,
			length(t.raw_trajectory) as traj_length,
			ST_NPoints(t.trajectory_geom) as traj_n_points,
			t.trajectory_geom as traj_geom 
		from region
			inner join master.mat T on
				ST_Intersects(T.trajectory_geom, region.geom))
		select inter.mat_id, inter.aspect_id,
			case when inter.traj_length > 0 then 
				trunc((inter.traj_n_points - 1) 
					* ST_LineLocatePoint(inter.traj_geom, inter.p_start))	
			else 1 end as p_start_order,
			inter.t_start,
			case when inter.traj_length > 0 then 
				trunc((inter.traj_n_points - 1) 
					* ST_LineLocatePoint(inter.traj_geom, inter.p_end))	
			else 1 end as p_end_order,
			inter.t_end
		from inter;
begin
	select min(date(mat_date)), max(date(mat_date + interval '1 day'))
	into start_date, end_date
	from master.mat ti ;

	call util.create_partitions_by_date(
		'master', 'point', start_date, end_date, 't', 'day');
	
	call util.disable_fks('master','point');
	call util.disable_indexes('master','point');
	call util.disable_fks('master','point_aspect');
	call util.disable_indexes('master','point_aspect');

	open c_trip;

	while processed > 0 loop
		declare
			point_a					point_typ[10000];
			i 							integer default 0;
			mat_id					point.mat_id%type;
			p_start_order		point.p_order%type;
			t_start					point.t%type;
			p_end_order			point.p_order%type;
			t_end						point.t%type;
			aspect_id				integer;
			aspect_id_a			integer[10000];
			point_id_a			integer[10000];
			point_aspect_a	point_aspect_typ[10000];
		begin
			--Load multiple aspect trajectories in batches of 10000 records
			loop
				fetch next from c_trip
				into mat_id, aspect_id, p_start_order, t_start, p_end_order, t_end;
			
			  exit when not found;
			 
				i := i + 1;
				point_a[i] := row(null, p_start_order, mat_id, t_start);
				aspect_id_a[i] := aspect_id;
				i := i + 1;
				point_a[i] := row(null, p_end_order, mat_id, t_end);
				aspect_id_a[i] := aspect_id;

				exit when i >= limit_rows;
			end loop;

			processed := i;

			if processed > 0 then					
				call point_create_many(point_a);
			
				select array_agg(r.point_id)
				into point_id_a
				from unnest(point_a) r;
			
				select array_agg(row(r.point_id, r.aspect_id))
				into point_aspect_a
				from (
					select unnest(point_id_a) point_id
						, unnest(aspect_id_a) aspect_id
				) r;

				start_row := start_row + processed;
			
				call point_aspect_create_many(point_aspect_a);
			
				raise notice '% processed records.', start_row;
			end if;			
		end;
	end loop;

	close c_trip;

	call util.enable_indexes('master', 'point');
	call util.enable_fks('master', 'point');
	call util.enable_fks('master','point_aspect');
	call util.enable_indexes('master','point_aspect');

end;
$body$;

comment on procedure staging.load_points_from_regions()
is 'Create anotated points from trajectories and regions intersection';

/*
create or replace procedure staging.load_mats_from_trips_v1()  
language plpgsql as
$body$
declare
	limit_rows	integer default 10000;
	start_row	integer default 0;
	processed	integer default 1;

	--Find trips, with respective cars (moving object)  
	c_trip cursor for
		select mo.mo_id, ti.trip_id, min(ti.t) mat_date,
			tgeompoint_seq(
				array_agg(
					tgeompoint_inst(
						ST_Transform(ST_SetSRID(
							ST_MakePoint(ti.lon , ti.lat), 4326), 5676)
							, ti.t
					) 
					order by ti.t asc
				)
			)
		from staging.trips_input ti 
			inner join moving_object mo on
				mo.description = ti.car_id::text
		where ti.trip_id in (
			select trip_id
			from staging.trips_input
			group by trip_id
			having count(*) > 2)
		group by mo.mo_id, ti.trip_id;
begin
	call util.disable_fks('master','mat');
	call util.disable_indexes('master','mat');

	call util.create_partitions_by_date(
		'master', 'mat', '2007-05-27', '2007-05-31', 'mat_date', 'day');
	
	open c_trip;

	while processed > 0 loop
		declare
			mat_a						mat_typ[10000];
			i 							integer default 0;
			mo_id						mat.mo_id%type;
			raw_trajectory	mat.raw_trajectory%type;
			mat_date				mat.mat_date%type;
			trip_id					staging.trips_input.trip_id%type;
		begin
			fetch next from c_trip
			into mo_id, trip_id, mat_date, raw_trajectory;
		
			--Load multiple aspect trajectories in batches of 10000 records
			while i < limit_rows and found loop
				i := i + 1;
				mat_a[i] := row(null, trip_id, mo_id, raw_trajectory, 
					trajectory(raw_trajectory), mat_date);
			
				fetch next from c_trip
				into mo_id, trip_id, mat_date, raw_trajectory;
			end loop;

			processed := i;

			if processed > 0 then					
				call mat_create_many(mat_a);

				start_row := start_row + processed;
				raise notice '% processed records.', start_row;
			end if;			
		end;
	end loop;

	close c_trip;

	call util.enable_indexes('master', 'mat');
	call util.enable_fks('master', 'mat');
end;
$body$;

*/

/*
create or replace procedure staging.load_temp_tables_from_csvs()  
language plpgsql as
$body$
begin
	--transfer cars from csv file to temp table
	drop table if exists temp_car;
	create temp table temp_car(car_id, licence, type, model) as
		select p.car_id, p.licence, p.type, p.model
		from staging.car p;
	create index xie1temp_car on temp_car(car_id);

	--transfer trips from csv file to temp table
	drop table if exists temp_trip;
	create temp table staging.trip(car_id, trip_id, x_start, y_start, t_start) as
	  select t.car_id, t.trip_id, t.x_start, t.y_start, t.t_start
	  from staging.trips_input t;
end;
$body$;

comment on procedure staging.load_temp_tables_from_csvs()
	is 'Migrates POIs and Check ins from csv files to temp tables';
*/


