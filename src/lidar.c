#include "lidar.h"
#include "serial.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h> 
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>

#define DEG2RAD(x) (x * M_PI / 180.f)

//private
void floosh(int fd);

void floosh(int fd){
    usleep(1000);
    tcflush(fd, TCIOFLUSH);
}

Lidar* lidar_create(const char *tty){
    Lidar *l= malloc(sizeof(Lidar));

    //initiate serial connection
    l->fd = open(tty, O_RDONLY | O_NOCTTY | O_SYNC);
    usleep(10000);

    if(l->fd < 0){
        fprintf(stderr, "error opening \"%s\": %s\n", tty, strerror(errno));
        exit(1);
    }

    set_interface_attribs(l->fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking(l->fd, 0);                    // set no blocking

    return l;
}

int lidar_scan(Lidar *l){
    int fd = l->fd;
    while(1){
        uint8_t buf[9];

        read(fd, buf, 2);
        if(buf[0] != 0x59 || buf[1] != 0x59){ continue; }

        for(int avail; ioctl(fd, FIONREAD, &avail), avail < 7;); //get rest of packet

        read(fd, buf + 2, 7); //read n bytes - the rest of the packet

        uint32_t check = 0x59 + 0x59;
        for(int i = 2; i < 8; ++i){
            check += buf[i];
        }

        check &= 0xff; 
        if(buf[8] != check){
            floosh(fd);
            return 0;
        }

        l->dist = (buf[3] << 8) + buf[2];
        l->stren = (buf[5] << 8) + buf[4];

        if(l->stren < 20){
            floosh(fd);
            return 0;
        }

        floosh(fd);
        return 1;
    }
}

void lidar_close(Lidar *l){
    tcflush(l->fd, TCIOFLUSH);
    usleep(1000);
    close(l->fd);
}
