#include <stdio.h>
#include <stdlib.h>

typedef struct _nodo{
    int chave;
    int altura, nivel;
    int altdireita,altesquerda;
    struct _nodo *esq;
    struct _nodo *dir;
    struct _nodo *pai;
} TpNodo;

typedef struct _arvore{
    TpNodo *raiz;
} TpArvore;

TpArvore *inicializa();

void imprime(TpNodo *node);

TpNodo *inserir(TpNodo * node, int valor, int nivel);

TpNodo *rot_dir(TpNodo *node);

TpNodo *rot_esq(TpNodo *node);

int altura(TpNodo *node);

TpNodo *pais(TpNodo *node);

TpNodo *nivel(TpNodo *node);

TpNodo *alturarefresh(TpNodo * nodo);

int max(int a, int b);

TpNodo* criarnodo(int valor, int nivel);

int main(){
    TpArvore *arvore=(TpArvore*)malloc(sizeof(TpArvore));
    arvore=inicializa();

    int escolha = 1,valor;

    do{
        printf("Escolha a opção:\n");
        printf("1-Inserir\n");
        printf("2-Listar nodos\n");
        printf("0-Sair\n");

        scanf("%d",&escolha);

        switch(escolha){
            case 1:
                printf("Digite o valor a ser inserido\n");
                scanf("%d",&valor);
                arvore->raiz = inserir(arvore->raiz,valor,0);
                arvore->raiz = pais(arvore->raiz);
				arvore->raiz = nivel(arvore->raiz);
                break;
            case 2:
            	printf("Raiz : %d\n", arvore->raiz->chave);
                imprime(arvore->raiz);
                break;
            case 0:
                break;
            default:
                printf("Valor inválido\n");
        }
    }while(escolha != 0);

    return 0;
}

TpNodo *inserir(TpNodo * node, int valor,int nivel){

    if (node == NULL)
        return(criarnodo(valor,nivel));
 
    if (valor < node->chave)
        node->esq  = inserir(node->esq, valor,nivel + 1);
    else if (valor > node->chave)
        node->dir = inserir(node->dir, valor, nivel + 1);
    else{
    	printf("Valor já existente na árvore.\n");
        return node;
    }
 
    node->altesquerda = altura(node->esq);
	node->altdireita = altura(node->dir);
	node->nivel = 1 + max(node->altesquerda, node->altdireita);
	node->altura = 1 + max(node->altesquerda, node->altdireita);

    int balanceamento = node->altesquerda - node->altdireita;
 
    // LL
    if (balanceamento > 1 && valor < node->esq->chave)
        return rot_dir(node);
 
    // RR
    if (balanceamento < -1 && valor > node->dir->chave)
        return rot_esq(node);
 
    // LR
    if (balanceamento > 1 && valor > node->esq->chave){
        node->esq =  rot_esq(node->esq);
        return rot_dir(node);
    }
 
    // RL
    if (balanceamento < -1 && valor < node->dir->chave){
        node->dir = rot_dir(node->dir);
        return rot_esq(node);
    }
 
    return node;

}

TpArvore *inicializa(){//aloca memoria para inicializar a arvore
    TpArvore *arvore=(TpArvore*)malloc(sizeof(TpArvore));
    arvore->raiz=NULL;
    return arvore;
}

void imprime (TpNodo *node) {
   if(node != NULL){
		(node->pai != NULL) ? printf("%d\tNivel: %d\tChave Pai: %d\n",node->chave, node->nivel, node->pai->chave) :	printf("%d\tNivel: %d\tChave Pai: NAO TEM - ELE EH RAIZ\n",node->chave, node->nivel);
		imprime(node->esq);
		imprime(node->dir);
	}
}

TpNodo *rot_esq(TpNodo *node){
    TpNodo *x = node->dir;
    TpNodo *y = x->esq;
    x->esq = node;
    node->dir = y;
 
    x->pai = node->pai;
    node->pai = x;

    node = alturarefresh(node);
    x = alturarefresh(x);

    return x;
}

TpNodo *rot_dir(TpNodo *node){
   	TpNodo *x = node->esq;
    TpNodo *y = x->dir;
    x->dir = node;
    node->esq = y;
 
    x->pai = node->pai;
    node->pai = x;

    node = alturarefresh(node);
    x = alturarefresh(x);

    return x;
}

int max(int a, int b){
    return (a > b)? a : b;
}

int altura(TpNodo *node) {
	return ((node != NULL) ? node->altura : 0);
}

TpNodo* criarnodo(int valor, int nivel){
    TpNodo * node = (TpNodo *) calloc(1,sizeof(TpNodo));

     node->chave = valor;
  	 node->dir = NULL;
  	 node->esq = NULL;
	 node->pai = NULL;
     node->altura = 1;
	 node->altdireita = 1;
	 node->altesquerda = 1;
	 node->nivel = 0;  // new node is initially added at leaf
     return(node);
}

TpNodo *alturarefresh(TpNodo * node){
	if(node->dir != NULL) node->dir->altura = altura(node->dir);
	else node->altdireita = 0;

	if(node->esq != NULL) node->esq->altura = altura(node->esq);
	else node->altesquerda = 0;

	node->altdireita = altura(node->dir);
	node->altesquerda = altura(node->esq);

	node->altura = 1 + max(node->altesquerda, node->altdireita);
	
	return node;
}

TpNodo *nivel(TpNodo *node){
	if(node->pai == NULL){
		node->nivel = 0;
	}else{
		node->nivel = node->pai->nivel + 1;
	}

	if(node->esq != NULL)
		node->esq = nivel(node->esq);
	if(node->dir != NULL)
		node->dir = nivel(node->dir);

	 return node;
}

TpNodo *pais(TpNodo *node){
	if(node->esq != NULL){
		node->esq->pai = node;
		node->esq = pais(node->esq);
	}
	if(node->dir != NULL){
		node->dir->pai = node;
		node->dir = pais(node->dir);
	}
	return node;
}