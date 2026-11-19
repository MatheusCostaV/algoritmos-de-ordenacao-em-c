#include "algoritmos.h"

#include <stdio.h>
#include <stdlib.h>

static int verifica(const char *cenario, SortFn ordenar,
                    int v[], const int esperado[], int n)
{
    Metricas m = {0};
    ordenar(v, n, &m);
    for (int i = 0; i < n; ++i) {
        if (v[i] != esperado[i]) {
            printf("FALHOU: %s, índice %d, esperado %d, obtido %d\n",
                   cenario, i, esperado[i], v[i]);
            return 1;
        }
    }
    printf("PASSOU: %s\n", cenario);
    return 0;
}

int main(void)
{
    int falhas = 0;
    int desordenado[] = {3, -1, 3, 0};
    const int esperado[] = {-1, 0, 3, 3};
    int crescente[] = {1, 2, 3};
    const int esperado_crescente[] = {1, 2, 3};
    int decrescente[] = {3, 2, 1};
    int unitario[] = {7};
    const int esperado_unitario[] = {7};

    falhas += verifica("Bubble com duplicatas e negativo", bubbleSort, desordenado, esperado, 4);
    falhas += verifica("Bubble com vetor crescente", bubbleSort, crescente, esperado_crescente, 3);
    falhas += verifica("Bubble com vetor decrescente", bubbleSort, decrescente, esperado_crescente, 3);
    falhas += verifica("Bubble com vetor unitário", bubbleSort, unitario, esperado_unitario, 1);
    falhas += verifica("Bubble com vetor vazio", bubbleSort, NULL, NULL, 0);

    int exemplo[] = {3, 1, 2};
    Metricas m = {0};
    bubbleSort(exemplo, 3, &m);
    int metricas_corretas = m.comparacoes == 3 && m.trocas == 2;
    printf("%s: Bubble com 3 comparações e 2 trocas\n", metricas_corretas ? "PASSOU" : "FALHOU");
    falhas += !metricas_corretas;

    /* TODO: acrescente pelo menos dois casos para cada algoritmo implementado. */
    puts("Escopo da suíte inicial: Bubble Sort.");
    int selection_exemplo[] = {3, 1, 2};
int selection_duplicatas[] = {3, -1, 3, 0};

falhas += verifica("Selection com vetor desordenado", selectionSort,
                   selection_exemplo, esperado_crescente, 3);
falhas += verifica("Selection com duplicatas e negativo", selectionSort,
                   selection_duplicatas, esperado, 4);
                   
    return falhas ? EXIT_FAILURE : EXIT_SUCCESS;
}

