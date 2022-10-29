#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED
#define EMPTYITEM {-1, "0"}
#define neq(A, B) (A != B)
#define eq(A, B) (A == B)
#define less(A, B) (A < B)
#define key(A) (A->numero)

typedef struct dato *Item;

Item ITEMscan();
void ITEMshow(Item d);

#endif
