#include <stdlib.h>
#include <stdio.h>
#include "keygen.h"
#include "bitwise.h"

char *random_key() { //выдает рандомный ключ
	char *a =malloc(7*sizeof(char));
	int i;
	for (i = 0; i < 8; i++)
		a[i] = rand() % 256;
	return a;
}

char *key_change(char *key_null) { // на вход поступает 56-битовый ключ, возвращается 64-битовый
	int map[56] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
	char *key_null_new = malloc(8 * sizeof(char));
	int i, j, num;
	char data;
	
	for(i = 0; i < 8; i++) {
		num = 0;
		for(j = 0; j < 7; j++) {
			data = bit_search(key_null, i * 7 + j);
			if(data == 1) 
				num++;
			bit_add(key_null_new, i * 8 + j, data);
		}
		if(num % 2 == 0) 
			bit_add(key_null_new, i * 8 + 7, 1);
		else 
			bit_add(key_null_new, i * 8 + 7, 0);
	}
	
	char *key_null_change = malloc(8 * sizeof(char));
	
	for (i = 0; i < 64; i++) {
		if(i % 8 != 7)
			bit_add(key_null_change, i, bit_search(key_null_new, map[i - (i/8)] - 1));
		else
			bit_add(key_null_change, i, bit_search(key_null_new, i));
	}

	free(key_null_new);
	
	return key_null_change;
}

char **keys_create(char *key_null) { //создается 16 ключей, для 16 циклов
	int map[48] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
	int move[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	char **keys = malloc(16 * sizeof(char *));
	int i, j;

	char *key_null_new = key_change(key_null);
	char *C = malloc(8 * sizeof(char)), *D = malloc(8 * sizeof(char));

	for (i = 0; i < 32; i++) {
		if(i % 8 != 7)
			bit_add(C, i - (i/8), bit_search(key_null_new, i));	
	}

	for (i = 32; i < 64; i++) {
		if(i % 8 != 7)
			bit_add(D, i - (i/8) - 28, bit_search(key_null_new, i));	
	}

	for (j = 0; j < 28; j++)
			printf("%d ", bit_search(D, j));
	printf("\n");

	for (i = 0; i < 16; i++) {
		cyclic_shift_right(C, move[i]);
		cyclic_shift_right(D, move[i]);
		keys[i] = malloc(6 * sizeof(char));
		for (j = 0; j < 48; j++) {
			if (map[j] > 32)
				bit_add(keys[i], j, bit_search(D, map[j] % 32 - 1));
			else
				bit_add(keys[i], j, bit_search(C, map[j] - 1));
		}
	}
	return keys;
}