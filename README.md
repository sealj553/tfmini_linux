#tfmini_linux

C library for interfacing with the Benewake TF Mini lidar sensor in Linux

Example usage:

    Lidar *lidar = lidar_create("/dev/ttyUSB0");

    while(running){
        while(lidar_scan(lidar) == 0);
        printf("dist:%d stren:%d\n", lidar->dist, lidar->stren);
    }
