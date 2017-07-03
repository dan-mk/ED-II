#include <stdio.h>
#include <stdlib.h>

int t, num = 0;

typedef struct tpnodo {
	struct chave *keys;
	struct tpnodo **filhos;
	struct tpnodo *pai;
	int quant;
	int num;
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
void imprime(Node *node);

int main(){
	Tree *tree=(Tree*)malloc(sizeof(Tree));
	tree->raiz = NULL;
	printf("Digite T\n");
	scanf("%d",&t);

	insere(10,tree,tree->raiz);
	insere(20,tree,tree->raiz);
	insere(30,tree,tree->raiz);
	insere(40,tree,tree->raiz);
	insere(50,tree,tree->raiz);
	insere(60,tree,tree->raiz);
	insere(15,tree,tree->raiz);
	insere(25,tree,tree->raiz);
	insere(5,tree,tree->raiz);
	insere(35,tree,tree->raiz);
	insere(17,tree,tree->raiz);
	insere(37,tree,tree->raiz);

	imprime(tree->raiz);
	return 0;
}

Node * crianodo(Key * keys, Node **filhos){
	Node * nodo = (Node *) calloc(1,sizeof(Node));
	nodo->keys = keys;
	nodo->filhos = filhos;
	nodo->quant = t-1;
	nodo->num = num++;
	if(filhos != NULL){
		int i = 0;
		printf("KAKAKAKAKA\n");
		for(;i < 2*t && nodo->filhos[i] != NULL;i++)
			nodo->filhos[i]->pai = nodo;
	}
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
		printf("banana\n");
		split(tree,node->pai);
	}
	Key *chesq = NULL, *chdir = NULL;
	chesq = node->keys;
	Key *aux = chesq;
	int a = 0;
	int aj = 2*t;
	for(;a < t-1;a++){
		aux = aux->prox;
	}
	aux->ant->prox = NULL;
	chdir = aux->prox;
	aux->prox->ant = NULL;

	Node **filesq = NULL, **fildir = NULL;
	if(node->filhos != NULL){
		int i = 0;
		filesq = (Node **) calloc(aj,sizeof(Node));
		fildir = (Node **) calloc(aj,sizeof(Node));
		for(;i < t;i++)
			filesq[i] = node->filhos[i];
		for(;i < 2*t;i++)
			fildir[i] = node->filhos[i];
	}

	Node *esq = crianodo(chesq,filesq); //na cria nodo lembra de fazerem os filhso apontarem pra ele PLEASE
	Node *dir = crianodo(chdir,fildir);
	Node **filhos = (Node **) calloc(aj,sizeof(Node));

	if(node->pai != NULL){
		esq->pai = node->pai;
		dir->pai = node->pai;
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
	}

	free(node);
}

void inseresplit(int value, Node *node,Node *esq, Node *dir){
	int i = 0,a;
	Key *aux = node->keys, *ant = NULL;
	for(;aux != NULL && aux->chave < value;aux = aux->prox){
		ant = aux;
		i++;
	}
	printf("%d kkkkkkkkkk\n",node->keys->chave );
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
	while(a < 2*t && node->filhos[a] != NULL )
		a++;
	for(; i != a; a--){
		node->filhos[a] = node->filhos[a-1];
	}
	node->filhos[i] = esq;
	node->filhos[i+1] = dir;
}

void imprime(Node *node){
		if(node != NULL){
			printf("Nodo numero : %d. Pai :",node->num);
			if(node->pai != NULL) printf("%d\n",node->pai->num);
			else printf("Raiz\n");
			Key *aux = node->keys;
			printf("Chaves: ");
			for(;aux != NULL; aux = aux->prox)
				printf("%d ",aux->chave);
			printf("\n");

			if(node->filhos != NULL){
				int i = 0;
				for(;node->filhos[i] != NULL;i++)
					imprime(node->filhos[i]);
			}
		}
}
