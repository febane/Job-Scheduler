#include "sequencia.h"

Sequencia *criarSequencia(int n, int **jobs) {
	Sequencia* seq = (Sequencia*) malloc(sizeof(Sequencia));
	int i;
	
	seq->numJobs = n;
	
	seq->vetor = (int*) calloc(n, sizeof(int));
	for(i = 0; i < n; i++) {
		seq->vetor[i] = 0;
	}
	
	seq->jobs = jobs;
	seq->atendidos = 0;
	seq->tempo = 0;
	seq->multa = 0;
	seq->lowerbound = 0;
	seq->upperbound = 0;
	
	for(i = 0; i < n; i++) {
		seq->upperbound += jobs[i][MULTA];
	}
	
	return seq;
}

Sequencia *copiarSequencia(Sequencia *seq) {
	Sequencia *copia = (Sequencia*) malloc(sizeof(Sequencia));
	int i, n = seq->numJobs;
	copia->vetor = (int*) calloc(n, sizeof(int));
	
	// Repassando as informações
	copia->jobs = seq->jobs;
	copia->numJobs = seq->numJobs;
	copia->atendidos = seq->atendidos;
	copia->tempo = seq->tempo;
	copia->multa = seq->multa;
	copia->lowerbound = seq->lowerbound;
	copia->upperbound = seq->upperbound;
	
	// Copiando o vetor que representa a sequência
	for(i = 0; i < n; i++)
		copia->vetor[i] = seq->vetor[i];
	
	return copia;
}

void adicionarJob(Sequencia *seq, int job) {
	// Verifica se o procedimento já foi realizado
	if(seq->vetor[job] != 0) {
		printf("O procedimento %d já foi realizado!\n", job);
		return;
	}
	
	// Incrementa o número de atendimentos e o armazena
	int m = ++seq->atendidos;
	
	// Guarda o número de procedimentos
	int n = seq->numJobs;
	
	int i;
	
	// Marca o procedimento job como o m-ésimo realizado
	seq->vetor[job] = m;
	
	seq->tempo += seq->jobs[job][TEMPO];
	
	/* Caso se realize o procedimento sem o pagamento da multa,
	 * descontar do pior caso
	 */
	if(seq->tempo <= seq->jobs[job][DEADLINE])
		seq->upperbound -= seq->jobs[job][MULTA];
	else
		seq->multa += seq->jobs[job][MULTA];
	
	// Atualiza o melhor caso
	seq->lowerbound = seq->multa;
	for(i = 0; i < n; i++) {
		if(seq->vetor[i] == 0 &&
		   seq->tempo + seq->jobs[i][TEMPO] > seq->jobs[i][DEADLINE])
			seq->lowerbound += seq->jobs[i][MULTA];
	}
}

Sequencia **gerarFilhos(Sequencia *seq) {
	int i, job, numFilhos = seq->numJobs - seq->atendidos;
	Sequencia **filhos = (Sequencia**) calloc(numFilhos, sizeof(Sequencia*));
	Sequencia *copia;
	
	job = 0;
	for(i = 0; i < numFilhos; i++) {
		copia = copiarSequencia(seq);
		
		while(seq->vetor[job] != 0)
			job++;
			
		adicionarJob(copia, job++);
		filhos[i] = copia;
	}
	
	return filhos;
}

void imprimirSeq(Sequencia *seq) {
	int i, n = seq->numJobs, m = seq->atendidos;
	
	printf("Atendidos: ");
	int *atendidos = (int*) calloc(m, sizeof(int));
	for(i = 0; i < n; i++) {
		if(seq->vetor[i] > 0)
			atendidos[seq->vetor[i]-1] = i;
	}
	
	for(i = 0; i < m; i++) {
		printf("%d ", atendidos[i]);
	}
	printf("\n");
	
	printf("Esperando: ");
	for(i = 0; i < n; i++) {
		if(seq->vetor[i] == 0)
			printf("%d ", i);
	}
	printf("\n");
	
	printf("Melhor caso: %d\n", seq->lowerbound);
	printf("Pior caso: %d\n", seq->upperbound);
	printf("Tempo: %d\n", seq->tempo);
	printf("Multa: %d\n", seq->multa);
	
	free(atendidos);
}

void printSeq(Sequencia *seq) {
	printf("%d: ", seq->multa);
	int i, n = seq->numJobs, m = seq->atendidos;
	
	int *atendidos = (int*) calloc(m, sizeof(int));
	for(i = 0; i < n; i++) {
		if(seq->vetor[i] > 0)
			atendidos[seq->vetor[i]-1] = i;
	}
	
	for(i = 0; i < m; i++) {
		printf("%d ", atendidos[i]);
	}
	printf("\n");
	
	free(atendidos);
}

void liberarSeq(Sequencia *seq) {
	free(seq->vetor);
	free(seq);
}


