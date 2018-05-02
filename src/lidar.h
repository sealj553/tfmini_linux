#pragma once

#include <stdint.h>

typedef struct lidar {
    int fd;
    uint16_t dist, stren;
} Lidar;

Lidar* lidar_create(const char *tty);

int lidar_scan(Lidar *l);

void lidar_close(Lidar *l);
