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

int main(){
	Tree *tree=(Tree*)malloc(sizeof(Tree));
	tree->raiz = NULL;
	printf("Digite T\n");
	scanf("%d",&t);

	insere(10,tree,tree->raiz);
	insere(20,tree,tree->raiz);
	printf("%d\n",tree->raiz->keys->chave);

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
				printf("precisa de split\n");
			}
		}
	}
}
