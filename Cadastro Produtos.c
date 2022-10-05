#include <stdio.h>
#include <string.h>

typedef struct{
	char nomeprod[40];
	char marcaprod[40];
	char categoria[40];
	int qtdcomprada;
	
}tcadProd;

int qtd=0; // controlar a quantidade comprada desse produto

//-----------

void addProduto(tcadProd p[]){
	
	printf("--Cadastro de Produtos--\n\n");
	printf("Nome do Produto: ");
	fflush(stdin); // limpa o buffer do teclado
	gets(p[qtd].nomeprod); // lendo o atributo nome
	printf("-----------------------------------");
	printf("\nMarca do Produto: ");
	fflush(stdin);
	gets(p[qtd].marcaprod);
	printf("-----------------------------------");
	printf("\nCategoria do Produto: ");
	gets(p[qtd].categoria);
	printf("-----------------------------------");
	printf("\nQuantidade Comprada Para Estoque: ");
    scanf("%d",&p[qtd].qtdcomprada);
    qtd++;
    printf("\n Produto Adicionado com Sucesso!!!");
	
}

// --------------

void listaprod(tcadProd p[]){
	int i;
	for(i=0;i<qtd;i++){
		printf("*** Produto %d ***\n",i+1);
		printf("Nome do Produto: %s\n", p[i].nomeprod);
		printf("Marca do Produto: %s\n", p[i].marcaprod);
		printf("Categoria do Produto: %s\n", p[i].categoria);
		printf("Quantidade em Estoque: %d\n", p[i].qtdcomprada);
		printf("-------------------------\n");	
			
	} // fim for
}
//-------------------------------------------
void salvaArquivo(tcadProd p[]){
	FILE *arq;
	int i=0;
	arq=fopen("dadosProdutos.txt","wb");
	fwrite(&p[i],sizeof(tcadProd),qtd,arq);
	printf("Dados salvos com sucesso\n");
	fclose(arq);
}

//--------------------------
void carregaArquivo(tcadProd p[]){
	FILE *arq;
	arq=fopen("dadosProdutos.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado :(\n");
	  return;
	  }// fim if
	 while(fread(&p[qtd],sizeof(tcadProd),1,arq) >0 )
	      qtd++;  
	 printf("Dados carregados com sucesso !\n");
	fclose(arq);
}
//----------------------------------------------------
int filtroCategoria(tcadProd p[], char filtrocat[40]){
	int i;
	char aux[40];
	for(i=0;i<qtd;i++){
		strcpy(aux,p[i].categoria); // copiando do vetor para aux
		strupr(aux);// uppercase
		if(strcmp(filtrocat,aux)==0){
			printf("** Produto %d **\n",i+1);
			printf("Nome do Produto: %s\n",p[i].nomeprod);
			printf("Marca do Produto: %s\n",p[i].marcaprod);
			printf("Categoria do Produto :%s\n",p[i].categoria);
			printf("Quantidade em Estoque: %d\n", p[i].qtdcomprada);
			printf("------------------------\n");
		return i;// retornando o indice
		}// fim if
	}// fim for
	return -1;// nao encontrou
}

//---------------------------------------------------------
int filtroNome(tcadProd p[],char filtronome[40]){
	int i;
	char aux[40];
	for(i=0;i<qtd;i++){
		strcpy(aux,p[i].nomeprod); // copiando do vetor para aux
		strupr(aux);// uppercase
		if(strcmp(filtronome,aux)==0){
			printf("** Produto %d **\n",i+1);
			printf("Nome do Produto: %s\n",p[i].nomeprod);
			printf("Marca do Produto: %s\n",p[i].marcaprod);
			printf("Categoria do Produto: %s\n",p[i].categoria);
			printf("Quantidade em Estoque: %d\n", p[i].qtdcomprada);
			printf("------------------------\n");
			return i;// retornando o indice
		}// fim if
	}// fim for
	return -1;// nao encontrou
}

//-----------------------------------------

void removeProduto(tcadProd p[], char filtronome[40]){
	int posicao, resp;
	posicao = filtroNome(p,filtronome);
	if(posicao== -1){
		printf("Produto nao encontrado\n");
		return;
	}// fim if
	printf("Tem certeza que deseja remover?[1-Sim|2-Nao]: ");
	scanf("%d",&resp);
	if(resp==1){
		p[posicao] = p[qtd-1]; // sobrepondo com a ultima
		qtd--;
		printf("Produto Removido Com Sucesso!");
	}// fim if
	else
	 printf("Operacao cancelada\n");
}

void alteraProduto(tcadProd p[], char filtronome[40]){
	int posicao, resp;
	char novonome[40];
	system("cls");
	posicao = filtroNome(p,filtronome);
	if(posicao== -1){
		printf("Produto nao encontrado\n");
		return;
	}
	else{
		printf("Qual Campo quer alterar?");
		fflush(stdin);
		printf("\n1 - Nome do Produto.\n2 - Marca do Produto. \n3 - Categoria do Produto. \n4 - Quantidade do Estoque.\n5 - Todos os Dados.\n");
		scanf("%d",&resp);
		fflush(stdin);
		if(resp==1){
			printf("Digite o Novo Nome: ");
			gets(p[posicao].nomeprod);
			printf("\n Nome Alterado com Sucesso!!!");
		}
		else if(resp==2){
			printf("Digite a Nova Marca: ");
			gets(p[posicao].marcaprod);
			printf("\n Marca Alterada com Sucesso!!!");
		}
		else if(resp==3){
			printf("Digite a Nova Categoria: ");
			gets(p[posicao].categoria);
			printf("\n Categoria Alterada com Sucesso!!!");
		}
		else if(resp==4){
			printf("Digite a Nova Quantidade: ");
			scanf("%d",&p[posicao].qtdcomprada);
			printf("\n Estoque Alterado com Sucesso!!!");
		}
		else if(resp==5){
			printf("Novo Nome: ");
			fflush(stdin); // limpa o buffer do teclado
			gets(p[posicao].nomeprod); // lendo o atributo nome
			printf("-----------------------------------");
			printf("\nNova Marca: ");
			fflush(stdin);
			gets(p[posicao].marcaprod);
			printf("-----------------------------------");
			printf("\nNova Categoria: ");
			gets(p[posicao].categoria);
			printf("-----------------------------------");
			printf("\nNovo Estoque: ");
    		scanf("%d",&p[posicao].qtdcomprada);
		}
	}
	
}
//-------------------------------------

int menu(){
	int opcao;
	printf("*** Sistema de Cadastro de Produtos Diversos ***\n");
	printf("1 - Cadastrar\n");
	printf("2 - Listar\n");
	printf("3 - Filtrar por Categoria\n");
	printf("4 - Filtrar por Nome\n");
	printf("6 - Remover Produto\n");
	printf("7 - Alterar Produto Cadastrado\n");
	printf("0 - Sair\n\n");
	scanf("%d",&opcao);
	return opcao;
	
} // fim do menu
  // ---------------
  
int main(){
	tcadProd produtos[100];
	int opcao, busca;
	char marca, filtrocat[40], filtronome[40];
	carregaArquivo(produtos);
	do{
		opcao = menu();
		switch(opcao){
			case 1: 
			system("cls");
			addProduto(produtos);
			break;
			
			case 2: 
			system("cls");
			printf("Listar Produto\n");
			listaprod(produtos);
			break;
			
			case 3:
			fflush(stdin);
			system("cls");
			printf("Filtrar por Categoria\n");
			gets(filtrocat);
			strupr(filtrocat);
			filtroCategoria(produtos,filtrocat);
			break;
			
			case 4: 
			fflush(stdin);
			system("cls");
			printf("Filtrar por Nome\n");
			gets(filtronome);
			strupr(filtronome);
			filtroNome(produtos,filtronome);
			break;
			
			case 6:
			system("cls");
			printf("Nome do Produto:");
			fflush(stdin);
			gets(filtronome);
			strupr(filtronome);
			removeProduto(produtos, filtronome);
			break;
			
			case 7:
			system("cls");
			printf("Nome do Produto:");
			fflush(stdin);
			gets(filtronome);
			strupr(filtronome);
			alteraProduto(produtos, filtronome);
			break;
			
			case 0: printf("Saindo...\n");
			salvaArquivo(produtos);
			break;
			default: printf("Opcao Invalida\n");
			
		}// fim switch
		
		getch(); // pausa de execução no sistema
		system("cls"); // limpa tela
		
		
	}while(opcao!=0);
	return 0;
	
		
} // fim main

