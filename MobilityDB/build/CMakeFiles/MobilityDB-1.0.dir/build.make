# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/flaris/git/MobilityDB

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/flaris/git/MobilityDB/build

# Include any dependencies generated for this target.
include CMakeFiles/MobilityDB-1.0.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MobilityDB-1.0.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MobilityDB-1.0.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MobilityDB-1.0.dir/flags.make

# Object files for target MobilityDB-1.0
MobilityDB__1_0_OBJECTS =

# External object files for target MobilityDB-1.0
MobilityDB__1_0_EXTERNAL_OBJECTS = \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/doublen.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/geo_constructors.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/lifting.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/period.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/periodset.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/rangetypes_ext.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/skiplist.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tbool_boolops.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tbox.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tempcache.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_aggfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_analyze.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_boxops.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_compops.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_gist.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_parser.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_posops.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_selfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_similarity.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_spgist.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_supportfn.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_tile.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_util.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/temporal_waggfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/time_aggfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/time_analyze.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/time_gist.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/time_ops.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/time_selfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/time_spgist.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/timestampset.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tinstant.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tinstantset.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tnumber_distance.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tnumber_gist.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tnumber_mathfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tnumber_selfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tnumber_spgist.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tsequence.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/tsequenceset.c.o" \
"/home/flaris/git/MobilityDB/build/src/general/CMakeFiles/general.dir/ttext_textfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/geography_functions.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/projection_gk.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/stbox.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_aggfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_analytics.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_analyze.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_boxops.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_datagen.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_distance.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_gist.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_in.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_out.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_parser.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_posops.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_selfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_spatialfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_spatialrels.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_spgist.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_tempspatialrels.c.o" \
"/home/flaris/git/MobilityDB/build/src/point/CMakeFiles/point.dir/tpoint_tile.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_aggfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_analyze.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_boxops.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_distance.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_indexes.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_parser.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_posops.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_selfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_spatialfuncs.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_spatialrels.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_static.c.o" \
"/home/flaris/git/MobilityDB/build/src/npoint/CMakeFiles/npoint.dir/tnpoint_tempspatialrels.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/bytebuffer.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/effectivearea.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/gbox.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/gserialized.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/gserialized1.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/gserialized2.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lookup3.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwalgorithm.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwboundingcircle.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwchaikins.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwcircstring.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwcollection.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwcompound.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwcurvepoly.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeodetic.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeodetic_tree.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_api.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_debug.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_geos.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_geos_clean.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_geos_cluster.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_geos_node.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_geos_split.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_median.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_topo.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_transform.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_wrapx.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwhomogenize.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_encoded_polyline.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_geojson.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_twkb.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_wkb.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_wkt.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_wkt_lex.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_wkt_parse.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwiterator.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwkmeans.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwline.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwlinearreferencing.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmcurve.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmline.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmpoint.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmpoly.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmsurface.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmval.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_encoded_polyline.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_geojson.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_gml.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_kml.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_svg.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_twkb.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_wkb.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_wkt.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_x3d.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwpoint.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwpoly.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwprint.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwpsurface.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwrandom.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwspheroid.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwstroke.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwtin.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwtree.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwtriangle.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwunionfind.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwutil.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/measures.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/measures3d.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/ptarray.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/stringbuffer.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/liblwgeom/CMakeFiles/liblwgeom.dir/varint.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/libpgcommon/CMakeFiles/libpgcommon.dir/gserialized_gist.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/libpgcommon/CMakeFiles/libpgcommon.dir/lwgeom_cache.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/libpgcommon/CMakeFiles/libpgcommon.dir/lwgeom_pg.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/libpgcommon/CMakeFiles/libpgcommon.dir/lwgeom_transform.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/libpgcommon/CMakeFiles/libpgcommon.dir/shared_gserialized.c.o" \
"/home/flaris/git/MobilityDB/build/postgis/ryu/CMakeFiles/ryu.dir/d2s.c.o"

libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/doublen.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/geo_constructors.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/lifting.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/period.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/periodset.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/rangetypes_ext.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/skiplist.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tbool_boolops.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tbox.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tempcache.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_aggfuncs.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_analyze.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_boxops.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_compops.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_gist.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_parser.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_posops.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_selfuncs.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_similarity.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_spgist.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_supportfn.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_tile.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_util.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/temporal_waggfuncs.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/time_aggfuncs.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/time_analyze.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/time_gist.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/time_ops.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/time_selfuncs.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/time_spgist.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/timestampset.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tinstant.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tinstantset.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tnumber_distance.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tnumber_gist.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tnumber_mathfuncs.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tnumber_selfuncs.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tnumber_spgist.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tsequence.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/tsequenceset.c.o
libMobilityDB-1.0.so: src/general/CMakeFiles/general.dir/ttext_textfuncs.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/geography_functions.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/projection_gk.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/stbox.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_aggfuncs.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_analytics.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_analyze.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_boxops.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_datagen.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_distance.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_gist.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_in.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_out.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_parser.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_posops.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_selfuncs.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_spatialfuncs.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_spatialrels.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_spgist.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_tempspatialrels.c.o
libMobilityDB-1.0.so: src/point/CMakeFiles/point.dir/tpoint_tile.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_aggfuncs.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_analyze.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_boxops.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_distance.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_indexes.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_parser.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_posops.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_selfuncs.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_spatialfuncs.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_spatialrels.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_static.c.o
libMobilityDB-1.0.so: src/npoint/CMakeFiles/npoint.dir/tnpoint_tempspatialrels.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/bytebuffer.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/effectivearea.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/gbox.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/gserialized.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/gserialized1.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/gserialized2.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lookup3.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwalgorithm.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwboundingcircle.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwchaikins.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwcircstring.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwcollection.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwcompound.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwcurvepoly.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeodetic.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeodetic_tree.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_api.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_debug.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_geos.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_geos_clean.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_geos_cluster.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_geos_node.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_geos_split.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_median.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_topo.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_transform.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwgeom_wrapx.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwhomogenize.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_encoded_polyline.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_geojson.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_twkb.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_wkb.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_wkt.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_wkt_lex.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwin_wkt_parse.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwiterator.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwkmeans.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwline.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwlinearreferencing.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmcurve.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmline.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmpoint.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmpoly.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmsurface.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwmval.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_encoded_polyline.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_geojson.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_gml.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_kml.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_svg.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_twkb.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_wkb.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_wkt.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwout_x3d.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwpoint.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwpoly.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwprint.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwpsurface.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwrandom.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwspheroid.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwstroke.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwtin.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwtree.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwtriangle.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwunionfind.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/lwutil.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/measures.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/measures3d.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/ptarray.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/stringbuffer.c.o
libMobilityDB-1.0.so: postgis/liblwgeom/CMakeFiles/liblwgeom.dir/varint.c.o
libMobilityDB-1.0.so: postgis/libpgcommon/CMakeFiles/libpgcommon.dir/gserialized_gist.c.o
libMobilityDB-1.0.so: postgis/libpgcommon/CMakeFiles/libpgcommon.dir/lwgeom_cache.c.o
libMobilityDB-1.0.so: postgis/libpgcommon/CMakeFiles/libpgcommon.dir/lwgeom_pg.c.o
libMobilityDB-1.0.so: postgis/libpgcommon/CMakeFiles/libpgcommon.dir/lwgeom_transform.c.o
libMobilityDB-1.0.so: postgis/libpgcommon/CMakeFiles/libpgcommon.dir/shared_gserialized.c.o
libMobilityDB-1.0.so: postgis/ryu/CMakeFiles/ryu.dir/d2s.c.o
libMobilityDB-1.0.so: CMakeFiles/MobilityDB-1.0.dir/build.make
libMobilityDB-1.0.so: /usr/lib/x86_64-linux-gnu/libjson-c.so
libMobilityDB-1.0.so: /usr/lib/x86_64-linux-gnu/libproj.so
libMobilityDB-1.0.so: /usr/lib/x86_64-linux-gnu/libgsl.so
libMobilityDB-1.0.so: /usr/lib/x86_64-linux-gnu/libgslcblas.so
libMobilityDB-1.0.so: CMakeFiles/MobilityDB-1.0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/flaris/git/MobilityDB/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking C shared module libMobilityDB-1.0.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MobilityDB-1.0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MobilityDB-1.0.dir/build: libMobilityDB-1.0.so
.PHONY : CMakeFiles/MobilityDB-1.0.dir/build

CMakeFiles/MobilityDB-1.0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MobilityDB-1.0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MobilityDB-1.0.dir/clean

CMakeFiles/MobilityDB-1.0.dir/depend:
	cd /home/flaris/git/MobilityDB/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/flaris/git/MobilityDB /home/flaris/git/MobilityDB /home/flaris/git/MobilityDB/build /home/flaris/git/MobilityDB/build /home/flaris/git/MobilityDB/build/CMakeFiles/MobilityDB-1.0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MobilityDB-1.0.dir/depend

