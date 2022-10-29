#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CARAT 4
#define LUNGHEZZA 100

int cerca_spazio_vuoto_nel_vettore (int vett[], int dimensione_vettore, int num_vuoto);

typedef struct
{
    char parola_ricorrente[MAX_CARAT+1];
    int dim_parola_ricorrente;
    int num_ricorrenze;
    int pos_parola_ricorrente[300];
} tipo_ricorrenza;

typedef enum {FALSE, TRUE} boolean;

int main(int argc, char *argv[])
{
    FILE *fpt;
    FILE *fpp;
    int num_parole, pos_parola, i, j, n, tot_carat, dim_parola, dim_riga;
    tipo_ricorrenza ricorrenza[300];
    char riga[LUNGHEZZA+1], riga2[MAX_CARAT+1];
    char parola[LUNGHEZZA+1];
    boolean finito;

    if (argc != 3)
    {
        printf("\nERRORE: Numero di parametri errati da linea di comando\n");
        return EXIT_FAILURE;
    }

    if ((fpt = fopen(argv[1], "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura\n", argv[1]);
        return EXIT_FAILURE;
    }

    if ((fpp = fopen(argv[2], "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura\n", argv[2]);
        return EXIT_FAILURE;
    }

    fscanf(fpp, "%d%*c", &num_parole);
    i=0;
    while ((fgets(riga2, MAX_CARAT+1, fpp)) != NULL)
    {
        sscanf(riga2, "%s", ricorrenza[i].parola_ricorrente);
        ricorrenza[i].dim_parola_ricorrente = strlen(ricorrenza[i].parola_ricorrente);
        ricorrenza[i].num_ricorrenze = 0;
        j=0;
        while (j<300)
        {
            ricorrenza[i].pos_parola_ricorrente[j] = 0;
            j++;
        }
        i++;
    }
    fclose(fpp);

    pos_parola = 0;
    while ((fgets(riga, LUNGHEZZA+1, fpt)) != NULL)
    {
        i = tot_carat = 0;
        dim_riga = strlen(riga);
        while (i+tot_carat < dim_riga)
         {
            if ((sscanf(&riga[i+tot_carat], "%s", parola)) == 1)
            {
                pos_parola++;
                dim_parola = strlen(parola);
                for (j=0; j<num_parole; j++)
                {
                    if ((strncmp(ricorrenza[j].parola_ricorrente, parola, ricorrenza[j].dim_parola_ricorrente)) == 0)
                    {
                        ricorrenza[j].num_ricorrenze++;
                        n = cerca_spazio_vuoto_nel_vettore(ricorrenza[j].pos_parola_ricorrente, 300, 0);
                        ricorrenza[j].pos_parola_ricorrente[n] = pos_parola;
                    }
                }
                tot_carat+=dim_parola;
                i++;
            }
         } /*fine while interno*/
    } /*fine while esterno*/
    fclose(fpt);
    printf("\n\n");

    for (i=0; i<num_parole; i++)
    {
        printf("%s - %d occorenza/e", ricorrenza[i].parola_ricorrente, ricorrenza[i].num_ricorrenze);
        if (ricorrenza[i].num_ricorrenze != 0)
        {
            printf(" - posizione/i: ");
            finito = FALSE;
            for (j=0; j<300 && !finito; j++)
            {
                if (ricorrenza[i].pos_parola_ricorrente[j] != 0)
                {
                    printf("%d ", ricorrenza[i].pos_parola_ricorrente[j]);
                }
                else
                {
                    finito = TRUE;
                }
            }
            printf("\n");
        }
    }

    printf("\n\n");
    system("PAUSE");

    return 0;
}

int cerca_spazio_vuoto_nel_vettore (int vett[], int dimensione_vettore, int num_vuoto)
{
    int indice;

    for (indice = 0; indice<dimensione_vettore; indice++)
    {
        if (vett[indice] == num_vuoto)
        {
            break;
        }
    }

    return indice;
}
