#include <stdio.h>
#include <stdlib.h>
#include "tadpilha.h"

int main(void)
{
    int x, k;
    pilhad *cabeca;
    init(&cabeca);
    PUSH(&cabeca, 2);
    PUSH(&cabeca, 3);
    PUSH(&cabeca, 5);
    PUSH(&cabeca, 10);
    POP(&cabeca, &x);
    POP(&cabeca, &k);
    printf("%d, %d\n", x, k);
    exibir(cabeca);
    return 0;
}