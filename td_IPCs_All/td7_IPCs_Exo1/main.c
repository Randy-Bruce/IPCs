/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: rly
 *
 * Created on 7 octobre 2021, 16:30
 */

//P1 file
#include <stdio.h>
#include <stdlib.h>
#include "zone.h"

/*
 * 
 */
int main(int argc, char** argv) {
    struct donnees maFile;
    int idFile;
    key_t clef;
    
    // creation de la File
    clef = ftok("/tmp/5678", 'a'); // generation d'une clef
    idFile=msgget(clef,IPC_CREAT | IPC_EXCL);
    if (idFile == -1){
        if (errno != EEXIST) {
            printf("pb msgget : %s\n", strerror(errno));
            exit(errno);
        }
    }
    while (1)
    {
        // envoyer temperature dans la file
        // type 2 selon le suhet
        sprintf (maFile.texte,"%.2f",randomF());
        maFile.type=2;
        msgsnd(idFile,(void *)&maFile,sizeof(maFile),IPC_NOWAIT);
        sleep(1);
    // envoyer pression dans la file
        // type 2 selon le suhet
        sprintf (maFile.texte,"%d",randomI());
        maFile.type=4;
        msgsnd(idFile,(void *)&maFile,sizeof(maFile),IPC_NOWAIT);
        sleep(2);
    }

    return (EXIT_SUCCESS);
}

