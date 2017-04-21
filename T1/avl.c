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

void imprime(TpArvore *tree, TpNodo *node);

TpNodo *inserir(TpNodo * node, int valor, int nivel);

TpNodo *rot_dir(TpNodo *node);

TpNodo *rot_esq(TpNodo *node);

int altura(TpNodo *node);

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
                break;
            case 2:
                imprime(arvore,arvore->raiz);
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
 
    node->altura = altura(node);

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

void imprime ( TpArvore *tree, TpNodo *node) {
    if ( tree == NULL || node == NULL ) return;
    imprime (tree, node->esq);
    printf("Chave: %d Altura: %d AltEsq: %d AltDir: %d\n",node->chave,node->altura,node->altesquerda,node->altdireita) ;
    imprime (tree, node->dir);
}

TpNodo *rot_esq(TpNodo *node){
    TpNodo *x = node->dir;
    TpNodo *y = x->esq;
 
    x->dir = node;
    node->esq = y;

    node->altura = altura(node);
    x->altura = altura(x);

    return x;
}

TpNodo *rot_dir(TpNodo *node){
   	TpNodo *x = node->dir;
    TpNodo *y = x->esq;
 
    x->esq = node;
    node->dir = y;

    node->altura = altura(node);
    x->altura = altura(node);

    return x;
}

int max(int a, int b){
    return (a > b)? a : b;
}

int altura(TpNodo *node) {
	node->altdireita = 0;
	node->altesquerda = 0;
	node->altura = 0;

	if(node->esq != NULL) node->altesquerda = altura(node->esq);
	if(node->dir != NULL) node->altdireita = altura(node->dir);

	return max(node->altesquerda,node->altdireita);
}

TpNodo* criarnodo(int valor, int nivel){
    TpNodo * node = (TpNodo *) calloc(1,sizeof(TpNodo));

    node->chave = valor;
    node->esq = NULL;
    node->dir = NULL;
    node->altura = 0;
    node->nivel = nivel;
    node->altesquerda = 0;
    node->altdireita = 0;   // new node is initially added at leaf
    return(node);
}

