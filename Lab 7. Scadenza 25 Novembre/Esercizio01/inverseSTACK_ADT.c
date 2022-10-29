#include "inverseSTACK_ADT.h"
#define LUNGHEZZA 1000

struct in_stack
{
    item *stringa;
    int numero elementi;
    in_stack *succ;
};
