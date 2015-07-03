
#ifdef __linux__
  #include <pthread.h>
  #include <unistd.h>
  #include <stdlib.h>
  //#include "unix.h"
#elif _WIN32
  #include <conio.h>
  #include <windows.h>
  //#include "windows.h"

#endif
#define PROD 1
#define CONS 2

/*Prototipos*/
#ifdef __linux__
  void *fProductor(void *n_productor);
#elif _WIN32
  DWORD WINAPI fProductor (LPVOID n_productor);
#endif

#ifdef __linux__
void *fConsumidor(void *n_consumidor);
#elif _WIN32
DWORD WINAPI fConsumidor (LPVOID n_consumidor);
#endif

void crearHilo(int, int);

#ifdef __linux__
  void instanciaHilo(pthread_t *hilo, int n_productor, void *(*funcion_hilo)(void *));
#elif _WIN32
  void instanciaHilo(DWORD *hiloId, int n_productor, void *(*funcion_hilo)(void *)){
#endif

void hiloConsumidor( void (*funcion_hilo)(void *), int a);
/*---*/

/*Función del productor*/
#ifdef __linux__
  void *fProductor(void *n_productor){
    int *n_pro = n_productor;
#elif _WIN32
  DWORD WINAPI funcionHilo (LPVOID n_productor)
    int *n_pro = (int *)n_productor;
#endif

  printf("Soy el productor %d\n", *n_pro);
}
/*---*/

/*Función del productor*/
#ifdef __linux__
  void *fConsumidor(void *n_consumidor){
    int *n_con = n_consumidor;
#elif _WIN32
  DWORD WINAPI funcionHilo (LPVOID n_consumidor)
  int *n_con = (int *)n_consumidor;
#endif

  printf("Soy el consumidor %d\n", *n_con);
}
/*---*/

/*Creación del hilo*/
void crearHilo(int tipo, int id){
  #ifdef __linux__
    pthread_t hilo;
  #elif _WIN32
    DWORD hilo;
  #endif

  switch(tipo){
    case PROD:
      instanciaHilo(&hilo, id, fProductor);
    break;
    case CONS:
      instanciaHilo(&hilo, id, fConsumidor);
    break;
  }
}
/*---*/

/*Hilo productor*/
#ifdef __linux__
void instanciaHilo(pthread_t *hilo, int n_pc, void *(*funcion_hilo)(void *)){
#elif _WIN32
void instanciaHilo(DWORD *hiloId, int n_pc, void *(*funcion_hilo)(void *)){

  HANDLE hilo = CreateThread (
  NULL,       // Atributo de seguridad: Usar el de la thread actual
  0,          // Tamaño del stack. Usar el tamaño por defecto
  funcion_hilo, // Función inicial de la thread
  (LPVOID) n_pc,    // Datos a pasar a la thread
  0,          // Flags de creación
  hiloId
  );

#endif

  #ifdef __linux__
    if ( pthread_create( hilo, NULL, funcion_hilo, &n_pc) ) {
  #elif _WIN32
    if( elHilo == NULL){
  #endif
      printf("Error al crear el hilo.");
      abort();
    }

  #ifdef __linux__
    if ( pthread_join (*hilo, NULL) ) {
  #elif _WIN32
    if (WaitForSingleObject(elHilo, 0) == WAIT_FAILED){
  #endif
    printf("Error al iniciar el hilo.");
    abort();
  }
}
/*---*/
