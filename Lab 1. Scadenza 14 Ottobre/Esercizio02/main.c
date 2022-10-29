#include <stdio.h>
#include <stdlib.h>
#define MAX_CARATTERI 80
#define MAX_PAROLE 100
#include <ctype.h>

typedef struct
{
    int numero;
    char parola[MAX_CARATTERI+1];
}tipo_chiave;

typedef enum {FALSE, TRUE} boolean;

int main()
{
    FILE *fpcod;
    FILE *fpdecod;
    FILE *fpdizio;
    char testo[MAX_CARATTERI+1];
    tipo_chiave chiave[MAX_PAROLE];
    int i,j;
    char carat;
    int num_parola;
    int tot_parole_dizio;
    boolean trovato;
    boolean fine_riga;

    if ((fpcod = fopen("codificato.txt", "r")) == NULL)   /*Verifico che l'apertura dei tre file sia corretta*/
    {
        printf("\nERRORE nell'apertura del file codificato.txt in lettura\n");
        return EXIT_FAILURE;
    }

    if ((fpdizio = fopen("dizionario.txt", "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file dizionario.txt in lettura\n");
        return EXIT_FAILURE;
    }

    if ((fpdecod = fopen("decodificato.txt", "w")) == NULL)
    {
        printf("\nERRORE nell'apertura del file decodificato.txt in scrittura\n");
        return EXIT_FAILURE;
    }
    i=0;
    while (((fscanf(fpdizio, "%d%s", &chiave[i].numero, chiave[i].parola))!= EOF) && (i<MAX_PAROLE)) /*Conoscendo le dimensioni del file dizionario.txt per semplicità lo salvo. Per semplicità lo faccio in una struct*/
    {
        i++;
    }
    fclose(fpdizio);
    tot_parole_dizio = i;
    while ((fgets(testo, MAX_CARATTERI+1, fpcod)) != NULL) /*Leggo da file riga per riga, dopodichè effettuo l'analisi leggendo carattere per carattere*/
    {
       fine_riga = FALSE;
        for (i=0; i<MAX_CARATTERI && !fine_riga; i++)
        {
            carat = testo[i];
            if (carat == '$') /*Se il carattere e' il simbolo del dollaro allora inizio la decodifica analizzando il numero che lo segue*/
            {
                if (isdigit((testo[i+1]))) /*Nel caso il numero sia di una sola cifra*/
                {
                    num_parola = (int)testo[i+1] - 48;  /* devo riallineare la trasposizione in ASCII con l'ordine dei numeri naturali a partire da zero*/
                }
                if ((isdigit(testo[i+1]) && (isdigit(testo[i+2])))) /*Nel caso il numero sia di due cifre. NOTA: nelle specifiche viene indicato come il numero di decodifica sia compreso fra 0 e 99: non posso avere più di 2 cifre.*/
                {
                    num_parola = (int)(testo[i+1]-48)*10 + (int)testo[i+2] -48;
                }
                trovato = FALSE;
                for (j=0; j<tot_parole_dizio && !trovato; j++) /*confronto il numero di decodifica con quelli del dizionario. Quando trovo il numero uguale stampo la parola corrispondente, dopodichè smetto di cercare*/
                {
                    if (num_parola == chiave[j].numero)
                    {
                        fprintf(fpdecod, "%s", chiave[j].parola);
                        trovato = TRUE;
                    }
                }
            }
            if (carat != '$') /*Se il carattere e' diverso dal dollaro devo stampare tutto TRANNE il numero che segue il $.*/
           {
               if (isprint(carat))
               {
                    if (isdigit(carat)) /*Se il numero non segue il simbolo di decodifica allora lo stampo*/
                    {
                        if ((testo[i-1] != '$') && (testo[i-2] != '$'))
                        {
                            fprintf(fpdecod, "%c", carat);
                        }
                    }
                    else
                    {
                    fprintf(fpdecod, "%c", carat);
                    }
            }

                if (carat == '\0')
                {
                    if ((testo[i-2] == '.') && (testo[i-1] == '\n')) /*Stampa il <CR> se e' presente un punto, altrimenti stampa <SPACE> non andando a capo*/
                    {
                        fprintf(fpdecod,"\n");
                        fine_riga = TRUE;
                    }
                    else
                    {
                        fprintf(fpdecod, " ");
                        fine_riga = TRUE;
                    }
                }
           }
        }
    } /*fine while*/
    fclose(fpdecod);
    fclose(fpcod);
    return  EXIT_SUCCESS;
}



