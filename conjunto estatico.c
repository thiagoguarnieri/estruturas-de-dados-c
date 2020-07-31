#include <stdio.h>
#include <stdlib.h>
#define MAXELEM 10000

typedef struct
{
    int qtd;
    int elementos[MAXELEM];
} Conjunto;


void imprimirConj(Conjunto * con)
{
    for(int i = 0; i < con->qtd; i++)
    {
        printf("%d ", con->elementos[i]);
    }
    printf("\n");
}

Conjunto novoConjunto()
{
    Conjunto novo;
    novo.qtd = 0;
    return novo;

}

void incluirElemento(Conjunto * con, int valor)
{
    int existente = 0;

    if(con->qtd == MAXELEM)
    {
        printf("Número máximo de elementos atingido\n");
    }
    else
    {
        for(int i = 0; i < con->qtd; i++)
        {
            if(con->elementos[i] == valor)
            {
                printf("Elemento já existe no conjunto\n");
                existente = 1;
            }
        }

        if(!existente)
        {
            con->elementos[con->qtd] = valor;
            con->qtd++;
        }
    }
}

Conjunto uniao(Conjunto * con1, Conjunto * con2)
{
    Conjunto uniao = novoConjunto();

    if(con1->qtd == 0 && con2->qtd == 0)
    {
        printf("os conjuntos são vazios");
    }
    else
    {
        for(int i = 0; i < con1->qtd; i++)
            incluirElemento(&uniao, con1->elementos[i]);

        for(int i = 0; i < con2->qtd; i++)
            incluirElemento(&uniao, con2->elementos[i]);
    }

    return uniao;
}

Conjunto intersecao(Conjunto * con1, Conjunto * con2)
{
    Conjunto intersecao = novoConjunto();

    if(con1->qtd == 0 || con2->qtd == 0)
    {
        printf("um dos conjuntos é vazio");
    }
    else
    {
        for(int i = 0; i < con1->qtd; i++)
        {
            for(int j = 0; j < con2->qtd; j++)
            {
                //se o elemento existir nos dois conjuntos, insira
                if(con1->elementos[i] == con2->elementos[j])
                {
                    incluirElemento(&intersecao, con1->elementos[i]);
                }
            }
        }
    }

    return intersecao;
}

int main()
{
    Conjunto c1 = novoConjunto();
    Conjunto c2 = novoConjunto();
    Conjunto un = novoConjunto();
    Conjunto in = novoConjunto();

    for(int i = 0; i < 10; i++)
    {
        incluirElemento(&c1, i);
        incluirElemento(&c2, i + 5);
    }

    un = uniao(&c1, &c2);
    in = intersecao(&c1, &c2);

    printf("\nconjunto 1: ");
    imprimirConj(&c1);
    printf("\nconjunto 2: ");
    imprimirConj(&c2);
    printf("\nUnião: ");
    imprimirConj(&un);
    printf("\nInterseção: ");
    imprimirConj(&in);

    return 0;
}
