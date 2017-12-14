#ifndef CIPHER_SUMM_H
#define CIPHER_SUMM_H

char* expansion(char*);

char* keyxor(char *, char *);

char* transformation_s(char* );

void SWAP_block(char *, char *);

char **blocks_break(char *);

#endif