#include "../algoritmos.h"

void selectionSort(int v[], int n, Metricas *m)
{
    for (int i = 0; i + 1 < n; ++i) {
        int menor = i;

        for (int j = i + 1; j < n; ++j) {
            ++m->comparacoes;
            if (v[j] < v[menor]) {
                menor = j;
            }
        }

        if (menor != i) {
            int temporario = v[i];
            v[i] = v[menor];
            v[menor] = temporario;
            ++m->trocas;
        }
    }
}