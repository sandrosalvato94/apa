/*Alessandro Salvato S201129*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#define D 10.0
/*Struttura Dati*/
typedef struct {
    int x;
    int y;
    float distanza_origine;
}tipo_punto;
/*Prototipi*/
int lunghezza_file (FILE *Puntatore_file, char Riga[], int Dim_riga);
void punti_piu_vicini_e_lontani (tipo_punto *lista_punti, int num_dati, int *num_segmenti, float limite_lunghezza_segm);
void punti_piu_vicini_origine (tipo_punto *lista_punti, int num_dati);
void SelectionSort (tipo_punto *lista_punti, int inizia_ordinamento, int num_dati);
void stampa_in_file (FILE *Puntatore_file, tipo_punto *lista_punti, int num_dati);

int main()
{
    FILE *fp, *fpu;
    tipo_punto *p_punto = NULL;
    int num_righe, i;
    char riga[10];
    int num_seg=0;

    if ((fp = fopen("lista_punti.txt", "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file lista_punti.txt in lettura\n");
        return EXIT_FAILURE;
    }

    if ((fpu = fopen("file_uscita.txt", "w")) == NULL)
    {
        printf("\nERRORE nell'apertura del file file_uscita.txt in scrittura\n");
        return EXIT_FAILURE;
    }

    num_righe = lunghezza_file (fp, riga, 10);
    p_punto = malloc(num_righe*sizeof(tipo_punto));

    if (p_punto == NULL)
    {
        printf("\nNon c'e' abbastanza memoria disponibile per eseguire il programma\n");
        return EXIT_SUCCESS;
    }
    rewind(fp);
    for (i=0; i<num_righe; i++)
    {
        fscanf(fp, "%d%d", &p_punto[i].x, &p_punto[i].y);
    }
    fclose(fp);

    punti_piu_vicini_e_lontani (p_punto, num_righe, &num_seg, D);
    punti_piu_vicini_origine (p_punto, num_righe);
    SelectionSort(p_punto, 0, num_righe);
    stampa_in_file(fpu, p_punto, num_righe);

    printf("\n\n%d segmenti", num_seg);

    fclose(fpu);
    free(p_punto);

    return 0;
}

int lunghezza_file (FILE *Puntatore_file, char Riga[], int Dim_riga)
{
    int a = 0;
    while ((fgets(Riga, Dim_riga, Puntatore_file)) != NULL)
    {
       a++;
    }
    return a;
}

void punti_piu_vicini_e_lontani (tipo_punto *lista_punti, int num_dati, int *num_segmenti, float limite_lunghezza_segm)
{
    /*In questa funzione ho esaudito le tre richieste delle specifiche*/
    int i, j;
    int x1, y1, x2, y2, x1_min, y1_min, x2_min, y2_min, x1_max, y1_max, x2_max, y2_max;
    float distanza;
    float distanza_massima = INT_MIN;
    float distanza_minima = INT_MAX;

    for (i=0; i<num_dati; i++)
    {
        for (j=0; j<num_dati; j++)
        {

            if (i!=j)   /*Effettuo la ricerca del massimo e del minimo sulla distanza fra due punti*/
            {
                x1 = lista_punti[i].x;
                y1 = lista_punti[i].y;
                x2 = lista_punti[j].x;
                y2 = lista_punti[j].y;
                distanza = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
                if (distanza<=limite_lunghezza_segm) /*Ad ogni segmento che soddisfa la condizione incremento*/
                {
                    *num_segmenti = (*num_segmenti+1);
                }
                if (distanza>distanza_massima)
                {
                    distanza_massima = distanza;
                    x1_max = lista_punti[i].x;
                    y1_max = lista_punti[i].y;
                    x2_max = lista_punti[j].x;
                    y2_max = lista_punti[j].y;
                }
                if (distanza<distanza_minima)
                {
                    distanza_minima = distanza;
                    x1_min = lista_punti[i].x;
                    y1_min = lista_punti[i].y;
                    x2_min = lista_punti[j].x;
                    y2_min = lista_punti[j].y;
                }
            }
        }
    }

    *num_segmenti = *num_segmenti/2; /*Facendo la considerazione che l'insieme dei segmenti che congiungono i punti nel piano cartesiano è un GRAFO NON ORIENTATO*/
    /*divido per due il numero totale di segmenti. Una linea sul piano cartesiano è priva di verso, quindi è da considerarsi un'unica volta e non due.*/
    printf("\n\nLa distanza minima e' %.2f fra i punti (%d; %d) e (%d; %d)\n\n", distanza_minima, x1_min, y1_min, x2_min, y2_min);
    printf("\n\nLa distanza massima e' %.2f fra i punti (%d; %d) e (%d; %d)\n\n", distanza_massima, x1_max, y1_max, x2_max, y2_max);
}

void punti_piu_vicini_origine (tipo_punto *lista_punti, int num_dati) /*A ciascun punto associo la la sua distanza con l'origine*/
{
    int i;

    for (i=0; i<num_dati; i++)
    {
        lista_punti[i].distanza_origine = sqrt(pow(lista_punti[i].x, 2) + pow(lista_punti[i].y, 2));
    }

}

void SelectionSort (tipo_punto *lista_punti, int inizia_ordinamento, int num_dati)
{
    int i, j;
    float minimo;
    float tmpf;
    int tmpi;

    for (i=inizia_ordinamento; i<num_dati; i++)
    {
        minimo = lista_punti[i].distanza_origine;
        for (j=i+1; j< num_dati; j++)
        {
            if (lista_punti[j].distanza_origine < minimo)
            {
                minimo = lista_punti[j].distanza_origine;
                tmpf = lista_punti[i].distanza_origine;         /*Effettuo lo scambio fra due intere struct*/
                lista_punti[i].distanza_origine = lista_punti[j].distanza_origine;
                lista_punti[j].distanza_origine = tmpf;
                tmpi = lista_punti[i].x;
                lista_punti[i].x = lista_punti[j].x;
                lista_punti[j].x = tmpi;
                tmpi = lista_punti[i].y;
                lista_punti[i].y = lista_punti[j].y;
                lista_punti[j].y = tmpi;
            }
        }
    }
}

void stampa_in_file (FILE *Puntatore_file, tipo_punto *lista_punti, int num_dati)
{
    int i;
    for (i=0; i<num_dati; i++)
    {
        fprintf(Puntatore_file, "(%d; %d)\n", lista_punti[i].x, lista_punti[i].y);
    }
}
