//
// Joaquim Madeira, AlgC, May 2020
// João Manuel Rodrigues, AlgC, May 2020
//
// Graph EXAMPLE
//

#include "Graph.h"
#include "GraphDFSRec.h"
#include "GraphDFSWithStack.h"
#include "GraphBFSWithQueue.h"

int main(void) {
  Graph* g01 = GraphCreate(6, 0, 0);

  GraphAddEdge(g01, 0, 5);
  GraphAddEdge(g01, 2, 4);
  GraphAddEdge(g01, 2, 3);
  GraphAddEdge(g01, 1, 2);
  GraphAddEdge(g01, 0, 1);
  GraphAddEdge(g01, 3, 4);
  GraphAddEdge(g01, 3, 5);
  GraphAddEdge(g01, 0, 2);
  
  GraphDisplay(g01);
  int startVertex = 0;
  GraphDFSRec* traversal = GraphDFSRecExecute(g01, startVertex);

  printf("Path from 0 to 5: ");
  GraphDFSRecShowPath(traversal, 4);
  printf("\n");

  GraphDFSRecDestroy(&traversal);

  GraphDFSWithStack* traversal2 = GraphDFSWithStackExecute(g01, startVertex);

  printf("Path from 0 to 5: ");
  GraphDFSWithStackShowPath(traversal2, 4);
  printf("\n");

  GraphDFSWithStackDestroy(&traversal2);

  GraphBFSWithQueue* traversal3 = GraphBFSWithQueueExecute(g01, startVertex);

  printf("Path from 0 to 5: ");
  GraphBFSWithQueueShowPath(traversal3, 4);
  printf("\n");
  int stronglyConex = 1; 
  printf("Vertice reachable from %d:\n", startVertex);
  for(int i = 0; i < GraphGetNumVertices(g01); i++) {
    if(i != startVertex) {
      printf("\t%d is reachable: %s\n", i, GraphBFSWithQueueHasPathTo(traversal3, i)? "true": "false");
      if(!GraphBFSWithQueueHasPathTo(traversal3, i)) stronglyConex = 0;
    }
  }
  printf("Grafo fortemente conexo: %s\n", stronglyConex?"true":"false");
  GraphBFSWithQueueDestroy(&traversal3);

  GraphDestroy(&g01);

  return 0;
}
