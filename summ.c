void bit_add(char *a, int m, char x) { //добавляет бит x в позицию m
	if(x == 1)
		a[(m / 8)] |= (1 <<  7 - (m % 8));
	else
		a[(m / 8)] &= ~(1 <<  7 - (m % 8));
}

char bit_search(char *a, int m) { //возвращает значение бита m
	return ((1 << 7 - (m % 8))  &  a[(m / 8)]) >> 7 - (m % 8);
}

void bit_change(char** m/*Указатель на указатель на чар*/, char** mk/*Указатель на указатель на ключ*/, int l/*Номер шифруемого блока*/) //правый полублок
{
    int i ;
    for (i = 0; i < 8; i ++)
        if (i>4)
            *(*m + i) ^= *(*mk + i) ;
}

char* expansion(char**m)//Передается указатель на указатель на блок, функция расширения
{
    int i;
    char* pi = m[4];
    char* k = (char*)malloc(sizeof(char)*6) ;
    bit_add(k, 0, bit_search(pi,31));
    bit_add(k, 1, bit_search(pi,0));
    bit_add(k, 2, bit_search(pi,1));
    bit_add(k, 3, bit_search(pi,2));
    bit_add(k, 4, bit_search(pi,3));
    bit_add(k, 5, bit_search(pi,4));
        bit_add(k, 6, bit_search(pi,3));
        bit_add(k, 7, bit_search(pi,4));
        bit_add(k, 8, bit_search(pi,5));
        bit_add(k, 9, bit_search(pi,6));
        bit_add(k, 10, bit_search(pi,7));
        bit_add(k, 11, bit_search(pi,8));
    bit_add(k, 12, bit_search(pi,7));
    bit_add(k, 13, bit_search(pi,8));
    bit_add(k, 14, bit_search(pi,9));
    bit_add(k, 15, bit_search(pi,10));
    bit_add(k, 16, bit_search(pi,11));
    bit_add(k, 17, bit_search(pi,12));
        bit_add(k, 18, bit_search(pi,11));
        bit_add(k, 19, bit_search(pi,12));
        bit_add(k, 20, bit_search(pi,13));
        bit_add(k, 21, bit_search(pi,14));
        bit_add(k, 22, bit_search(pi,15));
        bit_add(k, 23, bit_search(pi,16));
    bit_add(k, 24, bit_search(pi,15));
    bit_add(k, 25, bit_search(pi,16));
    bit_add(k, 26, bit_search(pi,17));
    bit_add(k, 27, bit_search(pi,18));
    bit_add(k, 28, bit_search(pi,19));
    bit_add(k, 29, bit_search(pi,20));
        bit_add(k, 30, bit_search(pi,19));
        bit_add(k, 31, bit_search(pi,20));
        bit_add(k, 32, bit_search(pi,21));
        bit_add(k, 33, bit_search(pi,22));
        bit_add(k, 34, bit_search(pi,23));
        bit_add(k, 35, bit_search(pi,24));
    bit_add(k, 36, bit_search(pi,23));
    bit_add(k, 37, bit_search(pi,24));
    bit_add(k, 38, bit_search(pi,25));
    bit_add(k, 39, bit_search(pi,26));
    bit_add(k, 40, bit_search(pi,27));
    bit_add(k, 41, bit_search(pi,28));
        bit_add(k, 42, bit_search(pi,27));
        bit_add(k, 43, bit_search(pi,28));
        bit_add(k, 44, bit_search(pi,29));
        bit_add(k, 45, bit_search(pi,30));
        bit_add(k, 46, bit_search(pi,31));
        bit_add(k, 47, bit_search(pi,0));
    return k ;
}

void blocks_break(char *elements, int maxN)//Разбивание исходного текста на блоки
{                                               // maxN - Количество элементов во входном потоке
    int i ;
    int l = maxN - (maxN/8)*8 ;
    for (i = maxN; i < maxN +(8-l) ; i ++)
        *(elements+i) = 0 ;
    maxN += l ;
    char **block ;
    block = (char**)malloc(sizeof(char)*(maxN/8)) ;
    for (i = 0; i < maxN/8; i ++)
        block[i] = elements+i*8 ;
}
