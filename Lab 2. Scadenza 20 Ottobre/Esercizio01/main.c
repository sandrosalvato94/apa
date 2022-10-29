#include <stdio.h>
#include <stdlib.h>
#define LUNGHEZZA_RIGA 100
#include <string.h>
#define MAX_LUNGHEZZA 10

int cerca_spazio_vuoto_nel_vettore (int vett[], int dimensione_vettore, int num_vuoto); /*prototipo*/

typedef struct {
  int conteggio;
  int posizioni[LUNGHEZZA_RIGA];
} tipo;

int main(int argc, char *argv[])
{
    FILE *fp;
    char riga[LUNGHEZZA_RIGA+1], parola[LUNGHEZZA_RIGA+1];
    tipo ordinamento[LUNGHEZZA_RIGA];
    int i, j, k, n, dim_parola, dim_riga, tot_carat, num_parola;

    if (argc != 2) /*Controllo sul corretto numero di parametri inseriti dalla linea di comando*/
    {
        printf("\nERRORE: Numero di parametri errato da linea di comando\n");
        return EXIT_FAILURE;
    }
    if ((fp = fopen(argv[1], "r")) == NULL) /*Controllo sull'apertura corretta dei file*/
    {
        printf("\nERRORE nell'apertura del file %s in lettura\n\n", argv[1]);
        return EXIT_FAILURE;
    }

    for (i=0; i<LUNGHEZZA_RIGA; i++) /*Inizzializzo i dati a zero*/
    {
        ordinamento[i].conteggio = 0;
        for (j=0; j<LUNGHEZZA_RIGA; j++)
            {
                ordinamento[i].posizioni[j] = 0;
            }
    }

    num_parola = 0;

    while ((fgets(riga, LUNGHEZZA_RIGA+1, fp)) != NULL)
    {
        dim_riga = strlen(riga);
        i= dim_parola = tot_carat = 0;
        while (i+tot_carat <dim_riga)
        {
            if((sscanf(&riga[i+tot_carat], "%[a-zA-Z0-9]", parola)) == 1) /*Leggo parola per parola solo i caratteri alfanumerici in quanto simboli di punteggiatura e <SPACE> non sono da considerare*/
            {
                dim_parola = strlen(parola);
                num_parola++;
                j = dim_parola-1; /*Devo allineare la dimensione della parola con l'indice del vettore, che è sempre inferiore di 1*/
                ordinamento[j].conteggio++;
                n = cerca_spazio_vuoto_nel_vettore(ordinamento[j].posizioni, LUNGHEZZA_RIGA, 0);
                ordinamento[j].posizioni[n] = num_parola;
                i++;
                tot_carat += dim_parola;
            }
            else
            {
                i++;
            }
        }
    }
    fclose(fp);

    printf("\nLunghezza\t\tConteggio\t\tPosizioni\n\n"); /*stampo tutto*/
    k=0;
    for (i=0; i<LUNGHEZZA_RIGA && k<10; i++)
    {
        if (ordinamento[i].conteggio != 0)
        {
            printf("\n%d\t\t\t%d\t\t\t", i+1, ordinamento[i].conteggio);
            for (j=0; j<LUNGHEZZA_RIGA; j++)
            {
                if (ordinamento[i].posizioni[j] != 0)
                {
                    printf("%d ", ordinamento[i].posizioni[j]);
                }
            }
            printf("\n");
            k++;
        }
    }
    printf("\n\n");
    system("PAUSE");

    return EXIT_SUCCESS;
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
