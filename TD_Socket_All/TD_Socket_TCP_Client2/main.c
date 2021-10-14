//--------------------------------------------------Envoie d'un Réelle

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

int main(int argc, char** argv) {
    int sock;
    float valEnvoyee, valRecue;
    int retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosReception;
    socklen_t taille;

    // creation de la socket udp
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    // init de la struture pour communiquer avec le serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(5555); // port dans ordre reseau // "htons" -> hote vers reseau
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.101");
    // Fonction Connect
    taille = sizeof (infosServeur);
    retour = connect(sock, (struct sockaddr *)&infosServeur, taille);
    if (retour == -1) {
        printf("pb connect : %s\n", strerror(errno));
        exit(errno);
    }
    // envoyer l'entier au serveur 
    valEnvoyee = 7.12345;
    retour = write(sock,&valEnvoyee ,sizeof(valEnvoyee) );
    if (retour == -1) {
        printf("pb write : %s\n", strerror(errno));
        exit(errno);
    }
    // recevoir l'entier en provenance du serveur 
    retour = read(sock,&valRecue ,sizeof(valEnvoyee) );
    if (retour == -1) {
        printf("pb read : %s\n", strerror(errno));
        exit(errno);
    }
    // affiche l'entier 
    printf("reponse du serveur = %f\n", valRecue);

    return (EXIT_SUCCESS);
}

