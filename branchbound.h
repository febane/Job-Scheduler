#include<stdio.h>
#include<stdlib.h>
#define INF 9999999

int bb(int n, int temp[], int deadline[], int multa[], int seq[], int c);
void buscaMenorCusto(int n, int tempo[], int deadline[], int multa[], int seq[], int ini, int visitado[], int atseq[]);
void zera(int n, int vet[]);
void adicionaSeq(int ini, int n, int atseq[]);
void pv(int n, int vet[]);
void removeSeq(int n, int atseq[]);
