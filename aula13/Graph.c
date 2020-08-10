//
// Joaquim Madeira, AlgC, May 2020
// João Manuel Rodrigues, AlgC, May 2020
//
// Graph - Using a list of adjacency lists representation
//

#include "Graph.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "SortedList.h"

struct _Vertex {
  unsigned int id;
  unsigned int inDegree;
  unsigned int outDegree;
  List* edgesList;
};

struct _Edge {
  unsigned int adjVertex;
  int weight;
};

struct _GraphHeader {
  unsigned short isDigraph;
  unsigned short isComplete;
  unsigned short isWeighted;
  unsigned int numVertices;
  unsigned int numEdges;
  List* verticesList;
};

// The comparator for the VERTICES LIST

int graphVerticesComparator(const void* p1, const void* p2) {
  unsigned int v1 = ((struct _Vertex*)p1)->id;
  unsigned int v2 = ((struct _Vertex*)p2)->id;
  int d = v1 - v2;
  return (d > 0) - (d < 0);
}

// The comparator for the EDGES LISTS

int graphEdgesComparator(const void* p1, const void* p2) {
  unsigned int v1 = ((struct _Edge*)p1)->adjVertex;
  unsigned int v2 = ((struct _Edge*)p2)->adjVertex;
  int d = v1 - v2;
  return (d > 0) - (d < 0);
}

Graph* GraphCreate(unsigned int numVertices, unsigned short isDigraph,
                   unsigned short isWeighted) {
  Graph* g = (Graph*)malloc(sizeof(struct _GraphHeader));
  if (g == NULL) abort();

  g->isDigraph = isDigraph;
  g->isComplete = 0;
  g->isWeighted = isWeighted;

  g->numVertices = numVertices;
  g->numEdges = 0;

  g->verticesList = ListCreate(graphVerticesComparator);

  for (int i = 0; i < numVertices; i++) {
    struct _Vertex* v = (struct _Vertex*)malloc(sizeof(struct _Vertex));
    if (v == NULL) abort();

    v->id = i;
    v->inDegree = 0;
    v->outDegree = 0;

    v->edgesList = ListCreate(graphEdgesComparator);

    ListInsert(g->verticesList, v);
  }

  assert(g->numVertices == ListGetSize(g->verticesList));

  return g;
}

Graph* GraphCreateComplete(unsigned int numVertices,
                           unsigned short isDigraph) {
  Graph* g = GraphCreate(numVertices, isDigraph, 0);

  g->isComplete = 1;

  List* vertices = g->verticesList;
  ListMoveToHead(vertices);
  int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++) {
    struct _Vertex* v = ListGetCurrentItem(vertices);
    List* edges = v->edgesList;
    for (int j = 0; j < g->numVertices; j++) {
      if (i == j) {
        continue;
      }
      struct _Edge* new = (struct _Edge*)malloc(sizeof(struct _Edge));
      if (new == NULL) abort();
      new->adjVertex = j;
      new->weight = 1;

      ListInsert(edges, new);
    }
    if (g->isDigraph) {
      v->inDegree = g->numVertices - 1;
      v->outDegree = g->numVertices - 1;
    } else {
      v->outDegree = g->numVertices - 1;
    }
  }
  if (g->isDigraph) {
    g->numEdges = numVertices * (numVertices - 1);
  } else {
    g->numEdges = numVertices * (numVertices - 1) / 2;
  }

  return g;
}

void GraphDestroy(Graph** p) {
  assert(*p != NULL);
  Graph* g = *p;

  List* vertices = g->verticesList;
  if (ListIsEmpty(vertices) == 0) {
    ListMoveToHead(vertices);
    int i = 0;
    for (; i < g->numVertices; ListMoveToNext(vertices), i++) {
      struct _Vertex* v = ListGetCurrentItem(vertices);

      List* edges = v->edgesList;
      if (ListIsEmpty(edges) == 0) {
        ListMoveToHead(edges);
        for (int i = 0; i < ListGetSize(edges); ListMoveToNext(edges), i++) {
          struct _Edge* e = ListGetCurrentItem(edges);
          free(e);
        }
      }
      ListDestroy(&(v->edgesList));
      free(v);
    }
  }

  ListDestroy(&(g->verticesList));
  free(g);

  *p = NULL;
}

Graph* GraphCopy(const Graph* g) {
  Graph* res;
  if(g->isComplete)
    res = GraphCreateComplete(g->numVertices, g->isDigraph);
  else {
    unsigned int* neighbors;
    res = GraphCreate(g->numVertices, g->isDigraph, g->isWeighted);
    for(int i = 0; i < g->numVertices; i++) {
      neighbors = GraphGetAdjacentsTo(res, i);
      for(int j = 1; j < neighbors[0]; j++) GraphAddEdge(res, i, neighbors[j]);
      free(neighbors);
    }
  }
  return res;
}

Graph* GraphFromFile(FILE* f) {
  // COMPLETAR !!
  Graph* res;
  int i,j,k;
  float z;
  int status = 3;
  fscanf(f, "%d", &i);
  fscanf(f, "%d\n", &j);
  fscanf(f, "%d\n", &k);
  printf("num vertices: %d | isDigraph: %d | isWeighted: %d\n\n", k, i, j);
  res = GraphCreate(k, i, j);
  fscanf(f, "%d\n", &k);
  res->numEdges = 0;
  while(status > 0) {
      //printf("%d - %d, %d\n", res->numVertices , i, j);
      if(res->isWeighted) {
        status = fscanf(f, "%d %d %f\n", &i, &j, &z);
        if(status < 3) break;
        GraphAddWeightedEdge(res, i, j, (int) z);
      }
      else {
        status = fscanf(f, "%d %d\n", &i, &j);
        if(status <2) break;
        GraphAddEdge(res, i, j);
      }
  }
  GraphCheckInvariants(res);
  return res;
}

// Graph

unsigned short GraphIsDigraph(const Graph* g) { return g->isDigraph; }

unsigned short GraphIsComplete(const Graph* g) { return g->isComplete; }

unsigned short GraphIsWeighted(const Graph* g) { return g->isWeighted; }

unsigned int GraphGetNumVertices(const Graph* g) { return g->numVertices; }

unsigned int GraphGetNumEdges(const Graph* g) { return g->numEdges; }

//
// For a graph
//
double GraphGetAverageDegree(const Graph* g) {
  assert(g->isDigraph == 0);
  return 2 * g->numEdges / g->numVertices;
}


static unsigned int _GetMaxDegree(const Graph* g) {
  List* vertices = g->verticesList;
  if (ListIsEmpty(vertices)) return 0;
  
  unsigned int maxDegree = 0;
  ListMoveToHead(vertices);
  int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++) {
    struct _Vertex* v = ListGetCurrentItem(vertices);
    if (v->outDegree > maxDegree) {
      maxDegree = v->outDegree;
    }
  }
  return maxDegree;
}

//
// For a graph
//
unsigned int GraphGetMaxDegree(const Graph* g) {
  assert(g->isDigraph == 0);
  return _GetMaxDegree(g);
}

//
// For a digraph
//
unsigned int GraphGetMaxOutDegree(const Graph* g) {
  assert(g->isDigraph == 1);
  return _GetMaxDegree(g);
}

// Vertices

//
// returns an array of size (outDegree + 1)
// element 0, stores the number of adjacent vertices
// and is followed by indices of the adjacent vertices
//
unsigned int* GraphGetAdjacentsTo(const Graph* g, unsigned int v) {
  assert(0 <= v && v < g->numVertices);

  // Node in the list of vertices
  List* vertices = g->verticesList;
  ListMove(vertices, v);
  struct _Vertex* vPointer = ListGetCurrentItem(vertices);
  unsigned int numAdjVertices = vPointer->outDegree;

  unsigned int* adjacent =
      (unsigned int*)calloc(1 + numAdjVertices, sizeof(unsigned int));

  if (numAdjVertices > 0) {
    adjacent[0] = numAdjVertices;
    List* adjList = vPointer->edgesList;
    ListMoveToHead(adjList);
    for (int i = 0; i < numAdjVertices; ListMoveToNext(adjList), i++) {
      struct _Edge* ePointer = ListGetCurrentItem(adjList);
      adjacent[i + 1] = ePointer->adjVertex;
    }
  }

  return adjacent;
}

int* GraphGetDistancesToAdjacents(const Graph* g, unsigned int v) {
  assert(0 <= v && v < g->numVertices);

  // Node in the list of vertices
  List* vertices = g->verticesList;
  ListMove(vertices, v);
  struct _Vertex* vPointer = ListGetCurrentItem(vertices);
  unsigned int numAdjVertices = vPointer->outDegree;

  int* distance = (int*)calloc(1 + numAdjVertices, sizeof(int));

  if (numAdjVertices > 0) {
    distance[0] = numAdjVertices;
    List* adjList = vPointer->edgesList;
    ListMoveToHead(adjList);
    for (int i = 0; i < numAdjVertices; ListMoveToNext(adjList), i++) {
      struct _Edge* ePointer = ListGetCurrentItem(adjList);
      distance[i + 1] = ePointer->weight;
    }
  }

  return distance;
}


//
// For a graph
//
unsigned int GraphGetVertexDegree(Graph* g, unsigned int v) {
  assert(g->isDigraph == 0);
  assert(0 <= v && v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex* p = ListGetCurrentItem(g->verticesList);

  return p->outDegree;
}

//
// For a digraph
//
unsigned int GraphGetVertexOutDegree(Graph* g, unsigned int v) {
  assert(g->isDigraph == 1);
  assert(0 <= v && v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex* p = ListGetCurrentItem(g->verticesList);

  return p->outDegree;
}

//
// For a digraph
//
unsigned int GraphGetVertexInDegree(Graph* g, unsigned int v) {
  assert(g->isDigraph == 1);
  assert(0 <= v && v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex* p = ListGetCurrentItem(g->verticesList);

  return p->inDegree;
}

// Edges

static unsigned short _addEdge(Graph* g, unsigned int v, unsigned int w,
                               int weight) {
  struct _Edge* edge = (struct _Edge*)malloc(sizeof(struct _Edge));
  edge->adjVertex = w;
  edge->weight = weight;

  ListMove(g->verticesList, v);
  struct _Vertex* vertex = ListGetCurrentItem(g->verticesList);
  int result = ListInsert(vertex->edgesList, edge);
  if (result == -1) {
    return 0;
  } else {
    g->numEdges++;
    vertex->outDegree++;
    if(g->isDigraph) { //Alteracao para o inDegree
      ListMove(g->verticesList, w);
      vertex = ListGetCurrentItem(g->verticesList);
      vertex->inDegree++;
    }
  }

  if (g->isDigraph == 0) {
    // Bidirectional edge
    struct _Edge* edge = (struct _Edge*)malloc(sizeof(struct _Edge));
    edge->adjVertex = v;
    edge->weight = weight;

    ListMove(g->verticesList, w);
    struct _Vertex* vertex = ListGetCurrentItem(g->verticesList);
    result = ListInsert(vertex->edgesList, edge);

    if (result == -1) {
      return 0;
    } else {
      //g->numEdges++; Para nao contar as arestas duas vezes
      vertex->outDegree++;
    }
  }

  return 1;
}

unsigned short GraphAddEdge(Graph* g, unsigned int v, unsigned int w) {
  assert(g->isWeighted == 0);  
  if(v == w) return 0;
  assert(0 <= v && v < g->numVertices);
  assert(0 <= w && w < g->numVertices);

  return _addEdge(g, v, w, 1);
}

unsigned short GraphAddWeightedEdge(Graph* g, unsigned int v, unsigned int w,
                                    int weight) {
  assert(g->isWeighted == 1);
  if(v == w) return 0;
  assert(0 <= v && v < g->numVertices);
  assert(0 <= w && w < g->numVertices);

  return _addEdge(g, v, w, weight);
}

// CHECKING

unsigned short GraphCheckInvariants(Graph* g) {
  unsigned int numVertices = GraphGetNumVertices(g);
  assert(ListGetSize(g->verticesList) == numVertices);
  int totalEdges = 0;
  unsigned int* neighbors;
  unsigned int inDegrees[numVertices];
  for(int i = 0; i < numVertices; i++) inDegrees[i] = 0;
  for(int i = 0; i < numVertices; i++) {
    neighbors = GraphGetAdjacentsTo(g, i);
    if(g->isDigraph) {
      assert(GraphGetVertexOutDegree(g, i) == neighbors[0]);
      for(int j = 1; j <= neighbors[0]; j++) {
        inDegrees[neighbors[j]]++;
      }
    }
    else {
      assert(GraphGetVertexDegree(g, i) == neighbors[0]);
    }
    totalEdges+=neighbors[0];
  }
  if(g->isDigraph) {
    for(int i = 0; i < numVertices; i++) {
      assert(GraphGetVertexInDegree(g, i) == inDegrees[i]);
    } 
  }else totalEdges/=2;
  assert(GraphGetNumEdges(g) == totalEdges);
  return 1;
}

// DISPLAYING on the console

void GraphDisplay(const Graph* g) {
  printf("---\n");
  if (g->isWeighted) {
    printf("Weighted ");
  }
  if (g->isComplete) {
    printf("COMPLETE ");
  }
  if (g->isDigraph) {
    printf("Digraph\n");
    printf("Max Out-Degree = %d\n", GraphGetMaxOutDegree(g));
  } else {
    printf("Graph\n");
    printf("Max Degree = %d\n", GraphGetMaxDegree(g));
  }
  printf("Vertices = %2d | Edges = %2d\n", g->numVertices, g->numEdges);

  List* vertices = g->verticesList;
  ListMoveToHead(vertices);
  int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++) {
    printf("%2d ->", i);
    struct _Vertex* v = ListGetCurrentItem(vertices);
    if (ListIsEmpty(v->edgesList)) {
      printf("\n");
    } else {
      List* edges = v->edgesList;
      ListMoveToHead(edges);
      for (int i = 0; i < ListGetSize(edges); ListMoveToNext(edges), i++) {
        struct _Edge* e = ListGetCurrentItem(edges);
        if (g->isWeighted) {
          printf("   %2d(%2d)", e->adjVertex, e->weight);
        } else {
          printf("   %2d", e->adjVertex);
        }
      }
      printf("\n");
    }
  }
  printf("---\n");
}

void GraphListAdjacents(const Graph* g, unsigned int v) {
  printf("---\n");

  unsigned int* array = GraphGetAdjacentsTo(g, v);

  printf("Vertex %d has %d adjacent vertices -> ", v, array[0]);

  for (int i = 1; i <= array[0]; i++) {
    printf("%d ", array[i]);
  }

  printf("\n");

  free(array);

  printf("---\n");
}
