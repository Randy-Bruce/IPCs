/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: rly
 *
 * Created on 30 septembre 2021, 09:15
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*
 * 
 */

void traitement(int sig) {
    // cpt++;
    (void) signal(SIGUSR1, traitement);
    // if (cpt == 2) {
    printf("signal SIGUSR1 recu par pid :%d\n", getpid());
    //}
}

int main(int argc, char** argv) {
    (void) signal(SIGUSR1, traitement); // rederoutage des signaux SIGUSR1
                                        // vers la fonction traitement
    int tube[2];
    int pid;
    int pidP3;
    // creation du premier tube
    if (pipe(tube) == 0) {
        //creation de p2
        pid = fork();
        if (pid == 0) //P2
        {
            //creation de p3
            pid = fork(); //P3
            if (pid == 0) {
                pidP3 = getpid();
                printf("je suis p3 mon pid est %d mon pere est %d\n", pidP3, getpid());
                write(tube[1], &pidP3, sizeof (pidP3));
                pause(); // attente d'un signal
                
            } else { //P3
                printf("je suis p2 mon pid est %d mon pere est %d\n", getpid(), getpid());
                pause();  // attente d'un signal
                
            }

        } else { //P1
            //Lecture du pid de P3
            read(tube[0], &pidP3, sizeof (pidP3));
            printf("je suis P1 mon pid est %d le pid de p3 est %d\n",getpid(),pidP3);
            // envoyer SIGUSR1 à P3
            kill(pidP3, SIGUSR1);
            // envoyer SIGUSR1 à P2
            kill(pid, SIGUSR1);
            
        }
    }


    return (EXIT_SUCCESS);
}

