#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tabella.h"
#define LUNGHEZZA 15
#define less(a, x) (strcmp(a[++i].city, x.city) < 0)
#define greater(a, x) (strcmp(a[--j].city, x.city) > 0)

struct tab
{
    Item *a;
    int grandezza;
};

ST ST_Init(int n)
{
    ST st = malloc(sizeof(*st));
    st->a = (Item*)malloc(n*sizeof(Item));
    st->grandezza = n;
    return st;
}

Item* ItemSCAN(FILE *Puntatore_File, Item* vett_item, int num_dati)
{
    int i;
    for (i=0; i<num_dati; i++)
    {
        fscanf(Puntatore_File, "%s%s", vett_item[i].city, vett_item[i].regione);
    }
    return vett_item;
}

ST ST_Scan(FILE *Puntatore_File, ST t)
{
    t->a = ItemSCAN(Puntatore_File, t->a, t->grandezza);
    return t;
}

void ST_Show(ST t)
{
    int i;

    for (i=0; i<t->grandezza; i++)
    {
        printf("\n%s %s", t->a[i].city, t->a[i].regione);
    }
}

void Swap(Item *a, int n1, int n2)
{
    Item tmp;
    tmp = a[n1];
    a[n1] = a[n2];
    a[n2] = tmp;
}

int Partition(Item *a, int l, int r)
{
    int i = l-1;
    int j=r;
    Item x = a[r];
    for( ; ; )
    {
        while(less(a, x));
        while(greater(a, x));
        if (j == l)
            break;
        if (i >= j)
            break;
        Swap(a, i, j);
    }
    Swap(a, i, r);
    return i;
}

void QuickSort(Item *a, int l, int r)
{
    int q;

    if (l>=r)
    {
        return;
    }
    q = Partition(a, l, r);
    QuickSort(a, l, q-1);
    QuickSort(a, q, r);
}

void ST_Sort(ST t)
{
    QuickSort(t->a, 0, t->grandezza-1);
}

int BinarySearch(ST t, int a, int b, char *key)
{
    int c;
    while (a<b)
    {
        c = (a+b)/2;
        if(strcmp(key, t->a[c].city) == 0)
        {
            return c;
        }
        else
        {
            if(strcmp(key, t->a[c].city) < 0)
            {
                b = c;
            }
            else
            {
                if(strcmp(key, t->a[c].city) > 0)
                {
                a = c;
                }
            }
        }
    }

    return -1;
}

int Scan_File(FILE *Puntatore_File, ST t, int *v, int *w, int *p)
{
    char r[LUNGHEZZA+1], h[LUNGHEZZA+1];
    if(fscanf(Puntatore_File, "%s%s%d", r,h,p) != EOF)
    {
        *v = BinarySearch(t, 0, t->grandezza, r);
        *w = BinarySearch(t, 0, t->grandezza, h);
        return 1;
    }
    else
    {
        return 0;
    }
}

Item Conversione_Number2City(ST t, int n)
{
    return t->a[n];
}

void ItemSHOW(Item item)
{
    printf("%s  %s", item.city, item.regione);
}

void DeallocaST(ST t)
{
    free(t->a);
    free(t);
}
