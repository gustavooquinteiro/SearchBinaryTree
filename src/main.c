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
				//removeNo(raiz);
			break;
			case ORDER_LIST:
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
	exit(EXIT_SUCCESS);
}

void insereNo(AVLtree * arvoreAVL){
	int codigoCliente, valor, operacao;
	scanf("%d %d %d", &codigoCliente, &operacao, &valor);
	Node * novoNo = criarCliente(codigoCliente, operacao, valor);
	definirRaiz(arvoreAVL, novoNo); 
}

void buscaNo(AVLtree * arvoreAVL){
	int chave;
	scanf ("%d", &chave);
	printf("%s %d\n", busca(getRaiz(arvoreAVL), chave)? FOUND_KEY: NOT_FOUND_KEY, chave);			
}

/*void removeNo(Node * raiz){
	int chave;
	scanf("%d", &chave);
	//removerNo(raiz, chave);
}*/

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
	printf("%d\n", !getRaiz(arvoreAVL) ? ZERO: getAltura(getRaiz(arvoreAVL))+ONE);
}
