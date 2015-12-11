#include "branchbound.h"

int custo, t, atual;

int bb(int n, int tempo[], int deadline[], int multa[], int seq[], int c){
	
	int i, visitado[n], atseq[n];
	
	custo = c;
	
	for(i=0;i<n;i++){
		
		t=0;
		atual = 0;
		zera(n, visitado);
		zera(n, atseq);
		buscaMenorCusto(n, tempo, deadline, multa, seq, i, visitado, atseq);
		
	}
	
	return custo;
	
}

void buscaMenorCusto(int n, int tempo[], int deadline[], int multa[], int seq[], int ini, int visitado[], int atseq[]){
	
	int i, check=0;
	visitado[ini] = 1;
	
	t += tempo[ini];
	
	adicionaSeq(ini+1, n, atseq);
	
	for(i=0;i<n;i++){
		
		if(visitado[i]==0){
			
			check = 1;
			
			if(tempo[i]+t>deadline[i] && multa[i]+atual < custo){
				
				atual += multa[i];
				buscaMenorCusto(n, tempo, deadline, multa, seq, i, visitado, atseq);
				atual -= multa[i];
				
			}
			else if(tempo[i]+t<=deadline[i])
				buscaMenorCusto(n, tempo, deadline, multa, seq, i, visitado, atseq);
				
		}
		
	}
	
	t -= tempo[ini];
	visitado[ini] = 0;
	
	if(check == 0){
		
		if(atual < custo){
			
			custo = atual;
			for(i=0;i<n;i++)
				seq[i] = atseq[i]-1;
			
		}
		
	}
	
	removeSeq(n, atseq);

}

void zera(int n, int vet[]){
	
	int i;
	
	for(i=0;i<n;i++)
		vet[i] = 0;
	
}

void adicionaSeq(int ini, int n, int atseq[]){
	
	int i=0;
	
	while(atseq[i]!=0)
		i++;
	
	atseq[i]=ini;
	
}

void pv(int n, int vet[]){

	int i;
	
	for(i=0;i<n;i++)
		printf("%d ", vet[i]-1);
	
	printf("\n");
	
}

void removeSeq(int n, int atseq[]){
	
	int i=0;
	
	while(i<n&&atseq[i]!=0)
		i++;
	
	atseq[--i] = 0;
	
}
