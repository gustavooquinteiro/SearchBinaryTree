#include <stdio.h>
#include <stdlib.h>
#include "../lib/avl.h"
#include "../lib/client.h"
#include "../lib/queue.h"
 
// Declaração das structs
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

/* Função que aloca na memória uma árvore AVL
 * perror() da stdio.h para lançar na saída padrão o texto MALLOC_ERROR (da queue.h) junto com o erro especifico
 * exit() da stdlib.h para interromper a execução do programa com o código de falha */
AVLtree * definirArvore(){
	AVLtree * arvore = (AVLtree *)malloc(sizeof(AVLtree));
	if (!arvore){
		perror(MALLOC_ERROR);
		exit(EXIT_FAILURE);
	}
	arvore->root = NULL;
	arvore->treeHeight = ZERO;
	arvore->nodeQuantity = ZERO; 
	return arvore;
}

// Função que define a raiz da arvore
AVLtree * definirRaiz(AVLtree * arvore, Node * novoNo){
	Node * raiz = isTreeEmpty(arvore);
	arvore->root =	 inserirNo(raiz, arvore, novoNo); 
	arvore->treeHeight = calculaAltura(arvore->root) + ONE;		
	return arvore;
}

// Função que aloca na memória um nó com os atributos do cliente 
Node * criarNo(Client * novoCliente){
	Node * novoNo = (Node *)malloc(sizeof(Node));
	if (!novoNo){
		perror(MALLOC_ERROR);
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
	if(abs(calculaAltura(raiz->right) - calculaAltura(raiz->left)) == TWO)
		raiz = balanceamento(raiz);		
	return raiz;
}

// Função que faz o balanceamento da arvore
Node * balanceamento(Node * x){
	if (calculaAltura(x->right) - calculaAltura(x->left) == UNBALANCED_TREE_LEFT){
		Node * y = x->left;
		if (calculaAltura(y->right) - calculaAltura(y->left) == BALANCED_TREE_RIGHT){
			x = rotacaoDuplaDireita(x);
		}else
			x = rotacaoDireita(x);
	} else{
		Node * y = x->right;
		if (calculaAltura(y->right) - calculaAltura(y->left) == BALANCED_TREE_LEFT){
			x = rotacaoDuplaEsquerda(x);
		}else
			x = rotacaoEsquerda(x);
	}
	return x;
}

/* Função que calcula o fator de balanceamento de um nó
 * Fator de balanceamento utilizado = altura da direita - altura da esquerda */
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

// Função que retorna o filho a esquerda de um nó
Node * getLeftSon(Node * raiz){
	return raiz->left; 
}

// Função que retorna o filho a direita de um nó
Node * getRightSon(Node * raiz){
	return raiz->right; 
}

// Função que retorna um cliente de um nó
Client * getClient(Node * no){
	return no->client;
}

// Função que verifica se a árvore está vazia
Node * isTreeEmpty(AVLtree * arvore){
	return (getAlturaArvore(arvore) == ZERO)? NULL: arvore->root;
}

// Função que retorna a altura da árvore
int getAlturaArvore (AVLtree * arvore){
	return arvore->treeHeight;
}

// Função que verifica se a árvore tem uma raiz
Node * isRootDefined(AVLtree * arvore){
	return (!arvore->root)? NULL: arvore->root;
}

// Função que retorna a raiz de uma árvore
Node * getRaiz(AVLtree * arvore){
	return isRootDefined(arvore); 
}

// Função que calcula o nível de um nó
int calculaNivel(Node * raiz){
	return (!raiz->dad)? ONE: calculaNivel(raiz->dad) + ONE; 
}

// Função que retorna a quantidade de nós de uma árvore
int getQuantidadeNos(AVLtree * arvore){
	return arvore->nodeQuantity;
}

// Função que realiza a rotação a direita de um nó e atualiza sua altura
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

	x->height = maximo(calculaAltura(x->left), calculaAltura(x->right)) + ONE;
	y->height = maximo(calculaAltura(y->left), calculaAltura(y->right)) + ONE;
	return y;
}

// Função que realiza a rotação a esquerda de um nó e atualiza sua altura
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

	x->height = maximo(calculaAltura(x->left), calculaAltura(x->right)) + ONE;
	y->height = maximo(calculaAltura(y->left), calculaAltura(y->right)) + ONE;
	return y;
}

// Função que realiza a rotação dupla a direita de um nó
Node * rotacaoDuplaDireita(Node * x){
	x->left = rotacaoEsquerda(x->left);
	return rotacaoDireita(x);
}

// Função que realiza a rotação dupla a esquerda de um nó
Node * rotacaoDuplaEsquerda(Node * x){
	x->right = rotacaoDireita(x->right);
	return rotacaoEsquerda(x);
}

// Função que retorna o mínimo valor de um nó
Node * getMinimo(Node * x){
	Node * y = x;
	while (y->left)
		y = y->left;
	return y;
}

// Função que remove um nó, que contenha chave igual a x, da árvore 
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
				if(raiz->right != NULL)
					raiz->right->dad = raiz->dad;
				raiz = raiz->right;
				
			}
			else if(raiz->right == NULL){
				if(raiz == arvoreAVL->root){
					arvoreAVL->root = raiz->left;
				}
				if(raiz->left != NULL){
					raiz->left->dad =raiz->dad;
				}
				raiz = raiz->left;

			}else{				
				Node * y = getMinimo(raiz->right);
				raiz->client=y->client;
				raiz->right = removerNo(raiz->right, getClientCode(y->client), arvoreAVL);

			}
		}
		if(raiz == NULL){
			return raiz;
		}
		raiz->height = maximo(calculaAltura(raiz->left), calculaAltura(raiz->right)) + ONE;
		if(abs(calculaAltura(raiz->right) - calculaAltura(raiz->left)) == TWO){
			raiz = balanceamento(raiz);
		}
	return raiz;
}

// Função que calcula a quantidade de nós de uma árvore
int calculaQuantidadeNos(Node * raiz){
	if(!raiz) return 0;
	else if(((raiz->left) == (raiz->right)) && raiz->left == NULL) return 1;
	return calculaQuantidadeNos(raiz->left) + calculaQuantidadeNos(raiz->right) + 1;
}

// Função que atualiza a árvore
void atualizaArvore(AVLtree * arvore){
	if(arvore->root!=NULL){
		arvore->treeHeight = calculaAltura(arvore->root) + 1;
		arvore->nodeQuantity =calculaQuantidadeNos(arvore->root);
	}else{
		arvore->treeHeight = 0;
		arvore->nodeQuantity =0;
	}

}

