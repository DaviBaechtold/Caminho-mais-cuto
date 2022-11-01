/*
Davi Baechtold Campos
PEDA - trabalho 10
Dijkstra Shortest Path


Sua  tarefa  será  construir  um  grafo,  com  20  vértices  cujos  valores  serão  aleatoriamente  selecinados em um conjunto de inteiros contendo números inteiros entre 1 e 100. Cada vértice terá um  número aleatório de arestas menor ou igual a três. Cada aresta terá um peso definido por um número 
inteiro positivo aleatoriament definido entre 1 e 20. Você deverá criar este grafo, armazenando estes  vértices  e  arestas  em  uma  tabela  de  adjacências  ou  em  uma  lista  de  adjacências,  nos  dois  caso  armazenando o peso definido para cada uma delas. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

int adjMatriz[30][30];

struct canto {
  int vertice;
  struct canto* prox;
};

struct grafos {
  int numVertices;
  struct canto** listaAdjacencia;
};

// criar a matriz adjacente
struct canto* criaAdjacencia(int v) {
  struct canto* novaAdj = malloc(sizeof(struct canto));
  novaAdj->vertice = v;
  novaAdj->prox = NULL;
  return novaAdj;
}
// criar matriz
void init_Matriz(){
  int i, j;
  for (i = 0; i < 30; i++)
    for (j = 0; j < 30; j++)
      adjMatriz[i][j] = 0;
}

int Distancia_menor(int dist[], bool sptSet[])
{

    int min = INT_MAX, minIndex;
 
    for (int v = 0; v < 30; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], minIndex = v;
 
    return minIndex;
}

// Cria os grafos
struct grafos* criar_grafos(int vertices) {
  init_Matriz();
  struct grafos* grafos = malloc(sizeof(struct grafos));
  grafos->numVertices = vertices;

  grafos->listaAdjacencia = malloc(vertices * sizeof(struct canto*));

  int i;
  for (i = 0; i < vertices; i++)
    grafos->listaAdjacencia[i] = NULL;

  return grafos;
}
void MatrizAdicionada(int i, int j){
    adjMatriz[i][j] = 1;
    adjMatriz[j][i] = 1;
}

void addAdjacencia(struct grafos* grafos, int s, int d) {
  if(d <= 99) MatrizAdicionada(s, d);
  struct canto* novaAdj = criaAdjacencia(d);
  novaAdj->prox = grafos->listaAdjacencia[s];
  grafos->listaAdjacencia[s] = novaAdj;

  
  novaAdj = criaAdjacencia(s);
  novaAdj->prox = grafos->listaAdjacencia[d];
  grafos->listaAdjacencia[d] = novaAdj;
}


// Coloca na lista adjacente os grafos

void listaAdjacencia(struct grafos* grafos) {
  int v;
  for (v = 0; v < grafos->numVertices; v++) {
    struct canto* temp = grafos->listaAdjacencia[v];
    int count = 0;
    printf("\n Vértice %d: ", v);
    while (temp) {
      if(count < 3){
        if(temp->vertice > 30) temp->vertice = 30;
        printf("%d -> ", temp->vertice);
        //printf("%d\n", temp);
      }
      count++;
      temp = temp->prox;
    }
    printf("\n");
  }
}

//Faz o printa da matriz a
void printAdjMatriz() {
  int i, j;
  
  for (i = 0; i < 30; i++) {
    printf("%d: ", i);
    for (j = 0; j < 30; j++) {
      printf("%d ", adjMatriz[i][j]);
    }
    printf("\n");
  }
}

 
// Faz o print do conjunto Dijkstra
void printDijkstra(int dist[])
{
    printf("Vértice: \t\t Distancia do vertice:\n");
    for (int i = 0; i < 30; i++) printf("%d \t\t\t\t %d\n", i, dist[i]);
}

void dijkstra(int grafos[30][30], int origem)
{
    int dist[30];
 
    bool sptSet[30]; 

    for (int i = 0; i < 30; i++) dist[i] = INT_MAX, sptSet[i] = false;

    dist[origem] = 0;
 
    for (int count = 0; count < 30 - 1; count++) {
        int u = Distancia_menor(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < 30; v++){
            if (!sptSet[v] && grafos[u][v] && dist[u] != INT_MAX && dist[u] + grafos[u][v] < dist[v]){
                dist[v] = dist[u] + grafos[u][v];
            }
        }
    }
 

    printDijkstra(dist);
}
 
int main(){
  struct grafos* grafos = criar_grafos(30);

  srand(time(NULL));
  for(int i = 0; i <= 30; i++ ){
    int quantcantosAleatorias =  1+rand()%3;
    int numcantos = 0;
    while(numcantos != quantcantosAleatorias){
      int cantosAleatorias =  1+rand()%30;
      addAdjacencia(grafos, i, cantosAleatorias);
      numcantos++;
    }
  }
  for(int j=0; j< 30; j++){
    printf("Numero do Vértice: %d\n", j);
    dijkstra(adjMatriz, j);
    printf("\n\n");
  }
  return 0;
}
