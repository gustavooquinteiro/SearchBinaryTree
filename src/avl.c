#include <stdio.h>
#include <stdlib.h>
#include "../lib/avl.h"
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
	int level; 
	int balanceFactor;
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
	arvore->root = inserirNo(raiz, novoNo); 
	arvore->treeHeight = calculaAltura(arvore->root) + ONE;		
	return arvore;
}

Node * criarCliente (int codigoCliente, int operacao, int valor){
	Client * novoCliente = (Client *)malloc(sizeof(Client));
	if (!novoCliente){
		perror(ERROR);
		exit(EXIT_FAILURE);
	} else{
		novoCliente->codigoCliente = codigoCliente;
		novoCliente->operacao = operacao;		
		novoCliente->valor = valor;
		novoCliente->saldo = ZERO;
		novoCliente->quantidadeOperacoes = ONE; 
		return criarNo(novoCliente);
	}
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
		novoNo->level = ONE; 
		novoNo->height = ONE; 
		novoNo->balanceFactor = ZERO;
	}
	return novoNo;
}

// Função que insere o nó na arvore 
Node * inserirNo(Node * raiz, Node * noAtual){
	if (!raiz){	
		// se entrar aqui tem que atualizar a qtd de nos nao sei como ainda se vira
		return noAtual; 
	}
	if (noAtual->client->codigoCliente > raiz->client->codigoCliente){
		raiz->right = inserirNo(raiz->right, noAtual);
		// Atualiza o filho de raiz
		raiz->right->dad = raiz;
		// Atualiza o nivel do filho  de raiz
		raiz->right->level = calculaNivel(raiz->right);
		// Atualiza o fator de balanceamento de raiz
		raiz->balanceFactor = calculaBalanceFactor(raiz);
	}
	if (noAtual->client->codigoCliente == raiz->client->codigoCliente)
		raiz = atualizarCliente(noAtual, raiz);

	if (noAtual->client->codigoCliente < raiz->client->codigoCliente){
		raiz->left = inserirNo(raiz->left, noAtual);
		raiz->left->dad = raiz;	
		raiz->left->level = calculaNivel(raiz->left);
		raiz->balanceFactor = calculaBalanceFactor(raiz);
	}
	raiz->height = calculaAltura(raiz);	
	raiz->level = calculaNivel(raiz); 
	//abs(int __x), da stdio.h, retorna valor absoluto, i.e, módulo do número 
	if (abs(raiz->balanceFactor) == TWO)
		raiz = balanceamento(raiz);		
	return raiz;
}

// Função que atualiza os dados do cliente e retorna o no com os dados devidamente atualizados
Node * atualizarCliente(Node * noAtual, Node * arvore){
	//Depósito
	if (noAtual->client->operacao == ZERO){
		arvore->client->saldo += noAtual->client->valor;
	//Saque
	} else
		arvore->client->saldo -= noAtual->client->valor;
	arvore->client->quantidadeOperacoes++; 
	return arvore;
}

// Função que faz o balanceamento da arvore
Node * balanceamento(Node * x){
	if (x->balanceFactor == UNBALANCED_TREE_LEFT){
		Node * y = x->left;
		if (calculaBalanceFactor(y) == BALANCED_TREE_RIGHT){
			// Rotação dupla a direita
			x = rotacaoEsquerdaDireita(x); 
		}else{
			// Rotação a direita
			x = rotacaoDireita(x);
		}
	} else{
		Node * y = x->right;
		if(calculaBalanceFactor(y) == BALANCED_TREE_LEFT){
			// Rotação dupla a esquerda
			x = rotacaoDireitaEsquerda(x);
		} else{
			// Rotação a esquerda
			x = rotacaoEsquerda(x);
		}
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
	if (!arvore || chave == arvore->client->codigoCliente)
		return arvore;
	if (chave < arvore->client->codigoCliente){
		return busca(arvore->left, chave);
	} else 
		return busca(arvore->right, chave);
}

Node * getLeftSon(Node * raiz){
	return raiz->left; 
}

Node * getRightSon(Node * raiz){
	return raiz->right; 
}

Node * isTreeEmpty(AVLtree * arvore){
	return (arvore->treeHeight == ZERO)? NULL: arvore->root;
}

int getNivel(Node * no){
	return no->level;
}

long long int getClientCode(Node * no){
	return no->client->codigoCliente;
}

long long int getClientOperationsQuantity(Node * no){
	return no->client->quantidadeOperacoes;
}

long long int getClientValue(Node * no){
	return no->client->valor;
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
	if (!raiz->dad)
		return ONE;
	return calculaNivel(raiz->dad) + ONE; 
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

	//atualiza altura, nivel e FB;
	x->height = calculaAltura(x);
	x->level = calculaNivel(x);
	x->balanceFactor = calculaBalanceFactor(x);
	y->height = calculaAltura(y);
	y->level = calculaNivel(y);
	y->balanceFactor = calculaBalanceFactor(y);
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

	//atualiza altura, nivel e FB;
	x->height = calculaAltura(x);
	x->level = calculaNivel(x);
	x->balanceFactor = calculaBalanceFactor(x);
	y->height = calculaAltura(y);
	y->level = calculaNivel(y);
	y->balanceFactor = calculaBalanceFactor(y);
	return y;
}

Node * rotacaoEsquerdaDireita(Node * x){
	x->left = rotacaoEsquerda(x->left);
	return (rotacaoDireita(x));
}

Node * rotacaoDireitaEsquerda(Node * x){
	x->right = rotacaoDireita(x->right);
	return (rotacaoEsquerda(x));
}

Node * getMinimo(Node * x){
	Node * y = x;
	while(y->left != NULL){
		y = y->left;
	}
	return y;
}

// Tentativa de fazer um sucessor removendo da arvore com free() vi aqui (http://www.lcad.icmc.usp.br/~nonato/ED/AVL/algo-remocao.html) mas nesse site faz o inverso pega o maximo do no esquerdo (antecessor no caso) o do prof usa o sucessor 
Node * sucessor(Node * raiz, Node * noChave){
	Node * noRemovido; 
	if (raiz->left){
		raiz->left = sucessor(raiz->left, noChave);
	}else{
		noChave->client->codigoCliente = raiz->client->codigoCliente;
		noRemovido = raiz;
		raiz = raiz->left; 
		if (raiz)
			raiz->dad = noRemovido->dad; 
		free(noRemovido);
	}
	return raiz;
}

// Função pra remover a porcaria de um nó (eu só troquei o nome e alterei uma coisinha que tava errada de resto ainda é seu código)
Node * removerNo(Node * raiz, int x, AVLtree * arvoreAVL){
	int validador_pai = 0;
	if (x == raiz->client->codigoCliente){
		validador_pai = 1;
	}
	if(raiz == NULL){
		return NULL;
	}
	if(x < raiz->client->codigoCliente){
		raiz->left = removerNo(raiz->left, x, arvoreAVL);
	}
	else if(x > raiz->client->codigoCliente){
		raiz->right = removerNo(raiz->right, x, arvoreAVL);
	}
	else{
		if(raiz->left == NULL){
			raiz = raiz->right;
			if(validador_pai){
				arvoreAVL->root = raiz;
				arvoreAVL->treeHeight = calculaAltura(arvoreAVL->root);
				arvoreAVL->nodeQuantity-=1;
			}
		}
		else if(raiz->right == NULL){
			raiz = raiz->left;
			if(validador_pai){
				arvoreAVL->root = raiz;
				arvoreAVL->treeHeight = calculaAltura(arvoreAVL->root);
				arvoreAVL->nodeQuantity-=1;
			}
		}else{				
			Node * y = getMinimo(raiz->right);
			raiz->client = y->client;
			arvoreAVL->root = y;
			arvoreAVL->treeHeight = calculaAltura(arvoreAVL->root);
			arvoreAVL->nodeQuantity-=1;
			raiz->right = removerNo(raiz->right, y->client->codigoCliente, arvoreAVL);

		}
	}
	if(raiz == NULL){
		return raiz;
	}
	raiz->height = calculaAltura(raiz);
	if(abs(calculaBalanceFactor(raiz)) == TWO){
		raiz = balanceamento(raiz);
	}
	return raiz;
}


