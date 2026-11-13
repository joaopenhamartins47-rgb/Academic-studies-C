#include <stdio.h>
#include <stdlib.h>

/* Metodo da divisao: retorna uma posicao de 1 ate n */
int dh(int chave, int n) {
    return (chave % n) + 1;
}

/* Soma os codigos ASCII dos caracteres */
int adh(char chave[], int n) {
    int i, soma;

    soma = 0;

    for (i = 0; chave[i] != '\0'; i++) {
        soma = soma + chave[i];
    }

    return (abs(soma) % n) + 1;
}

/* Soma os caracteres com deslocamentos de 0 ate 7 bits */
int sdh(char chave[], int n) {
    int i, soma;

    soma = 0;

    for (i = 0; chave[i] != '\0'; i++) {
        soma = soma + (chave[i] << (i % 8));
    }

    return (abs(soma) % n) + 1;
}

/* Meio do quadrado: reproduz o recorte da tabela do PDF.
   Retorna uma posicao de 0 ate 7. */
int mq(int chave) {
    int quadrado, mascara, resultado;

    quadrado = chave * chave;

    /* Cria a mascara 111 em binario, que vale 7 */
    mascara = (1 << 3) - 1;

    /* Descarta os 6 bits da direita e seleciona os proximos 3 */
    resultado = (quadrado >> 6) & mascara;

    return resultado;
}

int main() {
    int n;

    n = 5;

    printf("METODO DA DIVISAO - n = %d\n", n);
    printf("54 -> %d\n", dh(54, n));
    printf("21 -> %d\n", dh(21, n));
    printf("15 -> %d\n", dh(15, n));

    n = 7;

    printf("\nSOMA DOS CARACTERES - n = %d\n", n);
    printf("ABC -> %d\n", adh("ABC", n));
    printf("CBA -> %d\n", adh("CBA", n));

    printf("\nSOMA COM DESLOCAMENTOS - n = %d\n", n);
    printf("ABC -> %d\n", sdh("ABC", n));
    printf("ACB -> %d\n", sdh("ACB", n));
    printf("BAC -> %d\n", sdh("BAC", n));
    printf("BCA -> %d\n", sdh("BCA", n));
    printf("CAB -> %d\n", sdh("CAB", n));
    printf("CBA -> %d\n", sdh("CBA", n));

    printf("\nMEIO DO QUADRADO - 8 posicoes\n");
    printf("7  -> %d\n", mq(7));
    printf("12 -> %d\n", mq(12));
    printf("15 -> %d\n", mq(15));
    printf("22 -> %d\n", mq(22));
    printf("25 -> %d\n", mq(25));

    return 0;
}