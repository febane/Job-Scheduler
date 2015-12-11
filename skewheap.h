#include <stdio.h>
#include <stdlib.h>
#include "sequencia.h"

typedef struct skewheap {
	Sequencia *seq;
	struct skewheap *left;
	struct skewheap *right;
} SkewHeap;

SkewHeap *createSkewHeap(Sequencia *seq);
SkewHeap *merge(SkewHeap *h1, SkewHeap *h2);
SkewHeap *insert(SkewHeap *root, Sequencia *seq);
SkewHeap *construct(SkewHeap *root, Sequencia **seqs, int n);
SkewHeap *deleteMin(SkewHeap *root);
void preOrder(SkewHeap *root);
void inOrder(SkewHeap *root);
void postOrder(SkewHeap *root);
void printHeap(SkewHeap *root);
void getSeqs(SkewHeap *root, Sequencia ***seqs, int *pos);
void liberarHeap(SkewHeap *root);
void destruirHeap(SkewHeap *root);


