MODULE_big = mastermobilitydb
OBJS = dbutil.o mastermobilitydb.o aspect_attribute.o aspect_type.o aspect.o attribute.o mat_aspect.o mat.o mo_aspect.o mo_relationship.o mo_type.o mor_aspect.o moving_object.o point.o point_aspect.o
EXTENSION = mastermobilitydb
DATA = mastermobilitydb--0.1.1.sql
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
