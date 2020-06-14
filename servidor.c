#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int opcion;
    char PosiblesRespuestasEspanol[10];
    char RespuestasEspanol[10]={'c',' ','b',' ','a',' ','a',' ','c'};
    int mi_socket, nuevo, tam;
    struct sockaddr_in mi_estructura;
    mi_estructura.sin_family = AF_INET;
    mi_estructura.sin_port = 0;
    mi_estructura.sin_addr.s_addr = INADDR_ANY;//Para que escuche en caulquiera de las interfaces de SO
    memset(&(mi_estructura.sin_zero), '\0', 8);
    mi_socket = socket(AF_INET, SOCK_STREAM, 0); //Devuelve un entero que es el descriptor de fichero o –1 si ha habido algún error
    tam = sizeof(struct sockaddr);
    bind(mi_socket, (struct sockaddr *)&mi_estructura, tam);//Enlace al puerto
    listen(mi_socket, 5);//(descritor del socket, numero max de clientes encolados)

    do{
        nuevo = accept(mi_socket,(struct sockaddr *)&mi_estructura, &tam);//Espera que un cliente se conecte
        //printf("Bienvenido al menu");
        //Recibiendo la opcion
        recv(nuevo,&opcion,sizeof(int),0);
        switch(opcion){
            case 1:
                printf("******R E S U L T A D O S   E S P A Ñ O L ******\n");
                //se recibe el arreglo de respuetas
                recv(nuevo,&PosiblesRespuestasEspanol,sizeof(PosiblesRespuestasEspanol),0);
                printf("Evaluando\n");
                int calificacion=0;
                for(int i=0;i<10;i++){
                    if((PosiblesRespuestasEspanol[i]==RespuestasEspanol[i])&& PosiblesRespuestasEspanol[i]!=' '){
                        calificacion++;
                    }
                }
                printf("****** C A L I F I C A C I O N   F I N A L ******");
                //Enviando información
                send(nuevo,&calificacion,sizeof(calificacion),0);
                break;
            
        }
        close(nuevo);

    }while(opcion!=4);
    close(nuevo);
    return 0;
}
    