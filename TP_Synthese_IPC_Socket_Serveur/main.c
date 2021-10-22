//
// serveur tchat TCP multiThread
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

#define NB_MAX_CLIENT 50
#define TAILLE_MAX_MSG 255
#define TAILLE_MAX_REPONSE 400
#define TAILLE_MAX_PSEUDO 25

// definition de la structure

typedef struct {
    char pseudo[TAILLE_MAX_PSEUDO];
    char texteMessage[TAILLE_MAX_MSG];

} message;

// donnees partagees par les threads
int tabSocketClients[NB_MAX_CLIENT];
int nbClient;

// decalage d'une case a gauche du contenu du tableau des sockets a partir de l'indice nro

void removeClient(int nro) {
    int i;

    /* boucle pour le decalage*/
    for (i = 0; i < nro; i++) {
        // decrementation du nombre de clients
        nbClient--;
    }
    printf("maj tableau des clients, reste %d clients\n", nbClient);

}

void *traitementClient(void *arg) {
    int socketCommunication = *(int *) arg;
    char reponse[TAILLE_MAX_REPONSE];
    message messageClient;
    int i;
    int retour;


    printf(" pid : [%d] tid : [%ld] dans le thread socket du client : %d\n", getpid(), syscall(SYS_gettid), socketCommunication);
    /* faire tant que le texte du message client n'est pas "quit"*/
    do {
        /* lecture du message via la socket de communication et stockage dans la variable messageClient*/
        retour = read(socketCommunication, &messageClient, sizeof (messageClient));
        if (retour == -1) {
            printf("pb read : %s\n", strerror(errno));
            exit(errno);
        }

        printf("message du client %s: %s\n", messageClient.pseudo, messageClient.texteMessage);

        /* creation de la chaine de caractere reponse compose ainsi 
         pseudo : texteDuMessage */
        memset(reponse, '\0', TAILLE_MAX_REPONSE);


        printf("message diffusion : %s\n", reponse);
        /*Envoyer reponse à tous les clients sauf le client actuel*/
        printf("votre message : ");
        gets(reponse);

        retour = write(socketCommunication, &messageClient, sizeof (messageClient));
        if (retour == -1) {
            printf("pb write : %s\n", strerror(errno));
            exit(errno);
        }


    } while (strcmp("quit", &messageClient) != 0);
    // fermeture de la socket du client
    close(socketCommunication);
    // suppression du client de la liste des clients connectes
    removeClient(socketCommunication);

    printf("id thread fini : %lu\n", pthread_self());
    pthread_exit((void *) NULL);
}

int main(int argc, char *argv[]) {
    int socketFileAttente, socketCommunicationClient;

    struct sockaddr_in adresseServeur;
    struct sockaddr_in adresseClient;
    pthread_t threadClient;

    int retour;
    int tailleClient;
    char buffer[TAILLE_MAX_MSG];
    int res;
    nbClient = 0; //init du nombre de client


    printf("serveur TCP sur port 5678 \n");
    /* init de la structure pour le serveur*/
    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_port = htons(5678);
    adresseServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("serveur de Tchat tcp port 5678\n");

    /* creation de la socketFileAttente*/
    socketFileAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketFileAttente == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }

    /* association IP/PORT*/
    retour = bind(socketFileAttente, (struct sockaddr*) &adresseServeur, sizeof (adresseServeur));
    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(errno);
    }

    /* configuration de la longueur de la file d'attente*/
    tailleClient = sizeof (adresseClient);
    retour = listen(socketFileAttente, 50);
    if (retour == -1) {
        printf("pb listen : %s\n", strerror(errno));
        exit(errno);
    }

    tailleClient = sizeof ( adresseClient);


    while (1 == 1) {
        if (nbClient < NB_MAX_CLIENT) {
            /* attente de la connexion d'un client et recuperation de la socket de communication*/
            socketCommunicationClient = accept(socketFileAttente, (struct sockaddr *) &adresseClient, &tailleClient);
            printf("%s\n", inet_ntoa(adresseClient.sin_addr));
            retour = read(socketCommunicationClient, &threadClient, sizeof (threadClient));
            if (retour == -1) {
                printf("pb read : %s\n", strerror(errno));
                exit(errno);
            }
            printf("\nmsg provenant du client :%s\n", &threadClient);
            // creation du thread de traitement du client
            res = pthread_create(&threadClient, NULL, traitementClient, (void *) &socketCommunicationClient);
            if (res != 0) {
                perror("Thread creation failed");
                exit(EXIT_FAILURE);
            }
            /* ajout de la socket de communication au tableau representant la liste des clients connectes*/

            /* incrementer le nombre de client*/
            nbClient++;
        }


    }
    return EXIT_SUCCESS;
}