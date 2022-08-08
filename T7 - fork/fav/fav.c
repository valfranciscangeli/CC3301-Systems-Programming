#include <stdio.h>
#include <unistd.h> //fork
#include <stdlib.h> //exit
#include <sys/types.h> //pid_t
#include <sys/wait.h> //waitpid

#include "fav.h"

int favorables_par(int n, int sum, int rep, int p) {
  pid_t pids[p];         // arreglo con los pid de los hijos
  int in_fds[p];         // arreglo para guardar los resultados de los hijos
  int rep_hijos = rep/p; // cantidad de rep que hará cada hijo (suponemos div entera)
  
  for(int j=0; j<p; j++){ // aqui creamos p procesos hijos
    int fds[2];
    pipe(fds);
    init_rand_seed();     // llamamos a funcion para evitar igual semilla
    pids[j] = fork();     // creamos proceso hijo
    
    if(pids[j] == 0){     // estamos en el hijo
      close(fds[0]);      // en fds[0] se lee y el hijo solo escribe
      int fav_hijo = 0;   // aqui guardamos los casos favorables del hijo
      fav_hijo=favorables(n, sum, rep_hijos);     // usamos la version secuencial de favorables
      write(fds[1], &fav_hijo, sizeof(fav_hijo)); // escribimos el resultado en el pipe
      exit(0);           // se termina este proceso
    }
    else{ // estamos en el padre
      close(fds[1]); // solo leemos! cerramos el de escritura
      in_fds[j] = fds[0];
    }
  }
  // estamos en el padre porque los hijos hicieron exit
  int fav = 0;              // el total de casos fav por ahora es 0
  int fav_hijo;             // aqui guardamos el resultado del hijo i
  for(int j=0; j<p; j++){   // leemos el arreglo de resultados y sumamos
    leer(in_fds[j], &fav_hijo, sizeof(fav_hijo));  // usamos funcion leer
    fav += fav_hijo;        // aumentamos el contador de casos fav totales
    close(in_fds[j]);
    waitpid(pids[j], NULL, 0); // enterrar al hijo! para no tener zombies
  }
  return fav;
}
