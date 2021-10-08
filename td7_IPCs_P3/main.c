#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "zone.h"


int main(int argc, char** argv) {
    struct donnees maFile;
    key_t clef;
    int idFile;
    int ret;
    
    //creation de la file
    clef = ftok("/tmp/5678", 'a'); // generation d'une clef
    idFile = msgget(clef, IPC_CREAT | 0666);//Autorisation en R/W (Read/ write)
    if (idFile==-1)
    {
        //le segment n'existe pas
        if(errno!=EEXIST)
        {
            printf("pb msgget : %s\n",strerror(errno));
            exit(errno);
            
        }
    }    
    //Mise a jour pression et temperature
     while(1){
         
         //lecture des temperatures
         ret=msgrcv(idFile,(void *)&maFile,sizeof(maFile),2,IPC_NOWAIT);
         if(ret!=-1)  //pas d'erreur de lecture -> afficher le message
         {
             printf("temp : %s\n",maFile.texte);
         }
         
         //lecture des pressions
         ret=msgrcv(idFile,(void *)&maFile,sizeof(maFile),4,IPC_NOWAIT);
         if(ret!=-1)  //pas d'erreur de lecture -> afficher le message
         {
             printf("temp : %s\n",maFile.texte);
         }
         
           //lecture des ordres
         ret=msgrcv(idFile,(void *)&maFile,sizeof(maFile),3,IPC_NOWAIT);
         if(ret!=-1)  //pas d'erreur de lecture -> afficher le message
         {
             printf("temp : %s\n",maFile.texte);
         }
         sleep(1);
        
    }
    


    return (EXIT_SUCCESS);
}
