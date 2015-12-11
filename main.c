#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "beamsearch.h"
#include "branchbound.h"
#define INF 9999999

int main(int argc, char *argv[]) {
	if(argc < 3) {
		printf("Usage: ./trab3 <n> <algoritmo>\n");
		return 1;
	}
	
	if(strcmp(argv[2], "bs") && strcmp(argv[2], "bb")) {
		printf("Apenas dois algoritmos são válidos: bs e bb\n");
		return 2;
	}
	
	int i, j, n = atoi(argv[1]);

	int **jobs = (int**) calloc(n, sizeof(int*));
	
	for(i = 0; i < n; i++) {
		jobs[i] = (int*) calloc(3, sizeof(int));
	}
	
	for(i = 0; i < n; i++) {
		for(j = 0; j < 3; j++) {
			scanf("%d", &jobs[i][j]);
		}
	}
	
	BeamSearch *beam = criarBeamSearch(n, jobs, 15);
	for(i = 0; i < n; i++) {
		proxGeracao(beam);
		podarGeracao(beam);
	}
	
	if(!strcmp(argv[2], "bs")) {
		imprimirMelhor(beam);
	}
	
	else if(!strcmp(argv[2], "bb")) {
		
		int resp, seq[n];
		int tempo[n], deadline[n], multa[n];
		
		for(i=0;i<n;i++){
			
			tempo[i] = jobs[i][0];
			deadline[i] = jobs[i][1];
			multa[i] = jobs[i][2];
			
		}
		
		resp = bb(n, tempo, deadline, multa, seq, beam->heap->seq->multa + 1);
		
		printf("%d:", resp);
		
		for(i=0;i<n;i++)
			printf(" %d", seq[i]);
		
		printf("\n");
		
	}
	
	liberarBeamSearch(beam);
		
	for(i = 0; i < n; i++) {
		free(jobs[i]);
	}
	
	free(jobs);
	
	return 0;
}


