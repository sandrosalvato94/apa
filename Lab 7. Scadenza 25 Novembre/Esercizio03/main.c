#include <stdio.h>
#include <stdlib.h>
#define MAX_CIFRE 3
#define N 7

void powerset(int insieme[], int soluzione[], int indice);

int main()
{
    int vett[4] = {5, 6, 7, 8};
    int sol[MAX_CIFRE];

    powerset(vett, sol, 0);

    return EXIT_SUCCESS;
}

void powerset(int insieme[], int soluzione[], int indice)
{
    int i=0, numero;
    if (indice>=MAX_CIFRE)
    {
        numero = soluzione[0]*100 + soluzione[1]*10 + soluzione[2];
        if (numero%N == 0)
        {
            printf("%d\t", numero);
        }
        return;
    }
    for (i=0; i<4; i++)
    {
        soluzione[indice] = insieme[i];
        powerset(insieme, soluzione, indice+1);
    }
}
