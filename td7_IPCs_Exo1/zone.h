#include <sys/types.h> 
#include <sys/msg.h> 
#include <sys/ipc.h> 
#include <errno.h> 
#include <time.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <stdio.h>

#ifndef ZONE_H
#define ZONE_H

#ifdef __cplusplus
extern "C" {
#endif

    struct donnees {
        long type;
        char texte[9];
    };

    float randomF();
    int randomI();
    char randomC();

#ifdef __cplusplus
}
#endif

#endif /* ZONE_H */

