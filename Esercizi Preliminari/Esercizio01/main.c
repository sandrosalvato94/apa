#include <stdio.h>
#include <stdlib.h>
#define LUNGHEZZA 50

typedef struct
{
    float x;
    float y;
    float z;
} tipo_coordinate;

int main()
{
    FILE *fp;
    char riga[LUNGHEZZA+1];
    int r;
    tipo_coordinate coordinate1;
    tipo_coordinate coordinate2;

    if ((fp = fopen("Coordinate.txt", "r")) == NULL)
    {
        printf("\nERRORE nell'apertura del file Coordinate.txt\n");
        return EXIT_FAILURE;
    }

    r=0;
    coordinate1.x = coordinate1.y = coordinate1.z = coordinate2.x = coordinate2.y = coordinate2.z = 0;
    while (fgets(riga, LUNGHEZZA+1, fp) != NULL)
    {
        sscanf(riga, "%f%f%f", &coordinate1.x, &coordinate1.y, &coordinate1.z);
        coordinate2.x += coordinate1.x;
        coordinate2.y += coordinate1.y;
        coordinate2.z += coordinate1.z;
        r++;
    }
    fclose(fp);

    printf("\nBaricentro: %.1f %.1f %.1f\n", coordinate2.x/r, coordinate2.y/r, coordinate2.z/r);
    system("PAUSE");
    return 0;
}
