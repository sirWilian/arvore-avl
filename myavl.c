#include "libAvl.h"

int main(){
    char operacao;
    int chave;
    nodo *raiz;
    
    raiz = NULL;
    operacao = getchar();
    while(operacao != EOF){
        scanf("%d", &chave);
        if(operacao == 'i') 
            raiz = incluiNo(raiz, chave);
        if(operacao == 'r')
            if(busca(raiz, chave)) 
                raiz = exclui(busca(raiz, chave), raiz);
        operacao = getchar();
    }
    emOrdem(raiz);
    free(raiz);

    return 0;
}
