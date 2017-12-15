#include <stdlib.h>
#include <stdio.h>
#include "keygen.h"
#include "bitwise.h"
#include "summ.h"
#include "swaps.h"


int main() {
	int i = 0,j, k;
	char str[100000];
	int c;
	while ((c = getchar())!='\n') {
		str[i] = c;
		i++;
	}
	str[i] = 0x0;
	int m;
	char ** blocks = blocks_break(str, &m); 

	char * key = random_key();
	char ** all_keys = keys_create(key);
	printf("KEY :");
	for (i = 0; i < 6; i+=2)
		printf("%hX ", key[i]*256 + key[i+1]);
	printf("%hX ", key[6]*256);
	free(key);
	printf("\n");

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


	for (i = 0; i < m; i++)
		for (j = 0; j < 8; j+=2)
			printf("%hX ", blocks[i][j] * 256 + blocks[i][j+1]);

	printf("\n");

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



	for (i = 0; i < m; i++)
		for (j = 0; j < 8; j++)
			printf("%c", blocks[i][j]);
	printf("\n");
	

	for (i = 0; i < 16; i++)
		free(all_keys[i]);
	free(all_keys);
	for (i = 0; i < m; i++)
		free(blocks[i]);
	free(blocks);
	return 0;
}