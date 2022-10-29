#include <stdio.h>
#include <stdlib.h>
#define MAX_RIGHE 20
#define MAX_COLONNE 20
/*Questo programma va bene solo per matrici quadrate*/
void lettura_matrice_file_dim_note_interi (FILE *fp, int matrix[][MAX_COLONNE], int tot_righe, int tot_colonne);

int main(int argc, char *argv[])
{
    FILE *fpi; /*puntatore al file di ingresso*/
    FILE *fpu; /*puntatore al file di uscita*/
    int matrice_ingresso[MAX_RIGHE][MAX_COLONNE];
    int num_righe;
    int num_colonne;
    int i, j, x, y;
    float numero;
    float somma;
    float quantita;
    float media;

    if (argc != 3) /*Controllo sul numero di parametri passati da linea di comando*/
    {
        printf("\nERRORE: Numero di parametri errato da linea di comando\n");
        return EXIT_FAILURE;
    }

    if ((fpi = fopen(argv[1], "r")) == NULL) /*Controllo sull'apertura corretta dei file*/
    {
        printf("\nERRORE nell'apertura del file %s in lettura", argv[1]);
        return EXIT_FAILURE;
    }

    if ((fpu = fopen(argv[2], "w")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in scrittura", argv[2]);
        return EXIT_FAILURE;
    }

    fscanf(fpi, "%d%d", &num_righe, &num_colonne); /*Acquisisco da file i primi due interi che corrispondono al numero di righe e di colonne della matrice*/

    lettura_matrice_file_dim_note_interi(fpi, matrice_ingresso, num_righe, num_colonne);

    for (i=0; i<num_righe; i++)
    {
        for (j=0; j<num_colonne; j++)
        {
            quantita = media = numero = somma = 0.0;
            for (x = i-1; x<= i+1; x++) /*Con le variabili x ed y faccio il controllo sugli 8 elementi contigui all'elemento della matrice di coordinate i e j*/
            {
                for (y = j-1; y<= j+1; y++)
                {
                    if ((x>=0) && (x<num_righe) && (y>=0) && (y<num_colonne)) /*Effettuo il controllo sulla validità delle coordinate x ed y: verifico che esse indichino un elemento che è all'INTERNO della matrice*/
                    {
                        if (!((x == i) && (y == j))) /*Nelle specifiche viene richiesto che, dato un elemento di coordinate i e j si effettui la media degli al più 8 elementi contigui.*/
                        {                              /*Non viene rischiesto che anche l'elemento di coordinate i e j faccia parte della media. Quindi SE NON E' vero che sto considerando il numero centrale ALLORA eseguo le operazioni che mi porteranno alla media*/
                            numero = matrice_ingresso[x][y];
                            somma += numero;
                            quantita++;
                        }
                    }
                }
            }
            media = (float)(somma/quantita);
            fprintf(fpu, "%.1f     ", media); /*Stampo i risultati sul file di uscita*/
        }
        fprintf(fpu, "\n");
    }
    printf("\nOperazione terminata con successo\n");
    system("PAUSE");
    fclose(fpi);
    fclose(fpu);
    return 0;
}

void lettura_matrice_file_dim_note_interi (FILE *fp, int matrix[][MAX_COLONNE], int tot_righe, int tot_colonne)
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
