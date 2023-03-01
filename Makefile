MODULE_big = mastermobilitydb
OBJS = dbutil.o mastermobilitydb.o \
	core/aspect_attribute.o \
	core/aspect_type.o \
	core/aspect.o \
	core/data_type.o \
	core/attribute.o \
	core/mat_aspect.o \
	core/mat.o \
	core/mo_aspect.o \
	core/mo_relationship.o \
	core/mo_type.o \
	core/mor_aspect.o \
	core/moving_object.o \
	core/point.o \
	core/point_aspect.o
EXTENSION = mastermobilitydb
DATA = mastermobilitydb--0.2.3.sql
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
