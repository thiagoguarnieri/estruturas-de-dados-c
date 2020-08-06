#include <stdio.h>
#include <stdlib.h>

typedef struct Celula{
    int info;
    struct Celula *prox;
}Celula;

typedef struct Fila{
    Celula *inicio;
    Celula *fim;
}Fila;

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

Celula * criaCel(int x){
    Celula * nova = malloc(sizeof(Celula));
    nova->info = x;
    nova->prox = NULL;
    return nova;
}

void enfileirar(Fila *f, int x){
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

int desenfileirar(Fila *f){
    Celula *q;
    int x;

    if(vazia(f)){
        printf("Erro: lista vazia");
        return -1;
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

void imprimir(Fila *f){

    Celula * aux = f->inicio;

    while(aux != NULL)
    {
        printf("%d\t", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}

int main()
{
    Fila * fil = criaFila();
    enfileirar(fil, 1);
    enfileirar(fil, 2);
    enfileirar(fil, 3);
    enfileirar(fil, 4);

    imprimir(fil);

    printf("saiu da fila %d\n", desenfileirar(fil));
    printf("saiu da fila %d\n", desenfileirar(fil));
    printf("saiu da fila %d\n", desenfileirar(fil));
    printf("saiu da fila %d\n", desenfileirar(fil));

    return 0;
}
