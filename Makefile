MODULES = mo_type aspect_type moving_object point
EXTENSION = mastermobilitydb
DATA = mastermobilitydb--0.0.1.sql
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
