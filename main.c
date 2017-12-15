#include <stdlib.h>
#include <stdio.h>
#include "keygen.h"
#include "bitwise.h"
#include "summ.h"
#include "swaps.h"


int main() {
	
	char ** blocks = malloc(sizeof(char*));
	blocks[0] = malloc(8*sizeof(char));
	blocks[0][0] = 1;
	blocks[0][1] = 35;
	blocks[0][2] = 69;
	blocks[0][3] = 103;
	blocks[0][4] = 137;
	blocks[0][5] = 171;
	blocks[0][6] = 205;
	blocks[0][7] = 239;

	char key[] = {18,105,91,201,183,183,248};
	char ** all_keys = keys_create(key);
	int i,j, k;
	blocks[0] = swapstart(blocks[0]);
	for(i = 0; i < 16; i++) {
		char * right, rightnull[4] = {blocks[0][4],blocks[0][5],blocks[0][6],blocks[0][7]};
		char * left = blocks[0];
		right = expansion(blocks[0]+4);
		right = keyxor(right,all_keys[i], 48);
		right = transformation_s(right);
		right = Perestanovkap(right);
		right = keyxor(right,left, 32);
		for (j = 0; j < 4; j++) {
			blocks[0][j] = rightnull[j];
			blocks[0][j+4] = right[j];
		}
	}
	for (j = 0; j < 4; j++) {
		char change_a;
		change_a = blocks[0][j];
		blocks[0][j] = blocks[0][j+4];
		blocks[0][j+4]= change_a;
	}
	blocks[0] = swapend(blocks[0]);
	for (k = 0; k < 8; k++){
			for(j = 0; j < 8; j++)
				printf("%d", bit_search(blocks[0], k*8+j));
		
			printf(" ");

		}
	printf("\n");

	blocks[0] = swapstart(blocks[0]);
	for (j = 0; j < 4; j++) {
		char change_a;
		change_a = blocks[0][j];
		blocks[0][j] = blocks[0][j+4];
		blocks[0][j+4]= change_a;
	}
	for(i = 0; i < 16; i++) {
		char * left, leftnull[4] = {blocks[0][0],blocks[0][1],blocks[0][2],blocks[0][3]};
		char * right = blocks[0]+4;
		left = expansion(blocks[0]);
		left = keyxor(left,all_keys[15-i], 48);
		left = transformation_s(left);
		left = Perestanovkap(left);
		left = keyxor(left,right, 32);
		for(j = 0; j < 4; j++) {
			blocks[0][j + 4] = leftnull[j];
			blocks[0][j] = left[j]; 
		}
	}
	blocks[0] = swapend(blocks[0]);
	for (i = 0; i < 8; i++)
		printf("%d ", blocks[0][i]);
	printf("\n");;
	return 0;
}