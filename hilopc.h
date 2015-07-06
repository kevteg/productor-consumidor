


/*Creación del hilo*/
#ifdef __linux__
pthread_t crearHilo(int tipo, int *id){
  pthread_t hilo;
#elif _WIN32
HANDLE crearHilo(int tipo, int *id){
  HANDLE hilo;
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
void instanciaHilo(HANDLE *hilo, int *parametro, void *(*funcion_hilo)(void *)){
  DWORD hiloId;	
  HANDLE  mhilo = CreateThread (
  NULL,       // Atributo de seguridad: Usar el de la thread actual
  0,          // Tamaño del stack. Usar el tamaño por defecto
  *funcion_hilo, // Función inicial de la thread
  (LPVOID) parametro,    // Datos a pasar a la thread
  0,          // Flags de creación
  &hiloId
  );
  *hilo = mhilo;
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
      if (WaitForSingleObject(hilo, INFINITE) == WAIT_FAILED){
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
		WaitForSingleObject( 
            mutex,  
            0L);
      #endif
    break;
    case LLENO:
      #ifdef __linux__
        sem_wait(&lleno);
      #elif _WIN32
		WaitForSingleObject( 
            lleno,  
            0L);
      #endif
    break;
    case VACIO:
      #ifdef __linux__
        sem_wait(&vacio);
      #elif _WIN32
		WaitForSingleObject( 
            vacio,  
            0L);
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
		ReleaseSemaphore( 
                        mutex,  
                        1,            //Sumar 1
                        NULL);
      #endif
    break;
    case LLENO:
      #ifdef __linux__
        sem_post(&lleno);
      #elif _WIN32
		ReleaseSemaphore( 
                        lleno,  
                        1,            //Sumar 1
                        NULL);
      #endif
    break;
    case VACIO:
      #ifdef __linux__
        sem_post(&vacio);
      #elif _WIN32
		ReleaseSemaphore( 
                        vacio,  
                        1,            //Sumar 1
                        NULL);
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
	mutex = CreateSemaphore( 
        NULL,           
        1,  // Conteo inicial
        1,  // Conteo m�ximo
        NULL); 
    lleno = CreateSemaphore( 
        NULL,           
        0,  // Conteo inicial
        argumento[BUFFER],  // Conteo m�ximo
        NULL);     
    vacio = CreateSemaphore( 
        NULL,           
        argumento[BUFFER],  // Conteo inicial
        argumento[BUFFER],  // Conteo m�ximo
        NULL);     
  #endif
}
void detenerSemaforos(){
  #ifdef __linux__
    sem_destroy(&mutex);
    sem_destroy(&lleno);
    sem_destroy(&vacio);
  #elif _WIN32
	CloseHandle(mutex);
	CloseHandle(lleno);
	CloseHandle(vacio);
  #endif
}

/*---*/
