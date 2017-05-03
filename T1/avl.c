#include <stdio.h>
#include <stdlib.h>

//Estrutura da Árvore
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

//Protótipo das Funções
void printT(TpNodo *node);
int altura(TpNodo *node);
int maior(int a, int b);
TpArvore *inicializa();
TpNodo* criaNodo(int valor, int nivel);
TpNodo *inserir(TpNodo * node, int valor, int nivel);
TpNodo *alturaRefresh(TpNodo * nodo);
TpNodo *pais(TpNodo *node);
TpNodo *nivel(TpNodo *node);
TpNodo *rotDir(TpNodo *node);
TpNodo *rotEsq(TpNodo *node);
void liberarmemoria(TpNodo * node);

int main(){
    TpArvore *arvore=(TpArvore*)malloc(sizeof(TpArvore));
    arvore=inicializa();

    int escolha = 1,valor;

    do{
    	system("clear");
    	printf("|  AVL TREE\n");
        printf("|Escolha a opção:\n");
        printf("|1-Inserir\n");
        printf("|2-Listar nodos\n");
        printf("|0-Sair\n");

        printf("|");scanf("%d",&escolha);

        switch(escolha){
            case 1:
                printf("|Digite o valor a ser inserido\n");
                printf("|");scanf("%d",&valor);
				arvore->raiz = nivel(pais(inserir(arvore->raiz,valor,0)));
                break;
            case 2:
            	printf("\n|Modo de visialização: 'inOrder'\n");
            	printf("|Raiz : %d\n", arvore->raiz->chave);
                printT(arvore->raiz);
				printf("|Digite um número diferente de 0 para continuar\n");
				printf("|");scanf("%d",&escolha);

                break;
            case 0:
            	liberarmemoria(arvore->raiz);
                break;
            default:
                printf("|Valor inválido\n");
                printf("|Digite um número diferente de 0 para contnuiar\n");
				printf("|");scanf("%d",&escolha);
        }
    }while(escolha != 0);

    return 0;
}

//Funções da AVL

	//Aloca memoria para inicializar a arvore
TpArvore *inicializa(){
    TpArvore *arvore=(TpArvore*)malloc(sizeof(TpArvore));
    arvore->raiz=NULL;
    return arvore;
}

	//Novo node é inicalizado e adicionado na folha
TpNodo* criaNodo(int valor, int nivel){
    TpNodo * node = (TpNodo *) calloc(1,sizeof(TpNodo));

     node->chave = valor;
  	 node->dir = NULL;
  	 node->esq = NULL;
	 node->pai = NULL;
     node->altura = 1;
	 node->altdireita = 1;
	 node->altesquerda = 1;
	 node->nivel = 0; 
     return(node);
}

TpNodo *inserir(TpNodo * node, int valor,int nivel){
	int escolha;
    if (node == NULL)
        return(criaNodo(valor,nivel));
 
    if (valor < node->chave)
        node->esq  = inserir(node->esq, valor,nivel + 1);
    else if (valor > node->chave)
        node->dir = inserir(node->dir, valor, nivel + 1);
    else{
    	printf("|Valor já existente na árvore.\n");
    	printf("|Digite um número diferente de 0 para contiar\n");
		printf("|");scanf("%d",&escolha);
        return node;
    }
 
    node->altesquerda = altura(node->esq);
	node->altdireita = altura(node->dir);
	node->nivel = 1 + maior(node->altesquerda, node->altdireita);
	node->altura = 1 + maior(node->altesquerda, node->altdireita);

    int balanceamento = node->altesquerda - node->altdireita;

 	// Significa que a sub-árvore está desbalanceada
 	if (abs(balanceamento) > 1){
 		// Balanceamento simples à direira
	    if (balanceamento > 1 && valor < node->esq->chave)
	        return rotDir(node);
	 
	    // Balanceamento simples à esquerda
	    if (balanceamento < -1 && valor > node->dir->chave)
	        return rotEsq(node);
	 
	    // Balanceamento duplo a esquerda e a direita
	    if (balanceamento > 1 && valor > node->esq->chave){
	        node->esq =  rotEsq(node->esq);
	        return rotDir(node);
	    }
	 
	    // Balanceamento duplo à direira e a esquerda
	    if (balanceamento < -1 && valor < node->dir->chave){
	        node->dir = rotDir(node->dir);
	        return rotEsq(node);
	    }
 	}	    
 
    return node;
}

	//Corrige as alturas dos nodos
TpNodo *alturaRefresh(TpNodo * node){
	if(node->dir != NULL) node->dir->altura = altura(node->dir);
	else node->altdireita = 0;

	if(node->esq != NULL) node->esq->altura = altura(node->esq);
	else node->altesquerda = 0;

	node->altdireita = altura(node->dir);
	node->altesquerda = altura(node->esq);

	node->altura = 1 + maior(node->altesquerda, node->altdireita);
	
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

TpNodo *rotEsq(TpNodo *node){
    TpNodo *x = node->dir;
    TpNodo *y = x->esq;
    x->esq = node;
    node->dir = y;
 
    x->pai = node->pai;
    node->pai = x;

    node = alturaRefresh(node);
    x = alturaRefresh(x);

    return x;
}

TpNodo *rotDir(TpNodo *node){
   	TpNodo *x = node->esq;
    TpNodo *y = x->dir;
    x->dir = node;
    node->esq = y;
 
    x->pai = node->pai;
    node->pai = x;

    node = alturaRefresh(node);
    x = alturaRefresh(x);

    return x;
}

void printT(TpNodo *node) {
   if(node != NULL){
		printT(node->esq);
		(node->pai != NULL) ? printf("|%d\tNivel: %d\tChave Pai: %d\n",node->chave, node->nivel, node->pai->chave) :	printf("|%d\tNivel: %d\tChave Pai: Raiz.\n",node->chave, node->nivel);
		//(node->pai != NULL) ? printf("|%d\tNivel: %d\tChave Pai: %d\tAltura à Esqueda: %d\tAltura Direita: %d\n",node->chave, node->nivel, node->pai->chave, node->altesquerda,node->altdireita) 		:	printf("|%d\tNivel: %d\tChave Pai: Raiz.Altura à Esqueda: %d\tAltura Direita: %d\n",node->chave, node->nivel, node->altesquerda,node->altdireita);
		printT(node->dir);
	}
}

int maior(int a, int b){
    return (a > b)? a : b;
}
int altura(TpNodo *node) {
	return ((node != NULL) ? node->altura : 0);
}

void liberarmemoria(TpNodo * node){
    if(node == NULL) return;
    liberarmemoria(node->dir);
    liberarmemoria(node->esq);
    free(node);
}
