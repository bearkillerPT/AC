//
// Joaquim Madeira, AlgC, June 2020
// João Manuel Rodrigues, AlgC, June 2020
//
// Shortest Paths example
//

#include "Graph.h"
#include "GraphBellmanFord.h"
#include "GraphDijkstra.h"
#include "GraphShortestPathsWithQueue.h"
#include <dirent.h>
#include <string.h>

int main(void) {
  struct dirent *de;
  Graph* g01 = GraphCreate(6, 0, 1);
  DIR* testes = opendir("./testes");
  readdir(testes); // .
  readdir(testes); // ..
  readdir(testes); // README.txt
  // Nota: O graphCreate tinha numVertices como unsigned short e um dos exemplos tem 1000000 de vertices pelo que alterei para unsigned int.
  // NOTA2: Como se pode ver abaixo tinha uma pasta chamada testes com os testes fornecidos mas eram muito pesados para enviar
  //          por zip. O exemplo com um milhão de vértices está também a ser ignorado já que com esta TAD é muito lento

  while ((de = readdir(testes))) {
    char str[256] = "./testes/"; 
    strcat(str, de->d_name);
    if(!strcmp(de->d_name, "SWlargeG.txt")) continue; //1000000 vertices demora séculos a criar os vérices
    printf("%s\n", str);
    FILE* f = fopen(str, "r");
    Graph* g02 = GraphFromFile(f);
    //GraphDisplay(g02);
    GraphDestroy(&g02);
  }
  GraphAddWeightedEdge(g01, 0, 5, 1);
  GraphAddWeightedEdge(g01, 2, 4, 2);
  GraphAddWeightedEdge(g01, 2, 3, 3);
  GraphAddWeightedEdge(g01, 1, 2, 4);
  GraphAddWeightedEdge(g01, 0, 1, 5);
  GraphAddWeightedEdge(g01, 3, 4, 6);
  GraphAddWeightedEdge(g01, 3, 5, 1);
  GraphAddWeightedEdge(g01, 0, 2, 8);

  GraphDisplay(g01);
  int vertex = 5;
  GraphBellmanFord* shortestPathsBF = GraphBellmanFordExecute(g01, vertex);
  for (int i = 0; i < GraphGetNumVertices(g01); i++) {
    printf("Path from %d to %d: ", vertex, i);
    GraphBellmanFordShowPath(shortestPathsBF, i);
    printf("\n");
  }

  GraphBellmanFordDestroy(&shortestPathsBF);

  printf("---\n");

  GraphShortestPathsWithQueue* shortestPathsWithQueue =
      GraphShortestPathsWithQueueExecute(g01, vertex);

  for (int i = 0; i < GraphGetNumVertices(g01); i++) {
    printf("Path from %d to %d: ", vertex, i);
    GraphShortestPathsWithQueueShowPath(shortestPathsWithQueue, i);
    printf("\n");
  }

  GraphShortestPathsWithQueueDestroy(&shortestPathsWithQueue);

  printf("---\n");

  GraphDijkstra* shortestPathsDijkstra = GraphDijkstraExecute(g01, vertex);

  for (int i = 0; i < GraphGetNumVertices(g01); i++) {
    printf("Path from %d to %d: ", vertex, i);
    GraphDijkstraShowPath(shortestPathsDijkstra, i);
    printf("\n");
  }

  GraphDijkstraDestroy(&shortestPathsDijkstra);

  GraphDestroy(&g01);

  return 0;
}
