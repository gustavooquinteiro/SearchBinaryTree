#ifndef MAIN_H
#define MAIN_H

#define END 'f'
#define INSERT 'i'
#define SEARCH 'c'
#define REMOVE 'r'
#define ORDER_LIST 'p'
#define DECRESCENT_ORDER 'd'
#define LEVEL_LIST 'n'
#define HEIGHT 'h'
#define FOUND_KEY "existe no com chave: "
#define NOT_FOUND_KEY "nao existe no com chave: "

void insereNo();
Node * buscaNo();
void removeNo();
void listarNos(char option);
void mostrarAltura();
int getChave();

#endif
