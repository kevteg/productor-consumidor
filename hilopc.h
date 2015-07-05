


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
//printf("hilos[%d]\n", parametro);

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
/*---*/
