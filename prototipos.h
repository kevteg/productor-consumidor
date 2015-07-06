
#ifdef __linux__
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
//#include "unix.h"
#elif _WIN32
#include <conio.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
//#include "windows.h"
#endif
#define true                  1
#define COLOR_ROJO            "\x1b[31m"
#define COLOR_NORMAL          "\x1b[0m"
#define COLOR_VERDE           "\x1b[32m"
#define COLOR_AZUL            "\x1b[34m"
#define COLOR_NOTIFICACION    "\x1b[47m"
#define MUTEX      0
#define LLENO      1
#define VACIO      2
#define N_ARG      3
#define PRODUCTOR  0
#define CONSUMIDOR 1
#define BUFFER     2
#define GRAFICO    3
#define MAX_BUFFER 100
#define MAX_PC     50
#define clear()    printf("\033[H\033[J")

/*Prototipos de productor*/
#ifdef __linux__
  void *fProductor(void *);
#elif _WIN32
  DWORD WINAPI *fProductor (LPVOID );
#endif

/*Prototipos de consumidor*/
#ifdef __linux__
	void *fConsumidor(void *);
#elif _WIN32
	DWORD WINAPI *fConsumidor (LPVOID );
#endif

/*Prototipos de hilopc*/
#ifdef __linux__
  pthread_t crearHilo(int, int *);
#elif _WIN32
  HANDLE crearHilo(int, int *);
#endif

#ifdef __linux__
  void instanciaHilo(pthread_t *hilo, int *parametro, void *(*funcion_hilo)(void *));
#elif _WIN32
  void instanciaHilo(HANDLE *hilo, int *parametro, void *(*funcion_hilo)(void *));
#endif

#ifdef __linux__
  void iniciarHilo(pthread_t hilo);
#elif _WIN32
  void iniciarHilo(HANDLE hilo);
#endif


void gotoxy(int, int);
void *nivelProducto();
void nivelL();
void nivelW();
void crearRecuadro();
void dormir(int);
void down(int tipo);
void up(int tipo);
void iniciarSemaforos();
void detenerSemaforos();

#ifdef __linux__
  sem_t mutex;
  sem_t lleno;
  sem_t vacio;
#elif _WIN32
  HANDLE mutex;
  HANDLE lleno;
  HANDLE vacio;
  HANDLE hConsola;
  CONSOLE_SCREEN_BUFFER_INFO consolaInfo;
  WORD COLOR_NORMAL_W;
#endif

int *argumento;

int ult_pro;
int ult_con;
int buff;
