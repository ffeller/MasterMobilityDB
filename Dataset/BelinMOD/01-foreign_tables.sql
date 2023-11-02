CREATE SCHEMA IF NOT EXISTS STAGING;

CREATE SERVER IF NOT EXISTS BERLINMOD
	FOREIGN DATA WRAPPER FILE_FDW;
	
DROP FOREIGN TABLE IF EXISTS STAGING.TRIPS_INPUT;

CREATE FOREIGN TABLE IF NOT EXISTS STAGING.TRIPS_INPUT(
	CAR_ID INTEGER, 
	TRIP_ID INTEGER,
	T_START TIMESTAMP,
	T_END TIMESTAMP,
	X_START DOUBLE PRECISION, 
	Y_START DOUBLE PRECISION, 
	X_END DOUBLE PRECISION, 
	Y_END DOUBLE PRECISION 
) SERVER BERLINMOD
OPTIONS ( 
	FORMAT 'csv', 
	HEADER 'true',  
	FILENAME '/home/flaris/data/dataset/BerlinMOD_1_0_Geo_CSV/trips.csv',
	DELIMITER ',', 
	ENCODING 'UTF-8',
	NULL '');

DROP FOREIGN TABLE IF EXISTS STAGING.CAR;

CREATE FOREIGN TABLE IF NOT EXISTS STAGING.CAR (
	CAR_ID INTEGER, 
	LICENCE TEXT, 
	TYPE TEXT, 
	MODEL TEXT
) SERVER BERLINMOD
OPTIONS ( 
	FORMAT 'csv', 
	HEADER 'true',  
	FILENAME '/home/flaris/data/dataset/BerlinMOD_1_0_Geo_CSV/datamcar.csv',
	DELIMITER ',', 
	ENCODING 'UTF-8',
	NULL '');

DROP FOREIGN TABLE IF EXISTS STAGING.POINTS;

CREATE FOREIGN TABLE IF NOT EXISTS STAGING.POINTS(
	POINT_ID INTEGER, 
	POS_X DOUBLE PRECISION, 
	POS_Y DOUBLE PRECISION
) SERVER BERLINMOD
OPTIONS ( 
	FORMAT 'csv', 
	HEADER 'true',  
	FILENAME '/home/flaris/data/dataset/BerlinMOD_1_0_Geo_CSV/querypoints.csv',
	DELIMITER ',', 
	ENCODING 'UTF-8',
	NULL '');

DROP FOREIGN TABLE IF EXISTS STAGING.LICENCES;

CREATE FOREIGN TABLE IF NOT EXISTS STAGING.LICENCES(
	LICENCE TEXT, 
	LICENCE_ID INTEGER
) SERVER BERLINMOD
OPTIONS ( 
	FORMAT 'csv', 
	HEADER 'true',  
	FILENAME '/home/flaris/data/dataset/BerlinMOD_1_0_Geo_CSV/querylicences.csv',
	DELIMITER ',', 
	ENCODING 'UTF-8',
	NULL '');

DROP FOREIGN TABLE IF EXISTS STAGING.REGIONS_INPUT;

CREATE FOREIGN TABLE IF NOT EXISTS STAGING.REGIONS_INPUT(
	REGION_ID INTEGER, 
	SEG_NO INTEGER, 
	X_START DOUBLE PRECISION, 
	Y_START DOUBLE PRECISION, 
	X_END DOUBLE PRECISION, 
	Y_END DOUBLE PRECISION
) SERVER BERLINMOD
OPTIONS ( 
	FORMAT 'csv', 
	HEADER 'true',  
	FILENAME '/home/flaris/data/dataset/BerlinMOD_1_0_Geo_CSV/queryregions.csv',
	DELIMITER ',', 
	ENCODING 'UTF-8',
	NULL '');

drop foreign TABLE IF EXISTS STAGING.INSTANTS;

CREATE FOREIGN TABLE IF NOT EXISTS STAGING.INSTANTS(
	INSTANT_ID INTEGER, 
	INSTANT TIMESTAMP
) SERVER BERLINMOD
OPTIONS ( 
	FORMAT 'csv', 
	HEADER 'true',  
	FILENAME '/home/flaris/data/dataset/BerlinMOD_1_0_Geo_CSV/queryinstants.csv',
	DELIMITER ',', 
	ENCODING 'UTF-8',
	NULL '');

DROP FOREIGN TABLE IF EXISTS STAGING.PERIODS;

CREATE FOREIGN TABLE STAGING.PERIODS(
	PERIOD_ID INTEGER, 
	T_START TIMESTAMP, 
	T_END TIMESTAMP 
) SERVER BERLINMOD
OPTIONS ( 
	FORMAT 'csv', 
	HEADER 'true',  
	FILENAME '/home/flaris/data/dataset/BerlinMOD_1_0_Geo_CSV/queryperiods.csv',
	DELIMITER ',', 
	ENCODING 'UTF-8',
	NULL '');

 
