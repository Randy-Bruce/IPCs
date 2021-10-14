//--------------------------------------------------Envoie d'une Structure

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
    int sock;
    int retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosReception;
    socklen_t taille;
    
    datePerso date;
    date.jour = 13;
    date.mois = 10;
    date.annee = 2021;
    strcpy(date.jourDeLaSemaine, "Mercredi");

    // creation de la socket udp
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    // init de la struture pour communiquer avec le serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(2222); // port dans ordre reseau // "htons" -> hote vers reseau
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.102");
    // Fonction Connect
    taille = sizeof (infosServeur);
    retour = connect(sock, (struct sockaddr *)&infosServeur, taille);
    if (retour == -1) {
        printf("pb connect : %s\n", strerror(errno));
        exit(errno);
    }
    // envoyer l'entier au serveur 
    retour = write(sock,&date ,sizeof(date) );
    if (retour == -1) {
        printf("pb write : %s\n", strerror(errno));
        exit(errno);
    }
   

    return (EXIT_SUCCESS);
}

