#include "BST.h"
#include "Item.h"
#include <stdlib.h>
#include <stdio.h>

Item NULLitem = EMPTYITEM;

typedef struct nodo* link;

struct nodo
{
    Item item;
    link figlio_sinistro;
    link figlio_destro;
};

struct binary_search_tree
{
    link testa;
    int Numero_nodi;
    link z;
};

link NuovoNodo(Item d, link l, link r)
{
    link x = malloc(sizeof(*x));
    x->item = d;
    x->figlio_sinistro = l;
    x->figlio_destro = r;
    return x;
}

BST InizializzaBST()
{
    BST bst = malloc(sizeof(*bst));
    bst->Numero_nodi = 0;
    bst->testa = bst->z = NuovoNodo(NULLitem, NULL, NULL);
    return bst;
}

link InserimentoF(link h, link z, Item d)
{
    if (h==z)
    {
        return NuovoNodo(d, z, z);
    }
    else
    {
        if (less(key(d), key(h->item)))
        {
            h->figlio_sinistro = InserimentoF(h->figlio_sinistro, z, d);
        }
        else
        {
            h->figlio_destro = InserimentoF(h->figlio_destro, z, d);
        }
    }
    return h;
}

void BSTInserimento_Foglia(BST bst, Item d)
{
    bst->testa = InserimentoF(bst->testa, bst->z, d);
}

link rotR(link y)
{
    link x = y->figlio_sinistro;
    y->figlio_sinistro = x->figlio_destro;
    x->figlio_destro = y;
    return x;
}

link rotL(link y)
{
    link x = y->figlio_destro;
    y->figlio_destro = x->figlio_destro;
    x->figlio_sinistro = y;
    return x;
}

link InserimentoR(link h, link z, Item d)
{
    if (h==z) /*Se il BST è vuoto*/
    {
        return (NuovoNodo(d, z, z));
    }
    if (less(key(d), key(h->item)))
    {
        h->figlio_sinistro = InserimentoR(h->figlio_sinistro, z, d);
        h = rotR(h);
    }
    else
    {
        h->figlio_destro = InserimentoR(h->figlio_destro, z, d);
        h = rotL(h);
    }
    return h;
}

void BSTInserimento_Radice(BST bst, Item d)
{
    bst->testa = InserimentoR(bst->testa, bst->z, d);
}

Item Ricerca(link h, link z, int a)
{
    if(h == z)
    {
        return NULLitem;
    }
    else
    {
        if (eq(key(h->item), a))
        {
            return h->item;
        }
        if (less(a, key(h->item)))
        {
            return Ricerca(h->figlio_sinistro, z, a);
        }
        else
        {
            return Ricerca(h->figlio_destro, z, a);
        }
    }
}

Item BSTRicerca(BST bst, int a)
{
    return Ricerca(bst->testa, bst->z, a);
}

void BST_Min(BST bst)
{
    link t;
    for (t = bst->testa; t->figlio_sinistro!=bst->z; t = t->figlio_sinistro);
    ITEMshow(t->item);
}

void BST_Max(BST bst)
{
    link t;
    for (t = bst->testa; t->figlio_destro!=bst->z; t = t->figlio_destro);
    ITEMshow(t->item);
}

void PreOrder(link h, link z)
{
    if (h == z)
    {
        return;
    }

    ITEMshow(h->item);
    PreOrder(h->figlio_sinistro, z);
    PreOrder(h->figlio_destro, z);
}

void Pre_Order_Visit(BST bst)
{
    PreOrder(bst->testa, bst->z);
}

void In_Order(link h, link z)
{
    if (h == z)
    {
        return;
    }
    In_Order(h->figlio_sinistro, z);
    ITEMshow(h->item);
    In_Order(h->figlio_destro, z);
}

void In_Order_Visit(BST bst)
{
    In_Order(bst->testa, bst->z);
}

void Post_Order(link h, link z)
{
    if (h == z)
    {
        return;
    }

    Post_Order(h->figlio_sinistro, z);
    Post_Order(h->figlio_destro, z);
    ITEMshow(h->item);
}

void Post_Order_Visit(BST bst)
{
    Post_Order(bst->testa, bst->z);
}

int Altezza(link h, link z)
{
    int a,b;
    if (h==z)
    {
        return 0;
    }
    a = Altezza(h->figlio_sinistro, z); /*Calcolo dell'altezza del sottoalbero sinistro*/
    b = Altezza(h->figlio_destro, z); /*Calcolo dell'altezza del sottoalbero destro*/
    if (a>b) /*L'altezza dell'albero è data dall'altezza massima fra le due altezze dei sottoalberi destro e sinistro + 1, che è la radice del BST*/
    {
        return a+1;
    }
    else
    {
        return b+1;
    }
}

int AltezzaBST(BST bst)
{
    return Altezza(bst->testa, bst->z);
}

int NumeroNodi(link h, link z)
{
    if (h==z)
    {
        return 0;
    }
    return (NumeroNodi(h->figlio_sinistro, z) + NumeroNodi(h->figlio_destro, z) + 1);
}

int NumeroNodiBST(BST bst)
{
    return NumeroNodi(bst->testa, bst->z);
}
