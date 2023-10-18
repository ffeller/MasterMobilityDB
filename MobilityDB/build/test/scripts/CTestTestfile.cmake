# CMake generated Testfile for 
# Source directory: /home/flaris/git/MobilityDB/test/scripts
# Build directory: /home/flaris/git/MobilityDB/build/test/scripts
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(build "/usr/bin/cmake" "--build" "/home/flaris/git/MobilityDB/build")
set_tests_properties(build PROPERTIES  _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/scripts/CMakeLists.txt;7;add_test;/home/flaris/git/MobilityDB/test/scripts/CMakeLists.txt;0;")
add_test(setup "test.sh" "setup")
set_tests_properties(setup PROPERTIES  DEPENDS "build" FIXTURES_SETUP "DBSETUP" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/scripts/CMakeLists.txt;12;add_test;/home/flaris/git/MobilityDB/test/scripts/CMakeLists.txt;0;")
add_test(create_extension "test.sh" "create_ext")
set_tests_properties(create_extension PROPERTIES  DEPENDS "setup" FIXTURES_REQUIRED "DBSETUP" FIXTURES_SETUP "DBEXT" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/scripts/CMakeLists.txt;18;add_test;/home/flaris/git/MobilityDB/test/scripts/CMakeLists.txt;0;")
add_test(teardown "test.sh" "teardown")
set_tests_properties(teardown PROPERTIES  DBEXT "DBSETUP" FIXTURES_CLEANUP "DB" RESOURCE_LOCK "DBLOCK" WORKING_DIRECTORY "/home/flaris/git/MobilityDB/build/test/scripts" _BACKTRACE_TRIPLES "/home/flaris/git/MobilityDB/test/scripts/CMakeLists.txt;24;add_test;/home/flaris/git/MobilityDB/test/scripts/CMakeLists.txt;0;")
