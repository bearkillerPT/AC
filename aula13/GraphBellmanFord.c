//
// Joaquim Madeira, AlgC, June 2020
// João Manuel Rodrigues, AlgC, June 2020
//
// GraphBellmanFord - Bellman-Ford Alg. for the Shortest Paths Tree
//

#include "GraphBellmanFord.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersStack.h"

struct _GraphBellmanFord
{
  int *distance;
  int *predecessor;
  Graph *graph;
  unsigned int startVertex;
};

static void initBellman(GraphBellmanFord *result)
{
  unsigned int numVertices = GraphGetNumVertices(result->graph);
  for (int i = 0; i < numVertices; i++)
  {
    result->distance[i] = INT_MAX/2;
    result->predecessor[i] = -1;
  }
  result->distance[result->startVertex] = 0;
  unsigned int *neighbors;
  int *nDistance;
  for (int n = 0; n < numVertices; n++)
  {
    for (int i = 0; i < numVertices; i++)
    {
      neighbors = GraphGetAdjacentsTo(result->graph, i);
      nDistance = GraphGetDistancesToAdjacents(result->graph, i);
      //int finish = 1;
      for (int j = 1; j <= neighbors[0]; j++)
      {
        if (result->distance[neighbors[j]] > result->distance[i] + nDistance[j])
        {
          result->distance[neighbors[j]] = result->distance[i] + nDistance[j];
          result->predecessor[neighbors[j]] = i;
          //finish = 0;
        }
      }
      free(neighbors);
      free(nDistance);
    }
  }
}

GraphBellmanFord *GraphBellmanFordExecute(Graph *g, unsigned int startVertex)
{
  assert(g != NULL);
  assert(0 <= startVertex && startVertex < GraphGetNumVertices(g));

  GraphBellmanFord *bellmanFord =
      (GraphBellmanFord *)malloc(sizeof(struct _GraphBellmanFord));
  assert(bellmanFord != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

  //
  // COMPLETAR !!
  //
  // CRIAR e INICIALIZAR os campos de bellmanFord
  // bellmanFord->distance
  // bellmanFord->predecessor
  //
  bellmanFord->distance = (int *)malloc(numVertices * sizeof(int));
  assert(bellmanFord->distance != NULL);
  bellmanFord->predecessor = (int *)malloc(numVertices * sizeof(int));
  assert(bellmanFord->predecessor != NULL);

  bellmanFord->graph = g;
  bellmanFord->startVertex = startVertex;

  // EXECUTAR O ALGORITMO
  initBellman(bellmanFord);
  // COMPLETAR !!

  return bellmanFord;
}

void GraphBellmanFordDestroy(GraphBellmanFord **p)
{
  assert(*p != NULL);

  GraphBellmanFord *aux = *p;

  free(aux->distance);
  free(aux->predecessor);

  free(*p);
  *p = NULL;
}

// Getting the result

unsigned int GraphBellmanFordHasPathTo(const GraphBellmanFord *p,
                                       unsigned int v)
{
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  return (p->distance[v] != INT_MAX);
}

int GraphBellmanFordDistanceTo(const GraphBellmanFord *p, unsigned int v)
{
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  return p->distance[v];
}

Stack *GraphBellmanFordPathTo(const GraphBellmanFord *p, unsigned int v)
{
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  Stack *s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->distance[v] == INT_MAX)
  {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current])
  {
    StackPush(s, current);
    //printf("%d", current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphBellmanFordShowPath(const GraphBellmanFord *p, unsigned int v)
{
  assert(0 <= v && v < GraphGetNumVertices(p->graph));

  Stack *s = GraphBellmanFordPathTo(p, v);

  while (StackIsEmpty(s) == 0)
  {
    printf("%d ", StackPop(s));
  }

  printf(" --- Distance = %d", p->distance[v]);

  StackDestroy(&s);
}

void GraphBellmanFordDisplay(const GraphBellmanFord *p)
{
  // COMPLETAR !!
}
