#include <stdlib.h>
#include <stdio.h>
#include "keygen.h"
#include "bitwise.h"
#include "summ.h"
#include "swaps.h"


int k;

int main() {
	char str[10000];
	scanf("%s", str);
	char * key = random_key();
	printf("key : %s\n" key);
	char ** all_keys = keys_create(key);
	char ** blocks = blocks_break(str);
	char * hash;
	int i;
	for (i = 0; i < k; i++) {
		hash = blocks[i];
		blocks[i] = swapstart(blocks[i]);
		free(hash);
	}
	return 0;
}