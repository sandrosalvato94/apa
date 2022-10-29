#include <stdio.h>
#include <stdlib.h>
#define LUN_RIS 20
#define LUN_JOB 10
#include <string.h>

typedef struct nodo
{
    char job_assegnato[LUN_JOB+1];
    struct nodo *succ;
}link;

typedef struct
{
    char job[LUN_JOB+1];
    int carico;
}tipo_job;

typedef struct
{
    char risorsa[LUN_RIS+1];
    link *succ;
}tipo_risorsa;

int Num_Dati_File(FILE *Puntatore_File, int lunghezza);
tipo_risorsa *Alloca_Struct_Risorsa(int num_righe);
tipo_job *Alloca_Struct_Jobs(int num_righe);
tipo_risorsa *Leggi_Dati_Risorse_File(FILE *Puntatore_File, tipo_risorsa* m);
tipo_job *Leggi_Dati_Job_File(FILE *Puntatore_File, tipo_job *vett_struct);
void QuickSort (tipo_job *vett_job, int indice_sinistro, int indice_destro);
int partition (tipo_job *vett_job, int indice_sinistro, int indice_destro);
void Scambio(tipo_job *vett_job, int i, int j);
void Soluzione_Greedy(tipo_job *vett_job, tipo_risorsa *vett_ris, int num_jobs, int num_ris);
void Inserisci(tipo_risorsa *vett_ris, int indice_jobs, int indice_ris, tipo_job *vett_job);
void Stampa(tipo_risorsa *vett_ris, int num_ris);
void DeallocaVettore(tipo_risorsa *vett_ris, int num_ris);
void DeallocaLista(tipo_risorsa vett_ris, link *p_testa);

int main(int argc, char *argv[])
{
    FILE *fp_j, *fp_r;
    int num_risorse, num_jobs;
    tipo_job *vett_job=NULL;
    tipo_risorsa *vett_risorse=NULL;

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
    if ((vett_job == NULL) || (vett_risorse == NULL))
    {
        printf("\nERRORE: Memoria non disponibile.\n");
        return EXIT_FAILURE;
    }

    vett_job = Leggi_Dati_Job_File(fp_j, vett_job);
    vett_risorse = Leggi_Dati_Risorse_File(fp_r, vett_risorse);
    fclose(fp_j);
    fclose(fp_r);

    QuickSort(vett_job, 0, num_jobs-1);

    Soluzione_Greedy(vett_job, vett_risorse, num_jobs, num_risorse);
    printf("\n\n");

    free(vett_job);
    DeallocaVettore(vett_risorse, num_risorse);

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

tipo_job *Leggi_Dati_Job_File(FILE *Puntatore_File, tipo_job *vett_struct)
{
    int i=0;

    while ((fscanf(Puntatore_File, "%s%d", vett_struct[i].job, &vett_struct[i].carico))!=EOF)
    {
        i++;
    }

    return vett_struct;
}

tipo_risorsa *Leggi_Dati_Risorse_File(FILE *Puntatore_File, tipo_risorsa *m)
{
    int i=0;

    while ((fscanf(Puntatore_File, "%s", m[i].risorsa)) != EOF)
    {
        m[i].succ = NULL;
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

void Soluzione_Greedy(tipo_job *vett_job, tipo_risorsa *vett_ris, int num_jobs, int num_ris)
{
    int i, j=0;

    for (i=0; i<num_jobs; i++)
    {
        if(j>=num_ris)
        {
            j=0;
        }

        Inserisci(vett_ris, i, j, vett_job);
        j++;
    }
    printf("\n");
    Stampa(vett_ris, num_ris);
}

void Inserisci(tipo_risorsa *vett_ris, int indice_jobs, int indice_ris, tipo_job *vett_job)
{
    link *nuovo=NULL;
    link *p_corr=NULL;

    nuovo = (link*)malloc(sizeof(link));

    if(nuovo==NULL)
    {
        printf("\nERRORE: Memoria non piu' disponibile.\n");
        return;
    }

    if(vett_ris[indice_ris].succ == NULL)
    {
        strcpy(nuovo->job_assegnato, vett_job[indice_jobs].job);
        nuovo->succ = NULL;
        vett_ris[indice_ris].succ = nuovo;
    }
    else
    {
        for(p_corr = vett_ris[indice_ris].succ; p_corr->succ != NULL; p_corr = p_corr->succ); /*Percorro la lista fino ad arrivare in fondo, fermandomi all'ultimo non NULLO*/
        p_corr->succ = nuovo;
        strcpy(nuovo->job_assegnato, vett_job[indice_jobs].job);
        nuovo->succ = NULL;
    }
}

void Stampa(tipo_risorsa *vett_ris, int num_ris)
{
    int i=0;
    link *p_corr=NULL;

    while(i<num_ris)
    {
        printf("\n%s {", vett_ris[i].risorsa);
        for (p_corr = vett_ris[i].succ; p_corr !=NULL; p_corr = p_corr->succ)
        {
            printf("%s ", p_corr->job_assegnato);
        }
        printf("}");
        i++;
    }
}

void DeallocaVettore(tipo_risorsa *vett_ris, int num_ris)
{
    int i=0;
    while (i<num_ris)
    {
        DeallocaLista(vett_ris[i], vett_ris[i].succ);
        i++;
    }
    free(vett_ris);
}

void DeallocaLista(tipo_risorsa ris, link *p_testa)
{
    if (p_testa == NULL)
    {
        free(p_testa);
        return;
    }

    DeallocaLista(ris, p_testa->succ);
}
