#include <stdio.h>
#include <stdlib.h>
#define SOMMA 30
#define DIM_RES 3
#define DIM_VETT 8

int* InizializzaVett(int dim_vett);
int SommaElementiVett(int *res);
void Stampa(int *res);
void DisposizioniRipetizione(int *vett, int *res, int pos);

int count = 0;

int main()
{
    int vett[DIM_VETT] = {1, 3, 5, 7, 9, 11, 13, 15};
    int *vett_res;

    vett_res = InizializzaVett(DIM_RES);
    DisposizioniRipetizione(vett, vett_res, 0);
    printf("\nN. Disp_Rip = %d", count);
    system("PAUSE");
    free(vett_res);

    return EXIT_SUCCESS;
}

int* InizializzaVett(int dim_vett)
{
    int i;
    int *vett = malloc(dim_vett*sizeof(int));

    for(i=0; i<dim_vett; i++)
    {
        vett[i] = 0;
    }

    return vett;
}

int SommaElementiVett(int *res)
{
    int i;
    int sum=0;

    for(i=0; i<DIM_RES; i++)
    {
        sum += res[i];
    }

    return sum;
}

void Stampa(int *res)
{
    int i;

    printf("\n");
    for(i=0; i<DIM_RES; i++)
    {
        if(i==DIM_RES-1)
        {
            printf("%d = %d", res[i], SOMMA);
        }
        else
        {
            printf("%d + ", res[i]);
        }
    }
}

void DisposizioniRipetizione(int *vett, int *res, int pos)
{
    int j;

    if(pos>=DIM_RES)
    {
        count++;
        if(SommaElementiVett(res) == SOMMA)
        {
            Stampa(res);
            return;
        }
        return;
    }

    for(j=0; j<DIM_VETT; j++)
    {
        res[pos] = vett[j];
        DisposizioniRipetizione(vett, res, pos+1);
    }
}

