#include <stdio.h>
#include <stdlib.h>
#include "TADPilha.h"




int main(void)
{
    descritor *desc;
    init(&desc);
    InserirInicio(desc, 10);
    InserirInicio(desc, 5);
    exibir(desc);
    return 0;
}