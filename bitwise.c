#include "bitwise.h"

void bit_add(char *a, int m, char x) { //добавляет бит x в позицию m
	if(x == 1)
		a[(m / 8)] |= (1 <<  7 - (m % 8));
	else
		a[(m / 8)] &= ~(1 <<  7 - (m % 8));
} 

char bit_search(char *a, int m) { //возвращает значение бита m
	return ((1 << 7 - (m % 8))  &  a[(m / 8)]) >> 7 - (m % 8);
}

void cyclic_shift_left(char *a, int m) { //сдвигает на m бит влево
	int i, j;
	char b[4];
	for (j = 0; j < m; j++){

		for (i = 0; i < 4; i++)
			b[i] = bit_search(a, i * 8);
		
		for (i = 0; i < 4; i++)
			a[i] = a[i] << 1;
		
		bit_add (a, 27, b[0]);

		for (i = 0; i < 3; i++)
			bit_add(a, (i * 8)  + 7, b[i + 1]);
	}
}