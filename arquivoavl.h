#ifndef AVL_H
#define AVL_H

void definirArvore(int codigoCliente, int operacao, int valor);
No criarNo(int codigoCliente, int operacao, int valor);
void inserirNo(No & arvore, No noAtual);
int balanceamento(No * arvore);
int maximo(int esquerda, int direita);
int getAltura(No * arvore);


#endif
