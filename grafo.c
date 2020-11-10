#include <stdio.h>
#include <stdlib.h>

//lista de adjacentes
typedef struct vizinho
{
    int id_vizinho;
    struct vizinho *prox;
} TVizinho;

//lista de vértices
typedef struct grafo
{
    int id_vertice;
    TVizinho *prim_vizinho;
    struct grafo *prox;
} TGrafo;


TGrafo *inicializa()
{
    return NULL;
}

//impressao do grafo
void imprime(TGrafo *g)
{
    //laço para percorrer os vértices
    while(g != NULL)
    {
        printf("Vértice %d\n", g->id_vertice);
        printf("Vizinhos: ");
        TVizinho *v = g->prim_vizinho;

        //laço para percorrer os adjacentes
        while(v != NULL)
        {
            printf("%d ", v->id_vizinho);
            v = v->prox;
        }
        printf("\n\n");
        g = g->prox;
    }
}

//liberação de memoria
void libera_vizinhos(TVizinho *v)
{
    //remoção no início
    while(v != NULL)
    {
        TVizinho *temp = v;
        v = v->prox;
        free(temp);
    }
}

//liberação de memoria
void libera(TGrafo *g)
{
    while(g != NULL)
    {
        libera_vizinhos(g->prim_vizinho);

        //remoção no início
        TGrafo *temp = g;
        g = g->prox;
        free(temp);
    }
}

//basta buscar na lista de vertices
TGrafo* busca_vertice(TGrafo* g, int x)
{
    while((g != NULL) && (g->id_vertice != x))
    {
        g = g->prox;
    }
    return g;
}


TVizinho* busca_aresta(TGrafo *g, int v1, int v2)
{
    TGrafo *pv1 = busca_vertice(g,v1);
    TGrafo *pv2 = busca_vertice(g,v2);
    TVizinho *resp = NULL;

    //checa se ambos os vértices existem
    if((pv1 != NULL) && (pv2 != NULL))
    {
        //percorre a lista de vizinhos de v1 procurando por v2
        resp = pv1->prim_vizinho;
        while ((resp != NULL) && (resp->id_vizinho != v2))
        {
            resp = resp->prox;
        }
    }
    return resp;
}

TGrafo *insere_vertice(TGrafo *g, int x)
{
    TGrafo *p = busca_vertice(g, x);
    if(p == NULL)  //se o vértice ainda não existe
    {
        p = (TGrafo*) malloc(sizeof(TGrafo));
        p->id_vertice = x;
        p->prox = g; //inserindo no inicio da lista
        p->prim_vizinho = NULL; //sem vizinhos
        g = p; //inicio da lista passa a ser o novo vertice
    }
    return g;
}

//inserindo uma aresta em grafo orientado
void insere_um_sentido(TGrafo *g, int v1, int v2)
{
    TGrafo *p = busca_vertice(g, v1);
    TVizinho *nova = (TVizinho *) malloc(sizeof(TVizinho));
    nova->id_vizinho = v2;
    //inserção inicio
    nova->prox = p->prim_vizinho;
    p->prim_vizinho = nova;
}

//Não orientado
void insere_aresta(TGrafo *g, int v1, int v2)
{
    if(busca_aresta(g, v1, v2) == NULL)
    {
        insere_um_sentido(g, v1, v2);
        insere_um_sentido(g, v2, v1);
    }
}

//orientado
void insere_aresta_digrafo(TGrafo *g, int v1, int v2)
{
    if(busca_aresta(g, v1, v2) == NULL)
        insere_um_sentido(g, v1, v2);
}

//remoção
void retira_um_sentido(TGrafo *g, int v1, int v2)
{
    TGrafo *p = busca_vertice(g, v1);
    if(p != NULL)   //se o vértice v1 existe
    {
        TVizinho *ant = NULL;
        TVizinho *atual = p->prim_vizinho;
        while ((atual) && (atual->id_vizinho != v2))   //procura a aresta
        {
            ant = atual;
            atual = atual->prox;
        }

        if (ant == NULL) //v2 era o primeiro nó da lista
            p->prim_vizinho = atual->prox; //pula para segundo
        else
            ant->prox = atual->prox; //lista passa a pular o atual
        free(atual);
    }
}


void retira_aresta(TGrafo *g,int v1, int v2)
{
    TVizinho* v = busca_aresta(g,v1,v2);
    if(v != NULL)
    {
        retira_um_sentido(g, v1, v2);
        retira_um_sentido(g, v2, v1);
    }
}

void retira_aresta_digrafo(TGrafo *g,int v1, int v2)
{
    TVizinho* v = busca_aresta(g,v1,v2);
    if(v != NULL)
    {
        retira_um_sentido(g, v1, v2);
    }
}


TGrafo *retira_vertice(TGrafo *g, int v)
{
    TGrafo *p = g;
    TGrafo *ant = NULL;

    while((p != NULL) && (p->id_vertice != v)) //encontra vertice a ser removido
    {
        ant = p;
        p = p->prox;
    }

    if(p != NULL)  //se o vértice existe
    {
        while (p->prim_vizinho != NULL)//retira as arestas
            retira_aresta(g, v, p->prim_vizinho->id_vizinho);

        if (ant == NULL) //caso o vértice removido seja o primeiro da lista
            g = g->prox;
        else //caso não seja o primeiro
            ant->prox = p->prox;
        free(p); //libera o vertice
    }
    return g;
}

TGrafo *retira_vertice_digrafo(TGrafo *g, int v)
{
    TGrafo *p = g;
    TGrafo *ant = NULL;

    while((p != NULL) && (p->id_vertice != v)) //encontra vertice a ser removido
    {
        ant = p;
        //aproveita para retirar v da lista de outros vértices
        retira_aresta_digrafo(g, p->prim_vizinho->id_vizinho, v);
        p = p->prox;
    }

    if(p != NULL)  //se o vértice existe
    {
        while (p->prim_vizinho != NULL)//retira as arestas
            retira_aresta_digrafo(g, v, p->prim_vizinho->id_vizinho);

        if (ant == NULL) //caso o vértice removido seja o primeiro da lista
            g = g->prox;
        else //caso não seja o primeiro
            ant->prox = p->prox;
        ant = p;
        free(p); //libera o vertice
        while(ant != NULL)  //remove vértice dos demais nos
        {
            retira_aresta_digrafo(g, ant->prim_vizinho->id_vizinho, v);
            ant = ant->prox;
        }
    }
    return g;
}


int main()
{

    TGrafo *grafo = inicializa();

    grafo = insere_vertice(grafo, 1);
    grafo = insere_vertice(grafo, 2);
    grafo = insere_vertice(grafo, 3);
    grafo = insere_vertice(grafo, 4);

    insere_aresta(grafo, 1, 2);
    insere_aresta(grafo, 1, 3);
    insere_aresta(grafo, 2, 3);
    insere_aresta(grafo, 2, 4);

    imprime(grafo);



    return 0;
}
