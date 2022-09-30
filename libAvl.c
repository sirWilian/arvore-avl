#include "libAvl.h"

nodo *criaNo(int chave){
	nodo *no;
    
    if(!(no = ((nodo*) malloc(sizeof(nodo))))){
        fprintf(stderr, "erro de alocação no no");
        exit(1);
    }
	no->chave = chave;
	no->esq = NULL;
	no->dir = NULL;
	no->pai = NULL;
	no->altura = 0;
    no->profundidade = 0;

	return no;
}

/* rotaciona uma subarvore para a esquerda  */
nodo *rotEsquerda(nodo *raiz){
	nodo *filhoDir;
    
    filhoDir = raiz->dir;
	raiz->dir = filhoDir->esq;
	filhoDir->pai = raiz->pai;
    raiz->pai = filhoDir;

	if(filhoDir->esq != NULL) 
        filhoDir->esq->pai = raiz;

	filhoDir->esq = raiz;

	return filhoDir;
}

/* rotaciona uma subarvore para a direita  */
nodo *rotDireita(nodo *raiz){
    nodo *filhoEsq;
    
    filhoEsq = raiz->esq;
	raiz->esq = filhoEsq->dir;
	filhoEsq->pai = raiz->pai;
    raiz->pai = filhoEsq;

	if(filhoEsq->dir != NULL) 
        filhoEsq->dir->pai = raiz;

    filhoEsq->dir = raiz;

	return filhoEsq;
}

/* calcula a altura de uma subarvore dado o no raiz */
int altura(nodo *raiz) {
    int alturaEsquerda, alturaDireita;
    
    if (raiz == NULL) 
        return -1;
    alturaEsquerda = altura (raiz->esq);
    alturaDireita = altura (raiz->dir);
    if (alturaEsquerda > alturaDireita)
        return alturaEsquerda + 1;
    return alturaDireita + 1;
}

/* calcula a profundidade em que o no esta */
int profundidade(nodo *raiz){
    
    if (raiz->pai == NULL) 
        return 0;
    return profundidade(raiz->pai) + 1;
}

/* reorganiza os ponteiros apos a exclusao de um nodo */
void ajustaNoPai(nodo *no, nodo *novo){
    
    if (no->pai != NULL) {
        if (no->pai->esq == no){
            no->pai->esq = novo;
        }
        else{
            no->pai->dir = novo;
        }
    }
    if (novo != NULL)
        novo->pai = no->pai;
}

/* verifica se a diferenca eh menor que -1 ou maior que 1 */
int diferencaNos(nodo *esq, nodo *dir){
    
    if((altura(esq) - altura(dir) < -1) || (altura(esq) - altura(dir) > 1)) 
        return 1;
    return 0;
}

nodo *ajustaArvore(nodo *raiz){
    
    /* verifica se o no esta desbalanceado */
    if(!diferencaNos(raiz->esq, raiz->dir)) 
        return raiz;

    nodo *novoNo;

    /* verifica se esta desbalanceado para direita */
    if(altura(raiz->esq) - altura(raiz->dir) > 1){
        if(raiz->esq != NULL && altura(raiz->esq->esq) - altura(raiz->esq->dir) < 0){
            raiz->esq = rotEsquerda(raiz->esq);
            raiz->esq->altura = altura(raiz->esq);
        }
        novoNo = rotDireita(raiz);
    }
    else {
        if(altura(raiz->dir->esq) - altura(raiz->dir->dir) > 0){
            raiz->dir = rotDireita(raiz->dir);
            raiz->dir->altura = altura(raiz->dir);
        }
        novoNo = rotEsquerda(raiz);
    }
    /* se a raiz rotacionada eh a raiz da arvore ajusta os ponteiros */
    if(novoNo->pai) {
        if(novoNo->pai->esq == raiz) 
            novoNo->pai->esq = novoNo;
        else 
            novoNo->pai->dir = novoNo;
    }
    /* ajusta as alturas */
    novoNo->altura = altura(novoNo);
    if(novoNo->dir)
        novoNo->dir->altura = altura(novoNo->dir);
    if(novoNo->esq)
    novoNo->esq->altura = altura(novoNo->esq);

    return novoNo;
}

/* realiza a inclusao de um no na folha */
nodo* incluiNo(nodo *no, int chave){
    
    if(no == NULL){
        no = criaNo(chave);
        return no;
    }
    if(chave < no->chave){
        no->esq = incluiNo(no->esq, chave);
        no->esq->pai = no;
    }
    else {
        no->dir = incluiNo(no->dir, chave);
        no->dir->pai = no;
    }
    no->altura = altura(no);
    if(diferencaNos(no->esq, no->dir)) 
        no = ajustaArvore(no);

    return no;
}

/* imprime os nodos em ordem */
void emOrdem(nodo *no){
    
    if (no !=NULL){
        emOrdem(no->esq);
        no->profundidade = profundidade(no);
        printf("%d,%d\n", no->chave, no->profundidade);
        emOrdem(no->dir);
    }
}

/* encontra o valor minimo dado o no raiz de uma subarvore */
nodo *min(nodo *no){

	if(no->esq == NULL) 
        return no;
	return min(no->esq);
}

/* encontra o sucessor do no */
nodo *sucessor(nodo *no){
    
	nodo *noSucessor = NULL;
	if(no->dir != NULL) 
        return min(no->dir);
	return noSucessor;
}

/* exclui o nodo *no de uma arvore com raiz *raiz  */
nodo* exclui(nodo *no, nodo *raiz) {
    nodo *noSucessor, *novaRaiz = raiz;
    nodo *aux;

    if(no == NULL) 
        return NULL;
    /* caso 1 de exclusao */
    if(no->esq == NULL && no->dir == NULL) {
        /* arvore com um nodo */
        if (no == raiz) {
            free(no);
            return NULL;
        }    
        ajustaNoPai(no, NULL);
        free(no);
    } 
    else {
        /* caso 2 de exclusao */
        if(no->esq == NULL){
            ajustaNoPai(no, no->dir);
            if(no->pai == NULL) 
                novaRaiz = no->dir;
            free(no);
        } 
        else{
            if(no->dir == NULL){
                ajustaNoPai(no, no->esq);
                if (no->pai == NULL) 
                    novaRaiz = no->esq;
                free(no);
            }
            /* nó com dois filhos é substituido pelo sucessor  */
            noSucessor = sucessor(no);
            ajustaNoPai(noSucessor, noSucessor->dir);
            noSucessor->esq = no->esq;
            noSucessor->dir = no->dir;
            ajustaNoPai(no, noSucessor);
            if(no == raiz) 
                novaRaiz = noSucessor; 
            free(no);
        }
    }
    aux = novaRaiz->pai;
    while(aux != NULL){
        no = ajustaArvore(aux);
        if(no->pai == NULL){
            novaRaiz = no;
            aux = NULL;
        }
        else aux = no->pai;
    }
    if(!aux && diferencaNos(novaRaiz->esq, novaRaiz->dir)) 
        novaRaiz = ajustaArvore(novaRaiz);
    return novaRaiz;
}

/* busca a chave dado a raiz da arvore */
nodo *busca(nodo *no, int chave){

    if (no == NULL) 
        return NULL;
    if (no->chave == chave) 
        return no;
    if (chave < no->chave)
        return busca (no->esq, chave);
    return busca (no->dir, chave);
}
