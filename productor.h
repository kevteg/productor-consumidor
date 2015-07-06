#if __linux__
  void *fProductor(void *n_pr){
    int *n_pro = n_pr;
#elif _WIN32
  DWORD WINAPI *fProductor(LPVOID n_pr){
  int *n_pro = (int *)n_pr;
#endif
  while(true){
    if( buff < (argumento[BUFFER] - 1)){
      down(MUTEX);
      buff++;
      ult_pro = *n_pro;
      up(MUTEX);
      up(LLENO);
      down(VACIO);
    }else
      up(MUTEX);
    dormir(1);
  }

}
