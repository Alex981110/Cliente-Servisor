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
  int opcion, tam, mi_socket, calificacion = 0;
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
      printf("************Examen de Español ************\n\n");
      printf("1.-Sinónimo de Cabello\n");
      printf("\t\na) Pelo   b)Canas   c)Chinos\n\n"); //a) correcta

      printf("2.-Es un verbo en infinitivo\n");
      printf("\t\na) Comió	b) Correr	c) Saltará\n\n"); //b) correcta

      printf("3.-Ejemplo de un palíndromo\n");
      printf("\t\na) Computadora		b)Ana	c) Cuento\n\n"); //c) correcta

      printf("4.-Es una clase de verbo\n");
      printf("\t\na) Sintesis	b) Pasado perfecto	c) Transitivos\n\n"); // c) correcta

      printf("5.- ¿Cuántos tiempos verbales existen?\n");
      printf("\t\na) 4	b) 2	c) 7\n\n"); //b) correcta

      printf("\nIngresa tus respuestas separadas por un espacio\n");
      printf("\tRespuestas: ");
      getchar();
      fgets(respuestas, 10, stdin);

      send(mi_socket, &opcion, sizeof(opcion), 0);
      send(mi_socket, &respuestas, sizeof(respuestas), 0);
      recv(mi_socket, &calificacion, sizeof(int), 0);
      printf("\n*****CALIFICACIÓN: %d*****\n", calificacion * 2);
      if (calificacion > 6)
      {
        printf("\nEres inteligente we\n");
      }
      else
      {
        printf("\nPuto burro\n");
      }
      break;

    case 2:
      printf("************Examen de Matemáticas************\n\n");
      printf("1.-Es un número imaginario\n");
      printf("\t)a) 12\n"); 
      printf("\tb) 3i\n");//correcta
      printf("\tc) 7x\n");

      printf("2.-El resultado de 5! es:\n");
      printf("\ta) 12\n");
      printf("\tb) 0\n"); 
      printf("\tc) 120\n");//corecta

      printf("3.-¿Qué signo tiene el número 0?\n");
      printf("\ta) Más\n");
      printf("\tb) No tiene signo.\n"); //correcta
      printf("\tc) Menos\n");

      printf("4.-Es una función trigonométrica\n");
      printf("\ta) 3x+2=0\n");
      printf("\tb) F(x)\n");
      printf("\tc) Coseno\n");//correcta

      printf("5.- ¿Cuál es el resultado de 5x - 3 = 3?\n");
      printf("\ta) X = 4\n");
      printf("\tb) x = 6/5\n"); //corecta
      printf("\tc) x = 7\n");

      printf("\nIngresa tus respuestas separadas con un espacio\n");
      printf("\tRespuestas: ");
      getchar();
      fgets(respuestas, 10, stdin);

      send(mi_socket, &opcion, sizeof(opcion), 0);
      send(mi_socket, &respuestas, sizeof(respuestas), 0);
      recv(mi_socket, &calificacion, sizeof(int), 0);
      printf("\n*****CALIFICACIÓN: %d*****\n", calificacion * 2);
      if (calificacion > 6)
      {
        printf("\nEres inteligente we\n");
      }
      else
      {
        printf("\nPuto burro\n");
      }
      break;

    case 3:
      printf("************Examen de Geografía************\n\n");
      printf("1.-¿Cuál es la capital de Brasil?\n");
      printf("\t)a) Lima.\n");
      printf("\tb) Roma.\n");
      printf("\tc) Brasilia.\n");//correcta

      printf("2.-¿Cuántps estados tiene México?\n");
      printf("\ta) 28\n");
      printf("\tb) 32\n"); //corecta
      printf("\tc) 12\n");

      printf("3.-¿Cuál es el pais más frande del mundo?\n");
      printf("\ta) Rusia.\n");//correcta
      printf("\tb) China.\n"); 
      printf("\tc) Alemania.\n");

      printf("4.-¿En dónde se encuentra el Anfiteatro de Flavio?\n");
      printf("\ta) Bogotá, Colombia.\n");
      printf("\tb) Lisboa, Portugal.\n");
      printf("\tc) Roma, Italia.\n");//correcta

      printf("5.- ¿Cual es el país con más habitantes en el mundo?\n");
      printf("\ta) China.\n");//corecta
      printf("\tb) Francia.\n"); 
      printf("\tc) Suiza.\n");

      printf("Ingresa tus respuestas separadas con un espacio\n");
      printf("\tRespuestas: ");
      getchar();
      fgets(respuestas, 10, stdin);

      send(mi_socket, &opcion, sizeof(opcion), 0);
      send(mi_socket, &respuestas, sizeof(respuestas), 0);
      recv(mi_socket, &calificacion, sizeof(int), 0);
      printf("\n*****CALIFICACIÓN: %d*****\n", calificacion * 2);
      if (calificacion > 6)
      {
        printf("\nEres inteligente we\n");
      }
      else
      {
        printf("\nPuto burro\n");
      }
      break;

    case 4:
      printf("\n**********Hata pronto**********\n");
      break;
    } //Fin Switch
    close(mi_socket);
  } while (opcion != 4);

  return 0;
}