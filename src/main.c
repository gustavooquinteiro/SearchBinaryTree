#include <stdio.h>
#include <stdlib.h>
#include "../lib/avl.h"
#include "../lib/main.h"
#include "../lib/queue.h"

extern int chave; 

int main(){
	char opcao;
	while (scanf ("%c", &opcao) && opcao != END){
		printf("%c :", opcao); 
		switch(opcao){
			case INSERT:
				insereNo(); 
			break; 
			case SEARCH:
				if (buscaNo()){
					printf("%s %d", FOUND_KEY, getChave());
				} else{
					printf("%s %d", NOT_FOUND_KEY, getChave());			
				}
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
	exit(EXIT_SUCCESS);
}

void insereNo(){
	int codigoCliente, valor, operacao;
	scanf("%d %d %d", &codigoCliente, &operacao, &valor);
	Node * novoNo = criarCliente(codigoCliente, operacao, valor);
	if (arvoreVazia())
		definirArvore(novoNo); 
	inserirNo(getRaiz(), novoNo); 
}

Node * buscaNo(){
	scanf ("%d", &chave);
	return (busca(getRaiz(), chave));
}

void removeNo(){
	scanf("%d", &chave);
	removerNo(busca(getRaiz(), chave), chave);
}

void listarNos(char opcao){
	if (opcao == ORDER_LIST){
		char ordem; 
		scanf("%c", &ordem); 
		printf("%c :", ordem); 
		if (ordem == DECRESCENT_ORDER)
			listarDecrescente(getRaiz());
		else
			listarCrescente(getRaiz());
	} else{
		int nivel;
		scanf("%d", &nivel); 
		mostrarNivel(nivel);
	}
}

void mostrarAltura(){
	printf("%d", getAltura(getRaiz()));
}

int getChave(){
	static int * key = &chave;
	return *(key); 
}
