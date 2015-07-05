#ifdef __linux__
  void *fConsumidor(void *n_cn){
    int *n_con = n_cn;
#elif _WIN32
  DWORD WINAPI funcionHilo (LPVOID n_cn){
    int n_con = *(int *)n_cn;
#endif
while(true){
  if(buff > 0){
    up(MUTEX);
    sem_post(&mutex);
    buff--;
    ult_con = *n_con;
    up(VACIO);
    down(LLENO);
  }else
    down(MUTEX);
  dormir(1);
}
}
