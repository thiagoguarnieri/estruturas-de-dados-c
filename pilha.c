#include <stdio.h>
#include <stdlib.h>

typedef struct Celula{
    int info;
    struct Celula *inferior;
}Celula;

typedef struct Pilha{
    Celula *topo;
}Pilha;

Pilha * criaPilha(){
    Pilha * nova = malloc(sizeof(Pilha));
    nova->topo = NULL;
    return nova;
}

Celula * criaCel(int x){
    Celula * nova = malloc(sizeof(Celula));
    nova->info = x;
    nova->inferior = NULL;
    return nova;
}

int vazia(Pilha *p){
    if(p->topo == NULL)
        return 1;
    return 0;
}

void empilha(Pilha *p, int x){
    Celula *q = criaCel(x);

    if(vazia(p)){
        p->topo = q;
    }else{
        //novo elemento aponta para o topo
        q->inferior = p->topo;
        //ponteiro de topo aponta para o novo elemento
        p->topo = q;
    }
}

int desempilha(Pilha *p){
    Celula *q;
    int x;

    if(vazia(p)){
        printf("Erro: pilha vazia");
        return -1;
    }else{
        //guardando o topo para apagar depois
        q = p->topo;
        //guardando o valor do topo
        x = p->topo->info;
        //mudandoo toṕo para o próximo elemento
        p->topo = p->topo->inferior;
        //apagando a célula que éra topo
        free(q);
        return(x);
    }
}

int topoPilha(Pilha *p){

    if(!vazia(p)){
        return p->topo->info;
    }else{
        printf("Pilha vazia");
        return -1;
    }
}

void imprimir(Pilha *p){

    Celula * aux = p->topo;

    while(aux != NULL)
    {
        printf("%d\n", aux->info);
        aux = aux->inferior;
    }
    printf("\n");
}

int main()
{
    Pilha * pil = criaPilha();
    empilha(pil, 1);
    empilha(pil, 2);
    empilha(pil, 3);
    empilha(pil, 4);

    imprimir(pil);

    printf("Desempilhou %d\n", desempilha(pil));
    printf("Desempilhou %d\n", desempilha(pil));
    printf("Desempilhou %d\n", desempilha(pil));
    printf("Desempilhou %d\n", desempilha(pil));
    return 0;
}
