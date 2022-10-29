#include <stdio.h>
#include <stdlib.h>
#define MAX_DIMENSIONE 10
#include <limits.h>

typedef enum {FALSE, TRUE} boolean;

void funzione (FILE *fp1, FILE *fp2, float **matrix_real, int dimensioni);

int main()
{
    FILE *fpr, *fpw;
    int dim_matrix;
    float matrice[MAX_DIMENSIONE][MAX_DIMENSIONE], new_matrice[MAX_DIMENSIONE][MAX_DIMENSIONE];
    int i, j;
    float num;
    int divisore = 10;
    boolean trovato;

    if ((fpr = fopen("matrice.txt", "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file 'matrice.txt' in lettura\n");
        return EXIT_FAILURE;
    }

    if ((fpw = fopen("esito.txt", "w")) == NULL)
    {
        printf("\nERRORE nell'apertura del file 'esito.txt' in scrittura\n");
        return EXIT_FAILURE;
    }

    fscanf(fpr, "%d", &dim_matrix);


    return 0;
}


void funzione (FILE *fp1, FILE *fp2, float **matrix_real, int dimensioni)
{
    struct numero_reale
    {
        int parte_intera;
        int parte_decimale;
    };


}
