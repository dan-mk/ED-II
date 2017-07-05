#include<stdio.h>
#include<stdlib.h>

typedef struct _produto{
  int codigo;
  char nome[20];
  float preco;
} Produto;

void cadastro();
void listar();

int main() {
  int esc;
  do{
    printf("\n0-Sair\n");
    printf("1-Cadastro produto\n");
    printf("2-Listar produtos\n");
    scanf("%d",&esc);
    printf("\n");

    switch(esc){
      case 1:
        cadastro();
        break;
      case 2:
        listar();
        break;
      case 0:
        break;
      default:
        printf("Escolha não permitida\n");
    }
  }while(esc != 0);
  return 0;
}

void cadastro(){
    Produto prod;
    FILE * arq;
    printf("Digite o codigo do produto:\n");
    scanf("%d",&prod.codigo);
    printf("Digite o preco do produto:\n");
    scanf("%f",&prod.preco);
    getchar();
    printf("Digite o nome do produto:\n");
    scanf("%s",prod.nome);

    arq=fopen("produtos.txt","r+b");
    if (arq==NULL){
      arq=fopen("produtos.txt","w+b");
    }
    fseek(arq,0,SEEK_END);
    fprintf(arq, "%d ", prod.codigo);
    fprintf(arq, "%0.2f ",prod.preco);
    fprintf(arq, "%s ",prod.nome);

    fclose(arq);

}

void listar() {
  FILE * arq =fopen("produtos.txt","r+b");
  int result;
  if (arq==NULL){
    printf("Não existem produtos cadastrados\n");
  }else{
    Produto prod;
    do{
     result = fscanf(arq, "%d%f%s",&prod.codigo,&prod.preco,prod.nome);
     if(result != EOF)
        printf("Codigo: %d. Preco: %0.2f. Produto: %s\n",prod.codigo,prod.preco,prod.nome);
   }while (feof(arq) == 0);
  }
  fclose(arq);
}
