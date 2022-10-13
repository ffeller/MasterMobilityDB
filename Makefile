MODULES = aspect_attribute aspect_type aspect attribute mat_aspect mat mo_aspect mo_relationship mo_type mor_aspect moving_object point point_aspect
EXTENSION = mastermobilitydb
DATA = mastermobilitydb--0.0.1.sql
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
