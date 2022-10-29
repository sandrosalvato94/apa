#include <stdio.h>
#include <stdlib.h>
#define LUNGHEZZA 30
#include <string.h>

typedef enum {FALSE, TRUE} boolean;

int main()
{
    char stringa[LUNGHEZZA+1], sottostringa[LUNGHEZZA/2+1];
    int dim_stringa, dim_sottostringa;
    int i, j, r;
    boolean trovato, flag;


    printf("\nInserisci una parola di cui vuoi verificarne la periodicita ed in caso affermativo calcolarne il periodo minimo\nPer terminare digitare 'stop':\n\n");

    do
    {
       scanf("%s", stringa);
       dim_stringa = strlen(stringa);
       dim_sottostringa = 2; /*periodo minimo consentito per la periodicita'*/
       trovato = FALSE;
       if (strcmp(stringa, "stop") != 0)
       {
           while ((!trovato) &&(dim_sottostringa != dim_stringa))
           {
                r = 0;
                if (dim_stringa%dim_sottostringa == 0)
                {
                    strncpy(sottostringa, stringa, dim_sottostringa);
                    flag = FALSE;
                    for (i=dim_sottostringa+1; i<dim_stringa && !flag; i++)
                    {
                        for (j=0; j<dim_sottostringa && !flag; j++)
                        {
                            if (sottostringa[j] != stringa[i])
                            {
                                r++;
                                flag = TRUE;
                            }
                            i++;
                        }
                    }
                    if (r==0)
                    {
                        printf("\nLa stringa %s e' periodica di periodo minimo %d\n", stringa, dim_sottostringa);
                        trovato = TRUE;
                    }
                }
                else
                {
                    dim_sottostringa++;
                }
            }
            if (trovato == FALSE)
            {
                printf("\nLa stringa %s non e' periodica\n", stringa);
            }
        }
    }
    while (strcmp(stringa, "stop") != 0);
    printf("\nIl programma e' terminato.\n");
    system("PAUSE");
    return 0;
}
