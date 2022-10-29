#ifndef BST_H_DEFINED
#define BST_H_DEFINED
#include "Item.h"

typedef struct binary_search_tree *BST;

BST InizializzaBST();
void BSTInserimento_Foglia(BST bst, Item d);
void BSTInserimento_Radice(BST bst, Item d);
Item BSTRicerca(BST bst, int chiave);
void BST_Min(BST bst);
void BST_Max(BST bst);
void Pre_Order_Visit(BST bst);
void In_Order_Visit(BST bst);
void Post_Order_Visit(BST bst);
int AltezzaBST(BST bst);
int NumeroNodiBST(BST bst);

#endif
