#include "postgres.h"
#include "executor/spi.h"
#include "utils/builtins.h"

#include "connection.h"

bool db_connected = false;

int db_connect() {
  int ret;

  ret = SPI_connect();
  db_connected = true;

  return ret;
}

int db_disconnect() {
  int ret = SPI_OK_FINISH;

  if (db_connected) {
    ret = SPI_finish();
    db_connected = false;
  }

  return ret;
}
