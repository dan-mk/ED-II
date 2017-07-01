#include <stdio.h>
#include <stdlib.h>
#define PRETO 1
#define VERMELHO 0

typedef struct _nodo{
  int chave;
  int nivel;
  int cor; // Se cor 1 então é preta, se for 0 então é vermelha.
  struct _nodo *esq;
  struct _nodo *dir;
  struct _nodo *pai;
} TpNodo;

typedef struct _arvore{
  TpNodo *raiz;
} TpArvore;

//Prototipos das funções
TpArvore *inicializa();
TpNodo* criaNodo(int valor);
void leftRotate(TpNodo *x,TpArvore *t);
void rightRotate(TpNodo *x,TpArvore *t);
void insert(TpArvore *t, int valor);
void insertFixUp(TpNodo *z,TpArvore *t);
void nivel(TpNodo *node);
void printT(TpNodo *x);

int main(){
  TpArvore *arvore=(TpArvore*)malloc(sizeof(TpArvore));
    arvore=inicializa();
    int escolha = 1,valor;
    do{
      system("clear");
        printf("|RB TREE\n");
        printf("|Escolha a opção:\n");
        printf("|1-Inserir\n");
        printf("|2-Listar nodos\n");
        printf("|0-Sair\n");

        printf("|");scanf("%d",&escolha);

        switch(escolha){
            case 1:
                printf("|Digite o valor a ser inserido\n");
                printf("|");scanf("%d",&valor);
                insert(arvore,valor);
                nivel(arvore->raiz);
                break;
            case 2:
                printf("\n|Modo de visialização: 'pre-Order'\n");
                printf("|Raiz : %d\n", arvore->raiz->chave);
                printT(arvore->raiz);
                printf("|Digite um número para continuar\n");
                printf("|");scanf("%d",&escolha);
                break;
            case 0:
                break;
            default:
                printf("|Valor inválido\n");
                printf("|Digite um número para continuar\n");
                printf("|");scanf("%d",&escolha);
        }
    }while(escolha != 0);

    return 0;
}

TpArvore *inicializa(){//aloca memoria para inicializar a arvore
  TpArvore *arvore=(TpArvore*)malloc(sizeof(TpArvore));
  arvore->raiz=NULL;
  return arvore;
}

TpNodo* criaNodo(int valor){
    TpNodo * node = (TpNodo *) calloc(1,sizeof(TpNodo));

     node->chave = valor;
     node->dir = NULL;
     node->esq = NULL;
     node->pai = NULL;
     node->cor = VERMELHO;
     return(node);
}

//INSERÇÃO
void insert(TpArvore *t, int valor){
    int escolha = 0;

    if (t->raiz == NULL){ //verifica se a árvore possui raiz, senão ele insere na raiz
        t->raiz = criaNodo(valor);
        insertFixUp(t->raiz,t);

    }else{
      TpNodo *a,*b;
      a = t->raiz;
      while(a != NULL){ //buscando onde o valor irá ser inserido
        if (valor < a->chave){// se o valor for menor
          b = a;
          a = a->esq;
          continue;
        }
        else{
          if (valor > a->chave){ // se o valor for maior
            b = a;
            a = a->dir;
            continue;
          }
          else{ // se o valor ja existe
            do{
              printf("|Valor já existente na árvore.\n");
              printf("|Digite um número diferente de 0 para continuar\n");
              printf("|");scanf("%d",&escolha);
            }while(escolha == 0);
            break;
          }
        }
      }

      if (escolha == 0){ // encontrou o lugar, portanto irá inserir e realizar o fixup
        a = criaNodo(valor);
        a->pai = b;
        if (valor < b->chave)
          b->esq = a;
        else
          b->dir = a;

        insertFixUp(a,t);
      }
    }
}

//Função que faz atribui os níveis da árvore.
void nivel(TpNodo *node){
  if(node->pai == NULL)
    node->nivel = 0;
  else
    node->nivel = node->pai->nivel + 1;
  if(node->esq != NULL)
    nivel(node->esq);
  if(node->dir != NULL)
    nivel(node->dir);
}

//Rotação à Esquerda
void leftRotate(TpNodo *x,TpArvore *t){
  TpNodo *a,*b;
  a = x;
  b = x->dir;

  b->pai = a->pai;
  a->dir = b->esq;

  if(a->dir != NULL)
    a->dir->pai = a;

  a->pai = b;
  b->esq = a;

  if (b->pai == NULL)
    t->raiz = b;
  else{
    if (b->chave < b->pai->chave)
      b->pai->esq = b;
    else
      b->pai->dir = b;
  }

}

//Rotação à Direita
void rightRotate(TpNodo *x,TpArvore *t){
  TpNodo *a,*b;

  a = x;
  b = x->esq;

  b->pai = a->pai;
  a->esq = b->dir;

  if(a->esq != NULL)
    a->esq->pai = a;

  a->pai = b;
  b->dir = a;

  if (b->pai == NULL)
    t->raiz = b;
  else{
    if (b->chave < b->pai->chave)
      b->pai->esq = b;
    else
      b->pai->dir = b;
  }
}

//Função responsável por verificar os casos de insersão da RED-BLACK
void insertFixUp(TpNodo *z,TpArvore *t){
  if(z->pai == NULL){
    z->cor = PRETO;
  }else{
    if (z->pai->cor == VERMELHO && z->cor == VERMELHO){
      if(z->pai->pai->esq == z->pai){                                         //o pai é o filho à ESQUERDA do avô
        if (z->pai->pai->dir != NULL && z->pai->pai->dir->cor == VERMELHO){   //CASO 1
          z->pai->cor = PRETO;
          z->pai->pai->cor = VERMELHO;
          z->pai->pai->dir->cor = PRETO;
          insertFixUp(z->pai->pai,t);
        }else{
          if(z == z->pai->dir){                                               //CASO 2
            leftRotate(z->pai,t);                                             //CASO 2
            z=z->esq;                                                         //CASO 2
          }
          z->pai->cor = PRETO;                                                //CASO 3
          z->pai->pai->cor = VERMELHO;                                        //CASO 3
          rightRotate(z->pai->pai,t);                                         //CASO 3
        }
      }else{                                                                  //o pai é o filho à DIREITA do avô
        if (z->pai->pai->esq != NULL && z->pai->pai->esq->cor == VERMELHO){   //CASO 1
          z->pai->cor = PRETO;
          z->pai->pai->cor = VERMELHO;
          z->pai->pai->esq->cor = PRETO;
          insertFixUp(z->pai->pai,t);
        }else{
          if(z == z->pai->esq){                                               //CASO 2
            rightRotate(z->pai,t);                                            //CASO 2
            z=z->dir;                                                         //CASO 2
          }
          z->pai->cor = PRETO;                                                //CASO 3
          z->pai->pai->cor = VERMELHO;                                        //CASO 3
          leftRotate(z->pai->pai,t);                                          //CASO 3
        }
      }
    }
  }
}

void printT(TpNodo *x) {
   if(x != NULL){
    (x->pai != NULL) ? printf("|%d\tChave Pai: %d\t\tCor: %s\tNível: %d\n",x->chave, x->pai->chave,(x->cor == 0)?"Vermelho":"Preto",x->nivel) : printf("|%d\tChave Pai: Raiz.\tCor: %s\tNível: %d\n",x->chave,(x->cor == 0)?"Vermelho":"Preto",x->nivel);
    printT(x->esq);
    printT(x->dir);
  }
}
