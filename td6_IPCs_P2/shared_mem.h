#include <sys/types.h> 
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <errno.h> 
#include <time.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h>

#ifndef SHARED_MEME_H
#define SHARED_MEME_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
      float temp;
      int press;
      char ordre;
    }zone;
    
    float randomF();
    int randomI();
    char randomC();
    


#ifdef __cplusplus
}
#endif

#endif /* SHARED_MEME_H */
