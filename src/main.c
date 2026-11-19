#include "algoritmos.h"

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    const char *nome;
    SortFn ordenar;
} Algoritmo;

static const Algoritmo algoritmos[] = {
    {"bubble", bubbleSort},
    {"selection", selectionSort},
    {"insertion", NULL},
    {"merge", NULL},
    {"quick", NULL},
    {"heap", NULL},
};

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Uso: %s <n> [bubble|selection|insertion|merge|quick|heap]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *fim;
    errno = 0;
    long tamanho = strtol(argv[1], &fim, 10);
    if (errno || fim == argv[1] || *fim || tamanho < 0 || tamanho > INT_MAX
        || (uintmax_t)tamanho > SIZE_MAX / sizeof(int)) {
        fputs("Informe um tamanho inteiro não negativo válido.\n", stderr);
        return EXIT_FAILURE;
    }

    int n = (int)tamanho;
    size_t bytes = (n == 0 ? 1u : (size_t)n) * sizeof(int);
    int *original = malloc(bytes);
    int *copia = malloc(bytes);
    if (!original || !copia) {
        free(original);
        free(copia);
        fputs("Não foi possível alocar os vetores.\n", stderr);
        return EXIT_FAILURE;
    }

    srand(42);
    for (int i = 0; i < n; ++i) {
        original[i] = rand() % 1000000;
    }

    int status = EXIT_SUCCESS;
    int encontrado = argc == 2;
    for (size_t i = 0; i < sizeof algoritmos / sizeof algoritmos[0]; ++i) {
        const Algoritmo *alg = &algoritmos[i];
        if (argc == 3 && strcmp(argv[2], alg->nome) != 0) {
            continue;
        }
        encontrado = 1;
        if (!alg->ordenar) {
            fprintf(stderr, "%s: implementação pendente.\n", alg->nome);
            if (argc == 3) {
                status = EXIT_FAILURE;
            }
            continue;
        }

        memcpy(copia, original, (size_t)n * sizeof(int));
        Metricas m = {0};
        clock_t inicio = clock();
        alg->ordenar(copia, n, &m);
        clock_t fim_medicao = clock();
        if (inicio == (clock_t)-1 || fim_medicao == (clock_t)-1) {
            fprintf(stderr, "%s: relógio indisponível.\n", alg->nome);
            status = EXIT_FAILURE;
            continue;
        }
        double tempo_ms = 1000.0 * (double)(fim_medicao - inicio) / CLOCKS_PER_SEC;
        printf("%s: n=%d, tempo=%.3f ms, comparações=%lu, trocas=%lu\n",
               alg->nome, n, tempo_ms, m.comparacoes, m.trocas);
    }
    if (!encontrado) {
        fprintf(stderr, "Algoritmo desconhecido: %s\n", argv[2]);
        status = EXIT_FAILURE;
    }

    free(copia);
    free(original);
    return status;
}

