#include <stdio.h>
#include "hilopc.h"
#define N_ARG      3
#define BUFFER     0
#define PRODUCTOR  1
#define CONSUMIDOR 2
#define MAX_BUFFER 100
#define MAX_PC 10
int main(int argc, char *argv[]){
  int index, argumento[N_ARG];
  if(argc < N_ARG){
      printf("Número de argumentos invalidos.\n\tNúmero-de-productos-máximo Productores Consumidores");
      exit(-1);
  }else
    for(index = 1; index < N_ARG + 1; index++)
      argumento[index - 1] = atoi(argv[index]);
  if(!(argumento[BUFFER] > 0 && argumento[BUFFER] <= MAX_BUFFER) ||
     !(argumento[PRODUCTOR] > 0 && argumento[PRODUCTOR] <= MAX_PC)||
     !(argumento[CONSUMIDOR] > 0 && argumento[CONSUMIDOR] <= MAX_PC)){
         printf("Valores máximos: Buffer %d, Productores %d, Consumidores %d",
                MAX_BUFFER, MAX_PC, MAX_PC);
         exit(-1);
     }
     for(index = 0; index < argumento[PRODUCTOR]; index++)
       crearHilo(PRODUCTOR, index);
     for(index = 0; index < argumento[CONSUMIDOR]; index++)
       crearHilo(CONSUMIDOR, index);
    exit(0);
}
