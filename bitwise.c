#include "bitwise.h"

void bit_add(char *a, int m, char x) { //добавляет бит x в позицию m
	if(x == 1)
		a[(m / 8)] |= (1 << (m % 8));
	else
		a[(m / 8)] &= ~(1 << (m % 8));
} 

char bit_search(char *a, int m) { //возвращает значение бита m
	return ((1 << (m % 8))  &  a[(m / 8)]) >> (m % 8);
}