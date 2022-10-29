/*Alessandro Salvato S201129*/
#include <stdio.h>
#include <stdlib.h>

int** allocazione_matrice (int Num_righe, int Num_col);
void prodotto_matriciale(int **m1, int **m2, int **mp, int Num_righe1, int Num_righe2, int Num_col1, int Num_col2);
void lettura_matrice_file_dim_note_interi (FILE *fp, int **matrix, int tot_righe, int tot_colonne);
void deallocazione_matrice(int **matrice, int Num_righe);
void scrivi_matrice_in_file(FILE *Puntatore_file, int **matrice, int Num_righe, int Num_colonne);

int main(int argc, char *argv[])
{
    FILE *fm1;
    FILE *fm2;
    FILE *fmu;
    int **matrice1 = NULL, **matrice2 = NULL, **matrice_prodotto = NULL;
    int num_righe1, num_colonne1, num_righe2, num_colonne2, i, j;

    if (argc != 3)
    {
        printf("\nERRORE, numero di parametri errati da linea di comando\n");
        return EXIT_FAILURE;
    }

    if ((fm1 = fopen(argv[1], "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura\n", argv[1]);
        return EXIT_FAILURE;
    }

    if ((fm2 = fopen(argv[2], "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura\n", argv[2]);
        return EXIT_FAILURE;
    }

    if ((fmu = fopen("matrice_prodotto.txt", "w")) == NULL)
    {
        printf("\nERRORE nell'apertura del file matrice_prodotto.txt in scrittura\n");
        return EXIT_FAILURE;
    }

    fscanf(fm1, "%d%d", &num_righe1, &num_colonne1);
    fscanf(fm2, "%d%d", &num_righe2, &num_colonne2);

    if (num_colonne1 != num_righe2)
    {
        printf("\nLe dimensioni delle due matrici non ne consentono il prodotto\n");
    }
    else
    {
        matrice1 = allocazione_matrice(num_righe1, num_colonne1);
        matrice2 = allocazione_matrice(num_righe2, num_colonne2);
        matrice_prodotto = allocazione_matrice(num_righe1, num_colonne2);
        lettura_matrice_file_dim_note_interi(fm1, matrice1, num_righe1, num_colonne1);
        lettura_matrice_file_dim_note_interi(fm2, matrice2, num_righe2, num_colonne2);
        fclose(fm1);
        fclose(fm2);
        prodotto_matriciale(matrice1, matrice2, matrice_prodotto, num_righe1, num_righe2, num_colonne1, num_colonne2);
        fprintf(fmu, "%d %d\n", num_righe1, num_colonne2);
        scrivi_matrice_in_file(fmu, matrice_prodotto, num_righe1, num_colonne2);
        fclose(fmu);
        deallocazione_matrice(matrice1, num_righe1);
        deallocazione_matrice(matrice2, num_righe2);
        deallocazione_matrice(matrice_prodotto, num_righe1);
    }

    return 0;
}

int** allocazione_matrice(int Num_righe, int Num_col)
{
    int i;
    int **matrice;

    matrice = (int **)malloc(Num_righe*sizeof(int*));
    for (i=0; i<Num_righe; i++)
    {
        matrice[i] = (int*)malloc(Num_col*sizeof(int));
    }
    return(matrice);
}

void lettura_matrice_file_dim_note_interi (FILE *fp, int **matrix, int tot_righe, int tot_colonne)
{
    int i, j;
    for (i=0; i<tot_righe; i++)
    {
        for (j=0; j<tot_colonne; j++)
        {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }
    return;
}

void deallocazione_matrice(int **matrice, int Num_righe)
{
    int i;

    for (i=0; i<Num_righe; i++)
    {
        free(matrice[i]);
    }
    free(matrice);
}

void prodotto_matriciale(int **m1, int **m2, int **mp, int Num_righe1, int Num_righe2, int Num_col1, int Num_col2)
{
    int i, j, t;
    int somma;

    for (i=0; i<Num_righe1; i++)
    {
        for(j=0; j<Num_col2; j++)
        {
        somma = 0;
            for (t=0; t<Num_righe2; t++)
            {
                somma += m1[i][t]*m2[t][j];
            }
        mp[i][j] =  somma;
        }
    }

}

void scrivi_matrice_in_file(FILE *Puntatore_file, int **matrice, int Num_righe, int Num_colonne)
{
    int i, j;

    for(i=0; i<Num_righe; i++)
    {
        for (j=0; j<Num_colonne; j++)
        {
            fprintf(Puntatore_file, "%d ", matrice[i][j]);
        }
        fprintf(Puntatore_file,"\n");
    }
}
