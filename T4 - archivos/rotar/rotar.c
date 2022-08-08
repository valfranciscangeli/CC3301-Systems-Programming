//Trabajo realizado por Valeria Franciscangeli
//para CC3301 PSS Otono 2022

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SIZELIN 10


int main(int argc, char *argv[]) {
    // argc a largo menor a 4 no tendria intercambio
    if (argc<3) {
        fprintf(stderr, "Uso: %s <archivo> <l1> <l2> <l3> ...\n", argv[0]);
    exit(1);
  }
    //================= rotar =================
    
    char *nom= argv[1];                // El nombre del archivo
    FILE *f= fopen(nom, "r+");         // abrir archivo  
  
    int contador = 2;                  // contador de intercambios
    int nlinea = atoi(argv[2]);        // primera linea a cambiar
    int len = 10;                      // largo de linea del txt
  
    // crear buffers para guardar lineas
    char buf1[len+1];
    char buf2[len+1];
  
    // leemos el contenido con el que reemplazaremos la linea siguiente
    fseek(f, nlinea*len, SEEK_SET);
    fread(buf1, len, 1, f);
  
    contador++;
  
    while (contador<argc){
    
        nlinea = atoi(argv[contador]); // actualizamos linea siguiente
  
        // guardamos el contenido de la linea a cambiar
        fseek(f, nlinea*len, SEEK_SET);
        fread(buf2, len, 1, f);

        // cambiamos el contenido de la linea
        fseek(f, nlinea*len, SEEK_SET);
        fwrite(buf1, len, 1, f);

        // pasamos el contenido del buf 2 al buf 1
        strcpy(buf1, buf2);

        // aumentamos el contador
        contador++;

    }

    // cambiamos el contenido de la primera linea por el de la ultima
    nlinea=atoi(argv[2]);              // volvemos a la primera linea
    fseek(f, nlinea*len, SEEK_SET);
    fwrite(buf1, len-1, 1, f);
    
    return 0;
}
