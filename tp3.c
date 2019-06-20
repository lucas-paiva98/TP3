#include <stdio.h>
#include <stdlib.h>

// A structure to represent an adjacency list node 
struct AdjListNode { 
  int value; 
  struct AdjListNode* next; 
}; 
  
// A structure to represent an adjacency list 
struct AdjList { 
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
    struct Graph* graph =  
        (struct Graph*) malloc(sizeof(struct Graph)); 
    graph->vertexs = vertexQuantity; 
  
    // Create an array of adjacency lists.  Size of  
    // array will be vertexQuantity 
    graph->array =  
      (struct AdjList*) malloc(vertexQuantity * sizeof(struct AdjList)); 
  
    // Initialize each adjacency list as empty by  
    // making head as NULL 
    int i; 
    for (i = 0; i < vertexQuantity; ++i) 
        graph->array[i].head = NULL; 
  
    return graph; 
} 
  
// Adds an edge to an undirected graph 
void addEdge(struct Graph* graph, int src, int dest) { 
    // Add an edge from src to dest.  A new node is  
    // added to the adjacency list of src.  The node 
    // is added at the begining 
    struct AdjListNode* newNode = newAdjListNode(dest); 
    newNode->next = graph->array[src].head; 
    graph->array[src].head = newNode; 
  
    // Since graph is undirected, add an edge from 
    // dest to src also 
    newNode = newAdjListNode(src); 
    newNode->next = graph->array[dest].head; 
    graph->array[dest].head = newNode; 
} 

// Remove those strutures to use only the ones needed 
// and to make east to understand the constrution 
void printGraph(struct Graph* graph) { 
    int v; 
    for (v = 0; v < graph->vertexs; ++v) 
    { 
        struct AdjListNode* pCrawl = graph->array[v].head; 
        printf("\n Adjacency list of vertex %d\n head ", v); 
        while (pCrawl) 
        { 
            printf("-> %d", pCrawl->value); 
            pCrawl = pCrawl->next; 
        } 
        printf("\n"); 
    } 
} 

// The function to print vertex cover 
void printVertexCover(struct Graph* graph, int vertexQuantity) { 
    // Initialize all vertices as not visited. 
    int visited[vertexQuantity]; 
    for (int i=0; i < vertexQuantity; i++) 
        visited[i] = 0; 
  
    // Consider all edges one by one 
    for (int u=0; u < vertexQuantity; u++) { 
        // An edge is only picked when both visited[u] and visited[v] 
        // are false 
        if (visited[u] == 0) { 
            // Go through all adjacents of u and pick the first not 
            // yet visited vertex (We are basically picking an edge 
            // (u, v) from remaining edges.
          struct AdjListNode* pCrawl = graph->array[u].head; 
            while(pCrawl) {
                int v = pCrawl->value;
                printf("Adj: %d\n", v); 
                if (visited[v] == 0) { 
                     // Add the vertices (u, v) to the result set. 
                     // We make the vertex u and v visited so that 
                     // all edges from/to them would be ignored 
                     visited[v] = 1; 
                     visited[u]  = 1; 
                     break; 
                }
              pCrawl = pCrawl->next;  
            } 
        } 
    } 
  int count = 0;
    // Print the vertex cover 
    for (int i=0; i<vertexQuantity; i++) {
        if (visited[i]){
          printf("%d\n", i);  
          count++;
        }
    }
    printf("Size: %d", count);
     
}

int main(int argc, char const *argv[]) {
	FILE *filePaths;
	int vertexQuantity = 0;
	int edgeQuantity = 0;
  int auxU = 0;
  int auxV = 0;

	filePaths = fopen("trilha3.txt", "r");

	if (filePaths == NULL) {
		printf("Error! Cant't open the file.\n");
		exit(1);
	}

	fscanf(filePaths, "%d %d", &vertexQuantity, &edgeQuantity);

  struct Graph* graph = createGraph(vertexQuantity); 

	for (int i = 0; i < edgeQuantity; i++) {
    fscanf(filePaths, "%d %d", &auxU, &auxV);
    addEdge(graph, auxU, auxV);
	}

  printVertexCover(graph, vertexQuantity);
	return 0;
}
