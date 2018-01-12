#include <stdio.h>
#include <stdlib.h>
#include "../lib/avl.h"
#include "../lib/main.h"

int main(){
	AVLtree * arvoreAVL = definirArvore();
	char opcao;
	while (scanf("%c", &opcao) && opcao != END){
		switch(opcao){
			case INSERT:
				insereNo(arvoreAVL);
			break; 
			case SEARCH:
				buscaNo(arvoreAVL);
			break;
			case REMOVE:
				removeNo(arvoreAVL);
			break;
			case ORDER_LIST:
				printf("entra");
				listarNos(arvoreAVL);
			break;
			case LEVEL_LIST:
				listarNivel(arvoreAVL);
			break;
			case HEIGHT:
				mostrarAltura(arvoreAVL);
			break;
		}
	}
	//exibirRelatorio(); 
	free(arvoreAVL);
	exit(EXIT_SUCCESS);
}

void insereNo(AVLtree * arvoreAVL){
	int codigoCliente, valor, operacao;
	scanf("%d %d %d", &codigoCliente, &operacao, &valor);
	Node * novoNo = criarCliente(codigoCliente, operacao, valor);
	arvoreAVL = definirRaiz(arvoreAVL, novoNo); 
}

void buscaNo(AVLtree * arvoreAVL){
	int chave;
	scanf ("%d", &chave);
	printf("%s %d\n", busca(getRaiz(arvoreAVL), chave)? FOUND_KEY_MESSAGE: NOT_FOUND_KEY_MESSAGE, chave);			
}

void removeNo(AVLtree * arvoreAVL){
	int chave;
	scanf("%d", &chave);
	free(removerNo(getRaiz(arvoreAVL), chave));
}

void listarNos(AVLtree * arvoreAVL){
	char ordem; 
	scanf("%c", &ordem); 
	ordem == DECRESCENT_ORDER? listarDecrescente(getRaiz(arvoreAVL)): listarCrescente(getRaiz(arvoreAVL));
}

void listarNivel(AVLtree * arvoreAVL){
	int nivel;
	scanf("%d", &nivel); 
	mostrarNivel(nivel, arvoreAVL);	
}

void mostrarAltura(AVLtree * arvoreAVL){
	printf("%d\n", alturaArvore(arvoreAVL));
}
