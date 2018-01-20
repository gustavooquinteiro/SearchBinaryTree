#include <stdio.h>
#include <stdlib.h>
#include "../lib/avl.h"

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
 * perror() da stdio.h para lançar na saída padrão o texto MALLOC_ERROR junto com o erro especifico
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
AVLtree * definirRaiz(AVLtree * arvore, Client * cliente){
	Node * raiz = isTreeEmpty(arvore);
	arvore->root =	 inserirNo(raiz, cliente);
	arvore->treeHeight = calculaAltura(arvore->root) + ONE;
	arvore->nodeQuantity = calculaQuantidadeNos(arvore->root);
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
Node * inserirNo(Node * raiz, Client * cliente){
    // Caso nó atual seja uma folha, aloca na memória esse novo nó com o cliente, efetuando suas operções
    if (!raiz){
        raiz = criarNo(cliente);
		raiz->client = efetuarOperacao(cliente);
		return raiz;
	}
    // Caso código do cliente seja maior do que o código do cliente já presente na arvore, insere-o a direita desse nó
	if (getClientCode(cliente) > getClientCode(getClient(raiz))){
		raiz->right = inserirNo(getRightSon(raiz), cliente);
        // Atualiza o pai do nó alocado
		raiz->right->dad = raiz;
    // Caso código do cliente seja menor do que o código do cliente já presente na arvore, insere-o a esquerda desse nó
	} else if (getClientCode(cliente) < getClientCode(getClient(raiz))){
		raiz->left = inserirNo(getLeftSon(raiz), cliente);
		raiz->left->dad = raiz;
    // Caso o código do cliente já exista na arvore, atualiza as informações do cliente do nó com as operações e valores do cliente atual
	} else {
		raiz->client = atualizarCliente(cliente, getClient(raiz));
		return raiz;
	}
    // Calcula a altura do nó e se necessário realiza o balanceamento desse nó
    // Foi utilizado a função abs(int __x), da stdio.h, que retorna valor absoluto, i.e, módulo do número
	raiz->height = maximo(calculaAltura(getLeftSon(raiz)), calculaAltura(getRightSon(raiz))) + ONE;
	if(abs(calculaAltura(raiz->right) - calculaAltura(raiz->left)) == TWO)
		raiz = balanceamento(raiz);
	return raiz;
}

// Função que faz o balanceamento da arvore
Node * balanceamento(Node * x){
	if (calculaBalanceFactor(x) == -TWO){
		Node * y = x->right;
		if (calculaBalanceFactor(y) == ONE){
			x = rotacaoDuplaEsquerda(x);
		}else
			x = rotacaoEsquerda(x);
	} else{
		Node * y = x->left;
		if (calculaBalanceFactor(y) == -ONE){
			x = rotacaoDuplaDireita(x);
		}else
			x = rotacaoDireita(x);
	}
	return x;
}

/* Função que calcula o fator de balanceamento de um nó
 * Fator de balanceamento utilizado = altura da esquerda - altura da direita */
int calculaBalanceFactor(Node * no){
	if (!no){
        return ZERO;
    } else
        return calculaAltura(no->left) - calculaAltura(no->right);
}

// Função que realiza a rotação a direita de um nó
Node * rotacaoDireita(Node * x){
	Node * y = x->left;
	if(x){
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
	}
	return y;
}

// Função que realiza a rotação a esquerda de um nó
Node * rotacaoEsquerda(Node * x){
	Node * y = x->right;
	if(x){
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
	}
	return y;
}

// Função que realiza a dupla rotação a direita de um nó
Node * rotacaoDuplaDireita(Node * x){
	x->left = rotacaoEsquerda(x->left);
	return (rotacaoDireita(x));
}

// Função que realiza a dupla rotação a esquerda de um nó
Node * rotacaoDuplaEsquerda(Node * x){
	x->right = rotacaoDireita(x->right);
	return (rotacaoEsquerda(x));
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
	if(raiz)
        return raiz->left;
	return NULL;
}

// Função que retorna o filho a direita de um nó
Node * getRightSon(Node * raiz){
	if(raiz)
        return raiz->right;
	return NULL;
}

// Função que retorna um cliente de um nó
Client * getClient(Node * no){
	if(no)
        return no->client;
	return NULL;
}

// Função que verifica se a árvore está vazia
Node * isTreeEmpty(AVLtree * arvore){
	if(arvore){
        if (getAlturaArvore(arvore) == ZERO){
            return NULL;
        } else
            return arvore->root;
    }
	return NULL;
}

// Função que retorna a altura da árvore
int getAlturaArvore (AVLtree * arvore){
	return arvore->treeHeight;
}

// Função que verifica se a árvore tem uma raiz
Node * isRootDefined(AVLtree * arvore){
	if (!arvore->root){
        return NULL;
    } else
        return arvore->root;
}

// Função que retorna a raiz de uma árvore
Node * getRaiz(AVLtree * arvore){
	return isRootDefined(arvore);
}

// Função que calcula o nível de um nó
int calculaNivel(Node * raiz){
	if (!raiz->dad){
        return ONE;
    } else
        return calculaNivel(raiz->dad) + ONE;
}

// Função que retorna a quantidade de nós de uma árvore
int getQuantidadeNos(AVLtree * arvore){
	return arvore->nodeQuantity;
}

// Função que retorna o sucessor do nó
Node * sucessor(Node * raiz){
    return getMinimo(raiz->right);
}

// Função que retorna o menor valor, a partir de um nó fornecido
Node * getMinimo(Node * x){
	if(x) {
		Node * y = x;
		while (y->left)
			y = y->left;
		return y;
	}
	return NULL;
}

// Função que remove um nó, que contenha chave igual a x, da árvore
Node * removerNo(Node * raiz, int x){
	Node* nodeToRemove = NULL;

	if(!raiz)
		return NULL;

	if(x < getClientCode(getClient(raiz))){
		raiz->left = removerNo(raiz->left, x);
	} else if(x > getClientCode(getClient(raiz))){
		raiz->right = removerNo(raiz->right, x);
    // Encontrou nó a ser removido
	} else{
        // Caso nó tenha os dois filhos
        if (raiz->right && raiz->left){
           Node * temp = sucessor(raiz);
           Client* currentClient = getClient(temp);
           alterarClient(getClient(raiz), getClientCode(currentClient), getClientValue(currentClient), getClientOperation(currentClient), getSaldoCliente(currentClient), getClientOperationsQuantity(currentClient));
           raiz->right = removerNo(raiz->right, getClientCode(getClient(temp)));
       // Caso nó tenha um ou nenhum filho
       } else{
            // Caso nó tenha um filho a direita
            if(!raiz->left && raiz->right){
				raiz->right->dad = raiz->dad;
				if(raiz->dad){
					if(getClientCode(getClient(raiz->dad)) > getClientCode(getClient(raiz))){
						raiz->dad->left = raiz->right;
					}else{
						raiz->dad->right = raiz->right;
					}
				}
				nodeToRemove = raiz;
				raiz = raiz->right;

            // Caso nó tenha um filho a esquerda
            } else if(!raiz->right && raiz->left){
				raiz->left->dad = raiz->dad;
				if(raiz->dad) {
					if(getClientCode(getClient(raiz->dad)) > getClientCode(getClient(raiz))){
						raiz->dad->left = raiz->left;
					}else{
						raiz->dad->right = raiz->left;
					}
				}
				nodeToRemove = raiz;
				raiz = raiz->left;

            // Caso nó não tenha filhos
			}else{
				if(raiz->dad) {
					if(getClientCode(getClient(raiz->dad)) > getClientCode(getClient(raiz))){
						raiz->dad->left = NULL;
					}else{
						raiz->dad->right = NULL;
					}
				}
				nodeToRemove = raiz;
				raiz = NULL;
			}
            cleanNode(nodeToRemove);
		}
	}
	if(!raiz)
		return raiz;

	raiz->height = maximo(calculaAltura(raiz->left), calculaAltura(raiz->right)) + ONE;
	int balance = calculaBalanceFactor(raiz);
	if(abs(balance) == TWO)
			raiz = balanceamento(raiz);

	return raiz;
}

// Função que redefine a raiz da arvore
AVLtree * atualizarRaiz(AVLtree * arvore, int chave){
	Node * raiz = isTreeEmpty(arvore);
	arvore->root = removerNo(raiz, chave);
	arvore->treeHeight = calculaAltura(arvore->root) + ONE;
	arvore->nodeQuantity = calculaQuantidadeNos(arvore->root);
	return arvore;
}


// Função que calcula a quantidade de nós de uma árvore
int calculaQuantidadeNos(Node * raiz){
	if(!raiz) return ZERO;
	else if(((raiz->left) == (raiz->right)) && raiz->left == NULL) return ONE;
	return calculaQuantidadeNos(raiz->left) + calculaQuantidadeNos(raiz->right) + ONE;
}

// Função que retira a arvore da memória
void cleanTree(AVLtree * arvore){
    free(arvore);
    arvore = NULL;
}

// Função que retira o nó da memória, assim como o cliente contido
void cleanNode(Node * nodeToRemove){
    if (nodeToRemove){
    	removeClient(getClient(nodeToRemove));
    	free(nodeToRemove);
    	nodeToRemove = NULL;
    }
}
