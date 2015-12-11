#include <stdio.h>
#include <stdlib.h>

// Nome para as colunas da matriz dos procedimentos
#define TEMPO 0
#define DEADLINE 1
#define MULTA 2

typedef struct sequencia {
	int *vetor;
	int **jobs;
	int numJobs;
	int atendidos;
	int tempo;
	int multa;
	int lowerbound;
	int upperbound;
} Sequencia;

Sequencia *criarSequencia(int n, int **jobs);
Sequencia *copiarSequencia(Sequencia *seq);
void adicionarJob(Sequencia *seq, int job);
Sequencia **gerarFilhos(Sequencia *seq);
void imprimirSeq(Sequencia *seq);
void printSeq(Sequencia *seq);
void liberarSeq(Sequencia *seq);

