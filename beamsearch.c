#include "beamsearch.h"

BeamSearch *criarBeamSearch(int n, int **jobs, int width) {
	BeamSearch *beam = (BeamSearch*) malloc(sizeof(BeamSearch));
	beam->jobs = jobs;
	beam->numJobs = n;
	beam->numSeqs = 1;
	beam->width = width;
	
	Sequencia *seq = criarSequencia(n, jobs);
	beam->heap = createSkewHeap(seq);
	
	return beam;
}

void proxGeracao(BeamSearch *beam) {
	int i, num, count, n = beam->numSeqs, pos = 0;
	Sequencia **seqs = (Sequencia**) calloc(n, sizeof(Sequencia*));
	Sequencia **filhos;
	SkewHeap *heap = NULL;
	
	getSeqs(beam->heap, &seqs, &pos);
	
	count = 0;
	for(i = 0; i < n; i++) {
		filhos = gerarFilhos(seqs[i]);
		num = seqs[i]->numJobs - seqs[i]->atendidos;
		
		// Destruindo os pais
		liberarSeq(seqs[i]);
		
		count += num;
		heap = construct(heap, filhos, num);
	}
	
	// Liberando o vetor de ponteiros pros filhos
	free(filhos);
	
	// Destruindo a heap antiga
	liberarHeap(beam->heap);
	
	// Liberando o vetor de ponteiros pros pais
	free(seqs);
	
	beam->numSeqs = count;
	beam->heap = heap;
}

void podarGeracao(BeamSearch *beam) {
	int w = beam->width;
	if(w > beam->numSeqs)
		return;
	
	SkewHeap *heap = NULL;
	int i;
	for(i = 0; i < w; i++) {
		heap = insert(heap, beam->heap->seq);
		beam->heap = deleteMin(beam->heap);
	}
	
	// Eliminando as piores sequências
	destruirHeap(beam->heap);
	
	// Ficando com os w melhores
	beam->numSeqs = w;
	beam->heap = heap;
}

void imprimirMelhor(BeamSearch *beam) {
	printSeq(beam->heap->seq);
}

void liberarBeamSearch(BeamSearch *beam) {
	destruirHeap(beam->heap);
	free(beam);
}


