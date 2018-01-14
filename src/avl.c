#include <stdio.h>
#include <stdlib.h>
#include "../lib/avl.h"
#include "../lib/client.h"
#include "../lib/queue.h"

/* DE UMA OLHADA NO MATERIAL Q O PROF DISPONIBILIZOU NO CLASSROOM PQ LA TEM OS ALGORITMOS E TBM NO DESCRITIVO DO TRABALHO
 * OUTRA OBS IMPORTANTE: PARENTE NÃO QUER VARIAVEIS GLOBAIS ENTAO TEMOS QUE TRABALHAR COM VARIAVEIS LOCAIS E PASSA-LA POR REFERENCIA DE PONTEIRO 
 * O Q FALTA: 
 * Remoção de nó (OBS MT IMPORTANTE: Usar free(noAserRemovido) para desalocar da memoria perdemos pontos no trabalho passado pq nao usamos esse free) ESSA MERDAA
 * Mostrar por nivel (TA MEIO FEITO ESSA MERDA)
 * Exibir relatorio pela ordem de remoção da raiz CUU 
 * */
// Declaração das structs
typedef struct cliente{
	long long int codigoCliente;
	int operacao;
	long long int valor;
	long long int saldo;
	long long int quantidadeOperacoes; 
} Client;

typedef struct no{
	Client * client;
	struct no *right;
	struct no *left;
	struct no *dad;
	int height;
} Node;

typedef struct tree{
	Node * root;
	int treeHeight;
	int nodeQuantity; 
} AVLtree; 

AVLtree * definirArvore(){
	AVLtree * arvore = (AVLtree *)malloc(sizeof(AVLtree));
	if (!arvore){
		// perror() da stdio.h para lançar na saída padrão o texto ERROR (da queue.h) junto com o erro especifico
		perror(ERROR);
		//exit() da stdlib.h para interromper a execução do programa com o código de falha
		exit(EXIT_FAILURE);
	}
	arvore->root = NULL;
	// Define arvore com altura 0, i.e arvore vazia
	arvore->treeHeight = ZERO;
	arvore->nodeQuantity = ZERO; 
	return arvore;
}

AVLtree * definirRaiz(AVLtree * arvore, Node * novoNo){
	Node * raiz = isTreeEmpty(arvore);
	arvore->root =	 inserirNo(raiz, arvore, novoNo); 
	arvore->treeHeight = calculaAltura(arvore->root) + ONE;		
	return arvore;
}

// Aloca na memória um nó com os atributos do cliente 
Node * criarNo(Client * novoCliente){
	Node * novoNo = (Node *)malloc(sizeof(Node));
	if (!novoNo){
		perror(ERROR);
		exit(EXIT_FAILURE);
	} else{
		novoNo->client = novoCliente;
		novoNo->right = NULL;
		novoNo->left = NULL;
		novoNo->dad = NULL;
		novoNo->height = ONE; 
	}
	return novoNo;
}

// Função que insere o nó na arvore 
Node * inserirNo(Node * raiz, AVLtree * arvore, Node * noAtual){
	if (!raiz){	
		arvore->nodeQuantity++;
		noAtual->client = efetuarOperacao(getClient(noAtual));
		return noAtual; 
	}
	if (getClientCode(getClient(noAtual)) > getClientCode(getClient(raiz))){
		raiz->right = inserirNo(getRightSon(raiz), arvore, noAtual);
		// Atualiza o filho de raiz
		raiz->right->dad = raiz;
	}
	if (getClientCode(getClient(noAtual)) == getClientCode(getClient(raiz)))
		raiz->client = atualizarCliente(getClient(noAtual), getClient(raiz));

	if (getClientCode(getClient(noAtual)) < getClientCode(getClient(raiz))){
		raiz->left = inserirNo(getLeftSon(raiz), arvore, noAtual);
		raiz->left->dad = raiz;	
	}
	raiz->height = maximo(calculaAltura(getLeftSon(raiz)), calculaAltura(getRightSon(raiz))) + ONE;	
	//abs(int __x), da stdio.h, retorna valor absoluto, i.e, módulo do número 
	if (abs(calculaBalanceFactor(raiz)) == TWO)
		raiz = balanceamento(raiz);		
	return raiz;
}

// Função que faz o balanceamento da arvore
Node * balanceamento(Node * x){
	if (calculaBalanceFactor(x) == UNBALANCED_TREE_LEFT){
		if (calculaBalanceFactor(getLeftSon(x)) == BALANCED_TREE_RIGHT){
			x = rotacaoDuplaDireita(x);
		}else
			x = rotacaoDireita(x);
	} else{
		if (calculaBalanceFactor(getRightSon(x)) == BALANCED_TREE_LEFT){
			x = rotacaoDuplaEsquerda(x);
		}else
			x = rotacaoEsquerda(x);
	}
	return x; 
}

int calculaBalanceFactor(Node * no){
	return (!no)? ZERO: calculaAltura(no->right) - calculaAltura(no->left); 
}

// Função que retorna o maior valor entre os dois parametros recebidos 
int maximo(int esquerda, int direita){
	return (esquerda > direita)? esquerda: direita;
}

// Função que retorna a altura de determinado no da arvore
int calculaAltura(Node * node){
	return (!node)? -ONE: maximo(calculaAltura(node->left), calculaAltura(node->right)) + ONE;
}

// Função de busca da chave na arvore 
Node * busca(Node * arvore, int chave){
	if (!arvore || chave == getClientCode(arvore->client))
		return arvore;
	if (chave < getClientCode(arvore->client)){
		return busca(getLeftSon(arvore), chave);
	} else 
		return busca(getRightSon(arvore), chave);
}

Node * getLeftSon(Node * raiz){
	return raiz->left; 
}

Node * getRightSon(Node * raiz){
	return raiz->right; 
}

Client * getClient(Node * no){
	return no->client;
}

Node * isTreeEmpty(AVLtree * arvore){
	return (getAlturaArvore(arvore) == ZERO)? NULL: arvore->root;
}

int getAlturaArvore (AVLtree * arvore){
	return arvore->treeHeight;
}

Node * isRootDefined(AVLtree * arvore){
	return (!arvore->root)? NULL: arvore->root;
}

Node * getRaiz(AVLtree * arvore){
	return isRootDefined(arvore); 
}

int calculaNivel(Node * raiz){
	return (!raiz->dad)? ONE: calculaNivel(raiz->dad) + ONE; 
}

int getQuantidadeNos(AVLtree * arvore){
	return arvore->nodeQuantity;
}

Node * rotacaoDireita(Node * x){
	Node * y = x->left;
	if (x->dad){
		if (x->dad->left == x){
			x->dad->left = y;
		} else{
			x->dad->right = y;
		}
	}
	y->dad = x->dad;
	x->left = y->right;
	if (x->left) 
		x->left->dad = x; 
	y->right = x;
	x->dad = y;

	//atualiza altura
	x->height = maximo(calculaAltura(x->left), calculaAltura(x->right)) + ONE;
	y->height = maximo(calculaAltura(y->left), calculaAltura(y->right)) + ONE;
	return y;
}

Node * rotacaoEsquerda(Node * x){
	Node * y = x->right;
	if (x->dad){
		if (x->dad->left == x){
			x->dad->left = y;
		} else{
			x->dad->right = y;
		}
	}
	y->dad = x->dad;
	x->right = y->left;
	if (x->right)
		x->right->dad = x;
	y->left = x;
	x->dad = y;

	//atualiza altura
	x->height = maximo(calculaAltura(x->left), calculaAltura(x->right)) + ONE;
	y->height = maximo(calculaAltura(y->left), calculaAltura(y->right)) + ONE;
	return y;
}

Node * rotacaoDuplaDireita(Node * x){
	x->left = rotacaoEsquerda(x->left);
	return rotacaoDireita(x);;
}

Node * rotacaoDuplaEsquerda(Node * x){
	x->right = rotacaoDireita(x->right);
	return rotacaoEsquerda(x);
}

Node * getMinimo(Node * x){
	Node * y = x;
	while(y->left != NULL){
		y = y->left;
	}
	return y;
}

// Função pra remover a porcaria de um nó (eu só troquei o nome e alterei uma coisinha que tava errada de resto ainda é seu código)
Node * removerNo(Node * raiz, int x, AVLtree * arvoreAVL){
		if(raiz == NULL){
			return NULL;
		}
		if(x < getClientCode(raiz->client)){
			raiz->left = removerNo(raiz->left, x, arvoreAVL);
		}
		else if(x > getClientCode(raiz->client)){
			raiz->right = removerNo(raiz->right, x, arvoreAVL);
		} else{
			if(raiz->left == NULL){
				if(raiz == arvoreAVL->root){
					arvoreAVL->root = raiz->right;
				}
				raiz = raiz->right;
				
			}
			else if(raiz->right == NULL){
				if(raiz == arvoreAVL->root){
					arvoreAVL->root = raiz->left;
				}
				raiz = raiz->left;

			}else{				
				Node * y = getMinimo(raiz->right);
				raiz->client = y->client;
				raiz->right = removerNo(raiz->right, getClientCode(y->client), arvoreAVL);

			}
		}
		if(raiz == NULL){
			return raiz;
		}
		raiz->height = maximo(calculaAltura(raiz->left), calculaAltura(raiz->right)) + ONE;
		if(abs(calculaBalanceFactor(raiz)) == TWO){
			raiz = balanceamento(raiz);
		}

	return raiz;
}

void atualizaArvore(AVLtree * arvore){
	if(arvore->root!=NULL){
		arvore->treeHeight = calculaAltura(arvore->root) + 1;
		arvore->nodeQuantity = calculaNivel(arvore->root) + 1;
	}else{
		arvore->treeHeight = 0;
		arvore->nodeQuantity =0;
	}

}

