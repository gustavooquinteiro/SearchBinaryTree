#ifndef AVL_H
#define AVL_H

void definirArvore(int codigoCliente, int operacao, int valor);
No criarNo(int codigoCliente, int operacao, int valor);
void inserirNo(No & tree, No actualNode);
No balanceamento(No tree);
No atualizarCliente(No actualNode, No tree);
int maximo(int left, int right);
int getAltura(No * tree);

#endif
