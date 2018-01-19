#include <stdio.h>
#include <stdlib.h>
#include "../lib/main.h"

/* Trabalho de Estrutura de Dados e Algoritmos I - MATA40
 * Desenvolvido por Fábio Lopes Gomes e Gustavo Oliveira Quinteiro
 * Maiores detalhes do desenvolvimento vide https://github.com/gustavooquinteiro/SearchBinaryTree */

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
	cleanTree(arvoreAVL);
	exit(EXIT_SUCCESS);
}

// Função que insere um nó com um cliente na árvore
void insereNo(AVLtree * arvoreAVL){
	long long int codigoCliente, valor, operacao;
	scanf("%lld %lld %lld", &codigoCliente, &operacao, &valor);
	Node * novoNo = criarNo(criarCliente(codigoCliente, operacao, valor));
	arvoreAVL = definirRaiz(arvoreAVL, novoNo);
}

// Função que busca determinada chave na árvore e mostra na tela mensagem informativa
void buscaNo(AVLtree * arvoreAVL){
	long long int chave;
	scanf ("%lld", &chave);
	printf("%s %lld\n", busca(getRaiz(arvoreAVL), chave)? FOUND_KEY_MESSAGE: NOT_FOUND_KEY_MESSAGE, chave);
}

// Função que remove determinada chave da árvore, se essa chave existir
void removeNo(AVLtree * arvoreAVL){
	long long int chave;
	scanf("%lld", &chave);
	arvoreAVL = atualizarRaiz(arvoreAVL, chave);
}

// Função que lista os nós segundo ordem inserida
void listarNos(AVLtree * arvoreAVL){
	char ordem;
	scanf(" %c", &ordem);
	(ordem == DECRESCENT_ORDER)? listarDecrescente(getRaiz(arvoreAVL)):listarCrescente(getRaiz(arvoreAVL));
}

// Função que lista todos os nós da arvore em ordem decrescente
void listarDecrescente(Node * raiz){
	if (raiz){
		listarDecrescente(getRightSon(raiz));
		printf("%lld %lld %lld\n", getClientCode(getClient(raiz)), getClientOperationsQuantity(getClient(raiz)), getSaldoCliente(getClient(raiz)));
		listarDecrescente(getLeftSon(raiz));
	}
}

// Função que lista todos os nós da arvore em ordem crescente
void listarCrescente(Node * raiz){
	if (raiz){
		listarCrescente(getLeftSon(raiz));
		printf("%lld %lld %lld\n", getClientCode(getClient(raiz)), getClientOperationsQuantity(getClient(raiz)), getSaldoCliente(getClient(raiz)));
		listarCrescente(getRightSon(raiz));
	}
}

// Função que lista determinado nível da árvore, se nível existente
void listarNivel(AVLtree * arvoreAVL){
	int nivel;
	scanf("%d", &nivel);
	Node * raiz = getRaiz(arvoreAVL);
	Queue * fila = defineQueue();
	if (raiz && fila){
		fila = push(fila, raiz);
		while (!isEmpty(fila) && calculaNivel(front(fila)) < nivel){
			if (getLeftSon(front(fila)))
				fila = push(fila, getLeftSon(front(fila)));


			if (getRightSon(front(fila)))
				fila = push(fila, getRightSon(front(fila)));

			fila = pop(fila);

		}
		while(!isEmpty(fila)){
			printf("%lld\n", getClientCode(getClient(front(fila))));
			fila = pop(fila);
		}
	}
	clearQueue(fila);
}

// Função que mostra a altura da arvore
void mostrarAltura(AVLtree * arvoreAVL){
	printf("%d\n", getAlturaArvore(arvoreAVL));
}

// Função que exibe o relatorio final segundo a ordem de remoção da raiz
void exibeRelatorio(AVLtree * arvoreAVL){
	//atualizaArvore(arvoreAVL);
	printf("-+- Inicio relatorio -+-\n");
	printf ("%d\n", getQuantidadeNos(arvoreAVL));
	while(getRaiz(arvoreAVL)){
		long long int codigo = getClientCode(getClient(getRaiz(arvoreAVL)));
		long long int operacoes = getClientOperationsQuantity(getClient(getRaiz(arvoreAVL)));
		long long int saldo = getSaldoCliente(getClient(getRaiz(arvoreAVL)));
		printf("%lld %lld %lld\n", codigo, operacoes, saldo);
		arvoreAVL = atualizarRaiz(arvoreAVL, codigo);
	}
	free(arvoreAVL);
	printf("-+- Fim relatorio -+-\n");
}
