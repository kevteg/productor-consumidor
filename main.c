
#include <stdio.h>
#include "prototipos.h"
#include "hilopc.h"
#include "consumidor.h"
#include "productor.h"
/*Autores:
		  Kevin Hernánez 21256207
		  Estefany Salas 24820631*/
int main(int argc, char *argv[]){
  int index = 0, *id[2];
  argumento = malloc(N_ARG * sizeof(int));
  #ifdef __linux__
    clear();
	pthread_t *hilos[2];
    pthread_t gra;
  #elif _WIN32
  	/* Guardar colores de la consola */
	hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsola, &consolaInfo);
    COLOR_NORMAL_W = consolaInfo.wAttributes;
    HANDLE *hilos[2];
    HANDLE gra;
  #endif
  buff = 0;
  ult_con = -1;
  ult_pro = -1;
  if(argc < N_ARG){
    #ifdef __linux__
      printf("\nNúmero de argumentos invalidos.\nArgumentos:\tCant. productores   Cant. consumidores   Número-de-productos-máximo\n");
    #elif _WIN32
      printf("\nN%cmero de argumentos invalidos.\nArgumentos:\tCant. productores   Cant. consumidores   N%cmero-de-productos-m%cximo\n",163,163,160);
    #endif
      exit(-1);
  }else
    for(index = 1; index < N_ARG + 1; index++)
      argumento[index - 1] = atoi(argv[index]);
  if(!(argumento[BUFFER] > 9 && argumento[BUFFER] <= MAX_BUFFER) ||
     !(argumento[PRODUCTOR] > 0 && argumento[PRODUCTOR] <= MAX_PC)||
     !(argumento[CONSUMIDOR] > 0 && argumento[CONSUMIDOR] <= MAX_PC)){

         printf("\nValores de argumentos: 1 <= Cant. productores <= %d, 1 <= Cant. consumidores <= %d,  10 <= Buffer <= %d\n",
         MAX_PC, MAX_PC, MAX_BUFFER);

         exit(-1);
     }
     iniciarSemaforos();
     id[PRODUCTOR]     = malloc(argumento[PRODUCTOR] * sizeof(int));
     id[CONSUMIDOR]    = malloc(argumento[CONSUMIDOR] * sizeof(int));
     #ifdef __linux__
     	hilos[PRODUCTOR]  = malloc(argumento[PRODUCTOR] * sizeof(pthread_t));
     	hilos[CONSUMIDOR] = malloc(argumento[CONSUMIDOR] * sizeof(pthread_t));
     #elif _WIN32
     	hilos[PRODUCTOR]  = malloc(argumento[PRODUCTOR] * sizeof(HANDLE));
     	hilos[CONSUMIDOR] = malloc(argumento[CONSUMIDOR] * sizeof(HANDLE));
     #endif

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
    //SetConsoleTextAttribute(hConsole, saved_attributes);
    exit(0);
}

void *nivelProducto(){
  while(true){
 #ifdef __linux__
  nivelL();
#elif _WIN32
  nivelW();
#endif
  dormir(1);
}
}

void nivelL(){
  #if __linux__
	clear();
  int index = 0;
  int x;
  int y = -10;
  for(index = 0; index < MAX_BUFFER; index++){
    if(!(index %  (MAX_BUFFER/4))){
      x = 1;
      y += 10;
    }
    gotoxy(x, y);
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
  gotoxy(27, 3);
  printf("Producto: %d", buff);
  gotoxy(27, 19);
  printf("Máximo: %d", argumento[BUFFER]);
  gotoxy(28, 19);
  printf("Consumidores: %d", argumento[CONSUMIDOR]);
  gotoxy(28, 3);
  printf("Productores: %d",  argumento[PRODUCTOR]);
  if(ult_pro != -1){
    gotoxy(29, 3);
    printf("P[%d] agregó", ult_pro);
  }
  if(ult_con != -1){
    gotoxy(29, 19);
    printf("C[%d] quitó\n", ult_con);
  }
  #endif
}
void nivelW(){
  #if _WIN32
  system("cls");
  int index = 0;
  int y;
  int x = -10;
  for(index = 0; index < MAX_BUFFER; index++){
    if(!(index % (MAX_BUFFER/4))){
      y = 1;
      x += 10;
    }
    gotoxy(x, y);
    y++;
    SetConsoleTextAttribute(hConsola, FOREGROUND_BLUE);
    printf("|");
    if(index + 1 <= buff){
      SetConsoleTextAttribute(hConsola, FOREGROUND_GREEN);
      printf("%c%c%c%c%c",178,177,176,177,178);
    }else
      printf("     ");
    SetConsoleTextAttribute(hConsola, FOREGROUND_BLUE);
    printf("|");
    SetConsoleTextAttribute(hConsola, COLOR_NORMAL_W);
  }
  gotoxy(0, 27);
  printf("Producto: %d", buff);
  gotoxy(18, 27);
  printf("M%cximo: %d",160, argumento[BUFFER]);
  gotoxy(0, 28);
  printf("Consumidores: %d", argumento[CONSUMIDOR]);
  gotoxy(18, 28);
  printf("Productores: %d",  argumento[PRODUCTOR]);
  if(ult_pro != -1){
    gotoxy(18, 29);
    printf("P[%d] agreg%c", ult_pro, 162);
  }
  if(ult_con != -1){
    gotoxy(0, 29);
    printf("C[%d] quit%c\n", ult_con, 162);
  }
  #endif
}

void crearRecuadro(){
  int index;
  int tam_largo = 3;
  int tam_ancho =36;
  int x, y;
  x = 26; y = 0;
  printf(COLOR_VERDE);
  gotoxy(x, y);
  for(index = 0; index < tam_ancho; index++){
    if(!index)
      printf ("┌");
    else
      printf ("─");
  }
    printf("┐");
  x = 27;
  for(index = 0; index < tam_largo; index++){
    gotoxy(x, y);
    printf ("│");
    x++;
  }
  x = 30;
  y = 0;
  gotoxy(x, y);
  for(index = 0; index < tam_ancho; index++){
    if(!index)
      printf ("└");
      else
        printf ("─");
      }
  x = 27;
  y = 37;
  for(index = 0; index < tam_largo; index++){
    gotoxy(x, y);
    printf ("│");
    x++;
  }
  gotoxy(x, y);
  printf("┘");
  printf(COLOR_NORMAL);
}

void gotoxy(int x, int y){
#ifdef __linux__
  printf (" \033[%d;%dH", x, y);
#elif _WIN32
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
}
