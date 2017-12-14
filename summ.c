#include "summ.h"
#include "bitwise.h"

char* expansion(char* m)//peredaetsya ukazatel' na ukazatel' na blok, function rasshireniya
{
    int i;
    char* pi = m;
    char* k = malloc(sizeof(char)*6) ;
    bit_add(k, 0, bit_search(pi,31));
    bit_add(k, 1, bit_search(pi,0));
    bit_add(k, 2, bit_search(pi,1));
    bit_add(k, 3, bit_search(pi,2));
    bit_add(k, 4, bit_search(pi,3));
    bit_add(k, 5, bit_search(pi,4));
        bit_add(k, 6, bit_search(pi,3));
        bit_add(k, 7, bit_search(pi,4));
        bit_add(k, 8, bit_search(pi,5));
        bit_add(k, 9, bit_search(pi,6));
        bit_add(k, 10, bit_search(pi,7));
        bit_add(k, 11, bit_search(pi,8));
    bit_add(k, 12, bit_search(pi,7));
    bit_add(k, 13, bit_search(pi,8));
    bit_add(k, 14, bit_search(pi,9));
    bit_add(k, 15, bit_search(pi,10));
    bit_add(k, 16, bit_search(pi,11));
    bit_add(k, 17, bit_search(pi,12));
        bit_add(k, 18, bit_search(pi,11));
        bit_add(k, 19, bit_search(pi,12));
        bit_add(k, 20, bit_search(pi,13));
        bit_add(k, 21, bit_search(pi,14));
        bit_add(k, 22, bit_search(pi,15));
        bit_add(k, 23, bit_search(pi,16));
    bit_add(k, 24, bit_search(pi,15));
    bit_add(k, 25, bit_search(pi,16));
    bit_add(k, 26, bit_search(pi,17));
    bit_add(k, 27, bit_search(pi,18));
    bit_add(k, 28, bit_search(pi,19));
    bit_add(k, 29, bit_search(pi,20));
        bit_add(k, 30, bit_search(pi,19));
        bit_add(k, 31, bit_search(pi,20));
        bit_add(k, 32, bit_search(pi,21));
        bit_add(k, 33, bit_search(pi,22));
        bit_add(k, 34, bit_search(pi,23));
        bit_add(k, 35, bit_search(pi,24));
    bit_add(k, 36, bit_search(pi,23));
    bit_add(k, 37, bit_search(pi,24));
    bit_add(k, 38, bit_search(pi,25));
    bit_add(k, 39, bit_search(pi,26));
    bit_add(k, 40, bit_search(pi,27));
    bit_add(k, 41, bit_search(pi,28));
        bit_add(k, 42, bit_search(pi,27));
        bit_add(k, 43, bit_search(pi,28));
        bit_add(k, 44, bit_search(pi,29));
        bit_add(k, 45, bit_search(pi,30));
        bit_add(k, 46, bit_search(pi,31));
        bit_add(k, 47, bit_search(pi,0));
    return k ;
}

char* keyxor(char *m, char *key) // bit change ne nujen vse realizovano zdes'
{
    int i ;
    char* gen ;
    gen = malloc(sizeof(char)*6) ;
    for (i = 0; i < 48; i ++)
        bit_add(gen, i, (bit_search(m,i) ^ bit_search(key,i))) ;
    return  gen ;
}

char* transformation_s(char* m) //peredaem ukazatel' na block
{
    char x, y;
    int i ;
    char *p ;
    p = malloc(sizeof(char)*4) ; // 1 char - 8 bit
    char S[8][64] =
    {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
    0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
    4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
    15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13},
    {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
    3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
    0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
    13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9},
    {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
    13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
    13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
    1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12},
    {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
    13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
    10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
    3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14},
    {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
    14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
    4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
    11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3},
    {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
    10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
    9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
    4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13},
    {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
    13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
    1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
    6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12},
    {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
    1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
    7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
    2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}};
    int j = 0, k , l;
    for (i = 0 ; i < 48; i += 6)
    {
        x = bit_search(m, i) + 2*(bit_search(m, i + 5)) ; // y - koordinata v S
        y = bit_search(m, i + 1) + 2*(bit_search(m, i+ 2)) + 4*(bit_search(m, i + 3) ) + 8*(bit_search(m , i + 4)) ; // o - koordinata v S
        l = S[i/6][x*16+y] ;
        for ( k = 0; k < 4; k ++)
        {
            bit_add(p, j + 3 - k, l % 2);
            l /= 2 ;
        }
        j += 4; // uvelichivayu na 4
    }
    return p ;
}

void SWAP_blocks(char **r, char **l)
{
    int i ;
    char *c ;
    c =  *r ;
    *r = *l ;
    *l = c ;
}

char **blocks_break(char *elements)
{
    int Nmax = 0, i, j;
    while (elements[Nmax] != 0x0 && elements[Nmax] != '\n')
    Nmax ++;
    if (Nmax % 8 == 0)
    k = Nmax / 8;
    else
    k = Nmax / 8 + 1;
    char **bloks = malloc(k * sizeof(char *));
    for (i = 0; i < k; i++) {
        bloks[i] = malloc(8 * sizeof(char));
        for (j = 0; j < 8; j++)
            if (i*8 + j < Nmax)
        bloks[i][j] = elements[i*8 + j];
        else
        bloks[i][j] = 0;
    }
    return bloks;
}
