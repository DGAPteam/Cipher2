#ifndef CIPHER_SUMM_H
#define CIPHER_SUMM_H

char *Perestanovkap (char *);

char* expansion(char*);

char* keyxor(char *, char *, int);

char* transformation_s(char* );

void SWAP_block(char *, char *);

char **blocks_break(char *, int *);

#endif