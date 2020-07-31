#include <stdio.h>
#include <stdlib.h>

//estrutura da célula
typedef struct TipoCelula
{
    int info;
    struct TipoCelula *proximo;

} TipoCelula;

//Struct para guardar o início da lista
typedef struct
{
    int quantidade;
    TipoCelula *primeiro;
    TipoCelula *ultimo;
} TipoLista;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//cria uma lista vazia
TipoLista* criaLista()
{
    TipoLista *nova = malloc(sizeof(TipoLista));
    nova->primeiro = NULL;
    nova->ultimo = NULL;
    nova->quantidade = 0;
    return nova;
}

TipoCelula* criaCelula(int valor)
{
    TipoCelula *nova = malloc(sizeof(TipoCelula));
    nova->info = valor;
    nova->proximo = NULL;
    return nova;
}

void inserir(TipoLista *lista, int valor, int posicao)
{
    TipoCelula *novaCelula = criaCelula(valor);

    //lista vazia
    if(lista->quantidade == 0)
    {
        lista->primeiro = novaCelula;
        lista->ultimo = novaCelula;
        lista->quantidade++;
    }
    else
    {
        //inicio
        if(posicao == 0)
        {
            novaCelula->proximo = lista->primeiro;
            lista->primeiro = novaCelula;
            lista->quantidade++;

        }
        //meio
        else if(posicao > 0 && posicao < lista->quantidade)
        {
            //eu não sei qual o endereço bloco na posição desejada
            //eu tenho que varrer a lista para achar
            TipoCelula *aux = lista->primeiro;
            int pos = 0;
            //paro na celula imediatamente anterior
            while(pos < posicao - 1)
            {
                aux = aux->proximo;
                pos++;
            }

            //ajustanto ponteiros
            novaCelula->proximo = aux->proximo;
            aux->proximo = novaCelula;
            lista->quantidade++;
        }
        //final
        else if(posicao == lista->quantidade)
        {
            //ultimo elemento passa a apontar para a nova celular
            lista->ultimo->proximo = novaCelula;
            //referencia ao ultimo elemento passa a ser a nova celula
            lista->ultimo = novaCelula;
            lista->quantidade++;
        }
        else
        {
            printf("Posição fora dos limites!\n");
        }
    }
}

void remover(TipoLista *lista, int posicao)
{
    TipoCelula *auxiliar, *auxiliar2;

    //lista vazia
    if(lista->quantidade == 1)
    {
        auxiliar = lista->primeiro;
        lista->primeiro = NULL;
        lista->ultimo = NULL;
        free(auxiliar);
        lista->quantidade--;
    }
    else if(lista->quantidade > 1)
    {
        //inicio
        if(posicao == 0)
        {
            auxiliar = lista->primeiro;
            lista->primeiro = lista->primeiro->proximo;
            free(auxiliar);
            lista->quantidade--;

        }
        //meio
        else if(posicao > 0 && posicao < lista->quantidade)
        {
            auxiliar = lista->primeiro;
            int pos = 0;

            //paro na celula imediatamente anterior à desejada
            while(pos < posicao - 1)
            {
                auxiliar = auxiliar->proximo;
                pos++;
            }

            //o elemento que quero apagar
            auxiliar2 = auxiliar->proximo;
            //o elemento seguinte ao que quero apagar
            auxiliar->proximo = auxiliar->proximo->proximo;

            free(auxiliar2);
            lista->quantidade--;

        }
        //fim
        else if(posicao == lista->quantidade)
        {

            auxiliar = lista->primeiro;
            int pos = 0;

            //paro na penulima celula
            while(pos < posicao - 2)
            {
                auxiliar = auxiliar->proximo;
                pos++;
            }

            //auxiliar->proximo = ultimo
            free(auxiliar->proximo);
            auxiliar->proximo = NULL;
            lista->ultimo = auxiliar;
            lista->quantidade--;

        }
        else
        {

            printf("Indice fora dos limites!\n");
        }
    }
    else
    {
        printf("Lista vazia!\n");
    }
}

//imprime
void imprime(TipoLista *lista)
{
    TipoCelula *auxiliar = lista->primeiro;

    if(lista->primeiro == NULL)
    {
        printf("Lista vazia!\n");
    }
    else
    {
        while(auxiliar != NULL)
        {
            printf(" %d ", auxiliar->info);
            auxiliar = auxiliar->proximo;
        }
        printf("\n");
    }
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int main()
{

    //criando o cabeçalho e células
    TipoLista *novaLista = criaLista();

    //encadeando colocando sempre no final
    inserir(novaLista,1,0);
    inserir(novaLista,2,1);
    inserir(novaLista,3,2);
    inserir(novaLista,4,3);
    inserir(novaLista,5,4);

    imprime(novaLista);
    printf("tamanho da lista: %d\n", novaLista->quantidade);

    remover(novaLista, 3);
    remover(novaLista, 1);
    imprime(novaLista);
    printf("tamanho da lista: %d\n", novaLista->quantidade);

    return 0;
}

