//
// Algoritmos e Estruturas de Dados --- 2025/2026
//
// Joaquim Madeira, Joao Manuel Rodrigues - Nov 2025
//
// Graph EXAMPLE : Creating and displaying graphs and subgraphs
//
// MODIFY THIS FILE FOR FURTHER TESTS
//

#include <assert.h>
#include <stdlib.h>

#include "Graph.h"
#include "IndicesSet.h"

// COLORS :)
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"

int main(void) {
  // What kind of graph is g01?
  Graph* g01 = GraphCreate(6, 1, 0);
  GraphAddEdge(g01, 1, 2);
  GraphAddEdge(g01, 1, 4);
  GraphAddEdge(g01, 3, 4);
  printf("The graph:\n");
  // Displaying in DOT format
  GraphDisplayDOT(g01);
  // Saving in DOT format
  FILE* file = fopen("simple_graph.DOT", "w");
  GraphToDOTFile(g01, file);
  fclose(file);
  printf("\n");

  GraphCheckInvariants(g01);

  // The lists of adjacent vertices
  for (unsigned int i = 0; i < GraphGetNumVertices(g01); i++) {
    GraphListAdjacents(g01, i);
  }

  // Reading an undirected graph from file
  file = fopen("G_2.txt", "r");
  Graph* g02 = GraphFromFile(file);
  fclose(file);
  // Displaying in DOT format
  GraphDisplayDOT(g02);
  printf("\n");

  GraphCheckInvariants(g02);

  // Creating another graph

  Graph* g03 = GraphCreateEmpty(4, 0, 0);
  GraphAddVertex(g03, 2);
  GraphAddVertex(g03, 0);
  GraphAddVertex(g03, 1);
  GraphAddVertex(g03, 3);
  GraphAddEdge(g03, 0, 1);
  GraphAddEdge(g03, 0, 2);
  GraphAddEdge(g03, 0, 3);
  GraphAddEdge(g03, 2, 1);
  GraphAddEdge(g03, 2, 3);

  // Displaying in DOT format
  GraphDisplayDOT(g03);
  printf("\n");

  GraphCheckInvariants(g03);

  // The lists of adjacent vertices
  for (unsigned int i = 0; i < GraphGetNumVertices(g03); i++) {
    GraphListAdjacents(g03, i);
  }

  // The computed vertex weights
  double* weights_g03 = GraphComputeVertexWeights(g03);
  for (unsigned int i = 0; i < GraphGetVertexRange(g03); i++) {
    if (weights_g03[i] != -1) {
      printf("Vertex %u : weight = %f\n", i, weights_g03[i]);
    }
  }
  printf("\n");
  free(weights_g03);

  // A subgraph of g03
  IndicesSet* vertices = IndicesSetCreateEmpty(4);
  IndicesSetAdd(vertices, 0);
  IndicesSetAdd(vertices, 1);
  IndicesSetAdd(vertices, 2);
  IndicesSetAdd(vertices, 3);

  Graph* subg031 = GraphGetSubgraph(g03, vertices);
  IndicesSetDestroy(&vertices);

  // Displaying in DOT format
  GraphDisplayDOT(subg031);
  printf("\n");

  GraphCheckInvariants(subg031);

  // Another subgraph of g03
  vertices = IndicesSetCreateEmpty(4);
  IndicesSetAdd(vertices, 0);
  IndicesSetAdd(vertices, 2);
  IndicesSetAdd(vertices, 3);

  Graph* subg032 = GraphGetSubgraph(g03, vertices);
  IndicesSetDestroy(&vertices);

  // Displaying in DOT format
  GraphDisplayDOT(subg032);
  printf("\n");

  GraphCheckInvariants(subg032);

  // Reading a directed graph from file
  file = fopen("DG_2.txt", "r");
  Graph* g04 = GraphFromFile(file);
  fclose(file);
  // Displaying in DOT format
  GraphDisplayDOT(g04);
  printf("\n");

  GraphCheckInvariants(g04);

  // A subgraph of g04
  vertices = IndicesSetCreateEmpty(15);
  IndicesSetAdd(vertices, 1);
  IndicesSetAdd(vertices, 3);
  IndicesSetAdd(vertices, 5);
  IndicesSetAdd(vertices, 7);
  IndicesSetAdd(vertices, 9);

  Graph* subg041 = GraphGetSubgraph(g04, vertices);
  IndicesSetDestroy(&vertices);

  // Displaying in DOT format
  GraphDisplayDOT(subg041);
  printf("\n");


  printf(GREEN"========== STUDENT MADE TESTS =========="RESET"\n");

  // Create a new weighted graph
  Graph* wGraph = GraphCreate(6, 0, 1);
  // VERTEX 0
  GraphAddWeightedEdge(wGraph, 0, 1, 1);
  GraphAddWeightedEdge(wGraph, 0, 2, 2);
  GraphAddWeightedEdge(wGraph, 0, 3, 4);
  // VERTEX 1
  GraphAddWeightedEdge(wGraph, 1, 2, 1);
  // VERTEX 2
  GraphAddWeightedEdge(wGraph, 2, 3, 1);
  GraphAddWeightedEdge(wGraph, 2, 5, 3);
  // VERTEX 3
  GraphAddWeightedEdge(wGraph, 3, 4, 1);
  GraphAddWeightedEdge(wGraph, 3, 5, 2);
  // VERTEX 4
  GraphAddWeightedEdge(wGraph, 4, 5, 1);

  printf(RED"The graph:"RESET"\n");
  // Displaying in DOT format
  GraphDisplayDOT(wGraph);

  // Save new graph in file
  FILE* fptr = fopen("Weigthed Graph.DOT", "w");
  GraphToDOTFile(wGraph, fptr);
  fclose(fptr);

  printf(GREEN"========== GRAPH W COMPUTE VERTEX WEIGHTS ============"RESET"\n");
  double* wwGraph = GraphComputeVertexWeights(wGraph);
  for (unsigned int i = 0; i < GraphGetVertexRange(wGraph); i++) {
    if (wwGraph[i] != -1) {
      printf("Vertex %u : weight = %f\n", i, wwGraph[i]);
    }
  }
  printf("\n");
  free(wwGraph);

  printf(GREEN"========== GRAPH 2 COMPUTE VERTEX WEIGHTS ============"RESET"\n");
  double* weights_g02 = GraphComputeVertexWeights(g02);
  for (unsigned int i = 0; i < GraphGetVertexRange(g02); i++) {
    if (weights_g02[i] != -1) {
      printf("Vertex %u : weight = %f\n", i, weights_g02[i]);
    }
  }
  printf("\n");
  free(weights_g02);


  // Clearing
  GraphDestroy(&g01);
  GraphDestroy(&g02);
  GraphDestroy(&g03);
  GraphDestroy(&subg031);
  GraphDestroy(&subg032);
  GraphDestroy(&g04);
  GraphDestroy(&subg041);

  // DESTROY STUDENT TESTS
  GraphDestroy(&wGraph);

  return 0;
}
