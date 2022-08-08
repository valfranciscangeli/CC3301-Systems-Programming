// Trabajo realizado por Valeria Franciscangeli
// para CC3301 Otoño 2022

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "seleccion.h"

// ================================================

//funcion que libera la memoria de un nodo
void borrarNodo(Nodo *arbol){
    if (arbol!=NULL){
        borrarNodo(arbol->izq);
        arbol->izq=NULL;
        borrarNodo(arbol->der);
        arbol->der=NULL;
        free(arbol);
    }
}

//funcion que crea un nodo
Nodo *copiarNodo(int x, Nodo *izq, Nodo *der){
  Nodo *a = (Nodo*)malloc(sizeof(Nodo));
  a->x = x;
  a->izq = izq;
  a->der = der;
  return a;
}

// ================================================

int selprim(Nodo **pa, int k) {
    Nodo *a= *pa;

    //casos base
    if (a== NULL) return 0;

    if (k== 0) {   // debemos liberar memoria y dejar un arbol vacio (nulo)
        borrarNodo(a);
        *pa=NULL;
        return k;
    }

    //se encuentran k nodos a la izquierda
    int n_izq = selprim(&a->izq, k);

    if(n_izq == k){ //los k nodos estan en izq, sin la raiz
        Nodo *izq=a->izq;
        selprim(&a->der, 0); // se va arbol derecho
        free(a);    //liberamos la raiz
        *pa=izq;    // reemplazar raiz por arbol izquierdo
        return k;
    }

    if(n_izq == k-1){ //los k nodos estan en izq + raiz
        selprim(&a->der, 0);
        return k;
    }

    //se encuentran menos de k nodos a la izquierda
    int n_der = selprim(&a->der, k-n_izq-1);
    return n_izq+1+n_der;
}

// ============================================

Nodo *ultimos(Nodo *a, int *pk) {
    int k = *pk;
    
    //casos base:
    if (a==NULL){
        *pk=0;
        return NULL;
    }
    
    if (k==0){
        return NULL;
    }
    
    Nodo *a_der = ultimos (a->der, pk); 

    //se encuentran k nodos a la derecha

    int n_der = *pk;
    if(n_der == k){ //los k nodos estan en der, sin la raiz
        return a_der; 
    }

    if(n_der == k-1){ //los k nodos estan en derecha + raiz
        Nodo *copiaNodo = copiarNodo(a->x, NULL, a_der);
        *pk=k;
        return copiaNodo;
    }

    //se encuentran menos de k nodos a la derecha
    *pk = k-n_der-1;
    Nodo *a_izq =ultimos(a->izq, pk);
    Nodo *copiaNodo= copiarNodo(a->x, a_izq, a_der);
    *pk = n_der+1+*pk;
    copiaNodo->izq=a_izq;
    return copiaNodo;
}


