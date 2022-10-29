/*Alessandro Salvato S201129*/

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int indice;
    int valore;
} tipo_matrice_compatta;

int** allocazione_matrice(int Num_righe, int Num_col);
void lettura_matrice_file_dim_note_interi (FILE *fp, int ***matrix, int tot_righe, int tot_colonne);
int verifica_matrice_simmetrica (int **matrix, int Num_righe, int Num_col);
int verifica_matrice_compatta_simmetrica(tipo_matrice_compatta **matrixcompatta, int *v, int Num_righe);
int accesso_matrice_compatta (tipo_matrice_compatta **matrixcompatta, int i_utente, int j_utente, int *v);
void deallocazione_matrice(int **matrice, int Num_righe);
void deallocazione_matrice_compatta(tipo_matrice_compatta **matrixcompatta, int Num_righe);

typedef enum {FALSE, TRUE} boolean;

int main(int argc, char *argv[])
{
    FILE *fp;
    int num_righe, num_colonne;
    int i, j, k, i_client, j_client;
    int **matrice = NULL;
    int *vett_not_zero;
    tipo_matrice_compatta **p_matrice_compatta = NULL; /*Ha R righe*/

    if (argc != 2)
    {
        printf("\nERRORE: Numero di parametri errati da linea di comando. Devono essere %d\n", argc);
        return EXIT_FAILURE;
    }

    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura\n", argv[1]);
        return EXIT_FAILURE;
    }

    fscanf(fp, "%d%d", &num_righe, &num_colonne);

    matrice = allocazione_matrice(num_righe, num_colonne);
    lettura_matrice_file_dim_note_interi(fp, &matrice, num_righe, num_colonne);
    fclose(fp);
    p_matrice_compatta = (tipo_matrice_compatta**)malloc(num_righe*sizeof(tipo_matrice_compatta));
    vett_not_zero = (int*)malloc(num_righe*sizeof(int));

    for (k=0; k<num_righe; k++)
    {
        vett_not_zero[k] = 0;
    }

    for (i=0; i<num_righe; i++)
    {
        for (j=0; j<num_colonne; j++)
        {
            if (matrice[i][j]!=0)
            {
                vett_not_zero[i]++;
            }
        }
        k=0;
        p_matrice_compatta[i] = (tipo_matrice_compatta*)malloc((vett_not_zero[i])*sizeof(tipo_matrice_compatta));
        for (j=0; j<num_colonne; j++)

        {
            if (matrice[i][j] != 0)
            {
                p_matrice_compatta[i][k].indice = j;
                p_matrice_compatta[i][k].valore = matrice[i][j];
                k++;
            }
        }
    }

    printf("\nInserisci le coordinata <i; j> per visualizzare l'elemento desiderato: ");
    scanf("%d%d", &i_client, &j_client);
    i_client--;
    j_client--;

    if ((i_client>=0) && (i_client<num_righe) && (j_client>=0) && (j_client<num_colonne))
    {
        printf("\nL'elemento <i; j> della matrice di input e': %d", matrice[i_client][j_client]);
        if (matrice[i_client][j_client] == accesso_matrice_compatta(p_matrice_compatta, i_client, j_client, vett_not_zero))
        {
            printf("\nAccesso valido nella matrice compatta\nL'elemento e' lo stesso\n");
        }
        else
        {
            printf("\nERRORE: Accesso non valido nella matrice compatta\n\aL'elemento non e' lo stesso\n");
        }
    }
    else
    {
        printf("\nDati inseriti non validi\n");
        system("PAUSE");
    }
    k = verifica_matrice_simmetrica(matrice, num_righe, num_colonne);
    j = verifica_matrice_compatta_simmetrica(p_matrice_compatta, vett_not_zero, num_righe);

    if((k  == 1) && (j  == 1))
    {
        printf("\nLa matrice e' simmetrica per ambo le rappresentazioni\n");
        system("PAUSE");
    }
    else
    {
        printf("\nERRORE: La matrice non e' simmetrica\n");
        system("PAUSE");
    }

    free(vett_not_zero);
    deallocazione_matrice(matrice, num_righe);
    deallocazione_matrice_compatta(p_matrice_compatta, num_righe);


    return EXIT_SUCCESS;
}

int** allocazione_matrice(int Num_righe, int Num_col)
{
    int i;
    int **matrice;

    matrice = (int **)malloc(Num_righe*sizeof(int*));
    if (matrice == NULL)
    {
        return (NULL);
    }
    for (i=0; i<Num_righe; i++)
    {
        matrice[i] = (int*)malloc(Num_col*sizeof(int));
        if (matrice[i] == NULL)
        {
            return (NULL);
        }
    }
    return(matrice);
}

void lettura_matrice_file_dim_note_interi (FILE *fp, int ***matrix, int tot_righe, int tot_colonne)
{
    int i, j;
    int **m;
    m = allocazione_matrice(tot_righe, tot_colonne);
    for (i=0; i<tot_righe; i++)
    {
        for (j=0; j<tot_colonne; j++)
        {
            fscanf(fp, "%d", &m[i][j]);
        }
    }

    *matrix = m;
}

int verifica_matrice_simmetrica (int **matrix, int Num_righe, int Num_col)
{
    int i, j, flag = 1;

    if (Num_righe!= Num_col)
    {
        flag = 0;
    }
    else
    {
        for (i=0; i<Num_righe && flag == 1; i++)
        {
            for (j=0; j<Num_col && flag == 1; j++)
            {
                if (i!=j)
                {
                    if (matrix[i][j]!= matrix[j][i])
                    {
                        flag = 0;
                    }
                }
            }
        }
    }

    return flag;
}

int accesso_matrice_compatta (tipo_matrice_compatta **matrixcompatta, int i_utente, int j_utente, int *v) /*devo passare anche il vettore num_diverso da zero*/
{
    int  j=0;
    boolean trovato = FALSE;

    while ((j<v[i_utente]) && (!trovato))
    {
        if(matrixcompatta[i_utente][j].indice == j_utente)
        {
            trovato = TRUE;
        }
        else
        {
            j++;
        }
    }
    if (trovato)
    {
        return(matrixcompatta[i_utente][j].valore);
    }
    else
    {
        return (0);
    }
}

int verifica_matrice_compatta_simmetrica(tipo_matrice_compatta **matrixcompatta, int *v, int Num_righe)
{
    int i=0, j, k, q;
    int flag;
    boolean trovato = TRUE;

    while ((i<Num_righe) && (trovato))
    {
        j=0;

        while ((j<v[i]) && (trovato))
        {
          if (i!=matrixcompatta[i][j].indice) /*Se e' sulla diagonale non lo considero e proseguo*/
          {
                k=0;
                q=0;
                while ((k<v[matrixcompatta[i][j].indice]) && (trovato))
                {
                     /*Se q rimane zero, vuol dire che in riga matrixcompatta[i][j].indice {ovvero la riga in cui deve esserci l'elemento simmetrico}*/
                    /*non c'è nemmeno un elemento simmetrico*/
                    if(i==matrixcompatta[matrixcompatta[i][j].indice][k].indice)
                    {
                        q++;
                        if(matrixcompatta[i][j].valore != matrixcompatta[matrixcompatta[i][j].indice][k].valore)
                        {
                            trovato = FALSE;
                        }
                        else
                        {
                            k++;
                        }
                    }
                    else
                    {
                        k++;
                    }
                }
                if (q==0)
                {
                    trovato = FALSE;
                }
          }
          j++;
        }
        i++;
    }

    if (trovato)
    {
        flag = 1;
        return (flag);
    }
    else
    {
        flag = 0;
        return (flag);
    }
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

void deallocazione_matrice_compatta(tipo_matrice_compatta **matrixcompatta, int Num_righe)
{
    int i;

    for (i=0; i<Num_righe; i++)
    {
        free(matrixcompatta[i]);
    }
    free(matrixcompatta);
}

