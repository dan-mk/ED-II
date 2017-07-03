#include <stdio.h>
#include <stdlib.h>

int t, num = 0,b = 0;
#define clear() printf("\033[H\033[J");

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
void inseresplit(Node *node, Key * value,Node *Esq, Node *Dir);
void split(Tree *tree, Node *node);
void imprime(Node *node);
void imprimirMenu();
void testaValor(Node *node, int valor);

int main(){
	Tree *tree=(Tree*)malloc(sizeof(Tree));
	tree->raiz = NULL;

	clear();

	printf("Digite T\n");
	scanf("%d",&t);

	int valor;
	int opcao=-1;
	do{
		imprimirMenu();
		scanf("%d", &opcao);
		switch(opcao){
			case 0:
				exit(0);
			case 1:
				clear();
				printf("\nDigite o valor a inserir: ");
				scanf("%d", &valor);
				clear();
				b = 0;
				testaValor(tree->raiz, valor);
				if(b==0){
					insere(valor,tree,tree->raiz);
				}else{
					printf("\nO valor ja esta inserido!");
					getchar();
					getchar();
				}
				clear();
				break;
			case 2:
				clear();
				printf ("\nElementos da Arvore:\n");
				imprime(tree->raiz);
				getchar();
				getchar();
				clear();
				break;
			default:
				clear();
				printf("Opcao invalida\n");
		}
	}while(1);
}

void imprimirMenu(){
	printf("\nArvore B\n");
	printf("Escolha a opcao\n");
	printf("0 - Fechar o programa\n");
	printf("1 - Inserir Elemento\n");
	printf("2 - Listar Elementos da arvore\n");
	printf("\nOpção: ");
}

void testaValor(Node *node, int valor){

	if(node != NULL){

		Key *aux = node->keys;

		for(;aux != NULL; aux = aux->prox){
			if(aux->chave == valor){
				b=1;
			}
		}
		if(node->filhos != NULL){
			int i = 0;
			for(;node->filhos[i] != NULL;i++){
				testaValor(node->filhos[i], valor);
			}
		}
	}
}

Node * crianodo(Key * keys, Node **filhos){
	Node * nodo = (Node *) calloc(1,sizeof(Node));
	nodo->keys = keys;
	nodo->filhos = filhos;
	nodo->quant = t-1;
	nodo->num = num++;
	if(filhos != NULL){
		int i = 0;
		for(;i < 2*t && filhos[i] != NULL;i++)
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
		split(tree,node->pai);
	}
	int i=0;
	Key *aux = node->keys;
	Key *chesq = node->keys;
	for(;i<t-1;aux=aux->prox){
		i++;
	}
	Key *chdir = aux->prox;
	aux->prox->ant = NULL;
	aux->ant->prox = NULL;
	aux->ant = NULL;
	aux->prox = NULL;
	int aj=2*t;

	Node **filesq = NULL, **fildir = NULL;
	if(node->filhos != NULL){
		filesq = (Node **) calloc(aj,sizeof(Node));
		fildir = (Node **) calloc(aj,sizeof(Node));

		for(i=0;i<t;i++){
			filesq[i] = node->filhos[i];
		}
		for(i=0; i<t;i++){
			fildir[i] = node->filhos[i+t];
		}
	}

	Node *Dir = crianodo(chdir,fildir);
	Node *Esq = crianodo(chesq, filesq);
	
	if(node->pai != NULL){
		Esq->pai = node->pai;
		Dir->pai = node->pai;

		inseresplit(node->pai, aux, Esq,Dir);
	}else{
		Node *novaRaiz = (Node *) calloc(1,sizeof(Node));
		novaRaiz->keys = aux;
		novaRaiz->quant = 1;
		novaRaiz->num = num++;
		Node ** filhos = (Node **) calloc(aj, sizeof(Node));
		filhos[0] = Esq;
		filhos[1] = Dir;
		Esq->pai = novaRaiz;
		Dir->pai = novaRaiz;
		novaRaiz->filhos = filhos;
		tree->raiz = novaRaiz;
	}	
	free(node);
}

void inseresplit(Node *node, Key * value,Node *Esq, Node *Dir){
	Key *aux = node->keys, *ant = NULL;

	int i=0;
	int a = 0;
	for(;aux != NULL && aux->chave < value->chave; aux=aux->prox){
		ant = aux;
		i++;
	}
	if(ant == NULL){
		value->prox = aux;
		aux->ant = value;
		node->keys = value;
	}else{
		value->prox = aux;
		value->ant  = ant;
		ant->prox = value;
		if(aux != NULL)
			aux->ant = value;
			
	}
	node->quant++;

	a = i;
	while(a < 2*t && node->filhos[a] != NULL )
		a++;
	for(; i != a; a--){
		node->filhos[a] = node->filhos[a-1];
	}
	node->filhos[i] = Esq;
	node->filhos[i+1] = Dir;

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
