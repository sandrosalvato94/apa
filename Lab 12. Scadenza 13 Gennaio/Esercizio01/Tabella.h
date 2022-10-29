#ifndef TABELLA_H_DEFINED
#define TABELLA_H_DEFINED
#define LUNGHEZZA 15

typedef struct
{
    char city[LUNGHEZZA+1];
    char regione[LUNGHEZZA+1];
}Item;

typedef struct tab *ST;

ST ST_Init(int n);
ST ST_Scan(FILE *Puntatore_File, ST t);
void ST_Show(ST t);
void ST_Sort(ST t);
int Scan_File(FILE *Puntatore_File, ST t, int *v, int *w, int *p);
Item Conversione_Number2City(ST t, int n);
void ItemSHOW(Item item);
void DeallocaST(ST t);

#endif
