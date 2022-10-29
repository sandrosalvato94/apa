#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE, TRUE} boolean;
int mark[9] = {0};
int vett[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

void Permutazioni(char *operand1, char *operand2, char *somma, int mark[], boolean *sol_trovata, int pos, int cifre, int sol[9]);
void Inserisci(char *operand1, char *operand2, char *somma, boolean *sol_trovata, int sol[9], int cifre);
boolean Controlla(char *operand1, char *operand2, char *somma);

int main(int argc, char *argv[])
{
    int cifre;
    char *operand1 = NULL;
    char *operand2 = NULL;
    char *somma = NULL;
    boolean trovato = FALSE;

    if (argc != 5)
    {
        printf("\nERRORE: Numero di parametri errati da linea di comando.\n");
        return EXIT_FAILURE;
    }

    cifre = atoi(argv[1]);
    operand1 = (char*)malloc((cifre+1)*sizeof(char));
    operand2 = (char*)malloc((cifre+1)*sizeof(char));
    somma = (char*)malloc((cifre+1)*sizeof(char));
    strcpy(operand1, argv[2]);
    strcpy(operand2, argv[3]);
    strcpy(somma, argv[4]);

    Permutazioni(operand1, operand2, somma, mark, &trovato, 0, cifre, vett);

    free(operand1);
    free(operand2);
    free(somma);

    return EXIT_FAILURE;
}

void Permutazioni(char *operand1, char *operand2, char *somma, int mark[], boolean *sol_trovata, int pos, int cifre, int sol[9])
{
    int i;

    if (*sol_trovata != TRUE)
    {
        if (pos >= 9)
        {
            Inserisci(operand1, operand2, somma, sol_trovata, sol, cifre);
            return;
        }

        for(i=0; i<9; i++)
        {
            if(mark[i] == 0)
            {
                mark[i] = 1;
                sol[pos] = i;
                Permutazioni(operand1, operand2, somma, mark, sol_trovata, pos+1, cifre, sol);
                mark[i] = 0;
            }
        }
    }
    return;
}

void Inserisci(char *operand1, char *operand2, char *somma, boolean *sol_trovata, int sol[9], int cifre)
{
    int k=0;
    int i=0;
    char *n1, *n2, *n3;

    n1 = malloc((cifre+1)*sizeof(char));
    n2 = malloc((cifre+1)*sizeof(char));
    n3 = malloc((cifre+1)*sizeof(char));

    strcpy(n1, operand1);
    strcpy(n2, operand2);
    strcpy(n3, somma);

    for (k=0; k<cifre; k++)
    {
        if(n1[k] == '_')
        {
            n1[k] = sol[i] + 49;
            i++;
        }
        if(n2[k] == '_')
        {
            n2[k] = sol[i] + 49;
            i++;
        }
        if(n3[k] == '_')
        {
            n3[k] = sol[i] + 49;
            i++;
        }
    }

    *sol_trovata = Controlla(n1, n2, n3);
}

boolean Controlla(char *operand1, char *operand2, char *somma)
{
    boolean trovato = FALSE;

    int num1, num2, sum;

    sscanf(operand1, "%d", &num1);
    sscanf(operand2, "%d", &num2);
    sscanf(somma, "%d", &sum);

    if (num1+num2==sum)
    {
        trovato = TRUE;
        printf("\n%d  +\n", num1);
        printf("%d  =\n", num2);
        printf("_________\n");
        printf("%d\n", sum);
        return trovato;
    }

    return trovato;
}
