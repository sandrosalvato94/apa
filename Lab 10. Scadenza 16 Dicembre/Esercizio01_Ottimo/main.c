#include <stdio.h>
#include <stdlib.h>
#define LUN_RIS 20
#define LUN_JOB 10
#include <limits.h>

typedef enum {NON_ASSEGNATO, ASSEGNATO} tipo_condizione;
typedef enum {NON_OK, OK} tipo_controllo;

typedef struct
{
    char job[LUN_JOB+1];
    int carico;
    tipo_condizione condizione;
}tipo_job;

typedef struct
{
    char risorsa[LUN_RIS+1];
    int carico_complessivo;
}tipo_risorsa;

int Num_Dati_File(FILE *Puntatore_File, int lunghezza);
tipo_risorsa *Alloca_Struct_Risorsa(int num_righe);
tipo_job *Alloca_Struct_Jobs(int num_righe);
tipo_condizione **Alloca_Matrice_Assegnazioni(int num_righe, int num_col);
tipo_risorsa *Leggi_Dati_Risorse_File(FILE *Puntatore_File, tipo_risorsa* m);
tipo_job *Leggi_Dati_Job_File(FILE *Puntatore_File, tipo_job *vett_struct);
tipo_condizione **InizializzaTabella(tipo_condizione **matrice_assegnazioni, int num_righe, int num_col);
void funzione(tipo_job *vett_job, tipo_risorsa *vett_ris, int num_risorse, int pos, int i,
              int num_jobs, tipo_condizione **matrice_assegnazioni,int *best_sol,
             tipo_condizione ***matrice_assegnazioni_sol, int n);
void RicercaMAXMIN(tipo_risorsa *vett_ris, int num_ris, int *massimo, int *minimo);
tipo_controllo FunzioneControllo(tipo_job *vett_job, tipo_risorsa *vett_risorsa, int num_jobs, int num_ris);
void Stampa(tipo_condizione **m, int num_righe, int num_col);
void DeallocaMatrice (tipo_condizione **m, int num_righe);
void Stampa_Solution(tipo_condizione **m, tipo_job *vett_job, tipo_risorsa *vett_ris, int num_jobs, int num_ris);


int best_sol = INT_MAX; /*Variabile globale*/

int main(int argc, char *argv[])
{
    FILE *fp_j, *fp_r;
    int num_risorse, num_jobs;
    tipo_job *vett_job=NULL;
    tipo_risorsa *vett_risorse=NULL;
    tipo_condizione **matrice_assegnazioni=NULL;
    tipo_condizione **matrice_assegnazioni_sol = NULL;

    if (argc != 3)
    {
        printf("\nERRORE: Numero di parametri errati da linea di comando.\n");
        return EXIT_FAILURE;
    }

    if ((fp_j = fopen(argv[1], "r"))==NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura.\n", argv[1]);
        return EXIT_FAILURE;
    }

    if ((fp_r = fopen(argv[2], "r"))==NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura.\n", argv[2]);
        return EXIT_FAILURE;
    }

    num_risorse = Num_Dati_File(fp_r, LUN_RIS);
    num_jobs = Num_Dati_File(fp_j, LUN_JOB+5);
    num_jobs = num_jobs/2; /*La funzione che legge il numero di dati calza a pennello per il file risorse...
    ...e non per file jobs. Infatti la lettura di ciascuna riga viene effettuata tramite un'unica stringa...
    ...Nel file jobs le righe presentano il codice, che identifica il lavoro, e un valore simbolico di importanza,...
    ...separati da uno <SPACE>. Pertanto la funzione Num_Dati_File conteggia 2 volte la stessa riga. Per evitare di...
    ...implementare un'altra funzione ho preferito dividere per 2 il numero che mi ritorna.*/
    if ((num_jobs==EXIT_FAILURE) || (num_risorse==EXIT_FAILURE))
    {
        printf("\nERRORE: Memoria non piu disponibile");
        return EXIT_FAILURE;
    }
    rewind(fp_j);
    rewind(fp_r);

    vett_job = Alloca_Struct_Jobs(num_jobs);
    vett_risorse = Alloca_Struct_Risorsa(num_risorse);
    matrice_assegnazioni = Alloca_Matrice_Assegnazioni(num_jobs, num_risorse);
    matrice_assegnazioni_sol = Alloca_Matrice_Assegnazioni(num_jobs, num_risorse);
    matrice_assegnazioni = InizializzaTabella(matrice_assegnazioni, num_jobs, num_risorse);
    matrice_assegnazioni_sol = InizializzaTabella(matrice_assegnazioni_sol, num_jobs, num_risorse);
    if ((vett_job == NULL) || (vett_risorse == NULL) || (matrice_assegnazioni == NULL) || (matrice_assegnazioni_sol == NULL))
    {
        printf("\nERRORE: Memoria non disponibile.\n");
        return EXIT_FAILURE;
    }

    vett_job = Leggi_Dati_Job_File(fp_j, vett_job);
    vett_risorse = Leggi_Dati_Risorse_File(fp_r, vett_risorse);
    fclose(fp_j);
    fclose(fp_r);

    funzione(vett_job, vett_risorse, num_risorse, 0, 0, num_jobs, matrice_assegnazioni, &best_sol, &matrice_assegnazioni_sol, 1);

    printf("\n%d", best_sol);
    Stampa(matrice_assegnazioni_sol, num_jobs, num_risorse);
    DeallocaMatrice(matrice_assegnazioni, num_risorse);
    DeallocaMatrice(matrice_assegnazioni_sol, num_risorse);
    free(vett_job);
    free(vett_risorse);
    system("PAUSE");

    return EXIT_SUCCESS;
}

int Num_Dati_File(FILE *Puntatore_File, int lunghezza)
{
    int n=0;
    char *riga=NULL;

    riga = (char*)malloc((lunghezza+1)*sizeof(char));
    if (riga == NULL)
    {
        printf("\nNon e' presente piu' memoria disponibile.\n");
        return EXIT_FAILURE;
    }

    while((fscanf(Puntatore_File, "%s", riga))!= EOF)
    {
        n++;
    }

    free(riga);

    return n;
}

tipo_risorsa *Alloca_Struct_Risorsa(int num_righe)
{
    tipo_risorsa *m=NULL;

    m = (tipo_risorsa*)malloc((num_righe)*sizeof(tipo_risorsa));

    return m;

}

tipo_job *Alloca_Struct_Jobs(int num_righe)
{
    tipo_job *j=NULL;

    j=(tipo_job*)malloc((num_righe)*sizeof(tipo_job));

    return j;
}

tipo_condizione **Alloca_Matrice_Assegnazioni(int num_righe, int num_col)
{
    tipo_condizione **m=NULL;
    int i;

    m = (tipo_condizione**)malloc((num_righe)*sizeof(tipo_condizione*));
    for (i=0; i<num_righe; i++)
    {
        m[i]=(tipo_condizione*)malloc((num_col+1)*sizeof(tipo_condizione));
    }

    return m;

}

tipo_risorsa *Leggi_Dati_Risorse_File(FILE *Puntatore_File, tipo_risorsa *m)
{
    int i=0;

    while ((fscanf(Puntatore_File, "%s", m[i].risorsa)) != EOF)
    {
        m[i].carico_complessivo = 0;
        i++;
    }

    return m;
}

tipo_job *Leggi_Dati_Job_File(FILE *Puntatore_File, tipo_job *vett_struct)
{
    int i=0;

    while ((fscanf(Puntatore_File, "%s%d", vett_struct[i].job, &vett_struct[i].carico))!=EOF)
    {
        vett_struct[i].condizione = NON_ASSEGNATO;
        i++;
    }

    return vett_struct;
}

tipo_condizione **InizializzaTabella(tipo_condizione **matrice_assegnazioni, int num_righe, int num_col)
{
    int i,j;

    for (i=0; i<num_righe; i++)
    {
        for (j=0; j<num_col; j++)
        {
            matrice_assegnazioni[i][j] = NON_ASSEGNATO;
        }
    }

    return matrice_assegnazioni;
}

tipo_controllo FunzioneControllo(tipo_job *vett_job, tipo_risorsa *vett_ris, int num_jobs, int num_ris)
{
    int i;
    tipo_controllo c=OK;

    for (i=0; i<num_jobs; i++)
    {
        if (vett_job[i].condizione == NON_ASSEGNATO) /*Verifica se tutti i lavori sono stati assegnati*/
        {
            c=NON_OK;
            return c;
        }
    }

    for(i=0; i<num_ris; i++)
    {
        if(vett_ris[i].carico_complessivo == 0) /*Verifica se tutte le risorse sono state assegnate*/
        {
            c=NON_OK;
            return c;
        }
    }

    return c;
}

void RicercaMAXMIN(tipo_risorsa *vett_ris, int num_ris, int *massimo, int *minimo)
{
    int i;

    for(i=0; i<num_ris; i++)
    {
        if(vett_ris[i].carico_complessivo > *massimo)
        {
            *massimo = vett_ris[i].carico_complessivo;
        }

        if(vett_ris[i].carico_complessivo < *minimo)
        {
            *minimo = vett_ris[i].carico_complessivo;
        }
    }
}

void funzione(tipo_job *vett_job, tipo_risorsa *vett_ris, int num_risorse, int pos, int i,
              int num_jobs, tipo_condizione **matrice_assegnazioni,
               int *best_sol, tipo_condizione ***matrice_assegnazioni_sol, int n)
{
    int massimo=INT_MIN, minimo=INT_MAX;
    int j;

    if (pos >= num_jobs)
    {
        if(FunzioneControllo(vett_job, vett_ris, num_jobs, num_risorse))
        {
            RicercaMAXMIN(vett_ris, num_risorse, &massimo, &minimo);
            if ((massimo-minimo) < *best_sol)
            {
                *best_sol = massimo - minimo;
                *matrice_assegnazioni_sol = matrice_assegnazioni;
                //Stampa_Solution(*matrice_assegnazioni_sol, vett_job, vett_ris, num_jobs, num_risorse);
                printf("\nMATRICE SOL        CHIAMATA %d.   DIFFERENZA %d", n, *best_sol);
                printf("\n");
                Stampa(*matrice_assegnazioni_sol, num_jobs, num_risorse);
            }
        }
        return;
    }

    for(i=0; i<num_risorse; i++)
    {
        if((matrice_assegnazioni[pos][i] == NON_ASSEGNATO) && (vett_job[pos].condizione == NON_ASSEGNATO))
        {
            matrice_assegnazioni[pos][i] = ASSEGNATO;
            vett_job[pos].condizione = ASSEGNATO;
            vett_ris[i].carico_complessivo += vett_job[pos].carico;
            printf("\n");
            /*for(j=0; j<n; j++)
            {
                printf("*");
            }
            printf("CHIAMATA %d\n", n);*/
            Stampa(matrice_assegnazioni, num_jobs, num_risorse);
            funzione(vett_job, vett_ris, num_risorse, pos+1, i, num_jobs, matrice_assegnazioni, best_sol, matrice_assegnazioni_sol, n+1);
            matrice_assegnazioni[pos][i] = NON_ASSEGNATO;
            vett_job[pos].condizione = NON_ASSEGNATO;
            vett_ris[i].carico_complessivo -= vett_job[pos].carico;
        }
        else
        {
            pos++;
        }
    }
}

void Stampa(tipo_condizione **m, int num_righe, int num_col)
{
    int i,j;

    for (i=0; i<num_righe; i++)
    {
        for (j=0; j<num_col; j++)
        {
            if (m[i][j] == NON_ASSEGNATO)
            {
                printf("N   ");
            }
            else
            {
                printf("A   ");
            }
        }
        printf("\n");
    }
}

void DeallocaMatrice (tipo_condizione **m, int num_righe)
{
    int i;

    for (i=0; i<num_righe; i++)
    {
        free(m[i]);
    }
    free(m);
}

void Stampa_Solution(tipo_condizione **m, tipo_job *vett_job, tipo_risorsa *vett_ris, int num_jobs, int num_ris)
{
    int i, j=0, carico_complessivo;

    for (i=0; i<num_ris; i++)
    {
       printf("\n%s {", vett_ris[i].risorsa);
       carico_complessivo = 0;
       for (j=0; j<num_jobs; j++)
       {
           if(m[j][i] == ASSEGNATO)
           {
               printf("%s  ", vett_job[j].job);
               carico_complessivo += vett_job[j].carico;
           }
       }
       printf("} Carico: %d", carico_complessivo);
    }
    printf("\n");
}
