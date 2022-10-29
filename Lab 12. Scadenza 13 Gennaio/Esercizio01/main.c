#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define LUNGHEZZA 15
#include "grafo.h"
#include "Tabella.h"

void Leggo_Dati_File(FILE *Puntatore_File, GRAPH Grafo, ST Tabella);
int* Stampa_Gradi(GRAPH Grafo, ST Tabella, int num_vertici, int *vett_gradi);
void PAUSE();
void Stampa_Vertici(GRAPH Grafo, ST Tabella, int num_vertici);
void MatriceAdj(GRAPH Grafo);
void StampaIncidenze(GRAPH Grafo, int* vett_gradi, int num_vertici);
void CalcoloFlussi(GRAPH Grafo, ST Tabella, int num_vertici, int* vett_gradi);
void Dealloca(GRAPH Grafo, ST Tabella, int *vett_gradi);


int main(int argc, char *argv[])
{
    FILE *fp;
    int num_vertici;
    int *gradi_vertici;
    ST Tabella=NULL;
    GRAPH Grafo=NULL;

    if (argc != 2)
    {
        printf("\nERRORE: Numero di parametri errati da linea di comando.\n");
        return EXIT_FAILURE;
    }

    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura.\n", argv[1]);
        return EXIT_FAILURE;
    }

    fscanf(fp, "%d", &num_vertici);
    gradi_vertici = (int*)malloc(num_vertici*sizeof(int));

    Tabella = ST_Init(num_vertici);
    Tabella = ST_Scan(fp, Tabella);
    ST_Sort(Tabella);
    //ST_Show(Tabella); Ha lo stesso effetto della funzione Stampa_Vertici
    //PAUSE();

    Grafo = GraphInit(num_vertici);
    Leggo_Dati_File(fp, Grafo, Tabella);
    fclose(fp);
    gradi_vertici = Stampa_Gradi(Grafo, Tabella, num_vertici, gradi_vertici);
    PAUSE();

    Stampa_Vertici(Grafo, Tabella, num_vertici);
    PAUSE();

    MatriceAdj(Grafo);
    PAUSE();

    StampaIncidenze(Grafo, gradi_vertici, num_vertici);
    PAUSE();

    CalcoloFlussi(Grafo, Tabella, num_vertici, gradi_vertici);
    PAUSE();

    Dealloca(Grafo, Tabella, gradi_vertici);

    return EXIT_SUCCESS;
}

void Leggo_Dati_File(FILE *Puntatore_File, GRAPH Grafo, ST Tabella)
{
    int v, w, p;
    EDGE e;
    while(Scan_File(Puntatore_File, Tabella, &v, &w, &p))
    {
        e = GetEdge(v, w, p);
        GraphInsert(Grafo, e);
    }
}
int* Stampa_Gradi(GRAPH Grafo, ST Tabella, int num_vertici, int* vett_gradi)
{
    int i=0, g;
    Item nodo;
    printf("\n********GRADI VERTICI**********\n\n");
    while (i<num_vertici)
    {
        g = RankNode(Grafo, i);
        nodo = Conversione_Number2City(Tabella, i);
        ItemSHOW(nodo);
        printf(" GRADO: %d\n", g);
        vett_gradi[i] = g;
        i++;
    }

    return vett_gradi;
}

void PAUSE()
{
    printf("\n");
    system("PAUSE");
    printf("\n");
    system("cls");
}

void Stampa_Vertici(GRAPH Grafo, ST Tabella, int num_vertici)
{
    int i;

    printf("\nI vertici del grafo sono: %d\n", num_vertici);
    for (i=0; i<num_vertici; i++)
    {
        printf("%d - ", i+1);
        ItemSHOW(Conversione_Number2City(Tabella, i));
        printf("\n");
    }
}

void MatriceAdj(GRAPH Grafo)
{
    int d;

    printf("\nSi vuole generare la matrice delle adiacenze <Si = 1, No = 0>?\n");
    scanf("%d", &d);
    switch (d)
    {
        case 0:
        {
            return;
            break;
        }
        case 1:
        {
            InizializzaMatriceAdj(Grafo);
            Generazione_MatAdj(Grafo);
            StampaMatrice(Grafo);
            PAUSE();
            break;
        }
        default:
        {
            printf("\nERRORE: la matrice non verra' generata.\n");
            break;
        }
    }
}

void StampaIncidenze(GRAPH Grafo, int* vett_gradi, int num_vertici)
{
    int i;

    for(i=0; i<num_vertici; i++)
    {
        printf("\nIl vertice %d e' inciso da %d archi, dei vertici: ", i+1, vett_gradi[i]+1);
        Incidenze(Grafo, i);
    }
}

int RicercaMax(int *vett_gradi, int num_vertici)
{
    int i;
    int m;

    m = INT_MIN;
    for(i=0; i<num_vertici; i++)
    {
        if(vett_gradi[i]>m)
        {
            m = vett_gradi[i];
        }
    }
    return m;
}

int* InizializzaVettore(int* vett, int n)
{
    int i;

    for(i=0; i<n; i++)
    {
        vett[i] = 0;
    }
    return vett;
}

void CalcoloFlussi(GRAPH Grafo, ST Tabella, int num_vertici, int* vett_gradi)
{
    int f_inter=0, f_intra=0, i,j=1;
    int grado_max = RicercaMax(vett_gradi, num_vertici);
    int** m;
    Item dato1, dato2;
    char regione1[LUNGHEZZA+1];

    m = (int**)malloc(2*sizeof(int));

    for(i=0; i<2; i++)
    {
        m[i] = (int*)malloc(grado_max*sizeof(int));
    }

    for (i=0; i<num_vertici; i++)
    {
        InizializzaVettore(m[0], grado_max); /*vettore dei vertici di adiacenza. La prima casella è occupata dal vertice considerato, le altre caselle sono occupate dai vertici adiacenti*/
        InizializzaVettore(m[1], grado_max); /*vettore dei pesi degli archi. La prima casella è zero poichè non ci sono cappi, le altre sono i pesi che il vertice m[0][0] ha con i restanti vertici*/
        dato1 = Conversione_Number2City(Tabella, i);
        strcpy(regione1, dato1.regione);
        m = (int**)Scan_Incidenze_Vett(Grafo, i, m);
        for(j=1; j<=vett_gradi[i]; j++)
        {
            if(i<m[0][j])
            {
                dato2 = Conversione_Number2City(Tabella, m[0][j]);
                if (strcmp(regione1, dato2.regione) == 0)
                {
                    f_intra += m[1][j];
                }
                else
                {
                    f_inter += m[1][j];
                }
            }
        }
    }

    printf("\nIl flusso interregionale e' pari a: %d", f_inter);
    printf("\nIl flusso intraregionale e' pari a: %d", f_intra);

    free(m);
}

void Dealloca(GRAPH Grafo, ST Tabella, int *vett_gradi)
{
    free(vett_gradi);
    DeallocaGrafo(Grafo);
    DeallocaST(Tabella);
}

