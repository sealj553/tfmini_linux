#pragma once

#include <stdint.h>

typedef struct lidar {
    int fd;
    uint16_t dist, stren;
} Lidar;

//creates a Lidar that reads from tty
Lidar* lidar_create(const char *tty);

//if 1 is returned, a measurement was sucessfully read, otherwise 0 is returned
int lidar_scan(Lidar *l);

//closes and flushes serial port 
void lidar_close(Lidar *l);
