# CMake generated Testfile for 
# Source directory: /home/flaris/git/MobilityDB/test/npoint
# Build directory: /home/flaris/git/MobilityDB/build/test/npoint
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(load_npoint_tables "test.sh" "run_passfail" "load_npoint_tables" "/home/flaris/git/MobilityDB/test/npoint/data/load_npoint.sql.xz")
set_tests_properties(load_npoint_tables PROPERTIES  DEPENDS "create_extension" FIXTURES_REQUIRED "DBGEO" FIXTURES_SETUP "DBNPOINT" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;1;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(081_tnpoint_static "test.sh" "run_compare" "081_tnpoint_static" "/home/flaris/git/MobilityDB/test/npoint/queries/081_tnpoint_static.test.sql")
set_tests_properties(081_tnpoint_static PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(081_tnpoint_static_tbl "test.sh" "run_compare" "081_tnpoint_static_tbl" "/home/flaris/git/MobilityDB/test/npoint/queries/081_tnpoint_static_tbl.test.sql")
set_tests_properties(081_tnpoint_static_tbl PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(081_tnpoint_tbl_pg12 "test.sh" "run_compare" "081_tnpoint_tbl_pg12" "/home/flaris/git/MobilityDB/test/npoint/queries/081_tnpoint_tbl_pg12.test.sql")
set_tests_properties(081_tnpoint_tbl_pg12 PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(083_tnpoint "test.sh" "run_compare" "083_tnpoint" "/home/flaris/git/MobilityDB/test/npoint/queries/083_tnpoint.test.sql")
set_tests_properties(083_tnpoint PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(083_tnpoint_tbl "test.sh" "run_compare" "083_tnpoint_tbl" "/home/flaris/git/MobilityDB/test/npoint/queries/083_tnpoint_tbl.test.sql")
set_tests_properties(083_tnpoint_tbl PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(085_tnpoint_compops "test.sh" "run_compare" "085_tnpoint_compops" "/home/flaris/git/MobilityDB/test/npoint/queries/085_tnpoint_compops.test.sql")
set_tests_properties(085_tnpoint_compops PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(085_tnpoint_compops_tbl "test.sh" "run_compare" "085_tnpoint_compops_tbl" "/home/flaris/git/MobilityDB/test/npoint/queries/085_tnpoint_compops_tbl.test.sql")
set_tests_properties(085_tnpoint_compops_tbl PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(087_tnpoint_spatialfuncs "test.sh" "run_compare" "087_tnpoint_spatialfuncs" "/home/flaris/git/MobilityDB/test/npoint/queries/087_tnpoint_spatialfuncs.test.sql")
set_tests_properties(087_tnpoint_spatialfuncs PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(087_tnpoint_spatialfuncs_tbl "test.sh" "run_compare" "087_tnpoint_spatialfuncs_tbl" "/home/flaris/git/MobilityDB/test/npoint/queries/087_tnpoint_spatialfuncs_tbl.test.sql")
set_tests_properties(087_tnpoint_spatialfuncs_tbl PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(089_tnpoint_boxops "test.sh" "run_compare" "089_tnpoint_boxops" "/home/flaris/git/MobilityDB/test/npoint/queries/089_tnpoint_boxops.test.sql")
set_tests_properties(089_tnpoint_boxops PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(089_tnpoint_boxops_tbl "test.sh" "run_compare" "089_tnpoint_boxops_tbl" "/home/flaris/git/MobilityDB/test/npoint/queries/089_tnpoint_boxops_tbl.test.sql")
set_tests_properties(089_tnpoint_boxops_tbl PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(091_tnpoint_posops "test.sh" "run_compare" "091_tnpoint_posops" "/home/flaris/git/MobilityDB/test/npoint/queries/091_tnpoint_posops.test.sql")
set_tests_properties(091_tnpoint_posops PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(091_tnpoint_posops_tbl "test.sh" "run_compare" "091_tnpoint_posops_tbl" "/home/flaris/git/MobilityDB/test/npoint/queries/091_tnpoint_posops_tbl.test.sql")
set_tests_properties(091_tnpoint_posops_tbl PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(093_tnpoint_distance "test.sh" "run_compare" "093_tnpoint_distance" "/home/flaris/git/MobilityDB/test/npoint/queries/093_tnpoint_distance.test.sql")
set_tests_properties(093_tnpoint_distance PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(093_tnpoint_distance_tbl "test.sh" "run_compare" "093_tnpoint_distance_tbl" "/home/flaris/git/MobilityDB/test/npoint/queries/093_tnpoint_distance_tbl.test.sql")
set_tests_properties(093_tnpoint_distance_tbl PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(095_tnpoint_aggfuncs_tbl "test.sh" "run_compare" "095_tnpoint_aggfuncs_tbl" "/home/flaris/git/MobilityDB/test/npoint/queries/095_tnpoint_aggfuncs_tbl.test.sql")
set_tests_properties(095_tnpoint_aggfuncs_tbl PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(096_tnpoint_spatialrels "test.sh" "run_compare" "096_tnpoint_spatialrels" "/home/flaris/git/MobilityDB/test/npoint/queries/096_tnpoint_spatialrels.test.sql")
set_tests_properties(096_tnpoint_spatialrels PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(096_tnpoint_spatialrels_tbl "test.sh" "run_compare" "096_tnpoint_spatialrels_tbl" "/home/flaris/git/MobilityDB/test/npoint/queries/096_tnpoint_spatialrels_tbl.test.sql")
set_tests_properties(096_tnpoint_spatialrels_tbl PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(096_tnpoint_spatialrels_tbl_pg12 "test.sh" "run_compare" "096_tnpoint_spatialrels_tbl_pg12" "/home/flaris/git/MobilityDB/test/npoint/queries/096_tnpoint_spatialrels_tbl_pg12.test.sql")
set_tests_properties(096_tnpoint_spatialrels_tbl_pg12 PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(097_tnpoint_tempspatialrels "test.sh" "run_compare" "097_tnpoint_tempspatialrels" "/home/flaris/git/MobilityDB/test/npoint/queries/097_tnpoint_tempspatialrels.test.sql")
set_tests_properties(097_tnpoint_tempspatialrels PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")
add_test(097_tnpoint_tempspatialrels_tbl "test.sh" "run_compare" "097_tnpoint_tempspatialrels_tbl" "/home/flaris/git/MobilityDB/test/npoint/queries/097_tnpoint_tempspatialrels_tbl.test.sql")
set_tests_properties(097_tnpoint_tempspatialrels_tbl PROPERTIES  FIXTURES_REQUIRED "DBNPOINT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;25;add_test;/home/flaris/git/MobilityDB/test/npoint/CMakeLists.txt;0;")