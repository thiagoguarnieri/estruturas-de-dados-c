#include <stdio.h>
#include <stdlib.h>
#include<time.h>

//quantidade de elementos
#define MAXTAM 100000

typedef struct
{
    int ultimo;
    int elementos[MAXTAM];

} Lista;

//inicializando os valores de controle e criando a lista
Lista inicializa()
{
    Lista nova;
    //significa que a lista está vazia
    nova.ultimo = 0;

    return nova;
}

void imprimir(Lista *list)
{
    for(int i = 0; i < list->ultimo; i++)
        printf("%d ", list->elementos[i]);

    printf("\n");
}

void inserir(Lista *list, int valor, int pos)
{
    //deve haver espaço
    if(list->ultimo < MAXTAM)
    {
        //elementos não podem ser incluído depois do último
        if(pos <= list->ultimo)
        {
            //desloca os elementos pra frente para liberar espaço na posição escolhida
            for(int i = list->ultimo; i >= pos; i--)
                list->elementos[i] = list->elementos[i-1];

            //incluindo e aumentando o indice de ultimo
            list->elementos[pos] = valor;
            list->ultimo++;
        }
    }
}

void remover(Lista *list, int pos)
{
    //indice não pode estar além do último elemento
    if(pos <= list->ultimo)
    {
        //desloca os elementos pra trás
        for(int i = pos; i < list->ultimo; i++)
            list->elementos[i] = list->elementos[i+1];

        //reduzindo o contador de último
        list->ultimo--;
    }
}

int main()
{
    Lista lst = inicializa();

    //variaveis de contagem de tempo
    double tempo_gasto = 0.0;
    clock_t inicio, fim;

    //pegando o tempo de inicio
    inicio = clock();

    for(int i = 0; i <= MAXTAM; i++)
    {
        //inserir um valor entre 0 e rand() % MAXTAM
        //inserir na posição entre 0 e rand() % (lst.ultimo + 1) (primeira e última)
        inserir(&lst, rand() % MAXTAM, rand() % (lst.ultimo + 1));
    }

    for(int i = 0; i <= MAXTAM; i++)
    {
        //renover na posição entre 0  e ultimo
        remover(&lst, rand() % (lst.ultimo + 1));
    }

    //pegando o tempo de fim
    fim = clock();

    //tempo gasto
    tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo gasto %.5f segundos\n", tempo_gasto);

    return 0;
}