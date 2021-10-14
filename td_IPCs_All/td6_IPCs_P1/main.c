/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: rly
 *
 * Created on 7 octobre 2021, 15:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared_mem.h"


int main(int argc, char** argv) {
    int id;
    key_t clef;
    zone *partage;
    //creation de la zone memoire partagée
    clef = ftok("/tmp/1234", 'a'); // generation d'une clef
    //6 -> 110
    //     RWX 
    id = shmget(clef, sizeof (zone), IPC_CREAT | 0600); // autorisation en R/W (Read/Write)
    if (id == -1) {
        // le segment n'existe pas
        if (errno != EEXIST) {
            printf("pb shmget : %s\n", strerror(errno));
            exit(errno);
        }
    }
    // attribution adresse virtuelle du segment
    partage = shmat (id,NULL, SHM_W);   //En écriture
     if(partage == (void *)-1)
  {
      printf("pb shmat : %s\n",strerror(errno));
            exit(errno);
  }    
    // lecture et affichage de la zone partagee
    while(1){
        partage->press = randomI();
        sleep(1);
        partage->temp     = randomF();
        sleep(2);

        printf("temp: %.2f press : %d\n",partage->temp,partage->press);
        
    }
    

    return (EXIT_SUCCESS);
}

