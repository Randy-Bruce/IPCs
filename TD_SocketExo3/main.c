//--------------------------------------------------Envoie d'une date

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

typedef struct{
	unsigned char jour;
	unsigned char mois;
	unsigned short int annee;
	char jourDeLaSemaine[10];	// le jour en toute lettre
}datePerso;

int main(int argc, char** argv) {
    int sock;
    float valEnvoyee;
    int retour;
    struct sockaddr_in infosServeur;

    // creation de la socket udp
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    // init de la struture pour communiquer avecle serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(4444); // port dans ordre reseau // "htons" -> hote vers reseau
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.150");
    // envoyer l'entier au serveur 
    retour = sendto(sock, &datePerso.jourDeLaSemaine, sizeof (datePerso), 0, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
    if (retour == -1) {
        printf("pb sendto : %s\n", strerror(errno));
        exit(errno);
    }
    return (EXIT_SUCCESS);
}
