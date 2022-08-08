#include <string.h>

void sort(char **noms, int n) {
  char **ult= &noms[n-1];
  char **p= noms;
  while (p<ult) {
  
    ////////////////////////////////////////////
    // Comienza el codigo que Ud. debe modificar
    ////////////////////////////////////////////
    
    char *p1 = p[0];
    char *p2 = p[1];
    int cntp1 = 0;
    int cntp2 = 0;
    while (*p1 != 0){
        if(*p1 == ' ') {
          cntp1++;
          }
        p1++;
    }
    while (*p2 != 0){
        if(*p2 == ' ') {
          cntp2++;
          }
        p2++;
    }
    
    int rc = cntp1 > cntp2;

    ////////////////////////////////////////////
    // Fin del codigo que Ud. debe modificar
    ////////////////////////////////////////////
    
    if (rc<=0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= noms;
    }
  }
}
