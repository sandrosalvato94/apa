#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LUNGHEZZA 20
#define N 5.0
#include <limits.h>

typedef enum {NON_PRESO, PRESO} tipo_condizione;

typedef struct
{
    char oggetto[LUNGHEZZA+1];
    float peso;
    int importanza;
    tipo_condizione condizione;
} Item;

void backpack(Item *valigia, float capienza_massima, float peso_corrente, int valore_corrente,
              int pos, int numero_elementi, int *best_value, Item **soluzione, int *num_sol);
void StampaFile(FILE *Puntatore_File, Item *soluzione, int num_sol);
Item* Oggetti_Restanti(Item *valigia, Item *soluzione, int numero_elementi, int numero_soluzione);
void Permutazioni_Valigie(Item *valigia, int numero_elementi_restanti, int numero_valigie, int peso_massimo,
                          int pos, Item *sol, int *numero_valigie_minimo, FILE *Puntatore_File, char *nome_file);
int NUM_VALIGIE(Item *sol, float peso_massimo, int numero_elementi_restanti, FILE *Puntatore_File, char *nome_file);

int main(int argc, char *argv[])
{
    FILE *fp_list, *fp_opt, *fp_scase;
    int num_ele, i=0;
    Item *valigia=NULL, *soluzione=NULL, *oggetti_valigie=NULL;
    float peso_disp;
    int best_value=0, num_sol=0;
    int num_val_opt = INT_MAX;

    if (argc!=4)
    {
        printf("\nERRORE: Numero di parametri errati da linea di comando.\n");
        return EXIT_FAILURE;
    }

    if ((fp_list = fopen(argv[1], "r"))== NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura", argv[1]);
        return EXIT_FAILURE;
    }

    if ((fp_opt = fopen(argv[2], "w"))== NULL)
    {
        printf("\nERRORE nell'apertura del file %s in scrittura.\n", argv[2]);
        return EXIT_FAILURE;
    }

    fscanf(fp_list, "%d", &num_ele);
    valigia = (Item*)malloc(num_ele*sizeof(Item));
    soluzione = (Item*)malloc(num_ele*sizeof(Item));
    if ((valigia == NULL) ||(soluzione == NULL))
    {
        printf("\nERRORE: Memoria non disponibile.\n");
        return EXIT_FAILURE;
    }

    while (i<num_ele)
    {
        fscanf(fp_list, "%s%f%d", valigia[i].oggetto, &valigia[i].peso, &valigia[i].importanza);
        strcpy(soluzione[i].oggetto, "_");
        soluzione[i].peso = soluzione[i].importanza = -1;
        valigia[i].condizione = soluzione[i].condizione = NON_PRESO;
        i++;
    }
    fclose(fp_list);
    printf("\nQual e' la capienza massima (KG) a disposizione?\n");
    scanf("%f", &peso_disp);

    backpack(valigia, peso_disp, 0.0, 0, 0, num_ele, &best_value, &soluzione, &num_sol);
    StampaFile(fp_opt, soluzione, num_sol);
    fclose(fp_opt);
    oggetti_valigie = (Item*)malloc((num_ele-num_sol)*sizeof(Item));
    oggetti_valigie = Oggetti_Restanti(valigia, soluzione, num_ele, num_sol);
    for(i=0; i<(num_ele-num_sol); i++)
    {
        soluzione[i].condizione = NON_PRESO;
        strcpy(soluzione[i].oggetto, "_");
        soluzione[i].peso = -1;
    }
    Permutazioni_Valigie(oggetti_valigie, num_ele-num_sol, 0, N, 0, soluzione, &num_val_opt, fp_scase, argv[3]);
    printf("\nIl numero minimo di valigie e': %d", num_val_opt);

    return EXIT_SUCCESS;
}

void backpack(Item *valigia, float capienza_massima, float peso_corrente, int valore_corrente, int pos,
              int numero_elementi, int *best_value, Item **soluzione, int *num_sol)
{
    int i,j;

   if (pos >= numero_elementi)
   {
        if (peso_corrente <=capienza_massima)
        {
            if (valore_corrente > *best_value)
            {
                j=0;
                for(i=0; i<numero_elementi; i++)
                {
                    if (valigia[i].condizione == PRESO)
                    {
                        (*soluzione)[j] = valigia[i];
                        j++;
                    }
                }
                *best_value = valore_corrente;
                *num_sol = j;
            }
        }
        return;
    }

    valigia[pos].condizione = PRESO;
    peso_corrente += valigia[pos].peso;
    valore_corrente += valigia[pos].importanza;
    backpack(valigia, capienza_massima, peso_corrente, valore_corrente, pos+1, numero_elementi, best_value, soluzione, num_sol);

    valigia[pos].condizione = NON_PRESO;
    peso_corrente -= valigia[pos].peso;
    valore_corrente -= valigia[pos].importanza;
    backpack(valigia, capienza_massima, peso_corrente, valore_corrente, pos+1, numero_elementi, best_value, soluzione, num_sol);
}

void StampaFile(FILE *Puntatore_File, Item *soluzione, int num_sol)
{
    int i;
    for (i=0; i<num_sol; i++)
    {
        fprintf(Puntatore_File, "\n%s    %.2f      %d", soluzione[i].oggetto, soluzione[i].peso, soluzione[i].importanza);
    }
}

Item* Oggetti_Restanti(Item *valigia, Item *soluzione, int numero_elementi, int numero_soluzione)
{
    int i=0, j=0;

    Item* v= (Item*)malloc((numero_elementi-numero_soluzione)*sizeof(Item));

    while ((i<numero_elementi) && (j<numero_soluzione))
    {
        for(j=0; j<numero_soluzione;j++)
        {
            if(strcmp(soluzione[j].oggetto, valigia[i].oggetto) == 0)
            {
                valigia[i].condizione = PRESO;
            }
            else
            {
                j--;
            }
            i++;
        }
    }
    i=j=0;
    while ((j<(numero_elementi-numero_soluzione)) && (i<numero_elementi))
     {
         if(valigia[i].condizione == NON_PRESO)
        {
            v[j] = valigia[i];
            j++;
        }
        i++;
     }

    return v;
}

void Permutazioni_Valigie(Item *valigia, int numero_elementi_restanti, int numero_valigie, int peso_massimo,
                          int pos, Item *sol, int *numero_valigie_minimo, FILE *Puntatore_File, char *nome_file)
{
    int i;

    if(pos >=numero_elementi_restanti)
    {
        numero_valigie = NUM_VALIGIE(sol, N, numero_elementi_restanti, Puntatore_File, nome_file);
        if (numero_valigie < *numero_valigie_minimo)
        {
            *numero_valigie_minimo = numero_valigie;
        }
        return;
    }

    for (i=0; i<numero_elementi_restanti; i++)
    {
        if (valigia[i].condizione == NON_PRESO)
        {
            valigia[i].condizione = PRESO;
            sol[pos] = valigia[i];
            Permutazioni_Valigie(valigia, numero_elementi_restanti, numero_valigie, N, pos+1, sol, numero_valigie_minimo,
                                 Puntatore_File, nome_file);
            valigia[i].condizione = NON_PRESO;
        }
    }
}

int NUM_VALIGIE(Item *sol, float peso_massimo, int numero_elementi_restanti, FILE *Puntatore_File, char *nome_file)
{
    int n=1, i=0;
    float p_corr=0;

    if((Puntatore_File = fopen(nome_file, "w")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in scrittura.\n", nome_file);
        return EXIT_FAILURE;
    }

    fprintf(Puntatore_File, "Valigia %d\n", n);

    while(i<numero_elementi_restanti)
    {
        p_corr += sol[i].peso;
        if(p_corr > peso_massimo)
        {
            n++;
            fprintf(Puntatore_File,"\n\nValigia %d\n", n);
            fprintf(Puntatore_File, "%s    %.2f    %d\n", sol[i].oggetto, sol[i].peso, sol[i].importanza);
            p_corr = sol[i].peso;
        }
        else
        {
            fprintf(Puntatore_File, "%s    %.2f    %d\n", sol[i].oggetto, sol[i].peso, sol[i].importanza);
        }
        i++;
    }
    fclose(Puntatore_File);
    return n;
}
