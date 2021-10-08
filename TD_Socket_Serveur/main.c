//--------------------------------------------------Reception d'un Entier

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

int main(int argc, char** argv) {
    int sock;
    int retour;
    int valEnvoyee, valRecue;
    struct sockaddr_in adresseServeur;
    socklen_t taille;
    printf("serveur UDP sur port 2222 attend un ENTIER\n");

    // creation de la socket udp
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    // init de la struture pour communiquer avec le serveur
    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_port = htons(2222);
    adresseServeur.sin_addr.s_addr = htonl(INADDR_ANY);

    // Fonction bind
    retour = bind(sock, (struct sockaddr*) &adresseServeur, sizeof (adresseServeur));
    while (1) {
        // recevoir l'entier en provenance du client 
        retour = recvfrom(sock, &valRecue, sizeof (valRecue), 0, (struct sockaddr *) &adresseServeur, &taille);
        if (retour == -1) {
            printf("pb recvfrom : %s\n", strerror(errno));
            exit(errno);
        }
        // envoyer l'entier au client   
        valEnvoyee = -valRecue;
        retour = sendto(sock, &valEnvoyee, sizeof (valEnvoyee), 0, (struct sockaddr *) &adresseServeur, sizeof (adresseServeur));
        if (retour == -1) {
            printf("pb sendto : %s\n", strerror(errno));
            exit(errno);
        }
        // affiche l'entier 
        printf("message du client : %d\n", valRecue);
    }
    return (EXIT_SUCCESS);
}

