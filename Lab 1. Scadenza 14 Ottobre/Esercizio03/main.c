#include <stdio.h>
#include <stdlib.h>
#define LUNGHEZZA 30
#include <string.h>

typedef enum {FALSE, TRUE} boolean;

int main()
{
    char parola[LUNGHEZZA+1], sottoparola[LUNGHEZZA/2+1];
    int dim_parola, dim_sottoparola, r, i, j;
    char carat;
    boolean trovato;

    printf("\nInserisci le parole per verificarne la pariodicità e l'eventuale periodo minimo.\nDigitare 'stop' per terminare:\n\n");

    do
    {
       scanf("%s", parola);
       dim_parola = strlen(parola);
       carat = parola[0];
       if (strcmp(parola, "stop")!=0)
         {
            if (dim_parola == 1)
            {
                printf("\nLa stringa %s non e' periodica\n", parola);
            }
            else
            {
                trovato = FALSE;
                for (dim_sottoparola=1; dim_sottoparola<=dim_parola/2 && !trovato; dim_sottoparola++)
                {
                    r=0;
                    if (dim_parola%dim_sottoparola == 0)
                    {
                        strncpy(sottoparola, parola, dim_sottoparola);

                        for (i=dim_sottoparola; i<dim_parola && r==0; i++)
                        {
                            for (j=0; j<dim_sottoparola && r==0; j++)
                            {
                                if (parola[i] != sottoparola[j])
                                {
                                    r++;
                                }
                                i++;
                            }
                            i--;
                        }
                        if (r==0)
                        {
                            trovato = TRUE;
                        }
                    }
                }
                if (trovato)
                {
                    printf("\nLa stringa %s e' periodica di periodo %d\n\n", parola, dim_sottoparola-1);
                }
                else
                {
                    printf("\nLa stringa %s non e' periodica\n\n", parola);
                }
            }
         }
         else
         {
             printf("\nProgramma Terminato\n\n");
             system("PAUSE");
         }
    }
    while (strcmp(parola, "stop") != 0);
    return 0;
}
