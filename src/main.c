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
	long long int codigoCliente, valor, operacao;
	scanf("%lld %lld %lld", &codigoCliente, &operacao, &valor);
	Client * cliente = criarCliente(codigoCliente, operacao, valor);
	arvoreAVL = definirRaiz(arvoreAVL, cliente);
}

void buscaNo(AVLtree * arvoreAVL){
	long long int chave;
	scanf ("%lld", &chave);
	printf("%s %lld\n", busca(getRaiz(arvoreAVL), chave)? FOUND_KEY_MESSAGE: NOT_FOUND_KEY_MESSAGE, chave);
}

void removeNo(AVLtree * arvoreAVL){
	long long int chave;
	scanf("%lld", &chave);
	arvoreAVL = atualizarRaiz(arvoreAVL, chave);
}

void listarNos(AVLtree * arvoreAVL){
	char ordem;
	scanf(" %c", &ordem);
	(ordem == DECRESCENT_ORDER)? listarDecrescente(getRaiz(arvoreAVL)):listarCrescente(getRaiz(arvoreAVL));
}

void listarDecrescente(Node * raiz){
	if (raiz){
		listarDecrescente(getRightSon(raiz));
		printf("%lld %lld %lld\n", getClientCode(getClient(raiz)), getClientOperationsQuantity(getClient(raiz)), getSaldoCliente(getClient(raiz)));
		listarDecrescente(getLeftSon(raiz));
	}
}

void listarCrescente(Node * raiz){
	if (raiz){
		listarCrescente(getLeftSon(raiz));
		printf("%lld %lld %lld\n", getClientCode(getClient(raiz)), getClientOperationsQuantity(getClient(raiz)), getSaldoCliente(getClient(raiz)));
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

void mostrarAltura(AVLtree * arvoreAVL){
	printf("%d\n", getAlturaArvore(arvoreAVL));
}

void exibeRelatorio(AVLtree * arvoreAVL){
	printf("-+- Inicio relatorio -+-\n");
	printf ("%d\n", getQuantidadeNos(arvoreAVL));
	while(getRaiz(arvoreAVL)){
		long long int codigo = getClientCode(getClient(getRaiz(arvoreAVL)));
		long long int operacoes = getClientOperationsQuantity(getClient(getRaiz(arvoreAVL)));
		long long int saldo = getSaldoCliente(getClient(getRaiz(arvoreAVL)));
		printf("%lld %lld %lld\n", codigo, operacoes, saldo);
		arvoreAVL = atualizarRaiz(arvoreAVL, codigo);
	}
    cleanTree(arvoreAVL);
	printf("-+- Fim relatorio -+-\n");
}
