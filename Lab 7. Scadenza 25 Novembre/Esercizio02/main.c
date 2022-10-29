#include <stdio.h>
#include <stdlib.h>

typedef enum {FALSE, TRUE} boolean;

void Acquisisci_Alfabeto(char **alfabeta);
void disposizioni(FILE *Puntatore_file, char *alfabeto, char vett[], int k);

int k;
char vett[5];

int main(int argc, char *argv[])
{
    FILE *fp;
    char *alfabeto = NULL;
    int i;

    if (argc != 2)
    {
        printf("\nERRORE: Numero di parametri errati da linea di comando.\n");
        return EXIT_FAILURE;
    }

    if ((fp = fopen(argv[1], "w")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in scrittura.\n", argv[1]);
        return EXIT_FAILURE;
    }

    alfabeto = (char *)malloc(21*sizeof(char));
    if (alfabeto == NULL)
    {
        printf("\nNon c'e' abbastanza memoria disponibile.\n");
        return EXIT_FAILURE;
    }
    Acquisisci_Alfabeto(&alfabeto);
    disposizioni(fp, alfabeto, vett, 0);
    free(alfabeto);
    fclose(fp);

    return EXIT_SUCCESS;
}

void Acquisisci_Alfabeto(char **alfabeta)
{
    char c;
    char *s = *alfabeta;
    for(c='a';c<='z';c++)
    {
        if(c!='k' && c!='j' && c!='x' && c!='y' && c!='w')
        {
            *s=c;
            s++;
        }
    }
}

void disposizioni(FILE *Puntatore_file, char *alfabeto, char vett[], int k)
{
    int indice_alfabeto;
    boolean aggiunto;

    if (k>=4)
    {
        vett[4] = '\0';
        fprintf(Puntatore_file,"%s\n", vett);
        return;
    }

   for (indice_alfabeto = 0; indice_alfabeto<21; indice_alfabeto++)
   {

        if (k==0)
       {
           vett[k] = alfabeto[indice_alfabeto];
          aggiunto = TRUE;
       }
       else
       {
           if ((k>0) && (k<4))
            {
                if ((((vett[k-1] == 'a') || (vett[k-1] == 'e') || (vett[k-1] == 'i') || (vett[k-1] == 'o') || (vett[k-1] == 'u'))) && ((alfabeto[indice_alfabeto] != 'a') && (alfabeto[indice_alfabeto] != 'e') && (alfabeto[indice_alfabeto] != 'i') && (alfabeto[indice_alfabeto] != 'o') && (alfabeto[indice_alfabeto] != 'u')))
                {
                    vett[k] = alfabeto[indice_alfabeto];
                   aggiunto = TRUE;
                }
                else
                {
                    if ((((vett[k-1] != 'a') && (vett[k-1] != 'e') && (vett[k-1] != 'i') && (vett[k-1] != 'o') && (vett[k-1] != 'u'))) && ((alfabeto[indice_alfabeto] == 'a') || (alfabeto[indice_alfabeto] == 'e') || (alfabeto[indice_alfabeto] == 'i') || (alfabeto[indice_alfabeto] == 'o') || (alfabeto[indice_alfabeto] == 'u')))
                    {
                        vett[k] = alfabeto[indice_alfabeto];
                      aggiunto = TRUE;
                    }
                }
            }
        }

        if(aggiunto == TRUE)
        {
            disposizioni(Puntatore_file, alfabeto, vett, k+1);
            aggiunto = FALSE;
        }
   }
}
