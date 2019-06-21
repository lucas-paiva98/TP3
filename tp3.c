#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// A structure to represent an adjacency list node 
struct AdjListNode {
  int value; 
  struct AdjListNode* next; 
}; 
  
// A structure to represent an adjacency list 
struct AdjList {
  int size;
  struct AdjListNode *head;  
}; 

struct Graph { 
  int vertexs; 
  struct AdjList* array; 
};

// A utility function to create a new adjacency list node 
struct AdjListNode* newAdjListNode(int value) { 
  struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode)); 
  newNode->value = value; 
  newNode->next = NULL; 
  return newNode; 
} 

// A utility function that creates a graph of V vertices 
struct Graph* createGraph(int vertexQuantity) { 
  struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
  graph->vertexs = vertexQuantity; 

  // Create an array of adjacency lists.  Size of  
  // array will be vertexQuantity 
  graph->array = (struct AdjList*) malloc(vertexQuantity * sizeof(struct AdjList)); 

  // Initialize each adjacency list as empty by  
  // making head as NULL 
  int i; 
  for (i = 0; i < vertexQuantity; ++i) 
    graph->array[i].head = NULL; 

  return graph; 
} 
  
// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest) {
  struct AdjListNode* newNode = newAdjListNode(dest); 
  newNode->next = graph->array[src].head; 
  graph->array[src].head = newNode;
  graph->array[src].size++;

  newNode = newAdjListNode(src); 
  newNode->next = graph->array[dest].head; 
  graph->array[dest].head = newNode; 
} 

// Remove those strutures to use only the ones needed 
// and to make east to understand the constrution 
void printGraph(struct Graph* graph) { 
  int v; 
  for (v = 0; v < graph->vertexs; ++v) { 
    struct AdjListNode* pCrawl = graph->array[v].head; 
    printf("\n Adjacency list of vertex %d\n head ", v); 
    while (pCrawl) {
      printf("-> %d", pCrawl->value); 
      pCrawl = pCrawl->next; 
    } 
    printf("\n"); 
  } 
}

int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

void printVertexCover(struct Graph* graph, int vertexQuantity) {
  int visited[vertexQuantity]; 
  for (int i=0; i < vertexQuantity; i++) 
    visited[i] = 0; 

  for (int u=0; u < vertexQuantity; u++) {
    // Select a vertex that hasn't visited yet 
    if (visited[u] == 0) {
      // Go to all the adjacent vertexs of u  
      struct AdjListNode* adjVertex = graph->array[u].head;
      while(adjVertex) {
        int v = adjVertex->value;
        if (visited[v] == 0) {
          visited[v] = 1; 
          visited[u]  = 1; 
          break; 
        }
        adjVertex = adjVertex->next;  
      } 
    } 
  } 

int count = 0;
  for (int i=0; i < vertexQuantity; i++) {
    if (visited[i]){
      printf("%d\n", i);
      count++;  
    }
  }
  printf("COunt : %d", count);
}

int minVertexCover(struct Graph* graph, int node, int isIn, int **cache, int *parent) {
  int adjacentSize = graph->array[node].size; 
  if(adjacentSize == 0) {
    return isIn;
  }
  else if (cache[node][isIn] != -1) {
    return cache[node][isIn];
  }

  int sum = 0;
  struct AdjListNode* adjVertex = graph->array[node].head;

  while (adjVertex) {
    int v = adjVertex->value;
    if (v != parent[node]) {
      parent[v] = node;

      if (isIn == 0) {
        sum += minVertexCover(graph, v, 1, cache, parent);
      }
      else {
        sum += min(minVertexCover(graph, v, 1, cache, parent), minVertexCover(graph, v, 0, cache, parent));
      }
    }
    adjVertex = adjVertex->next;      
  }
  
  cache[node][isIn] = sum + isIn;

  return cache[node][isIn];
  
}

int main(int argc, char const *argv[]) {
	FILE *filePaths;
	int vertexQuantity = 0;
	int edgeQuantity = 0;
  int auxU = 0;
  int auxV = 0;

	filePaths = fopen("t1.txt", "r");

	if (filePaths == NULL) {
		printf("Error! Cant't open the file.\n");
		exit(1);
	}

	fscanf(filePaths, "%d %d", &vertexQuantity, &edgeQuantity);

  struct Graph* graph = createGraph(vertexQuantity); 
  
  int **cache = allocateMatrixInt(vertexQuantity, 1);
  int parent[vertexQuantity];
  int vertexCover = 0;
  for (int i = 0; i < vertexQuantity; i++) {
    parent[i] = -1;
    for (int j = 0; j < 2; j++) {
      cache[i][j] = -1;
    }
	}

	for (int i = 0; i < edgeQuantity; i++) {
    fscanf(filePaths, "%d %d", &auxU, &auxV);
    addEdge(graph, auxU, auxV);
	}

  struct AdjListNode* u = graph->array[0].head;

  // printVertexCover(graph, vertexQuantity);
  vertexCover = min(minVertexCover(graph, u->value, 0, cache, parent), minVertexCover(graph, u->value, 1, cache, parent));

  printf("%d", vertexCover);
	return 0;
}
