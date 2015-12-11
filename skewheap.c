#include "skewheap.h"

SkewHeap *createSkewHeap(Sequencia *seq) {
	SkewHeap *heap = (SkewHeap*) malloc(sizeof(SkewHeap));

	heap->seq = seq;
	heap->left = NULL;
	heap->right = NULL;
	
	return heap;
}

SkewHeap *merge(SkewHeap *h1, SkewHeap *h2) {
	SkewHeap *temp;
	
	if (h1 == NULL)
		return h2;
	else if (h2 == NULL)
		return h1;
		
	else {
		if(h1->seq->lowerbound > h2->seq->lowerbound) {
			temp = h1;
			h1 = h2;
			h2 = temp;
		}
		
		temp = h1->left;
		h1->left = h1->right;
		h1->right = temp;
		h1->left = merge(h2, h1->left);
	}
	return h1;
}

SkewHeap *insert(SkewHeap *root, Sequencia *seq) {
	SkewHeap *temp = createSkewHeap(seq);
	root = merge(root, temp);
	return root;
}

SkewHeap *construct(SkewHeap *root, Sequencia **seqs, int n) {
	int i;
	
	for(i = 0; i < n; i++)
		root = insert(root, seqs[i]);
	
	return root;
}

SkewHeap *deleteMin(SkewHeap *root) {
	if(root == NULL) {
		printf("\nThe heap is empty.\n");
		return NULL;
	}
	
	SkewHeap *temp1, *temp2;
	temp1 = root->left;
	temp2 = root->right;
	temp1 = merge(temp1, temp2);
	
	free(root);
	return temp1;
}

void preOrder(SkewHeap *root) {
	if(root == NULL)
		return;
	
	printf("%d ", root->seq->lowerbound);
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder(SkewHeap *root) {
	if(root == NULL)
		return;
		
	inOrder(root->left);
	printf("%d ", root->seq->lowerbound);
	inOrder(root->right);
}

void postOrder(SkewHeap *root) {
	if(root == NULL)
		return;
		
	postOrder(root->left);
	postOrder(root->right);
	printf("%d ", root->seq->lowerbound);
}

void printHeap(SkewHeap *root) {
	printf("SkewHeap in pre-order:\n");
	preOrder(root);
	
	printf("\n\nSkewHeap in in-order:\n");
	inOrder(root);
	
	printf("\n\nSkewHeap in post-order:\n");
	postOrder(root);
	
	printf("\n\n");
}

void getSeqs(SkewHeap *root, Sequencia ***seqs, int *pos) {
	if(root == NULL)
		return;
		
	getSeqs(root->left, seqs, pos);
	(*seqs)[(*pos)++] = root->seq;
	getSeqs(root->right, seqs, pos);
}

void liberarHeap(SkewHeap *root) {
	if(root == NULL)
		return;
		
	liberarHeap(root->left);
	liberarHeap(root->right);
	free(root);
}

void destruirHeap(SkewHeap *root) {
	if(root == NULL)
		return;
		
	destruirHeap(root->left);
	destruirHeap(root->right);
	liberarSeq(root->seq);
	free(root);
}


