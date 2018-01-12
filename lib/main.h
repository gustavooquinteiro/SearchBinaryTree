#ifndef MAIN_H
#define MAIN_H

#define END 'f'
#define INSERT 'i'
#define SEARCH 'c'
#define REMOVE 'r'
#define LEVEL_LIST 'n'
#define HEIGHT 'h'

#define ORDER_LIST 'p'
#define DECRESCENT_ORDER 'd'

#define FOUND_KEY "existe no com chave:"
#define NOT_FOUND_KEY "nao existe no com chave:"

void insereNo(AVLtree * tree);
void buscaNo(AVLtree * tree);
void removeNo(AVLtree * tree);
void listarNos(AVLtree * tree);
void listarNivel(AVLtree * tree);
void mostrarAltura(AVLtree * tree);


#endif