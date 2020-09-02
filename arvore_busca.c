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

void incluir(No * raiz, int valor)
{
    //se menor
    if(valor < raiz->info)
    {
        //se nao tem filho esqueda
        if(raiz->esq == NULL)
            raiz->esq = criaNo(valor);
        else
            //desce na árvore
            incluir(raiz->esq, valor);
    }
    //se maior
    else
    {
        //se nao tem filho direita
        if(raiz->dir == NULL)
            raiz->dir = criaNo(valor);
        else
            //desce na árvore
            incluir(raiz->dir, valor);
    }
}

void busca(No * raiz, int valor)
{
    if(raiz != NULL)
    {
        if(valor < raiz->info)
        {
            busca(raiz->esq, valor);
        }
        else if(valor > raiz->info)
        {
            busca(raiz->dir, valor);
        }
        else
        {
            printf("elemento %d encontrado", valor);
        }

    }
    else
    {
        printf("elemento %d não encontrado", valor);
    }
}
////////////////////////////////////////////////////////
//principal
int main()
{
    No *raiz = criaNo(20);
    incluir(raiz, 13);
    incluir(raiz, 30);
    incluir(raiz, 11);
    incluir(raiz, 15);
    incluir(raiz, 25);
    incluir(raiz, 33);
    incluir(raiz, 10);
    incluir(raiz, 12);
    incluir(raiz, 14);
    incluir(raiz, 18);
    emOrdem(raiz);

    busca(raiz, 99);
    return 0;
}

