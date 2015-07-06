#ifdef __linux__
  void *fConsumidor(void *n_cn){
    int *n_con = n_cn;
#elif _WIN32
  DWORD WINAPI *fConsumidor(LPVOID n_cn){
    int *n_con = (int *)n_cn;
#endif
while(true){
  if(buff > 1){
    down(MUTEX);
    buff--;
    ult_con = *n_con;
    up(MUTEX);
	up(VACIO);
    down(LLENO);
  }else
    up(MUTEX);
  dormir(1);
}

}
