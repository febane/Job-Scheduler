#include "skewheap.h"

typedef struct beamSearch {
	int **jobs;
	int numJobs;
	int numSeqs;
	int width;
	SkewHeap *heap;
} BeamSearch;

BeamSearch *criarBeamSearch(int n, int **jobs, int width);
void proxGeracao(BeamSearch *beam);
void podarGeracao(BeamSearch *beam);
void imprimirMelhor(BeamSearch *beam);
void liberarBeamSearch(BeamSearch *beam);


