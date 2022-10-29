#include <stdio.h>
#include <stdlib.h>
#define LUN_RIS 20
#define LUN_JOB 10


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
tipo_condizione **InizializzaTabella(tipo_condizione **matrice_assegnazioni, int num_righe, int num_col);
tipo_risorsa *Leggi_Dati_Risorse_File(FILE *Puntatore_File, tipo_risorsa* m);
tipo_job *Leggi_Dati_Job_File(FILE *Puntatore_File, tipo_job *vett_struct);
void QuickSort (tipo_job *vett_job, int indice_sinistro, int indice_destro);
int partition (tipo_job *vett_job, int indice_sinistro, int indice_destro);
void Scambio(tipo_job *vett_job, int i, int j);
void Soluzione_Greedy(tipo_condizione **matrice_assegnazione, tipo_job *vett_job, tipo_risorsa *vett_risorsa,
                                   int num_jobs, int num_ris);
void Stampa(tipo_condizione **matrice_assegnazione, tipo_job *vett_job, tipo_risorsa *vett_risorsa, int num_jobs, int num_ris);

int main(int argc, char *argv[])
{
    FILE *fp_j, *fp_r;
    int num_risorse, num_jobs;
    tipo_job *vett_job=NULL;
    tipo_risorsa *vett_risorse=NULL;
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
    num_jobs = num_jobs/2;
    if ((num_jobs==EXIT_FAILURE) || (num_risorse==EXIT_FAILURE))
    {
        printf("\nERRORE: Memoria non piu disponibile");
        return EXIT_FAILURE;
    }
    rewind(fp_j);
    rewind(fp_r);

    vett_job = Alloca_Struct_Jobs(num_jobs);
    vett_risorse = Alloca_Struct_Risorsa(num_risorse);
    matrice_assegnazioni_sol = Alloca_Matrice_Assegnazioni(num_jobs, num_risorse);
    matrice_assegnazioni_sol = InizializzaTabella(matrice_assegnazioni_sol, num_jobs, num_risorse);
    if ((vett_job == NULL) || (vett_risorse == NULL) || (matrice_assegnazioni_sol == NULL))
    {
        printf("\nERRORE: Memoria non disponibile.\n");
        return EXIT_FAILURE;
    }

    vett_job = Leggi_Dati_Job_File(fp_j, vett_job);
    vett_risorse = Leggi_Dati_Risorse_File(fp_r, vett_risorse);
    fclose(fp_j);
    fclose(fp_r);

    QuickSort(vett_job, 0, num_jobs-1);

    Soluzione_Greedy(matrice_assegnazioni_sol, vett_job, vett_risorse, num_jobs, num_risorse);

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

tipo_job *Alloca_Struct_Jobs(int num_righe)
{
    tipo_job *j=NULL;

    j=(tipo_job*)malloc((num_righe)*sizeof(tipo_job));

    return j;
}

tipo_risorsa *Alloca_Struct_Risorsa(int num_righe)
{
    tipo_risorsa *m=NULL;


    m = (tipo_risorsa*)malloc((num_righe)*sizeof(tipo_risorsa));
    return m;

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

void QuickSort (tipo_job *vett_job, int indice_sinistro, int indice_destro)
{
    int q;
    if (indice_destro <= indice_sinistro)
    {
       return;
    }

    q = partition(vett_job, indice_sinistro, indice_destro);
    QuickSort(vett_job, indice_sinistro, q-1);
    QuickSort(vett_job, q+1, indice_destro);
    return;
}

int partition (tipo_job *vett_job, int indice_sinistro, int indice_destro)
{
    int i = indice_sinistro, j = indice_destro;
    tipo_job tmp = vett_job[indice_destro];
    for ( ; ; )
    {
        while(vett_job[++i].carico < tmp.carico);
        while(vett_job[--j].carico > tmp.carico);
        if (j == indice_sinistro)
        {
            break;
        }
        if (i >= j)
        {
            break;
        }

        Scambio(vett_job, i, j);
    }
    Scambio(vett_job, i, indice_destro);

    return i;
}

void Scambio(tipo_job *vett_job, int i, int j)
{
    tipo_job tmp;

    tmp = vett_job[i];
    vett_job[i] = vett_job[j];
    vett_job[j] = tmp;
}

void Soluzione_Greedy(tipo_condizione **matrice_assegnazione, tipo_job *vett_job, tipo_risorsa *vett_risorsa,
                                   int num_jobs, int num_ris)
{
    int i, j;
    int indice_sinistro = 0;
    int indice_destro = num_jobs-1;
    int indice_medio = (indice_sinistro+indice_destro)/2;

    while (indice_sinistro <= indice_medio)
    {
        i=0;
        while ((i<num_ris) && (indice_sinistro <= indice_medio))
        {
            if (vett_job[indice_sinistro].condizione == NON_ASSEGNATO)
            {
                matrice_assegnazione[indice_sinistro][i] = ASSEGNATO;
                vett_job[indice_sinistro].condizione = ASSEGNATO;
            }
            i++;
            indice_sinistro++;
        }
    }
    while (indice_destro > indice_medio)
    {
        i=0;
        while ((i<num_ris) && (indice_destro > indice_medio))
        {
            if (vett_job[indice_destro].condizione == NON_ASSEGNATO)
            {
                matrice_assegnazione[indice_destro][i] = ASSEGNATO;
                vett_job[indice_destro].condizione = ASSEGNATO;
            }
            i++;
            indice_destro--;
        }
    }
    matrice_assegnazione[indice_sinistro][i-1] = ASSEGNATO;
    for(i=0; i<num_jobs; i++)
    {
        for(j=0; j<num_ris; j++)
        {
            if (matrice_assegnazione[i][j] == ASSEGNATO)
            {
                printf("    A");
            }
            else
            {
                printf("    N");
            }
        }
        printf("\n");
    }

    Stampa(matrice_assegnazione, vett_job, vett_risorsa, num_jobs, num_ris);
}

void Stampa(tipo_condizione **matrice_assegnazione, tipo_job *vett_job, tipo_risorsa *vett_risorsa, int num_jobs, int num_ris)
{
    int i, j;

    for (i=0; i<num_ris; i++)
    {
        printf("%s : {", vett_risorsa[i].risorsa);
        for (j=0; j<num_jobs; j++)
        {
            if (matrice_assegnazione[j][i] == ASSEGNATO)
            {
                printf("%s ", vett_job[j].job);
            }
        }
        printf("}\n");
    }
}
