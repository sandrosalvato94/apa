#include <stdio.h>
#include <stdlib.h>
#define LUNGHEZZA 20
#include <string.h>
#include <ctype.h>

int ordine_alfabetico_2parole(char parola1[], char parola2[], int lunghezza_parola);

int main()
{
    FILE *fp;
    FILE *fp2;
    int num_righe;
    char parola[LUNGHEZZA+1];
    char parola_riferimento[LUNGHEZZA+1];
    int i;
    int x;

    if ((fp = fopen("albero.txt", "r")) == NULL)
    {
        printf("\nERRORE: Il file albero.txt non e' stato trovato");
        return EXIT_FAILURE;
    }

    if ((fp2 = fopen("esito.txt", "w")) == NULL)
    {
        printf("\nERRORE nell'apertura del file esito.txt in scrittura");
        return EXIT_FAILURE;
    }

    fscanf(fp, "%d%s", &num_righe, parola_riferimento);

    for (i=0; i<num_righe; i++)
    {
        fscanf(fp, "%s", parola);
        x = ordine_alfabetico_2parole(parola_riferimento, parola, LUNGHEZZA);
        if (x<=0)
        {
            fprintf(fp2, "%s\n", parola);
        }
    }

    fclose(fp);
    fclose(fp2);

    return 0;
}

int ordine_alfabetico_2parole(char parola1[], char parola2[], int lunghezza_parola)

{
    int n;
    char w1[lunghezza_parola+1];
    char w2[lunghezza_parola+1];

    strcpy(w1, parola1);
    strcpy(w2, parola2);

    for (n = 0; n<lunghezza_parola; n++)
    {
        w1[n] = tolower(w1[n]);
        w2[n] = tolower(w2[n]);
    }

    n = strcmp(w1, w2);

    return n;
}
