#include <stdio.h>
#include <stdlib.h>
#include "TADdesc.h"




int main(void)
{
    descritor *desc;
    init(&desc);
    InserirInicio(desc, 10);
    InserirInicio(desc, 5);
    InserirFinal(desc, 12);
    int removido = Exclui(desc, 5);
    printf("Excluido: %d\n", removido);
    exibir(desc);
    return 0;
}