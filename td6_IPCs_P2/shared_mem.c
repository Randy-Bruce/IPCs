#include "shared_mem.h"
#include <sys/types.h> 
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <errno.h> 
#include <time.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h>

float randomF(){ 
	return ((float)100.0*(rand()/(RAND_MAX+0.1))); 
} 

int randomI(){ 
	return ((int)100.0*(rand()/(RAND_MAX+0.1))); 
}
char randomC(){ 
	char car='A';
        car=car+(char)25.0*(rand()/(RAND_MAX+0.1));
        return car;
}

