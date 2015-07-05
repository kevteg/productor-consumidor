#if __linux__
  void *fProductor(void *n_pr){
    int *n_pro = n_pr;
#elif _WIN32
  DWORD WINAPI funcionHilo (LPVOID n_pr){
  int *n_pro = (int *)n_pr;
#endif
  while(true){
    if( buff < 100){
      up(MUTEX);
      buff++;
      ult_pro = *n_pro;
      up(LLENO);
      down(VACIO);
    }else
      down(MUTEX);
    dormir(1);
  }
}
