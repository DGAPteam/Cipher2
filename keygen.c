#include <stdlib,h>
#include "keygen.h"
#include "bitwise.h"

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
	//int map[48]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
	char **keys = malloc(16 * sizeof(char *));
	int i;
	char *key_null_new = key_change(key_null);
	char *C = malloc(3 * sizeof(char)), *D = malloc(3 * sizeof(char));
	return keys;
}