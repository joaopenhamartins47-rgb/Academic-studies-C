#include <stdio.h>
#include <stdlib.h>
#include "TADFilaP.h"

int main(void)
{
    filap *inicio;
    init(&inicio);
    int x, p;
    Enqueue(&inicio, 10, 2);
    Enqueue(&inicio, 5, 1);
    Enqueue(&inicio, 37, 3);
    Enqueue(&inicio, 7, 2);
    Dequeue(&inicio, &x, &p);
    printf("Elemento removido: %d %d\n", x, p);
    exibe(inicio);

    return 0;
}