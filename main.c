#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "keygen.h"
#include "bitwise.h"
#include "summ.h"
#include "swaps.h"

void print (char * s, int a) {
	int m;
	if (a == 1)
		m = 8*bit_search(s,0) + 4*bit_search(s,1) + 2*bit_search(s,2) + bit_search(s,3);
	else
		m = 8*bit_search(s,4) + 4*bit_search(s,5) + 2*bit_search(s,6) + bit_search(s,7);
	switch (m) {
		case 15 :
			printf("F");
			break;
		case 14 :
			printf("E");
			break;
		case 13 :
			printf("D");
			break;
		case 12 :
			printf("C");
			break;
		case 11 :
			printf("B");
			break;
		case 10 :
			printf("A");
			break;
		default :
			printf("%d", m);
	}
}

int main() {
	int i = 0,j, k;
	printf("Введите сообщение:\n");
	char str[100000];
	int c;
	while ((c = getchar())!='\n') {
		str[i] = c;
		i++;
	}
	str[i] = 0x0;
	int m, d;
	//Разбиение на блоки
	char ** blocks = blocks_break(str, &m); 

	srand(time(NULL));
	char * key[3];
	for (d = 0; d < 3; d++) {//TripleDES
		//Создание ключа
		key[d] = random_key();
		char ** all_keys = keys_create(key[d]);
	
		printf("KEY%d :", d + 1);
		for (i = 0; i < 7; i++) {
			print(key[d] + i, 1);
			print(key[d] + i, 2);
			printf(" ");
		}
		printf("\n");

		#pragma omp parallel for
		for (k = 0; k < m; k++) {//шифрование
			char * hash;
			hash = blocks[k];
			blocks[k] = swapstart(blocks[k]);
			free(hash);
			for(i = 0; i < 16; i++) {
				char * right, rightnull[4] = {blocks[k][4],blocks[k][5],blocks[k][6],blocks[k][7]};
				char * left = blocks[k];
			
				right = expansion(blocks[k]+4);
			
				hash = right;
				right = keyxor(right,all_keys[i], 48);
				free(hash);
			
				hash =right;
				right = transformation_s(right);
				free(hash);

				hash = right;
				right = Perestanovkap(right);
				free(hash);

				hash = right;
				right = keyxor(right,left, 32);
				free(hash);

				for (j = 0; j < 4; j++) {
					blocks[k][j] = rightnull[j];
					blocks[k][j+4] = right[j];
				}

				free(right);
			}
			for (j = 0; j < 4; j++) {
				char change_a;
				change_a = blocks[k][j];
				blocks[k][j] = blocks[k][j+4];
				blocks[k][j+4]= change_a;
			}

			hash = blocks[k];
			blocks[k] = swapend(blocks[k]);
			free(hash);
		}
		for (i = 0; i < 16; i++)
			free(all_keys[i]);
		free(all_keys);
	}
	//вывод
	printf("Зашифрованное сообщение в шестанцатиричной системе\n");
	for (i = 0; i < m; i++)
		for (j = 0; j < 8; j++) {
			print(blocks[i] + j, 1);
			print(blocks[i] + j, 2);
			printf(" ");
		}

	printf("\n");
	for (d = 2; d >= 0; d--) {//TripleDES
		char ** all_keys = keys_create(key[d]);	
		#pragma omp parallel for
		for (k = 0; k < m; k++) {//Расшифровка
			
			char * hash;
		
			hash = blocks[k];
			blocks[k] = swapstart(blocks[k]);
			free(hash);

			for (j = 0; j < 4; j++) {
				char change_a;
				change_a = blocks[k][j];
				blocks[k][j] = blocks[k][j+4];
				blocks[k][j+4]= change_a;
			}
			for(i = 0; i < 16; i++) {
				char * left, leftnull[4] = {blocks[k][0],blocks[k][1],blocks[k][2],blocks[k][3]};
				char * right = blocks[k]+4;
			
				left = expansion(blocks[k]);
			
				hash = left;
				left = keyxor(left,all_keys[15-i], 48);
				free(hash);

				hash = left;
				left = transformation_s(left);
				free(hash);

				hash = left;
				left = Perestanovkap(left);
				free(hash);

				hash = left;
				left = keyxor(left,right, 32);
				free(hash);

				for(j = 0; j < 4; j++) {
					blocks[k][j + 4] = leftnull[j];
					blocks[k][j] = left[j]; 
				}
				free(left);
			}

			hash = blocks[k];
			blocks[k] = swapend(blocks[k]);
			free(hash);
		}
		
		for (i = 0; i < 16; i++)
			free(all_keys[i]);
		free(all_keys);
	}

	printf("Ваше сообщение:\n");
	for (i = 0; i < m; i++)
		for (j = 0; j < 8; j++)
			printf("%c", blocks[i][j]);
	printf("\n");
	
	for (i = 0; i < 3; i++)
		free(key[i]);
	
	for (i = 0; i < m; i++)
		free(blocks[i]);
	free(blocks);
	return 0;
}
