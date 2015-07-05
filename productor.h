#if __linux__
  void *fProductor(void *n_pr){
    int *n_pro = n_pr;
#elif _WIN32
  DWORD WINAPI funcionHilo (LPVOID n_pr){
  int *n_pro = (int *)n_pr;
#endif
//int num = *n_pro;

  while(true){
    if(/*buff >= 0 &&*/ buff < 100){
      sem_post(&mutex);
      buff++;
      ult_pro = *n_pro;
      sem_post(&lleno);
      sem_wait(&vacio);
    }else
      sem_wait(&mutex);
    sleep(1);
  }
}
