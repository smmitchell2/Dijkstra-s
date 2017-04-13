#include "binomial.h"
#include "integer.h"
#include "queue.h"
#include "darray.h"

static void consolidate(Binomial *, BinomialNode *);
static void merge (Binomial *,DArray *);
static BinomialNode *bubbleUp(Binomial *, BinomialNode *);
static BinomialNode *combine(Binomial *, BinomialNode *, BinomialNode *);
static BinomialNode *getSubHeap(DArray *, int);//int is an index
static void updateExtreme(Binomial *, BinomialNode *);
static void findNewExtreme(Binomial *);
static void levelOrderTraversal(FILE *, BinomialNode *);

/*******************************BinomialNode*******************************/

struct BinomialNode
{
	void *value;
	DArray *children;
	struct BinomialNode *parent;
	void (*display)(FILE *,void *);
};

BinomialNode *newBinomialNode(void (*display)(FILE *,void *),void *value)
{
	BinomialNode *n = malloc(sizeof(BinomialNode));
	n->value = value;
	n->children = newDArray(display);
	n->parent = n;
	n->display = display;

	return n;
}

static int nodeDegree(BinomialNode *n)
{
	return sizeDArray(n->children);
}

void displayBinomialNode(FILE *fp,BinomialNode *n)
{
	n->display(fp, n->value);
	fprintf(fp, "-%d", nodeDegree(n));
	if(n != n->parent)
	{
		fprintf(fp, "(");
		n->parent->display(fp, n->parent->value);
		fprintf(fp, "-%d)", nodeDegree(n->parent));
	}

}

/*******************************Binomial***********************************/

struct Binomial
{
	DArray *rootlist;
	int (*compare)(void *,void *);
	void (*update)(void *,BinomialNode *);
	BinomialNode *extreme;
	int size;
	void (*display)(FILE *,void *);
};

Binomial *newBinomial(
    void (*d)(FILE *,void *),        
    int (*c)(void *,void *),         
    void (*u)(void *,BinomialNode *)
    )
{
	Binomial *b = malloc(sizeof(Binomial));
	b->display = d;
	b->compare = c;
	b->update = u;
	b->rootlist = newDArray(d);
	b->extreme = NULL;
	b->size = 0;

	return b;
}

BinomialNode *insertBinomial(Binomial *b,void *value){
	BinomialNode *n = newBinomialNode(b->display, value);
	updateExtreme(b,n);
	consolidate(b, n);
	b->size++;
	return n;
}

int sizeBinomial(Binomial *b){
	return b->size;
}

void deleteBinomial(Binomial *b,BinomialNode *n){
	decreaseKeyBinomial(b, n, NULL);
	(void) extractBinomial(b);
}

void decreaseKeyBinomial(Binomial *b,BinomialNode *n,void *value){
	n->value = value;
	BinomialNode *vp =  bubbleUp(b, n);
	updateExtreme(b, vp);
}

void *extractBinomial(Binomial *b){
	BinomialNode *y = b->extreme;
	int i = 0;
	while(sizeDArray(b->rootlist) > i){
		if(getDArray(b->rootlist, i)==y){
			setDArray(b->rootlist, i, NULL);
		}
		++i;
	}
	merge(b, y->children);
	b->size--;
	void *temp = y->value;
	free(y);
	findNewExtreme(b);
	return temp;
}

void displayBinomial(FILE *fp,Binomial *b){
	if(sizeBinomial(b) == 0){
		fprintf(fp, "0:\n");
        return;
	}
	int i = 0;
	while(i < sizeDArray(b->rootlist)){
		if(getSubHeap(b->rootlist, i) != NULL){
			levelOrderTraversal(fp, (BinomialNode *) getSubHeap(b->rootlist, i));
			fprintf(fp, "----\n");
		}
		++i;
	}
}

static void levelOrderTraversal(FILE *fp, BinomialNode *n){
	queue *newQ = newQueue(n->display);
	enqueue(newQ, n);
	enqueue(newQ, NULL);
	BinomialNode *x;
	int breadthLevel = 0;
	fprintf(fp, "%d: ", breadthLevel);
	while (sizeQueue(newQ)){
		x = dequeue(newQ);
		if(sizeQueue(newQ) == 0){
			fprintf(fp, "\n");
			break;
		}

		else if(x == NULL){
			fprintf(fp,"\n");
			enqueue(newQ, NULL);
			breadthLevel++;
			if(sizeQueue(newQ) > 0){
				fprintf(fp, "%d: ", breadthLevel);
			}
		}
		else{			
			displayBinomialNode(fp, x);	
			if(peekQueue(newQ) != NULL) {
				fprintf(fp, " ");
			}
			for(int i = 0; i < sizeDArray(x->children); i++){
				enqueue(newQ, (BinomialNode *) getSubHeap(x->children, i));
			}
		}
	}
}

static void updateExtreme(Binomial *b, BinomialNode *n){
	if (b->extreme == NULL){
		b->extreme = n;
	}
	else if(b->compare(b->extreme->value, n->value) > 0){
		b->extreme = n;
	}
}

static void findNewExtreme(Binomial *b){
	b->extreme = NULL;
	BinomialNode *n = NULL;
	for(int i=0; i < sizeDArray(b->rootlist); i++){
		n = getSubHeap(b->rootlist, i);
		if(n != NULL){
			updateExtreme(b, n);
		}
	}
}

static BinomialNode *getSubHeap(DArray *a, int degree){
	if(degree > sizeDArray(a)){
		fprintf(stderr, "Fatal error\n");
		exit(-1);
	}
	else if(degree == sizeDArray(a)){
		return NULL;
	}

	return getDArray(a, degree);
}

static void consolidate(Binomial *b, BinomialNode *n){
	int degree = nodeDegree(n);
	while (getSubHeap(b->rootlist, degree) != NULL){
		n = combine(b, n, getSubHeap(b->rootlist, degree));
		setDArray(b->rootlist, degree, NULL);
		degree++;

		if(degree == sizeDArray(b->rootlist)){
			insertDArray(b->rootlist, NULL);
		}
	}
	setDArray(b->rootlist, degree, n);
}

static void merge(Binomial *b, DArray *donor){
	for(int index = 0; index < sizeDArray(donor); index++){
		BinomialNode *n = (BinomialNode *) getDArray(donor, index);
		n->parent = n;
		consolidate(b, n);
	}
	free(donor);
}

static BinomialNode *bubbleUp(Binomial *b, BinomialNode *n){
	if(n->parent == n){
		return n;
	}
	else if(b->compare(n->parent->value, n->value) < 0){
		return n;
	}
	else{
		b->update(n->value, n->parent);
		b->update(n->parent->value, n);
		void *temp = n->value;
		n->value = n->parent->value;
		n->parent->value = temp;

		return bubbleUp(b, n->parent);
	}
}


static BinomialNode *combine(Binomial *b, BinomialNode *x, BinomialNode *y){
	int i = 0;
	if(b->compare(x->value, y->value) < 0){
		i = nodeDegree(y);
		setDArray(x->children, i, y);
		y->parent = x;

		return x;
	}
	else{
		i = nodeDegree(x);
		setDArray(y->children, i, x);
		x->parent = y;

		return y;
	}
}
