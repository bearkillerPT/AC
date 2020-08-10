//
// Joaquim Madeira, AlgC, June 2020
// João Manuel Rodrigues, AlgC, June 2020
//
// GraphShortestPathsWithQueue - QUEUE algorithm for the Shortest Paths Tree
//

#include "GraphShortestPathsWithQueue.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersStack.h"
#include "IntegersQueue.h"

struct _GraphShortestPathsWithQueue {
  int* distance;
  int* predecessor;
  Graph* graph;
  unsigned int startVertex;
};

static void initShortestPathsInfo(GraphShortestPathsWithQueue* ShortestPathsWithQueue) {
  unsigned int numVertices = GraphGetNumVertices(ShortestPathsWithQueue->graph);
  Queue* queue = QueueCreate(numVertices);
  for(int i = 0; i < numVertices; i++) {
    ShortestPathsWithQueue->distance[i] = INT_MAX;
    ShortestPathsWithQueue->predecessor[i] = -1;
  }
  ShortestPathsWithQueue->distance[ShortestPathsWithQueue->startVertex] = 0;
  QueueEnqueue(queue, ShortestPathsWithQueue->startVertex);
  unsigned int* neighbors;
  int* nDistance;
  while(!QueueIsEmpty(queue)) {
    int v = QueueDequeue(queue);
    neighbors = GraphGetAdjacentsTo(ShortestPathsWithQueue->graph, v);
    nDistance = GraphGetDistancesToAdjacents(ShortestPathsWithQueue->graph, v);
    for(int i = 1; i <= neighbors[0]; i++) {
      if(ShortestPathsWithQueue->distance[v] + nDistance[i] < ShortestPathsWithQueue->distance[neighbors[i]]) {
        ShortestPathsWithQueue->distance[neighbors[i]] = ShortestPathsWithQueue->distance[v] + nDistance[i];
        ShortestPathsWithQueue->predecessor[neighbors[i]] = v;
        QueueEnqueue(queue, neighbors[i]);
      }
    }
  free(neighbors);
  free(nDistance);
  }
  
  QueueDestroy(&queue);
}

GraphShortestPathsWithQueue* GraphShortestPathsWithQueueExecute(
    Graph* g, unsigned int startVertex) {
  assert(g != NULL);
  assert(0 <= startVertex && startVertex < GraphGetNumVertices(g));

  GraphShortestPathsWithQueue* ShortestPathsWithQueue =
      (GraphShortestPathsWithQueue*)malloc(
          sizeof(struct _GraphShortestPathsWithQueue));
  assert(ShortestPathsWithQueue != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

  //
  // COMPLETAR !!
  //
  // CRIAR e INICIALIZAR os campos de ShortestPathsWithQueue
  // ShortestPathsWithQueue->distance
  // ShortestPathsWithQueue->predecessor
  //
  ShortestPathsWithQueue->distance = (int* ) calloc(numVertices, sizeof(int));
  assert(ShortestPathsWithQueue->distance != NULL);
  ShortestPathsWithQueue->predecessor = (int* ) calloc(numVertices, sizeof(int));
  assert(ShortestPathsWithQueue->predecessor != NULL);
  ShortestPathsWithQueue->graph = g;
  ShortestPathsWithQueue->startVertex = startVertex;

  // EXECUTAR O ALGORITMO
  initShortestPathsInfo(ShortestPathsWithQueue);
  // COMPLETAR !!

  return ShortestPathsWithQueue;
}

void GraphShortestPathsWithQueueDestroy(GraphShortestPathsWithQueue** p) {
  assert(*p != NULL);

  GraphShortestPathsWithQueue* aux = *p;

  free(aux->distance);
  free(aux->predecessor);

  free(*p);
  *p = NULL;
}

// Getting the result

unsigned int GraphShortestPathsWithQueueHasPathTo(
    const GraphShortestPathsWithQueue* p, unsigned int v) {
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  return (p->distance[v] != INT_MAX);
}

int GraphShortestPathsWithQueueDistanceTo(const GraphShortestPathsWithQueue* p,
                                          unsigned int v) {
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  return p->distance[v];
}

Stack* GraphShortestPathsWithQueuePathTo(const GraphShortestPathsWithQueue* p,
                                         unsigned int v) {
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  Stack* s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->distance[v] == INT_MAX) {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current]) {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphShortestPathsWithQueueShowPath(const GraphShortestPathsWithQueue* p,
                                         unsigned int v) {
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  Stack* s = GraphShortestPathsWithQueuePathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d ", StackPop(s));
  }

  printf(" --- Distance = %d", p->distance[v]);

  StackDestroy(&s);
}

void GraphShortestPathsWithQueueDisplay(const GraphShortestPathsWithQueue* p) {
  // COMPLETAR !!
}
