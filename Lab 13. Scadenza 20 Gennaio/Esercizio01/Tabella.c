#include "Tabella.h"
#include <string.h>
#define LUNGHEZZA 10
#define less(a, x) (strcmp(a[++i].nome_vertice, x.nome_vertice) < 0)
#define greater(a, x) (strcmp(a[--j].nome_vertice, x.nome_vertice) > 0)

struct symbtab
{
    Item *a;
    int num_ver_corr;
    int num_ver_tot;
};

ST ST_Init(int n)
{
    ST st = malloc(sizeof(*st));
    st->a = (Item*)malloc(n*sizeof(Item));
    st->num_ver_corr = 0;
    st->num_ver_tot = n;
    return st;
}

void ST_SCAN(ST t, char r[])
{
    int i;

    for(i=0; i<t->num_ver_tot; i++)
    {
        if(strcmp(t->a[i].nome_vertice, r) == 0)
        {
            return;
        }
    }
    strcpy(t->a[t->num_ver_corr].nome_vertice, r);
    t->num_ver_corr++;
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
    QuickSort(t->a, 0, t->num_ver_tot-1);
}

int BinarySearch(ST t, int a, int b, char *key)
{
    int c;
    while (a<=b)
    {
        c =  a+(b-a)/2;
        if(strcmp(key, t->a[c].nome_vertice) == 0)
        {
            return c;
        }
        else
        {
            if(strcmp(key, t->a[c].nome_vertice) < 0)
            {
                b=c-1;
            }
            else
            {
                if(strcmp(key, t->a[c].nome_vertice) > 0)
                {
                    a = c+1;
                }
            }
        }
    }

    return -1;
}

void ST_Show(ST t)
{
    int i;

    for (i=0; i<t->num_ver_tot; i++)
    {
        printf("\n%s", t->a[i].nome_vertice);
    }
}

int Conversion_Word2Numb(ST t, char *r)
{
    int b;
    b = BinarySearch(t, 0, t->num_ver_tot-1, r);
    return b;
}

char* ConversionNumber2Word(ST t, int n)
{
    return t->a[n].nome_vertice;
}
