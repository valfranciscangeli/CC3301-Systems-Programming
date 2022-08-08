/*
 * Trabajo realizado por Valeria Vallejos Franciscangeli
 * CC3301 Otono 2022
 */
#include <stdio.h>
#include <stdlib.h>

#include "borrar-bits.h"

uint borrar_bits(uint x, uint pat, int len) {
    uint mask = ~(-1 << (len-1)<<1); 
    uint borrador = -1 << (len-1)<<1;
    for (int i =0;i< (sizeof(x)<<3)-len+1; i++) {
        if (((x >> i) & mask) == pat) {
            x = x & borrador;
		    borrador = ~((~borrador)<<len);
		    i+=len-1;
	    }
	    else {
	        borrador = ~((~borrador)<<1);
        }
    }
    return x;
}
