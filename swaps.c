#include <stdlib.h>
#include "swaps.h"

char *swapstart(char *block) { //Начальная перестановка
    char *zz = (char*)malloc(8 * sizeof(char));
    int table[8] = {2,4,6,8,1,3,5,7};
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((block[7 - j] & (1 << (8 - table[i]))) == 0) {zz[i] &= ~(1 << 7 - j);}
            else {zz[i] |= (1 << 7 - j);}
        }
    }
    return zz;
}

char *swapend (char *block) { //Конечная перестановка
    char *zz = (char*)malloc(8 * sizeof(char));
    int table[8] = {4,0,5,1,6,2,7,3};
    int i, j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if ((block[table[j]] & (1 << i)) == 0) {zz[i] &= ~(1 << 7 - j);}
            else {zz[i] |= (1 << 7 - j);}
        }
    }
    return zz;
}
