#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "metricas.h"

typedef void (*SortFn)(int[], int, Metricas *);

void bubbleSort(int v[], int n, Metricas *m);
void selectionSort(int v[], int n, Metricas *m);
void insertionSort(int v[], int n, Metricas *m);
void mergeSort(int v[], int n, Metricas *m);
void quickSort(int v[], int n, Metricas *m);
void heapSort(int v[], int n, Metricas *m);

#endif

