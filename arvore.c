#include <stdio.h>
#include <stdlib.h>
////////////////////////////////////////////////////////
//estrutura do nó da árvore
typedef struct No
{
    int info;
    struct No *esq;
    struct No *dir;
} No;
////////////////////////////////////////////////////////
//estrutura da fila para busca em largura
typedef struct Celula{
    //ponteiro para nó da árvore
    struct No * info;
    struct Celula *prox;
}Celula;

typedef struct Fila{
    Celula *inicio;
    Celula *fim;
}Fila;
////////////////////////////////////////////////////////
//operações da fila
Fila * criaFila(){
    Fila * nova = malloc(sizeof(Fila));
    nova->inicio = NULL;
    nova->fim = NULL;
    return nova;
}

int vazia(Fila *f){
    if(f->inicio == NULL)
        return 1;
    return 0;
}

Celula * criaCel(No * x){
    Celula * nova = malloc(sizeof(Celula));
    nova->info = x;
    nova->prox = NULL;
    return nova;
}

void enfileirar(Fila *f, No * x){
    Celula *q = criaCel(x);

    if(vazia(f)){
        f->inicio = q;
        f->fim = q;
    }else{
        //encadeando novo elemento no fim
        f->fim->prox = q;
        //ponteiro de último aponta para o novo elemento
        f->fim = q;
    }
}

No * desenfileirar(Fila *f){
    Celula *q;
    No * x;

    if(vazia(f)){
        printf("Erro: lista vazia");
        return NULL;
    }else{
        //guardando referência para o segundo elemento
        q = f->inicio->prox;
        //guardando valor do primeiro elemento
        x = f->inicio->info;
        //retirando primeiro elemento
        free(f->inicio);
        //agora o segundo da fila é o primeiro
        f->inicio = q;
        //se era o último da fila
        if(f->inicio == NULL)
            f->fim = NULL;
        //retorna o antigo primeiro elemento
        return(x);
    }
}
////////////////////////////////////////////////////////
//operações da árvore
No * criaNo(int valor)
{
    No * novo = malloc(sizeof(No));
    novo->esq = NULL;
    novo->dir = NULL;
    novo->info = valor;
    return novo;
}

void preOrdem(No * raiz)
{
    if(raiz != NULL)
    {
        printf("%d\n", raiz->info);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

void emOrdem(No * raiz)
{
    if(raiz != NULL)
    {
        emOrdem(raiz->esq);
        printf("%d\n", raiz->info);
        emOrdem(raiz->dir);
    }
}

void posOrdem(No * raiz)
{
    if(raiz != NULL)
    {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d\n", raiz->info);
    }
}

void buscaLargura(No * raiz)
{
    Fila *f = criaFila();
    enfileirar(f,raiz);

    while(!vazia(f)){
        No *temp = f->inicio->info;
        desenfileirar(f);
        if(temp->esq != NULL) enfileirar(f, temp->esq);
        if(temp->dir != NULL) enfileirar(f, temp->dir);

        printf("%d,", temp->info);
    }
}
////////////////////////////////////////////////////////
//exemplos de aplicação
int somaValor(No * raiz)
{
    if(raiz != NULL)
        //pré ordem: vista + acessoSae + acessoSad
        return (raiz->info + somaValor(raiz->esq) + somaValor(raiz->dir));
}
////////////////////////////////////////////////////////
//principal
int main()
{
    No *a = criaNo(8);
    No *b = criaNo(5);
    No *c = criaNo(12);
    No *d = criaNo(4);
    No *e = criaNo(7);

    a->esq = b;
    a->dir = c;
    b->esq = d;
    b->dir = e;


    preOrdem(a);
    printf("\n");
    emOrdem(a);
    printf("\n");
    posOrdem(a);

    printf("\nnumero de elementos: %d\n", somaValor(a));

    buscaLargura(a);
    return 0;
}

