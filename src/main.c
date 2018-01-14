#include <stdio.h>
#include <stdlib.h>
#include "../lib/avl.h"
#include "../lib/main.h"
#include "../lib/queue.h"

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
	exibeRelatorio(arvoreAVL); 
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
	removerNo(getRaiz(arvoreAVL), chave, arvoreAVL);
	//free(teste);
}

void listarNos(AVLtree * arvoreAVL){
	char ordem; 
	scanf(" %c", &ordem); 
	(ordem == DECRESCENT_ORDER)? listarDecrescente(getRaiz(arvoreAVL)):listarCrescente(getRaiz(arvoreAVL));
}

// Função que lista todos os nós da arvore em ordem decrescente
void listarDecrescente(Node * raiz){
	if (raiz){
		listarDecrescente(getRightSon(raiz));
		printf("%lld %lld %lld\n", getClientCode(raiz), getClientOperationsQuantity(raiz), getClientValue(raiz));
		listarDecrescente(getLeftSon(raiz));
	}
}

// Função que lista todos os nós da arvore em ordem crescente
void listarCrescente(Node * raiz){
	if (raiz){
		listarCrescente(getLeftSon(raiz));
		printf("%lld %lld %lld\n", getClientCode(raiz), getClientOperationsQuantity(raiz), getClientValue(raiz));
		listarCrescente(getRightSon(raiz));
	}
}

void listarNivel(AVLtree * arvoreAVL){
	int nivel;
	scanf("%d", &nivel); 
	Node * raiz = getRaiz(arvoreAVL);
	Queue * fila = defineQueue();	
	if (raiz && fila){
		fila = push(fila, raiz); 
		while (!isEmpty(fila) && getNivel(front(fila)) < nivel){

			if (getLeftSon(front(fila)))
				fila = push(fila, getLeftSon(front(fila))); 

			if (getRightSon(front(fila))) 
				fila = push(fila, getRightSon(front(fila))); 
				
			pop(fila);		
		}
		while(!isEmpty(fila)){
			printf("%lld %lld %lld\n", getClientCode(front(fila)), getClientOperationsQuantity(front(fila)), getClientValue(front(fila))); 
			pop(fila);
		}
	}
}

void mostrarAltura(AVLtree * arvoreAVL){
	printf("%d\n", getAlturaArvore(arvoreAVL));
}

void exibeRelatorio(AVLtree * arvoreAVL){
	printf("-+- Inicio relatorio -+-\n");
	printf ("%d\n", getQuantidadeNos(arvoreAVL));
	//enquanto arvore não vazia se vira aqui e faz 
	// atualizarCliente(getRaiz(arvore))
	// remover(getRaiz(arvore)) 
	printf("-+- Fim relatorio -+-\n");
}
