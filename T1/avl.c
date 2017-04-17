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

TpArvore *inicializa(){//aloca memoria para inicializar a arvore
	TpArvore *arvore=(TpArvore*)malloc(sizeof(TpArvore));
	arvore->raiz=NULL;
	return arvore;
}

void imprime ( TpArvore *tree, TpNodo *node) {    
    if ( tree == NULL || node == NULL ) return; 
    imprime (tree, node->esq);
    printf("Chave: %d Altura: %d AltEsq: %d AltDir: %d, ",node->chave,node->altura,node->altesquerda,node->altdireita) ;
    imprime (tree, node->dir);
}

TpArvore *inserir(TpArvore * tree, int valor){
	TpNodo * new = (TpNodo *) calloc(1,sizeof(TpNodo));
	int lado = 0;

	if (tree->raiz == NULL){
		new->chave = valor;
		new->altura = 0;
		new->nivel = 0;
		new->altdireita = 0;
		new->altesquerda = 0;
		new->esq = NULL;
		new->dir = NULL;
		new->pai = NULL;
		tree->raiz = new;
		return tree;
	}else{
		TpNodo *aux = tree->raiz;

		while(1){
			if (valor > aux->chave){
				if (aux->dir == NULL){
					break;
				}else{
					aux = aux->dir;
				}
			}else{
				if (aux->esq == NULL){
					break;
				}else{
					aux = aux->esq;
				}
			}
		}

		if (valor > aux->chave){
			aux->dir = new;
			lado = 1;
		}else{
			aux->esq = new;
		}

		new->chave = valor;
		new->pai = aux;
		new->nivel = aux->nivel + 1;
		new->altura = 0;
		new->altdireita = 0;
		new->altesquerda = 0;

		while(aux != NULL){
			aux->altura++;
			if (lado == 1)
				aux->altdireita++;
			else
				aux->altesquerda++;
			aux = aux->pai;
		}
		return tree;

	}

}

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
				arvore = inserir(arvore,valor);
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
}

