#include "../src/lidar.h"

#include <stdio.h>
#include <signal.h>

int running = 1;

void sighandler(int signum){
    running = 0;
}

int main(int argc, char **argv){
    //set up signal handling to exit cleanly on interrupt
    struct sigaction new_action, old_action;
    new_action.sa_handler = sighandler;
    sigemptyset(&new_action.sa_mask);
    sigaddset(&new_action.sa_mask, SIGTERM);
    new_action.sa_flags = 0;
    sigaction(SIGINT, NULL, &old_action);

    if(old_action.sa_handler != SIG_IGN){
        sigaction(SIGINT, &new_action, NULL);
    }

    Lidar *lidar = lidar_create("/dev/ttyUSB0");

    while(running){
        //make sure we get a good scan
        while(lidar_scan(lidar) == 0);
        printf("dist:%d stren:%d\n", lidar->dist, lidar->stren);
    }

    lidar_close(lidar);

    return 0;
}
