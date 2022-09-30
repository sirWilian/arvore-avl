#include <stdio.h>
#include <stdlib.h>

#ifndef __LIBAVL__
#define __LIBAVL__

typedef struct nodo{
    int chave;
    struct nodo *esq, *pai, *dir;
    int altura;
    int profundidade;
} nodo;

nodo *criaNo(int chave);

nodo *rotEsquerda(nodo *raiz);

nodo *rotDireita(nodo *raiz);

int altura (nodo *raiz) ;

int profundidade(nodo *raiz);

void ajustaNoPai(nodo *no, nodo *novo);

int diferencaNos(nodo *esq, nodo *dir);

nodo *ajustaArvore(nodo *raiz);

nodo* incluiNo(nodo *no, int chave);

nodo *min(nodo *no);

nodo *sucessor(nodo *no);

nodo* exclui(nodo *no, nodo *raiz);

nodo *busca(nodo *no, int chave);

void emOrdem(nodo *no);

#endif