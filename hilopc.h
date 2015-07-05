


/*Creación del hilo*/
#ifdef __linux__
pthread_t crearHilo(int tipo, int *id){
  pthread_t hilo;
#elif _WIN32
DWORD* crearHilo(int tipo, int *num_ins){
  DWORD hilo;
#endif
    switch(tipo){
      case PRODUCTOR:
        instanciaHilo(&hilo, id, fProductor);
      break;
      case CONSUMIDOR:
        instanciaHilo(&hilo, id, fConsumidor);
      break;
      case GRAFICO:
        instanciaHilo(&hilo, NULL, nivelProducto);
      break;
    }

return hilo;
}

#ifdef __linux__
void instanciaHilo(pthread_t *hilo, int *parametro, void *(*funcion_hilo)(void *)){
#elif _WIN32
void instanciaHilo(DWORD *hiloId, int *parametro, void *(*funcion_hilo)(void *)){

  HANDLE hilo = CreateThread (
  NULL,       // Atributo de seguridad: Usar el de la thread actual
  0,          // Tamaño del stack. Usar el tamaño por defecto
  funcion_hilo, // Función inicial de la thread
  (LPVOID) parametro,    // Datos a pasar a la thread
  0,          // Flags de creación
  hiloId
  );
#endif
  #ifdef __linux__
    if (pthread_create(hilo, NULL, funcion_hilo, parametro)){
  #elif _WIN32
    if(hilo == NULL){
  #endif
      printf("Error al crear el hilo.");
      abort();
    }
}

#ifdef __linux__
  void iniciarHilo(pthread_t hilo){
#elif _WIN32
  void iniciarHilo(HANDLE hilo){
#endif
    #ifdef __linux__
      if ( pthread_join (hilo, NULL) ) {
    #elif _WIN32
      if (WaitForSingleObject(*hilo, 0) == WAIT_FAILED){
    #endif
        printf("Error al iniciar el hilo.");
        abort();
      }
}
void dormir(int tiempo){
  #ifdef __linux__
    sleep(tiempo);
  #elif _WIN32
    Sleep(tiempo*1000);
  #endif
}
void down(int tipo){
  switch(tipo){
    case MUTEX:
      #ifdef __linux__
        sem_wait(&mutex);
      #elif _WIN32

      #endif
    break;
    case LLENO:
      #ifdef __linux__
        sem_wait(&lleno);
      #elif _WIN32

      #endif
    break;
    case VACIO:
      #ifdef __linux__
        sem_wait(&vacio);
      #elif _WIN32

      #endif
    break;
  }
}
void up(int tipo){
  switch(tipo){
    case MUTEX:
      #ifdef __linux__
        sem_post(&mutex);
      #elif _WIN32

      #endif
    break;
    case LLENO:
      #ifdef __linux__
        sem_post(&lleno);
      #elif _WIN32

      #endif
    break;
    case VACIO:
      #ifdef __linux__
        sem_post(&vacio);
      #elif _WIN32

      #endif
    break;
  }
}
void iniciarSemaforos(){
  #ifdef __linux__
    sem_init(&mutex, 0, 1);
    sem_init(&lleno, 0, 0);
    sem_init(&vacio, 0, argumento[BUFFER]);
  #elif _WIN32

  #endif
}
void detenerSemaforos(){
  #ifdef __linux__
    sem_destroy(&mutex);
    sem_destroy(&lleno);
    sem_destroy(&vacio);
  #elif _WIN32

  #endif
}

/*---*/
