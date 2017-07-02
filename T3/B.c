#include <stdio.h>
#include <stdlib.h>

int t;

typedef struct tpnodo {
	struct chave *keys;
	struct tpnodo **filhos;
	struct tpnodo *pai;
	int quant;
}Node;

typedef struct chave{
	struct chave *ant;
	int chave;
	struct chave *prox;
}Key;

typedef struct tparvore {
	Node *raiz;
}Tree;

Node * crianodo(Key * keys, Node **filhos);
void insere(int value, Tree *tree, Node *node);
void inseresplit(int value, Node *node,Node *esq, Node *dir);
void split(Tree *tree, Node *node);

int main(){
	Tree *tree=(Tree*)malloc(sizeof(Tree));
	tree->raiz = NULL;
	printf("Digite T\n");
	scanf("%d",&t);

	insere(10,tree,tree->raiz);
	insere(20,tree,tree->raiz);
	insere(30,tree,tree->raiz);
	insere(40,tree,tree->raiz);

	printf("%d\n",tree->raiz->filhos[0]->keys->chave);
	printf("%d\n",tree->raiz->filhos[1]->keys->prox->chave);


	return 0;
}

Node * crianodo(Key * keys, Node **filhos){
	Node * nodo = (Node *) calloc(1,sizeof(Node));
	nodo->keys = keys;
	nodo->filhos = filhos;
	nodo->quant = t-1;
	return nodo;
}

void insere(int value, Tree *tree, Node *node){
	if(tree->raiz == NULL){
		Node * nodo = crianodo(NULL,NULL);
		Key *key = (Key *) calloc(1,sizeof(Key));
		key->chave = value;
		key->ant = NULL;
		key->prox = NULL;
		nodo->keys = key;
		nodo->quant = 1;
		nodo->pai = NULL;
		tree->raiz = nodo;
	}else{
		if(node->filhos == NULL){ //nodo n tem filhos
			if(node->quant < ((2*t) -1)){
				Key *aux = node->keys, *ant = NULL;
				for(;aux != NULL && aux->chave < value;aux = aux->prox)
					ant = aux;
				Key *novo = (Key *) calloc(1,sizeof(Key));
				novo->chave = value;
				novo->ant = ant;
				novo->prox = aux;
				if(ant == NULL)
					node->keys = novo;
				else
					ant->prox = novo;
				if(aux != NULL)
					aux->ant = novo;
				node->quant++;
			}else{
				split(tree,node);
				insere(value,tree,tree->raiz);
			}
		}else{
			Key *aux = node->keys;
			int i = 0;
			for(;aux != NULL && aux->chave < value;aux = aux->prox){
				i++;
			}
			insere(value,tree,node->filhos[i]);
		}
	}
}

void split(Tree *tree, Node *node){
	if(node->pai != NULL && node->pai->quant == ((2*t)-1)){
		split(tree,node->pai);
	}
	Key *chesq = NULL, *chdir = NULL;
	chesq = node->keys;
	Key *aux = chesq;
	int a = 0;

	for(;a < t-1;a++){
		aux = aux->prox;
	}
	aux->ant->prox = NULL;
	chdir = aux->prox;
	aux->prox->ant = NULL;

	Node **filesq = NULL, **fildir = NULL;
	if(node->filhos != NULL){
		int i = 0;
		for(;i < t;i++)
			filesq[i] = node->filhos[i];
		for(;i < 2*t;i++)
			fildir[i] = node->filhos[i];
	}

	Node *esq = crianodo(chesq,filesq);
	Node *dir = crianodo(chdir,fildir);
	int aj = 2*t;
	Node **filhos = (Node **) calloc(aj,sizeof(Node));

	if(node->pai != NULL){
		esq->pai = dir->pai = node->pai;
		inseresplit(aux->chave,node->pai,esq,dir);
	}else{
		filhos[0] = esq;
		filhos[1] = dir;
		Node *raiznova = crianodo(NULL,filhos);
		Key *key = (Key *) calloc(1,sizeof(Key));
		key->chave = aux->chave;
		key->ant = NULL;
		key->prox = NULL;
		raiznova->keys = key;
		raiznova->quant = 1;
		raiznova->pai = NULL;
		tree->raiz = raiznova;

		esq->pai = tree->raiz;
		dir->pai = tree->raiz;
	}


}

void inseresplit(int value, Node *node,Node *esq, Node *dir){
	int i = 0,a;
	Key *aux = node->keys, *ant = NULL;
	for(;aux != NULL && aux->chave < value;aux = aux->prox){
		ant = aux;
		i++;
	}
	Key *novo = (Key *) calloc(1,sizeof(Key));
	novo->chave = value;
	novo->ant = ant;
	novo->prox = aux;
	if(ant == NULL)
		node->keys = novo;
	else
		ant->prox = novo;
	if(aux != NULL)
		aux->ant = novo;
	node->quant++;
	a = i;
	while(node->filhos[a] != NULL)
		a++;
	for(; i != a; a--){
		node->filhos[a] = node->filhos[a-1];
	}
	node->filhos[i] = esq;
	node->filhos[i+1] = esq;
}
