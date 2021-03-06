/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: rly
 *
 * Created on 30 septembre 2021, 14:31
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

typedef struct {
    int v1;
    int v2;
    int v3;
} laStruct;

//Zone de partage
laStruct partage;

void *thread1(void *arg) {
    int *ptr = (int *) arg;
    printf("dans le thread1 mon tid est %ld\n", syscall(SYS_gettid));
    printf("mise a jour de la v1 avec la valeur %d\n", *ptr);
    partage.v1 = *ptr;
    pthread_exit((void *) "merci pour le temps CPU");
    pthread_exit(NULL);
}

void *thread2(void *arg) {
    int *ptr = (int *) arg;
    printf("dans le thread2 mon tid est %ld \n", syscall(SYS_gettid));
    printf("mise a jour de la v2 avec la valeur %d\n", *ptr);
    partage.v2 = *ptr;
    pthread_exit((void *) "merci pour le temps CPU");
    pthread_exit(NULL);
}

void *thread3(void *arg) {
    int *ptr = (int *) arg;
    printf("dans le thread3 mon tid est %ld\n", syscall(SYS_gettid));
    printf("mise a jour de la v3 avec la valeur %d\n", *ptr);
    partage.v3 = *ptr;
    pthread_exit((void *) "merci pour le temps CPU");
    pthread_exit(NULL);
}

void *threadMulti(void *arg) {
    laStruct *ptr = (laStruct *) arg;
    printf("dans le thread3 mon tid est %ld\n", syscall(SYS_gettid));
    printf("mise a jour des valeur v1, v2 et v3 avec ls valeurs %d, %d, %d\n", ptr->v1, ptr->v2, ptr->v3);
    partage.v1 = ptr->v1;
    partage.v2 = ptr->v2;
    partage.v3 = ptr->v3;
    pthread_exit(NULL);
}

void affichePartage() {
    printf("__________________\n");
    printf("v1 = %d\n", partage.v1);
    printf("v2 = %d\n", partage.v2);
    printf("v3 = %d\n", partage.v3);
}

int main(int argc, char** argv) {
    pthread_t t1, t2, t3;
    int ret;
    void *thread_result;
    laStruct param1, param2, param3;
    param1.v1 = 1;
    param1.v2 = 1;
    param1.v3 = 1;

    //Creation du thread1
    ret = pthread_create(&t1, NULL, thread1, (void *) &param1);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    //Creation du thread2
    param2.v1 = 2;
    param2.v2 = 2;
    param2.v3 = 2;
    ret = pthread_create(&t2, NULL, thread2, (void *) &param2);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    //Creation du thread3
    param3.v1 = 3;
    param3.v2 = 3;
    param3.v3 = 3;
    ret = pthread_create(&t3, NULL, thread3, (void *) &param3);
    if (ret != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();

    //Attendre fin du thread 1
    ret = pthread_join(t1, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echou??");
        exit(EXIT_FAILURE);
    }
    //Attendre fin du thread 2
    ret = pthread_join(t2, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echou??");
        exit(EXIT_FAILURE);
    }
    //Attendre fin du thread 3
    ret = pthread_join(t3, &thread_result);
    if (ret != 0) {
        perror("Thread join a foir... echou??");
        exit(EXIT_FAILURE);
    }
    affichePartage();


    return (EXIT_SUCCESS);
}

