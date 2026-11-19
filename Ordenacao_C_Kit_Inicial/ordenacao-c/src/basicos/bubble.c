#include "../algoritmos.h"

void bubbleSort(int v[], int n, Metricas *m)
{
    for (int limite = n; limite > 1; --limite) {
        int houve_troca = 0;

        /* O maior elemento desta passada termina na posição limite - 1. */
        for (int i = 1; i < limite; ++i) {
            ++m->comparacoes;
            if (v[i - 1] > v[i]) {
                int anterior = v[i - 1];
                v[i - 1] = v[i];
                v[i] = anterior;
                ++m->trocas;
                houve_troca = 1;
            }
        }

        if (!houve_troca) {
            break;
        }
    }
}

