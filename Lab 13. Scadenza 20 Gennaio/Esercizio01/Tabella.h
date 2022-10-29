#ifndef TAB_H_DEFINED
#define TAB_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#define LUNGHEZZA 10

typedef struct
{
    char nome_vertice[LUNGHEZZA+1];
}Item;

typedef struct symbtab *ST;

ST ST_Init(int n);
void ST_SCAN(ST t, char r[]);
void ST_Show(ST t);
void ST_Sort(ST t);
int Conversion_Word2Numb(ST t, char *a);
char* ConversionNumber2Word(ST t, int n);

#endif
