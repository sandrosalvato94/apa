#include <stdio.h>
#include <stdlib.h>

void RecursiveConversion (int numero_decimale, int base_arrivo);

int main()
{
    int num_decimal;
    int base;
    int num_convertito;

    printf("\nPROGRAMMA PER LA CONVERSIONE DI NUMERI DALLA BASE 10 ALLA BASE 'b'\n");
    printf("\nInserisci il numero da convertire: ");
    scanf("%d", &num_decimal);
    do /*Controllo se la base inserita dall'utente è corretta*/
    {
        printf("\nInserisci la base di conversione <compresa fra 2 e 10 inclusi> 'b': ");
        scanf("%d", &base);
        if ((base<2) || (base>10))
        {
            printf("\nBase non valida.\n");
            system("PAUSE");
        }
    }
    while ((base<2) || (base>10));

    printf("\n%d = ", num_decimal);
    RecursiveConversion(num_decimal, base);
    printf("\n");

    system("PAUSE");

    return 0;
}

void RecursiveConversion (int numero_decimale, int base_arrivo)
{
    int resto = numero_decimale%base_arrivo;

    if (numero_decimale>1)
    {
        RecursiveConversion(numero_decimale/base_arrivo, base_arrivo);
    }
    printf("%d", resto);
}
