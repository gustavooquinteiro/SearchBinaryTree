#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

void print (char opcao){
	printf("%c", opcao); 
}

void insereNo(){
	int codigoCliente, valor, operacao;
	scanf("%d %d %d", &codigoCliente, &operacao, &valor);
	criarCliente(codigoCliente, operacao, valor);
	if (arvoreVazia()){
		definirArvore(getNo()); 
	} else{
		inserirNo(getRaiz(), getNo()); 
	}
}

void buscaNo(){
	int chave; 
	scanf ("%d", &chave);
	if (busca(getRaiz(), chave) == NULL){
		printf("nao existe no com chave: %d", chave);
	} else{
		printf("existe no com chave: %d", chave);
	}
}

void removeNo(){
	int chave; 
	scanf ("%d", &chave);
	removerNo(busca(getRaiz(), chave));
}

void listarNos(char opcao){
	if (opcao == ORDER_LIST){
		char ordem; 
		scanf("%c", &ordem); 
		print(ordem);
		if (ordem == DECRESCENT_ORDER)
			listarDecrescente(getRaiz());
		if (ordem == CRESCENT_ORDER)
			listarCrescente(getRaiz());
	} else{
		int nivel;
		scanf("%d", &nivel); 
		mostrarNivel(nivel)
	}
}

void mostrarAltura(){
	printf("%d", getAltura(getRaiz()));
}

int main(){
	char opcao;
	while (scanf ("%c", &opcao) && opcao != END){
		print(opcao);
		switch(opcao){
			case INSERT:
				insereNo(); 
			break; 
			case SEARCH:
				buscaNo();
			break;
			case REMOVE:
				removeNo();
			break;
			case ORDER_LIST:
			case LEVEL_LIST:
				listarNos(opcao);
			break;
			case HEIGHT:
				mostrarAltura();
			break;
		}
	}
	//exibirRelatorio(); 
	return ZERO;
}
