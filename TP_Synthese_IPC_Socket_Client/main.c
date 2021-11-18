//
// Client tchat TCP 
// sur port 5678
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <signal.h>

#define TAILLE_MAX_MSG 255
#define TAILLE_MAX_PSEUDO 25

typedef struct {
    char pseudo[TAILLE_MAX_PSEUDO];
    char texteMessage[TAILLE_MAX_MSG];
} message;

int main(int argc, char** argv) {
    int sock;
    int retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosReception;
    socklen_t taille;
    int pid;
    char msgRecu[TAILLE_MAX_MSG];
    char buffer[TAILLE_MAX_MSG];

    message msg;
    strcpy(msg.pseudo, "Randy");
    msg.texteMessage;
    /* strcpy(msg.pseudo, "Randy");
     strcpy(msg.texteMessage, "Bonjour le monde");*/

    // creation de la socket udp
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    // init de la struture pour communiquer avec le serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(5678); // port dans ordre reseau // "htons" -> hote vers reseau
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.104");
    //demande de connexion au serveur
    retour = connect(sock, (struct sockaddr *) &infosServeur,
            sizeof (infosServeur));
    if (retour == -1) {
        printf("pb connect : %s\n", strerror(errno));
        exit(errno);
    }
    pid = fork();
    if (pid == 0) {//boucle d'envoie
        do {
            printf("votre message : ");
            gets(msg.texteMessage);
            retour = write(sock, &msg, sizeof (msg));
            if (retour == -1) {
                printf("pb write : %s\n", strerror(errno));
                exit(errno);
            }
        } while (strcmp("quit", &msg.texteMessage) != 0);
        //arreter le processus de connexion
        kill(getppid(), SIGTERM);
        close(sock);
    } else {//boucle de reception
        while (1) {
            // reception en provenance du serveur
            memset(msgRecu, '\0', TAILLE_MAX_MSG);
            retour = read(sock, msgRecu, TAILLE_MAX_MSG);
            if (retour == -1) {
                printf("pb read : %s\n", strerror(errno));
                exit(errno);
            }
            printf("\n{ %s}\n", msgRecu);

        }
    }
}