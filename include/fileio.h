#ifndef FILEIO_H
#define FILEIO_H

#include <string.h>
#include "device.h"

void load_devices_file(const char* filename);
void save_devices_file(const char* filename);

#endif