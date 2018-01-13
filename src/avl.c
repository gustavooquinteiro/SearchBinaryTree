#include <stdio.h>
#include <stdlib.h>
#include "../lib/avl.h"
#include "../lib/queue.h"

/* DE UMA OLHADA NO MATERIAL Q O PROF DISPONIBILIZOU NO CLASSROOM PQ LA TEM OS ALGORITMOS E TBM NO DESCRITIVO DO TRABALHO
 * OUTRA OBS IMPORTANTE: PARENTE NÃO QUER VARIAVEIS GLOBAIS ENTAO TEMOS QUE TRABALHAR COM VARIAVEIS LOCAIS E PASSA-LA POR REFERENCIA DE PONTEIRO 
 * Remoção de nó (OBS MT IMPORTANTE: Usar free(noAserRemovido) para desalocar da memoria perdemos pontos no trabalho passado pq nao usamos esse free) ESSA MERDAA
 * Mostrar por nivel (TA MEIO FEITO OLHA O queue.c TEM MEU AVAL PRA MEXER LÁ)
 * Exibir relatorio pela ordem de remoção
 * */
// Declaração das structs
typedef struct cliente{
	int codigoCliente;
	int operacao;
	int valor;
	int saldo;
	int quantidadeOperacoes; 
} Client;

typedef struct no{
	Client client;
	struct no *right;
	struct no *left;
	struct no *dad;
	int height;
	int level; 
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
	
	// Define arvore com altura 0, i.e arvore vazia
	arvore->treeHeight = getAltura(arvore->root) + ONE;
	arvore->nodeQuantity = ZERO; 
	return arvore;
}

AVLtree * definirRaiz(AVLtree * arvore, Node * novoNo){
	printf("INSERIR NO: %d\n", novoNo->client.codigoCliente);
	
	Node * raiz = isTreeEmpty(arvore);
	printf("ATUAL RAIZ: %d\n", raiz ? raiz->client.codigoCliente: ZERO);
	if (!busca(raiz, novoNo->client.codigoCliente))
		arvore->nodeQuantity += ONE;
	arvore->root = inserirNo(raiz, novoNo); 
	arvore->treeHeight = getAltura(arvore->root) + ONE;		
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
		novoNo->client = *(novoCliente);
		novoNo->right = NULL;
		novoNo->left = NULL;
		novoNo->dad = NULL;
		novoNo->level = ZERO; 
	}
	return novoNo;
}

// Função que insere o nó na arvore 
Node * inserirNo(Node * raiz, Node * noAtual){
	if (!raiz){	
		noAtual->level = getNivel(noAtual) + ONE;
		return noAtual; 
	}
	if (noAtual->client.codigoCliente > raiz->client.codigoCliente){
		raiz->right = inserirNo(raiz->right, noAtual);
		if (!raiz->right->dad)
			raiz->right->dad = raiz;
		raiz->right->level = getNivel(raiz->right) + ONE;
	}
	if (noAtual->client.codigoCliente == raiz->client.codigoCliente)
		raiz = atualizarCliente(noAtual, raiz);

	if (noAtual->client.codigoCliente < raiz->client.codigoCliente){
		raiz->left = inserirNo(raiz->left, noAtual);
		if (!raiz->left->dad)
			raiz->left->dad = raiz;	
		raiz->left->level = getNivel(raiz->left) + ONE;
	}
	raiz->height = getAltura(raiz);	
	raiz->level = getNivel(raiz) + ONE; 
	//abs(int __x), da stdio.h, retorna valor absoluto, i.e, módulo do número 
	if (abs(getBalanceFactor(raiz)) == TWO)
		raiz = balanceamento(raiz);		
	printf("NIVEL RETORNADO === %d para NO=== %d\n", raiz->level, raiz->client.codigoCliente); 
	return raiz;
}

// Função que atualiza os dados do cliente e retorna o no com os dados devidamente atualizados
Node * atualizarCliente(Node * noAtual, Node * arvore){
	//Depósito
	if (noAtual->client.operacao == ZERO){
		arvore->client.saldo += noAtual->client.valor;
	//Saque
	} else
		arvore->client.saldo -= noAtual->client.valor;
	arvore->client.quantidadeOperacoes++; 
	return arvore;
}

// Função que faz o balanceamento da arvore
Node * balanceamento(Node * x){
	if (getBalanceFactor(x) == UNBALANCED_TREE_LEFT){
		Node * y = x->left;
		if (getBalanceFactor(y) == BALANCED_TREE_RIGHT){
			// Rotação dupla a direita
			x = rotacaoEsquerdaDireita(x); 
		}else{
			// Rotação a direita
			x = rotacaoDireita(x);
		}
	} else{
		Node * y = x->right;
		if(getBalanceFactor(y) == BALANCED_TREE_LEFT){
			// Rotação dupla a esquerda
			x = rotacaoDireitaEsquerda(x);
		} else{
			// Rotação a esquerda
			x = rotacaoEsquerda(x);
		}
	}
	return x; 
}

int getBalanceFactor(Node * no){
	return no? getAltura(no->right) - getAltura(no->left): ZERO; 
}

// Função que retorna o maior valor entre os dois parametros recebidos 
int maximo(int esquerda, int direita){
	return esquerda > direita ? esquerda: direita;
}

// Função que retorna a altura de determinado no da arvore
int getAltura(Node * node){
	if (!node)
		return -ONE; 
	return maximo(getAltura(node->left), getAltura(node->right)) + ONE;
}

// Função de busca da chave na arvore 
Node * busca(Node * arvore, int chave){
	if (!arvore || chave == arvore->client.codigoCliente)
		return arvore;
	if (chave < arvore->client.codigoCliente){
		return busca(arvore->left, chave);
	} else 
		return busca(arvore->right, chave);
}

// Função que lista todos os nós da arvore em ordem crescente
Node * listarCrescente(Node * raiz){
	if (raiz){
		if (raiz->left) listarCrescente(raiz->left);
		printf("%d\n %d\n %d\n", raiz->client.codigoCliente, raiz->client.quantidadeOperacoes, raiz->client.saldo);
		if (raiz->right) listarCrescente(raiz->right); 
	}
	return raiz; 
}

// Função que lista todos os nós da arvore em ordem decrescente
Node * listarDecrescente(Node * raiz){
	if (raiz){
		if (raiz->right) listarDecrescente(raiz->right); 
		printf("%d \n %d\n %d\n", raiz->client.codigoCliente, raiz->client.quantidadeOperacoes, raiz->client.saldo);
		if (raiz->left) listarDecrescente(raiz->left);
	}
	return raiz;
}

// Função que lista todos os nós da arvore em um determinado nível
void mostrarNivel(int nivel, AVLtree * arvore){
	Node * raiz = getRaiz(arvore);
	Queue * fila = defineQueue();	
	if (raiz && fila){
		fila = push(fila, raiz); 
		printf("NIVEL DO NO DA FRENTE DA FILA === %d E NIVEL QUE EU QUERO == %d\n", front(fila)->level, nivel);
		while (!isEmpty(fila) && (front(fila)->level < nivel || front(fila)->level != back(fila)->level)){
			// Se existe filho a esquerda coloca na fila 
			if (front(fila)->left){ 
				printf("TEM FILHO A ESQUERDA ADICIONA NA FILA: %d DE NIVEL == %d\n", front(fila)->left->client.codigoCliente, front(fila)->left->level);
				fila = push(fila, front(fila)->left); 
			}
			// Se existe filho a direita coloca na fila 
			if (front(fila)->right){ 
				printf("TEM FILHO A DIREITA ADICIONA NA FILA == %d DE NIVEL == %d\n", front(fila)->right->client.codigoCliente, front(fila)->right->level);
				fila = push(fila, front(fila)->right); 
			}
			printf("RETIRA DA FRENTE == %d\n", front(fila)->client.codigoCliente);
			pop(fila);		
			printf("AGORA A FRENTE É == %d de NIVEL === %d\n", front(fila)->client.codigoCliente, front(fila)->level);
		}
		while(!isEmpty(fila)){
			printf("%d\n", front(fila)->client.codigoCliente); 
			pop(fila);
		}
	}
	clearQueue(fila); 
} 

Node * isTreeEmpty(AVLtree * arvore){
	if (arvore->treeHeight == ZERO) 
		return NULL;	
	return arvore->root;
}

int alturaArvore (AVLtree * arvore){
	return arvore->treeHeight;
}

Node * isRootDefined(AVLtree * arvore){
	if (!arvore->root)
		return NULL;
	return arvore->root;
}

Node * getRaiz(AVLtree * arvore){
	return isRootDefined(arvore); 
}

int getNivel(Node * raiz){
	if (!raiz)
		return -ONE; 
	return getNivel(raiz->dad) + ONE; 
}

Node * rotacaoDireita(Node * x){
	Node * y = x->left;
	x->left = y->right;
	y->right = x;

	//atualiza altura e nivel;
	x->height = getAltura(x);
	x->level = getNivel(x) + ONE;
	y->height = getAltura(y);
	y->level = getNivel(y) + ONE;
	return y;

}

Node * rotacaoEsquerda(Node * x){
	Node * y = x->right;
	x->right = y->left;
	y->left = x;

	//atualiza altura e nivel;
	x->height = getAltura(x);
	x->level = getNivel(x) + ONE;
	y->height = getAltura(y);
	y->level = getNivel(y) + ONE;
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
		noChave->client.codigoCliente = raiz->client.codigoCliente;
		noRemovido = raiz;
		raiz = raiz->left; 
		if (raiz)
			raiz->dad = noRemovido->dad; 
		free(noRemovido);
	}
	return raiz;
}

// Função pra remover a porcaria de um nó (eu só troquei o nome e alterei uma coisinha que tava errada de resto ainda é seu código)
Node * removerNo(Node * raiz, int x){
	if(raiz == NULL){
		return NULL;
	}
	if(x < (raiz->client).codigoCliente){
		raiz->left = removerNo(raiz->left, x);
	}
	else if(x > (raiz->client).codigoCliente){
		raiz->right = removerNo(raiz->right, x);
	}
	else{
		if(raiz->left == NULL){
			raiz = raiz->right;
		}
		else if(raiz->right == NULL){
			raiz = raiz->left;
		}else{
			Node * y = getMinimo(raiz->right);
			raiz->client = y->client;
			raiz->right = removerNo(raiz->right, y->client.codigoCliente);
		}
	}
	if(raiz == NULL){
		return raiz;
	}
	raiz->height = getAltura(raiz);
	if(abs(getBalanceFactor(raiz)) == TWO){
		raiz = balanceamento(raiz);
	}
	raiz->level = getNivel(raiz) + ONE; 
	return raiz;
}


