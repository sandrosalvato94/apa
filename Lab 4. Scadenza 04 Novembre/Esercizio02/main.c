/*Alessandro Salvato S201129*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_CARAT 35
#include <string.h>
#include <ctype.h>
#define ERR_MDINAMIC "ERRORE: Non c'e' abbastanza memoria disponibile"
#define MASCHIO "M"
#define FEMMINA "F"

typedef struct
{
    char *nome;
    char *cognome;
    int giorno;
    int mese;
    int anno;
    char *sesso;
}tipo_studente;


char* RendiMinuscolo(char *parola, int lunghezza_parola);
void ordina(tipo_studente **lista_studenti, int Num_studenti, int indice_inserimento);
void inserisci_ordina(tipo_studente *lista_studenti, int Num_studenti);
void stamparagazzi_e(FILE *Puntatore_file , tipo_studente *lista_studenti, int Num_studenti, char *sesso);
void dealloca_memoria (tipo_studente *lista_studenti, int Num_studenti);


int main(int argc, char *argv[])
{
    FILE *fpstu, *fpboys, *fpgirls;
    tipo_studente *p_studente=NULL;
    int num_studenti, day, month, year;
    char name[MAX_CARAT+1], surname[MAX_CARAT+1], sex[2];
    int dim_name, dim_surname;
    int i;

    if (argc != 4)
    {
        printf("\nERRORE: Numero di parametri errato da linea di comando\n");
        return EXIT_FAILURE;
    }

    if ((fpstu = fopen(argv[1], "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in lettura\n", argv[1]);
        return EXIT_FAILURE;
    }
    if ((fpboys = fopen(argv[2], "w")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in scrittura\n", argv[2]);
        return EXIT_FAILURE;
    }
    if ((fpgirls = fopen(argv[3], "w")) == NULL)
    {
        printf("\nERRORE nell'apertura del file %s in scrittura\n", argv[3]);
        return EXIT_FAILURE;
    }

    fscanf(fpstu, "%d", &num_studenti);

    p_studente = (tipo_studente*)malloc(num_studenti*sizeof(tipo_studente));
    if (p_studente == NULL)
    {
        printf("\nERRORE: Non c'e' abbastanza memoria disponibile\n");
        return EXIT_FAILURE;
    }
    i=0;
    while ((fscanf(fpstu, "%s%s%d%*c%d%*c%d%s", name, surname, &day, &month, &year,  sex)) != EOF)
    {
        dim_name = strlen(name);
        p_studente[i].nome = (char*)malloc((dim_name+1)*sizeof(char));
        if (p_studente[i].nome == NULL)
        {
            printf("%s\n", ERR_MDINAMIC);
            system("PAUSE");
            return EXIT_FAILURE;
        }
        strcpy(p_studente[i].nome, name);
        dim_surname = strlen(surname);
        p_studente[i].cognome = (char *)malloc((dim_surname+1)*sizeof(char));
        if (p_studente[i].cognome == NULL)
        {
            printf("%s\n", ERR_MDINAMIC);
            system("PAUSE");
            return EXIT_FAILURE;
        }
        strcpy(p_studente[i].cognome, surname);
        p_studente[i].giorno = day;
        p_studente[i].mese = month;
        p_studente[i].anno = year;
        p_studente[i].sesso = (char*)malloc(2*sizeof(char));
        if (p_studente[i].sesso == NULL)
        {
            printf("%s\n", ERR_MDINAMIC);
            system("PAUSE");
            return EXIT_FAILURE;
        }
        strcpy(p_studente[i].sesso, sex);
        if (i>0)
        {
            inserisci_ordina(p_studente, i);
        }
        i++;
    }/*Fine while*/
    fclose(fpstu);
    stamparagazzi_e(fpboys, p_studente, i, MASCHIO);
    fclose(fpboys);
    stamparagazzi_e(fpgirls, p_studente, i, FEMMINA);
    fclose(fpgirls);

    dealloca_memoria(p_studente, num_studenti);
    free(p_studente);

    return 0;
}

char* RendiMinuscolo(char *parola, int lunghezza_parola)
{
    int i;

    for (i=0; i<lunghezza_parola; i++)
    {
        parola[i] = tolower(parola[i]);
    }
    return(parola);
}

void inserisci_ordina(tipo_studente *lista_studenti, int Num_studenti)
{
    int i;

    for (i=0; i<Num_studenti; i++)
    {
        if (lista_studenti[Num_studenti].anno < lista_studenti[i].anno) /*Se questa condizione non viene soddisfatta, si verifica l'uguaglianza*/
        {
            ordina(&lista_studenti, Num_studenti, i);
            break;
        }
        else
        {
            if (lista_studenti[Num_studenti].anno == lista_studenti[i].anno) /*Se non e' uguale allora l'anno dello studente appena aggiunto sarà maggiore. Quindi viene posto alla fine della lista*/
            {
                if (lista_studenti[Num_studenti].mese < lista_studenti[i].mese)
                {
                    ordina(&lista_studenti, Num_studenti, i);
                    break;
                }
                else
                {
                    if (lista_studenti[Num_studenti].mese == lista_studenti[i].mese)
                    {
                        if (lista_studenti[Num_studenti].giorno < lista_studenti[i].giorno)
                        {
                            ordina(&lista_studenti, Num_studenti, i);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void ordina(tipo_studente **lista_studenti, int Num_studenti, int indice_inserimento)
{
    tipo_studente *stud = *lista_studenti;
    tipo_studente tmpstud;
    int j;

    tmpstud = stud[Num_studenti];

    for(j= Num_studenti-1; j>=indice_inserimento; j--)
    {
        stud[j+1] = stud[j];
    }

    stud[indice_inserimento] = tmpstud;

    *lista_studenti = stud;
}

void stamparagazzi_e(FILE *Puntatore_file , tipo_studente *lista_studenti, int Num_studenti, char *sesso)
{
    int i;

    for (i=0; i<Num_studenti; i++)
    {
        if (strcmp(lista_studenti[i].sesso, sesso) == 0)
        {
            fprintf(Puntatore_file, "%s %s %d/%d/%d %s\n", lista_studenti[i].nome, lista_studenti[i].cognome, lista_studenti[i].giorno, lista_studenti[i].mese, lista_studenti[i].anno, lista_studenti[i].sesso);
        }
    }
}

void dealloca_memoria (tipo_studente *lista_studenti, int Num_studenti)
{
    int i;

    for (i=0; i<Num_studenti; i++)
    {
        free(lista_studenti[i].nome);
        free(lista_studenti[i].cognome);
        free(lista_studenti[i].sesso);
    }
}
