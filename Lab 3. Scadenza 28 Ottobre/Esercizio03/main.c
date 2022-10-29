/*Alessandro Salvato S201129*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_PAROLE 100
#define MAX_CARAT 25
#include <string.h>
#include <ctype.h>

void StampaMenu();
int RicercaBinaria(char **lista_parole, int numero_parole, char *chiave);
int trova_indice_in_lista(char **lista_parole, int numero_parole, char *nuova_parola);
void OrdinaParoleAggiunte(char **lista_parole, int indice_partenza, int indice_arrivo, char *nuova_parola);
void OrdinaParoleTolte(char **lista_parole, int indice_partenza, int indice_arrivo);
void deallocazione_matrice(char **matrice, int Num_righe);
void RendiMinuscolo(char parola[], int lunghezza_parola);
void StampaLista(char **lista_parole, int num_parole);
int Verifica_presenza_parola_in_lista(char **lista_parole, int num_parole, char *n_parola);

int main()
{
    char **matrice;/*matrice[100][25+1]*/
    int decisione = 1;
    int dim_parola, i, num_parole, indice;
    char parola[MAX_CARAT+1];

    matrice = (char**)malloc(MAX_PAROLE*sizeof(char*));
    num_parole = 0;
    while (decisione!=0)
    {
        StampaMenu();
        scanf("%d", &decisione);
        printf("\n\n");

        switch (decisione)
        {
        case 1:
            {
                printf("\nInserisci la parola: ");
                scanf("%s", parola);
                dim_parola = strlen(parola);
                if (dim_parola<=MAX_CARAT)
                {
                    RendiMinuscolo(parola, dim_parola);
                    matrice[num_parole] = (char*)malloc((dim_parola+1)*sizeof(char));
                    strcpy(matrice[num_parole], parola);
                    if (num_parole>0)
                    {
                        indice = trova_indice_in_lista(matrice, num_parole, parola);
                        OrdinaParoleAggiunte(matrice, indice, num_parole, parola);
                        num_parole++;
                    }
                    else
                    {
                        num_parole++;
                    }
                }
                else
                {
                    printf("\nLa parola %s e' troppo lunga.\n", parola);
                    system("PAUSE");
                }
                break;
            }
        case 2:
            {
                if(num_parole>0)
                {
                    printf("\nDigita la parola da eliminare :");
                    scanf("%s", parola);
                    if((Verifica_presenza_parola_in_lista(matrice, num_parole, parola)) == 1)
                    {   if (num_parole>1)
                        {

                            if ((i = RicercaBinaria(matrice, num_parole, parola))> 0)
                            {
                                OrdinaParoleTolte(matrice, i, num_parole);
                                num_parole--;
                            }
                            else
                            {
                                printf("\nLa parola %s non e' presente in lista. Effettuare l'operazione successiva\n", parola);
                                system("PAUSE");
                            }
                        }
                        else
                        {
                            num_parole=0;
                        }
                    }
                    else
                    {
                        printf("\nParola non trovata\n");
                        system("PAUSE");
                    }

                }
                else
                {
                    printf("\nNon ci sono parole che possono essere eliminate\n");
                    system("PAUSE");
                }
                break;
            }
        case 3:
            {
                if (num_parole > 0)
                {
                    printf("\nRicerca la posizione in elenco della parola cercata inserita dall'utente: ");
                    scanf("%s", parola);
                    dim_parola = strlen(parola);
                    RendiMinuscolo(parola, dim_parola);
                    i = RicercaBinaria(matrice, num_parole, parola);
                    if (i>=0)
                    {
                        printf("\nLa posizione della parola %s e' la numero %d\n", parola, i+1);
                        system("PAUSE");
                    }
                    else
                    {
                        printf("\nLa parola %s non e' presente in elenco. Premere Invio per continuare\n", parola);
                        system("PAUSE");
                    }
                }
                else
                {
                    printf("\nNon sono ancora presenti parole in elenco\n");
                    system("PAUSE");
                }
                    break;
            }
        case 0:
            {
                deallocazione_matrice(matrice, num_parole);
                break;
            }
        case 4:
            {
                if (num_parole>0)
                {
                    StampaLista(matrice, num_parole);
                    system("PAUSE");
                }
                else
                {
                    printf("\nLista vuota\n");
                    system("PAUSE");
                }
                break;
            }
        default:
            {
                printf("\nERRORE: Comando non valido\n");
                system("PAUSE");
            }
        }
    }

    printf("\nProgramma terminato\n");
    system("PAUSE");

    return EXIT_SUCCESS;
}

void StampaMenu()
{
        printf("\nSelezione una delle seguenti operazioni: \n\n");
        printf("\n1 - Introduci una parola nuova");
        printf("\n2 - Elimina una parola");
        printf("\n3 - Verifica la presenza di una parola nell'elenco");
        printf("\n4 - Stampa Lista");
        printf("\n0 - Per terminare");
        printf("\nScelta dell'utente: ");
}

int RicercaBinaria(char **lista_parole, int numero_parole, char *chiave)
{
    int flag = 0;
    int a=0;
    int b=numero_parole;
    int c=(a+b)/2;

    while (a!=b)
    {
        if (strcmp(lista_parole[c], chiave) == 0)
        {
            flag = 1;
            break;
        }
        if (strcmp(lista_parole[c], chiave) < 0)
        {
            a = c;
            c = (a+b)/2;
        }
        if (strcmp(lista_parole[c], chiave) > 0)
        {
            b = c;
            c = (a+b)/2;
        }
    }
    if (flag == 1)
    {
        return(c);
    }
    else
    {
        return -1;
    }
}

int trova_indice_in_lista(char **lista_parole, int numero_parole, char *nuova_parola)
{
    int i;

    for (i=0; i<numero_parole; i++)
    {
        if (strcmp(lista_parole[i], nuova_parola) > 0)
        {
            break;
        }
    }

    return (i);

}

void deallocazione_matrice(char **matrice, int Num_righe)
{
    int i;

    for (i=0; i<Num_righe; i++)
    {
        free(matrice[i]);
    }
    free(matrice);
}


void RendiMinuscolo(char parola[], int lunghezza_parola)
{
    int i;

    for (i=0; i<lunghezza_parola; i++)
    {
        parola[i] = tolower(parola[i]);
    }

    parola[i] = '\0';
}

void OrdinaParoleAggiunte(char **lista_parole, int indice_partenza, int indice_arrivo, char *nuova_parola)
{
    int i;

    for(i=indice_arrivo-1; i>=indice_partenza; i--)
    {
        strcpy(lista_parole[i+1], lista_parole[i]);
        if (i==indice_partenza)
        {
            strcpy(lista_parole[i], nuova_parola);
        }
    }
}

void OrdinaParoleTolte(char **lista_parole, int indice_partenza, int indice_arrivo)
{
    int k;

    for (k=indice_partenza; k<indice_arrivo-1; k++)
    {
        strcpy(lista_parole[k], lista_parole[k+1]);
    }
}

void StampaLista(char **lista_parole, int num_parole)
{
    int i;

    for (i=0; i<num_parole; i++)
    {
        printf("\n%s", lista_parole[i]);
    }

    printf("\n");
}

int Verifica_presenza_parola_in_lista(char **lista_parole, int num_parole, char *n_parola)
{
    int i;
    int flag = 0;

    for(i=0; i<num_parole && flag==0; i++)
    {
        if (strcmp(lista_parole[i], n_parola) == 0)
        {
            flag = 1;
        }
    }

    return(flag);
}
