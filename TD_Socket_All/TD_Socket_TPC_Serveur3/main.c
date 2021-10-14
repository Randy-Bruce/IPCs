//--------------------------------------------------Reception d'une Structure (PAS REUSSI)

#include <stdio.h>
#include <stdlib.h>
//include pour socket
#include <sys/types.h>
#include <sys/socket.h>
//include pour sockaddr_in
#include <netinet/in.h>
#include <arpa/inet.h>
//include gestin erreur
#include <string.h>
#include <errno.h>
#include <unistd.h>

typedef struct {
        unsigned char jour;
        unsigned char mois;
        unsigned short int annee;
        char jourDeLaSemaine[10]; // le jour en toute lettre
    } datePerso;

int main(int argc, char** argv) {
    int socketFileAttente;
    int retour;
    datePerso date;
    int socketCommunicationClient;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    socklen_t tailleClient;
     printf("serveur TCP sur port 2222 attend une STRUCTURE\n");

    // creation de la socket udp
    socketFileAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFileAttente == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    // init de la struture pour communiquer avec le serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(2222); // port dans ordre reseau // "htons" -> hote vers reseau
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    //Fonction bind
    retour = bind(socketFileAttente, (struct sockaddr*) &infosServeur, sizeof (infosServeur)); 
    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(errno);
    }
    // Fonction listen
    tailleClient = sizeof (infosClient);
    retour = listen(socketFileAttente, 10);
    if (retour == -1) {
        printf("pb listen : %s\n", strerror(errno));
        exit(errno);
    }
    while(1){
    // Fonction accept
    socketCommunicationClient = accept(socketFileAttente,(struct sockaddr *)&infosClient, &tailleClient);    
    // recevoir l'entier en provenance du serveur 
    retour = read(socketCommunicationClient, &date ,sizeof(date) );
    if (retour == -1) {
        printf("pb read : %s\n", strerror(errno));
        exit(errno);
    }
    // affiche l'entier 
    printf("message du client = %s %d/%d/%d\n",date.jourDeLaSemaine, date.jour,date.mois,date.annee);
    }
    return (EXIT_SUCCESS);
}

