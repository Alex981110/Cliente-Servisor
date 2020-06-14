#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> //Asegura que podemos ocuapar las llamadas al sistema para implementar el socket
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 255

int main(int argc, char *argv[])
{
  int opcion, tam, mi_socket, suma = 0;
  char respuestas[10];
  struct sockaddr_in mi_estructura;

  if (argc != 3)
  {
    printf("error: modo de empleo: clientetcp ip puerto\n");
    exit(-1);
  }

  mi_estructura.sin_family = AF_INET;
  mi_estructura.sin_port = htons(atoi(argv[2])); //El puerto en el que debe de escuchar
  inet_aton(argv[1], &(mi_estructura.sin_addr));
  memset(&(mi_estructura.sin_zero), '\0', 8);
  mi_socket = socket(AF_INET, SOCK_STREAM, 0);
  tam = sizeof(struct sockaddr);

  if (connect(mi_socket, (struct sockaddr *)&mi_estructura, tam) == -1){ //abre una conexion en el socket
    perror("Error en conexion");
    exit(1);
  }

  do
  {
    printf("\nElija una opción de examen:\n");
    printf("\t1.Examen de Español\n");
    printf("\t2.Examen de Matematicas\n");
    printf("\t3.Examen de Geografía\n");
    printf("\t4.Salir\n");
    scanf("%d", &opcion);
    send(mi_socket, &opcion, sizeof(int), 0);
    switch (opcion)
    {
    case 1:
      printf("************Examen de Español ************\n");
      printf("1.-¿Qué es un formulario?\n");
      printf("\t)a) Un documento de opinion personal\n");
      printf("\tb) Un examen\n");
      printf("\tc) Documento que contiene preguntas\n\n");

      printf("2.-¿Qué es una antología?\n");
      printf("\ta) Algo en orden cronologico\n");
      printf("\tb) Diversos elementos que podrán considerarse los mejores en su rama\n");
      printf("\tc) Resumen de argumentos\n\n");

      printf("3.-¿Qué es una leyenda?\n");
      printf("\ta) Algo que te cuantan otras personas\n");
      printf("\tb) Algo falso\n");
      printf("\tc) Un cuento\n\n");

      printf("4.-¿Tipos de argumento?\n");
      printf("\ta) Consigno, analógico y nexos casuales\n");
      printf("\tb) Los que yo quiera\n");
      printf("\tc) Explicativo, razonamiento, casual\n\n");

      printf("5.- ¿Qué es un panel de discusión?\n");
      printf("\ta) Contradecir las opiniones de los demás\n");
      printf("\tb) Un debate\n");
      printf("\tc) Intercambio público de ideas\n\n");

      printf("Respuestas con un espacio\n");
      printf("\tRespuestas: ");

      getchar();
      fgets(respuestas, 10, stdin);
      send(mi_socket, &opcion, sizeof(opcion), 0);
      send(mi_socket, &respuestas, sizeof(respuestas), 0);
      recv(mi_socket, &suma, sizeof(int), 0);
      printf("\n*****CALIFICACIÓN: %d*****\n", suma * 2);
      if (suma > 6){
        printf("\nEres inteligente we\n");
      }else
      {
        printf("\nPuto burro\n");
      }      
      break;

      case 4: 
          break;
    } //Fin Switch
    close(mi_socket);
  } while (opcion != 4);

  return 0;
}