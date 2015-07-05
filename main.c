
#include <stdio.h>
#include "prototipos.h"
#include "hilopc.h"
#include "consumidor.h"
#include "productor.h"

int main(int argc, char *argv[]){
  clear();
  int index = 0, *id[2];
  argumento = malloc(N_ARG * sizeof(int));
  #ifdef __linux__
    pthread_t *hilos[2];
    pthread_t gra;
  #elif _WIN32
    DWORD *hilos[2];
    DWORD gra;
  #endif
  buff = 0;
  ult_con = -1;
  ult_pro = -1;
  if(argc < N_ARG){
      printf("Número de argumentos invalidos.\n\tProductores Consumidores Número-de-productos-máximo");
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
     iniciarSemaforos();
     id[PRODUCTOR]     = malloc(argumento[PRODUCTOR] * sizeof(int));
     id[CONSUMIDOR]    = malloc(argumento[CONSUMIDOR] * sizeof(int));
     hilos[PRODUCTOR]  = malloc(argumento[PRODUCTOR] * sizeof(pthread_t));
     hilos[CONSUMIDOR] = malloc(argumento[CONSUMIDOR] * sizeof(pthread_t));

     for(index = 0; index < argumento[PRODUCTOR]; index++)
       id[PRODUCTOR][index] = index + 1;

     for(index = 0; index < argumento[CONSUMIDOR]; index++)
       id[CONSUMIDOR][index] = index + 1;

     gra = crearHilo(GRAFICO, NULL);
     for(index = 0; index < argumento[PRODUCTOR]; index++)
       hilos[PRODUCTOR][index] = crearHilo(PRODUCTOR, &id[PRODUCTOR][index]);
     for(index = 0; index < argumento[CONSUMIDOR]; index++)
       hilos[CONSUMIDOR][index] = crearHilo(CONSUMIDOR, &id[CONSUMIDOR][index]);

     iniciarHilo(gra);
     for(index = 0; index < argumento[PRODUCTOR]; index++)
       iniciarHilo(hilos[PRODUCTOR][index]);
     for(index = 0; index < argumento[CONSUMIDOR]; index++)
       iniciarHilo(hilos[CONSUMIDOR][index]);

    detenerSemaforos();
    exit(0);
}
void *nivelProducto(){
  while(true){
  clear();
  int index = 0;
  int x;
  int y = -10;
  for(index = 0; index < MAX_BUFFER; index++){
    if(!(index %  (MAX_BUFFER/4))){
      x = 1;
      y += 10;
    }
    printf (" \033[%d;%dH", x, y);
    x++;
    printf(COLOR_AZUL);
    printf("▎");
    if(index + 1 <= buff){
      printf(COLOR_VERDE);
      printf("◧◨◧◨");
    }else
      printf("    ");
    printf(COLOR_AZUL);
    printf(" ▎");
    printf(COLOR_NORMAL);
  }
  crearRecuadro();
  printf (" \033[%d;%dH", 27, 5);
  printf("Producto: %d", buff);
  printf (" \033[%d;%dH", 28, 5);
  printf("Máximo: %d", argumento[BUFFER]);
  printf (" \033[%d;%dH", 27, 18);
  printf("Consumidores: %d", argumento[CONSUMIDOR]);
  printf (" \033[%d;%dH", 28, 18);
  printf("Productores: %d",  argumento[PRODUCTOR]);
  if(ult_pro != -1){
    printf (" \033[%d;%dH", 29, 5);
    printf("P[%d] agregó", ult_pro);
  }
  if(ult_con != -1){
    printf (" \033[%d;%dH", 29, 18);
    printf("C[%d] quitó\n", ult_con);
  }
  dormir(1);
}
}
void crearRecuadro(){
  int index;
  int tam_largo = 3;
  int tam_ancho =36;
  int x, y;
  x = 26; y = 0;
  printf(COLOR_VERDE);
  printf (" \033[%d;%dH", x, y);
  for(index = 0; index < tam_ancho; index++){
    if(!index)
      printf ("┌");
    else
      printf ("─");
  }
    printf("┐");
  x = 27;
  for(index = 0; index < tam_largo; index++){
    printf (" \033[%d;%dH", x, y);
    printf ("│");
    x++;
  }
  x = 30;
  y = 0;
  printf (" \033[%d;%dH", x, y);
  for(index = 0; index < tam_ancho; index++){
    if(!index)
      printf ("└");
      else
        printf ("─");
      }
  x = 27;
  y = 37;
  for(index = 0; index < tam_largo; index++){
    printf (" \033[%d;%dH", x, y);
    printf ("│");
    x++;
  }
  printf (" \033[%d;%dH", x, y);
  printf("┘");
  printf(COLOR_NORMAL);
}
