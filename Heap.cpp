#include<stdio.h>
#include<stdlib.h>

int pai(int i)
{
    return ((i-1)/2);
}
int esq(int i)
{
    return (i*2)+1;
}
int dir(int i)
{
    return (i*2+2);
}

void subir(int *heap, int i, int n)   //n = tamanho do vetor
{
    int j = pai(i);
    if (j >= 0)   //Se existe pai (no não é raiz)
    {
        if (heap[i] > heap[j])   //Se há violação de prop.
        {
            //faz a subida
            int temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
            subir(heap, j, n); //subida recursiva
        }
    }
}

void descer(int *heap, int i, int n)   //n = tamanho do vetor
{
    //descobre quem é o maior filho de i
    int e = esq(i);
    int d = dir(i);
    int maior = i;
    if (e < n && heap[e] > heap[i])
    {
        // Se existe filho a esquerda e ele é maior que o pai
        maior = e;
    }
    if (d < n && heap[d] > heap[maior])
    {
        // Se existe filho a direita e ele é o maior
        maior=d;
    }

    if (maior != i)  // Se houve violação das propriedades Heap
    {
        //faz a descida trocando com o maior filho
        int temp=heap[i];
        heap[i] = heap[maior];
        heap[maior]=temp;
        descer(heap, maior, n); // Descida recursiva
    }
}//fim da função descer

int insere(int *heap, int novo, int n)
{
    //aumenta o tamanho do vetor
    heap = (int *) realloc(heap, sizeof(int) * (n + 1));
    n = n + 1;
    heap[n-1] = novo;
    subir(heap, n-1, n);
    //retorna o novo valor de n
    return n;
}

int exclui(int *heap, int n)
{
    heap[0] = heap[n-1];
    n = n - 1;
    //diminui o tamanho do vetor
    heap = (int *) realloc(heap, sizeof(int) * (n));
    descer(heap, 0, n);
    //retorna o novo valor de n
    return n;
}

void constroi_heap_maximo(int *heap, int n)
{
    int i;
    int j=((n-1)/2); // último nó não folha
    for(i=j; i>=0; i--)
        descer(heap, i, n);
}

void heap_sort(int *heap, int n)
{
    int i;
    int j = n;
    constroi_heap_maximo(heap, n);
    for(i = n - 1; i >= 0; i--)
    {
        //troca raiz com o ultimo elemento (posicao j)
        int temp = heap[i];
        heap[i] = heap[0];
        heap[0] = temp;
        //diminui o tamanho do vetor a ser considerado no heap
        j--;
        //desce com a raiz nesse novo heap de tamanho j-1
        descer(heap, 0, j);
    }
}

void imprime(int* heap, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d-", heap[i]);
}

int main(void)
{
    int *heap;
    int n = 8;
    //printf("Digite o tamanho do vetor de elementos: ");
    //scanf("%d",&n);
    if(n <= 0)
    {
        return 0;
    }
    heap = (int *) malloc(sizeof(int) * n);
    heap[0] = 28;
    heap[1] = 33;
    heap[2] = 39;
    heap[3] = 60;
    heap[4] = 66;
    heap[5] = 70;
    heap[6] = 78;
    heap[7] = 95;
    printf("Lista:\n");
    imprime(heap,n);

    constroi_heap_maximo(heap, n);
    printf("\n\nTransformada em Heap:\n");
    imprime(heap,n);

    n = insere(heap,55,n);
    printf("\n\nInsere 55:\n");
    imprime(heap,n);

    n = insere(heap,80,n);
    printf("\n\nInsere 80:\n");
    imprime(heap,n);

    n = exclui(heap,n);
    printf("\n\nRemove maior:\n");
    imprime(heap,n);

    heap_sort(heap,n);
    printf("\n\nOrdena:\n");
    imprime(heap,n);


}

