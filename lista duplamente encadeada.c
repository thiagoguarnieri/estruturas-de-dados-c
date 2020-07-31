#include <stdio.h>
#include <stdlib.h>

//estrutura da célula
typedef struct TipoCelula
{
    int info;
    struct TipoCelula *anterior;
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
    nova->anterior = NULL;
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
            //nova celula aponta para o primeiro elemento
            novaCelula->proximo = lista->primeiro;
            //primeiro elemento aponta para a nova celula
            lista->primeiro->anterior = novaCelula;
            //descritor atualizado para assumir a nova celula como primeira
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

            //paro na posição em que quero incluir
            while(pos < posicao)
            {
                aux = aux->proximo;
                pos++;
            }

            //colocando a nova celula entre duas ja existentes
            novaCelula->proximo = aux;
            novaCelula->anterior = aux->anterior;

             //ajustando os ponteiros das duas celulas para apontar para a nova
            aux->anterior->proximo = novaCelula;
            aux->anterior = novaCelula;
            lista->quantidade++;
        }
        //final
        else if(posicao == lista->quantidade)
        {
            //ultimo elemento passa a apontar para a nova celular
            lista->ultimo->proximo = novaCelula;
            novaCelula->anterior = lista->ultimo;

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
    TipoCelula *auxiliar;

    //lista com 1 elemento
    if(lista->quantidade == 1)
    {
        free(lista->primeiro);
        //atualizando descritor
        lista->primeiro = NULL;
        lista->ultimo = NULL;
        lista->quantidade--;
    }
    else if(lista->quantidade > 1)
    {
        //inicio
        if(posicao == 0)
        {
            //apontando descritor para o segundo
            lista->primeiro = lista->primeiro->proximo;

            //apagando o primeiro
            free(lista->primeiro->anterior);
            lista->primeiro->anterior = NULL;
            lista->quantidade--;

        }
        //meio
        else if(posicao > 0 && posicao < lista->quantidade)
        {
            auxiliar = lista->primeiro;
            int pos = 0;

            //paro na celula que quero apagar
            while(pos < posicao)
            {
                auxiliar = auxiliar->proximo;
                pos++;
            }

            //estamos fazendo o elemento posterior e anterior ao auxiliar
            //se conectarem diretamente com isso a célula apontada pelo
            //auxiliar sai da lista
            auxiliar->proximo->anterior = auxiliar->anterior;
            auxiliar->anterior->proximo = auxiliar->proximo;

            free(auxiliar);
            lista->quantidade--;

        }
        //fim
        else if(posicao == lista->quantidade)
        {
            //descritor passa a apontar par o último
            lista->ultimo = lista->ultimo->anterior;
            //apagando o último
            free(lista->ultimo->proximo);
            //atualizando o ponteiro para o novo último apontar para NULL
            lista->ultimo->proximo = NULL;
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

