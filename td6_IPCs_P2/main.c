/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: rly
 *
 * Created on 7 octobre 2021, 15:52
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "shared_mem.h"


int main(int argc, char** argv) {
    key_t clef;
    int id;
    zone *partage;
    // creation de la zone mémoire partagée
    clef = ftok("/tmp/1234", 'a'); // generation d'une clef
    //6 -> 110
    //     RWX
    id = shmget(clef, sizeof (zone), IPC_CREAT | 0600); // autorisation en R/W (Read/ write)
    if (id == -1) {
        //le segment n'existe pas
        if (errno != EEXIST) {
            printf("pb shmget : %s\n", strerror(errno));
            exit(errno);
        }
    }
    // attribution adresse virtuelle du segment
    partage = shmat(id, NULL, SHM_W); //En écriture
    if (partage == (void *) - 1) {
        printf("pb shmat : %s\n", strerror(errno));
        exit(errno);
    }
    // Mise a jour ordre
    while (1) {
        partage->ordre = randomC();
        sleep(3);


    }




    return (EXIT_SUCCESS);
}