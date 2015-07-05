#ifdef __linux__
  void *fConsumidor(void *n_cn){
    int *n_con = n_cn;
#elif _WIN32
  DWORD WINAPI funcionHilo (LPVOID n_cn){
    int n_con = *(int *)n_cn;
#endif
while(true){
  if(buff > 0 /*&& buff <= 100*/){
    sem_post(&mutex);
    buff--;
    ult_con = *n_con;
    sem_post(&vacio);
    sem_wait(&lleno);
  }else
    sem_wait(&mutex);
  sleep(1);
}


}
