// Trabajo de Valeria Vallejos Franciscangeli - Tarea 2 PSS Otoño 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elim.h"

void eliminar_espacios(char *s) {

    char *lec=s;
    char *esc=s;

    while(*lec != 0 ) {
        if (*lec != ' ') { 
            *esc = *lec;
            lec++;
        }else{
            *esc = *lec;
            lec++;
            while(*lec == ' ') {
                lec++;
            }
        }
        esc++;
    }
    *esc=0;
}

// cuenta cuantos son los espacios superfluos de el string
    int contar_espacios_sup(const char *str) {
        int contador = 0;
        while(*str != 0) {
            if(*str == ' ') {
                str++;
                while(*str == ' ') {
                    contador++;
                    str++;
                }
            }else{
                str++;
            }
        }
        return contador;
    }

char *eliminacion_espacios(const char *s) {

    char *res = malloc(strlen(s)+1-contar_espacios_sup(s)); // pedimos la memoria exacta que necesita el string final
    char *ptr=res;      //puntero a el inicio de res
    const char *lec=s;  //puntero que leera s

    while(*lec != 0 ) {
        if (*lec != ' ') {
            *ptr = *lec;
            lec++;
        }else{
            *ptr = *lec;
            lec++;
            while(*lec == ' ') {
                lec++;
            }
        }
        ptr++;
    }
    *ptr=0;  //agregamos el 0 que determina final de string

    return res;
}
