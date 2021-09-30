/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: rly
 *
 * Created on 30 septembre 2021, 08:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
int cpt;
/*
 * 
 */

// fonction de traitement du signal SIGUSR1

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
    int pidP1, pidP2, pidP3;
    //P1
    pidP1 = getpid();
    printf("proces principal p1, pid %d\n", pidP1);
    // intit du compteur
    cpt = 0;
    pidP2 = fork();
    if (pidP2 == 0) //P2
    {
        pidP3 = fork();
        if (pidP3 == 0)//P3
        {
            sleep(2);
            //envoyer SIGUSR1 à P2
            kill(getppid(), SIGUSR1);

        } else { //P2
            printf("je suis P2 pid : %d\n", getpid);
            pause();
            pause();
        }
    } else { //P1
        //envoyer SIGUSR1 à P2
        kill(pidP2, SIGUSR1);
    }


    return (EXIT_SUCCESS);
}
