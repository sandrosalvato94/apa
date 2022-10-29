#include <stdio.h>
#include <stdlib.h>

int RecursiveCatalan (int n);

int main()
{
    int indice, numero;

    printf("\nI numeri di Catalan hanno svariate applicazioni nel calcolo combinatorio,\nad esempio Cn è il numero di modi in cui un poligono convesso con n+2 lati può essere suddiviso in triangoli.\nPer n=4 il poligono è un esagono e i modi sono 14\n");
    do
    {
        printf("\nInserisci il numero di Catalan da calcolare: ");
        scanf("%d", &indice);
        if (indice <0)
        {
            printf("\nIndice non valido. Deve essere un valore positivo o al piu' uguale a zero\n");
            system("PAUSE");
        }
    }
    while (indice<0);


        numero = RecursiveCatalan(indice);
        printf("\n%d\n\n", numero);


    system("PAUSE");


    return 0;
}

int RecursiveCatalan(int n)
{
    int num_somme = n;
    int num_cat1, num_cat2, somma = 0;
    int i;

    if (n == 0)
        {

            return 1;
        }

    while (num_somme>0)
    {
        num_cat1 = RecursiveCatalan(n-num_somme);
        num_cat2 = RecursiveCatalan(num_somme-1);
        somma += num_cat1*num_cat2;

        num_somme--;
    }


    return somma;
}
