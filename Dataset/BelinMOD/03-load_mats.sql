set search_path to master,public;
alter system set autovacuum to off;
select pg_reload_conf();

call master.point_aspect_delete_all() ;
call master.point_delete_all() ;
call master.mat_delete_all() ;
call master.aspect_attribute_delete_all() ;
call master.aspect_delete_all() ;
call master.attribute_delete_all() ;
call master.aspect_type_delete_all()  ;
call master.data_type_delete_all() ;
call master.moving_object_delete_all();
call master.mo_type_delete_all();

call util.reset_sequences('master');

vacuum (analyze);

call staging.load_mos_from_cars();
call staging.load_aspects_from_pois(); 
call staging.load_aspects_from_regions(); 
call staging.load_aspects_from_instants(); 
call staging.load_mats_from_trips();
call staging.load_points_from_trips();
call staging.load_points_from_regions();

vacuum (analyze);

alter system reset autovacuum;
select pg_reload_conf();




