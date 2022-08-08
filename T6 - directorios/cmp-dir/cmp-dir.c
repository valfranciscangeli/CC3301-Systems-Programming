#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>

int subconjunto(char *path1, char *path2) {

  // sacamos stats del primer path
  struct stat st_path1;
  int rc1;
  rc1 = stat(path1, &st_path1);

  // sacamos stats del segundo path
  struct stat st_path2;
  int rc2;
  rc2 = stat(path2, &st_path2);

  // =========== Casos no existencia =========

  // caso 4:
  if (rc1 != 0) {
    printf("%s no existe\n", path1);
    exit(0);
  }

  //caso 3:
  if (rc2 != 0){ 
    printf("%s si existe, %s no existe\n", path1, path2);
    exit(0);
  }

  // =========== Casos archivo regular =========

  if (S_ISREG(st_path1.st_mode)) {    // si path 1 es regular
    if (S_ISREG(st_path2.st_mode)) {  // si path 2 tambien es regular

      // caso 2: comparamos tamaño
      if (st_path1.st_size != st_path2.st_size){
        printf("%s y %s son de distinto tamanno\n", path1, path2);
        exit(0);

      } else {// si llegan aqui es que tienen igual tamanno
        int size = st_path1.st_size;
        if (size <= 0){
          size = 1; // para no pedir buffer tamanno <= 0
        }
        
        // buffers
        char buff1[size];
        char buff2[size];
        
        // abrir los archivos para leer
        int fd1 = open(path1, O_RDONLY);
        int fd2 = open(path2, O_RDONLY); 
        
        // errores en al abrir el path
        if (fd1 == -1){ 
          perror(path1);
          exit(1);
        }
        if (fd2 == -1){ 
          perror(path2);
          exit(1);
        }
        
        // leemos el contenido y lo guardamos en el buffer
        read(fd1, buff1, st_path1.st_size);
        read(fd2, buff2, st_path2.st_size);
        
        // comparamos contenido
        int ret = memcmp(buff1, buff2, st_path1.st_size);
        
        // cerramos
        close(fd1);
        close(fd2);            
        
        // caso 1: contenidos diferentes
        if(ret != 0) {
          printf("Contenidos de %s y %s difieren\n", path1, path2);
          exit(0);
        } else {  // si llega aqui es porque cumple todas las condiciones (1)
          printf("Es subconjunto\n");
          exit(0);
        }
      }
    }
  }

  // =========== Casos es directorio ========= 

  // caso 6:
  if (S_ISDIR(st_path2.st_mode)){ 
    if (!(S_ISDIR(st_path1.st_mode))){
        printf("%s no es directorio, %s si es directorio\n", path1, path2);
        exit(0);
    }
  }

  // si el path1 es de un directorio
  if (S_ISDIR(st_path1.st_mode)) {
    DIR *dir = opendir(path1); // lo abrimos

    // error al entrar al directorio A (permisos)
    if (dir == NULL) {
      perror(path1);
      exit(1);
     }

    // caso 5: 
    if (!(S_ISDIR(st_path2.st_mode))){
      printf("%s es directorio, %s no es directorio\n", path1, path2);
      exit(0);
    }

    DIR *dir2 = opendir(path2); // lo abrimos

    // error al entrar al directorio B (permisos)
    if (dir2 == NULL) {
      perror(path2);
      exit(1);
    }

    for (struct dirent *entry = readdir(dir);
        entry != NULL;
        entry = readdir(dir)) {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
        continue;
      }

      // extendemos el path1
      char *path1_arch = malloc(strlen(path1)+strlen(entry->d_name)+2);
      strcpy(path1_arch, path1);
      strcat(path1_arch, "/");
      strcat(path1_arch, entry->d_name);

      // extendemos el path2
      char *path2_arch = malloc(strlen(path2)+strlen(entry->d_name)+2);
      strcpy(path2_arch, path2);
      strcat(path2_arch, "/");
      strcat(path2_arch, entry->d_name);

      subconjunto(path1_arch, path2_arch); // llamada recursiva

      // liberamos la memoria
      free(path1_arch);
      free(path2_arch);
    }

    closedir(dir);  // cerramos el directorio del path 1
    closedir(dir2); // cerramos el directorio del path 2
  }
  else {
    fprintf(stderr, "Archivo %s es de tipo desconocido\n", path1);
    exit(1);
  }

  return 0; // exito
}

// ================= main =================
int main(int argc, char *argv[]) {

  if (argc != 3) {
    fprintf(stderr, "uso: %s <arch|dir> <arch|dir>\n", argv[0]);
    exit(2);
  }

  // si los parametros estaban bien, llamamos a la funcion que recorre el path 1
  subconjunto(argv[1], argv[2]);

  return 0; // exito
}
