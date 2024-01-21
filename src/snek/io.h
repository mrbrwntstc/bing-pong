#ifndef __SNEK_IO_H__
#define __SNEK_IO_H__

#include <stdlib.h>
#include <stdbool.h>

#include "types.h"

typedef struct snek_file_t {
  char* data;
  usize len;
  bool is_valid;
} snek_file;

snek_file io_file_read(const char* path);

#endif // __SNEK_IO_H__