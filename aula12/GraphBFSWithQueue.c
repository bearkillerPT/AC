//
// Joaquim Madeira, AlgC, May 2020
// João Manuel Rodrigues, AlgC, May 2020
//
// GraphBFS - QUEUE-based Breadth-First Search
//

#include "GraphBFSWithQueue.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersQueue.h"
#include "IntegersStack.h"
#include "limits.h"

struct _GraphBFSWithQueue {
  unsigned int* marked;
  int* distance;
  int* predecessor;
  Graph* graph;
  unsigned int startVertex;
};

static void _bfs(GraphBFSWithQueue* traversal, unsigned int vertex) {
  //usando INT_MAX como maior valor possivel
  Queue* queue = QueueCreate(GraphGetNumVertices(traversal->graph));
  QueueEnqueue(queue, vertex);
  unsigned int* neighbors;
  while(!QueueIsEmpty(queue)) {
    vertex = QueueDequeue(queue);
    traversal->marked[vertex] = 1;
    neighbors = GraphGetAdjacentsTo(traversal->graph, vertex);
    for (int i = 1; i <= neighbors[0]; i++) {
      unsigned int w = neighbors[i];
      if(traversal->distance[vertex] + 1 < traversal->distance[w]) {
        traversal->distance[w] = traversal->distance[vertex] + 1;
        if (!traversal->marked[w]) {
          traversal->predecessor[w] = vertex; 
          QueueEnqueue(queue, w);
        }
      } 
    }
    free(neighbors);
  }
  
    QueueDestroy(&queue);
}

GraphBFSWithQueue* GraphBFSWithQueueExecute(Graph* g,
                                            unsigned int startVertex) {
  assert(g != NULL);
  assert(0 <= startVertex && startVertex < GraphGetNumVertices(g));

  GraphBFSWithQueue* traversal =
      (GraphBFSWithQueue*)malloc(sizeof(struct _GraphBFSWithQueue));
  assert(traversal != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

  //
  // COMPLETAR !!
  //
  // CRIAR e INICIALIZAR os campos de traversal
 
  // traversal->marked
  traversal->marked = (unsigned int*)calloc(numVertices, sizeof(unsigned int));
  assert(traversal->marked != NULL);
  // traversal->distance
  traversal->distance = (int*)calloc(numVertices, sizeof(unsigned int));
  assert(traversal->distance != NULL);
  // traversal->predecessor
  traversal->predecessor = (int*)calloc(numVertices, sizeof(unsigned int));
  assert(traversal->predecessor != NULL);
  //
  
  traversal->graph = g;
  traversal->startVertex = startVertex;
  for(int i = 0; i < numVertices; i++) {
    traversal->distance[i] = INT_MAX;
  }
  traversal->distance[startVertex] = 0;
  // EFETUAR A TRAVESSIA
  _bfs(traversal, startVertex);
  // COMPLETAR !!

  return traversal;
}

void GraphBFSWithQueueDestroy(GraphBFSWithQueue** p) {
  assert(*p != NULL);

  GraphBFSWithQueue* aux = *p;

  free(aux->marked);
  free(aux->predecessor);

  free(*p);
  *p = NULL;
}

// Getting the result

unsigned int GraphBFSWithQueueHasPathTo(const GraphBFSWithQueue* p,
                                        unsigned int v) {
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

Stack* GraphBFSWithQueuePathTo(const GraphBFSWithQueue* p, unsigned int v) {
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  Stack* s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0) {
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

void GraphBFSWithQueueShowPath(const GraphBFSWithQueue* p, unsigned int v) {
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  Stack* s = GraphBFSWithQueuePathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

void GraphBFSWithQueueDisplay(const GraphBFSWithQueue* p) {
  // COMPLETAR !!
  for(int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    if(i != p->startVertex) GraphBFSWithQueueShowPath(p, i);
  }

}
