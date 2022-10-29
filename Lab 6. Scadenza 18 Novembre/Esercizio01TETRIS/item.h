#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#define LUNGHEZZA 35

typedef struct carriera
{
    int crediti;
    float media;
}tipo_carriera;

typedef struct studente
{
    char nome[LUNGHEZZA+1];
    char cognome[LUNGHEZZA+1];
    char matricola[LUNGHEZZA+1];
    tipo_carriera carriera;
    struct studente *succ;
} ITEM;

void StructITEMscan(ITEM **stud);
void StructITEMshow(ITEM *stud_corrente);
char* RendiMinuscolo (char *chiave, int dim_chiave);

#endif



