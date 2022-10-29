#include <stdio.h>
#include <stdlib.h>
#define MAX 200
#include <string.h>
#define F_INTERI "vettore_interi.txt"
#define F_STRINGHE "vettore_stringhe.txt"
#include <ctype.h>
#define ERR_FILE "ERRORE nell'apertura del file"
#define MAX_CARAT 50

/*Versione con interi

item* Lettura_dati_file(FILE *Puntaore_file, item *v);
void MergeSort (item *vett, int indice_inizio, int indice_fine);
void MergeInt (item *vett, int indice_inizio, int indice_intermedio, int indice_fine);

typedef int item;

int main()
{
    item *vettore;
    char nome_file[MAX];
    FILE *fp;
    int num_dati;
    int i;


    printf("\nSu quale file di testo si desidera lavorare?\n");
    scanf("%s", nome_file);

    if ((fp = fopen(nome_file, "r")) == NULL)
    {
        printf("\n%s\n", ERR_FILE);
        return EXIT_FAILURE;
    }

    fscanf(fp, "%d", &num_dati);

    vettore = (item*)malloc(num_dati*sizeof(item));
    vettore = Lettura_dati_file(fp, vettore);

    fclose(fp);
    MergeSort(vettore, 0, num_dati-1, nome_file);

    for (i=0; i<num_dati; i++)
    {
        printf("\n%d", vettore[i]);
    }

    free(vettore);
    return EXIT_SUCCESS;

}

item* Lettura_dati_file(FILE *Puntaore_file, item *v)
{
    int i;

    i=0;
    while ((fscanf(Puntaore_file, "%d", &v[i])) != EOF)
    {
        i++;
    }

    return (v);
}

void MergeSort (item *vett, int indice_inizio, int indice_fine)
{
    int indice_medio = (indice_inizio+indice_fine)/2;

    if (indice_fine <= indice_inizio)
    {
        return;
    }
    MergeSort(vett, indice_inizio, indice_medio);
    MergeSort(vett, indice_medio+1, indice_fine);
    MergeInt(vett, indice_inizio, indice_medio, indice_fine);
}

void MergeInt(item *vett, int indice_inizio, int indice_intermedio, int indice_fine)
{
    int i, j, k;
    item vettSX[MAX];

    i = indice_inizio; j = indice_intermedio+1;
    for (k = indice_inizio; k <= indice_fine; k++)
    {
        if (i > indice_intermedio)
        {
            vettSX[k] = vett[j++];
        }
        else
        {
            if (j > indice_fine)
            {
               vettSX[k] = vett[i++];
            }
            else
            {
                if ((vett[i] < vett[j]) || ((vett[i] == vett[j])))
                {
                    vettSX[k] = vett[i++];
                }
                else
                {
                    vettSX[k] = vett[j++];
                }
            }
        }
    }

    for ( k = indice_inizio; k <= indice_fine; k++ )
    {
        vett[k] = vettSX[k];
    }
return;

*/


/*Versione con Stringhe */

typedef char* item;

item RendiMinuscolo(item parola, int lunghezza_parola);
item* Alloca_testo_file (FILE *Puntatore_file, int Num_righe);
void MergeSort (item *vett, int indice_inizio, int indice_fine);
void MergeChar (item *vett, int indice_inizio, int indice_intermedio, int indice_fine);
void deallocazione_matrice(item *vett, int Num_righe);

int main ()
{
    FILE *fp;
    char nome_file[MAX];
    item *matrice;
    int num_righe;
    int i;

    printf("\nInserisci il nome del file con il quale vuoi lavorare:\n");
    scanf("%s", nome_file);


    if ((fp = fopen("vettore_stringhe.txt", "r")) == NULL)
    {
        printf("\n%s\n", ERR_FILE);
    }

    fscanf(fp, "%d", &num_righe);

    matrice = Alloca_testo_file(fp, num_righe);
    fclose(fp);

    MergeSort(matrice, 0, num_righe-1);

    for (i=0; i<num_righe; i++)
    {
        printf("\n%s\n", matrice[i]);
    }

    deallocazione_matrice(matrice, num_righe);
    system("PAUSE");

    return EXIT_SUCCESS;
}


/*Funzioni*/
item* Alloca_testo_file (FILE *Puntatore_file, int Num_righe)
{
    char riga[MAX_CARAT+1];
    int i=0;
    item *matrx;

    matrx = (item*)malloc(Num_righe*sizeof(item));

    while((fscanf(Puntatore_file, "%s", riga)) != EOF)
    {
        matrx[i] = strdup(riga);
        i++;
    }

    return(matrx);
}

char* RendiMinuscolo(char *parola, int lunghezza_parola)
{
    int i;

    for (i=0; i<lunghezza_parola; i++)
    {
        parola[i] = tolower(parola[i]);
    }
    return(parola);
}

void MergeSort (item *vett, int indice_inizio, int indice_fine)
{
    int indice_medio = (indice_inizio+indice_fine)/2;

    if (indice_fine <= indice_inizio)
    {
        return;
    }
    MergeSort(vett, indice_inizio, indice_medio);
    MergeSort(vett, indice_medio+1, indice_fine);
    MergeChar(vett, indice_inizio, indice_medio, indice_fine);
}


void MergeChar (item *vett, int indice_inizio, int indice_intermedio, int indice_fine)
{
    int i = indice_inizio, j = indice_intermedio+1, k;
    item vett_ordinato[MAX];
    item w1, w2;

    for (k=indice_inizio; k<=indice_fine; k++)
    {
       if (i > indice_intermedio) /*Se l'indice del vett SX supera il limite allora esso è già ordinato. Considero quindi il vett DX*/
       {
           vett_ordinato[k] = strdup(vett[j]);
           j++;
       }
       else /*Se l'indice del vett Sx non supera il limite*/
       {
           if (j > indice_fine) /*Verifico che non sia l'indice del vett Dx ad aver superato il suo limite*/
           { /*Perchè se j supera indice_fine allora devo ancora ordinare il vettore Sx*/
               vett_ordinato[k] = strdup(vett[i]);
               i++;
           }
               else /*Se nessuno degli indici dei due vettori supera il proprio limite*/
               {
                   w1 = strdup(vett[i]); /*Mi servono poichè le stringhe possono contenere caratteri maiuscoli e minuscoli...*/
                   w2 = strdup(vett[j]); /*Salvo in w1 e w2 le due parole che sto confrontando, trasformando però tutto in minuscolo, preservando l'ordine reale*/
                   w1 = RendiMinuscolo(w1, strlen(w1));
                   w2 = RendiMinuscolo(w2, strlen(w2));

                   if (((strcmp(w1, w2)) < 0) || ((strcmp(w1, w2) == 0))) /*Verifico se l'elemento del vett SX...*/
                   { /*...è più piccolo o al più uguale di quello destro. Se è cosi lo salvo nel vettore(matrice) composto*/
                       vett_ordinato[k] = strdup(vett[i]);
                       i++;
                   }
                   else /*Se è l'elemento j di vettDX ad essere più piccolo (considerare l'uguaglianza è inutile), pongo l'elemento nel vettore risultante*/
                   {
                       vett_ordinato[k] = strdup(vett[j]);
                       j++;
                   }
                   free(w1);
                   free(w2);
               }
        }
    } /*fine for*/

    for (k=indice_inizio; k<= indice_fine; k++) /*Copio gli elementi ordinati nel vettore di partenza*/
    {
        vett[k] = vett_ordinato[k];
    }
}

void deallocazione_matrice(item *vett, int Num_righe)
{
    int i;

    for (i=0; i<Num_righe; i++)
    {
        free(vett[i]);
    }
    free(vett);
}
