//
// Algoritmos e Estruturas de Dados --- 2025/2026
//
// Joaquim Madeira, Joao Manuel Rodrigues - Nov 2025
//
// Testing the Dominating Sets algorithms
//
// MODIFY THIS FILE FOR FURTHER TESTS
//

#include <assert.h>

#include "Graph.h"
#include "GraphDominatingSets.h"
#include "IndicesSet.h"

// COLORS :)
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"

int main(void) {
  // Reading an undirected graph from file
  FILE* file = fopen("G_2.txt", "r");
  Graph* g02 = GraphFromFile(file);
  fclose(file);
  // Displaying in DOT format
  GraphDisplayDOT(g02);
  printf("\n");

  GraphCheckInvariants(g02);

  printf(GREEN"========== G02 =========="RESET"\n");

  // A full vertex set is a dominating set
  IndicesSet* full_set = IndicesSetCreateFull(GraphGetNumVertices(g02));
  printf("The full set is a dominating set? %d\n",
         GraphIsDominatingSet(g02, full_set));
  IndicesSetDestroy(&full_set);
  printf("\n");

  // Another set for testing domination
  IndicesSet* test_set = IndicesSetCreateEmpty(GraphGetNumVertices(g02));
  IndicesSetAdd(test_set, 0);
  IndicesSetAdd(test_set, 1);
  IndicesSetDisplay(test_set);
  printf("The test set is a dominating set? %d\n",
         GraphIsDominatingSet(g02, test_set));

  IndicesSetDestroy(&test_set);
  printf("\n");

  printf("Finding a MIN dominating set\n");
  IndicesSet* mdset = GraphComputeMinDominatingSet(g02);
  IndicesSetDisplay(mdset);
  printf("The subgraph defined by the MIN dominating set\n");
  Graph* mdset_graph = GraphGetSubgraph(g02, mdset);
  GraphDisplayDOT(mdset_graph);
  // The union of the mdset with the set of neighbors of each mdset vertex MUST
  // BE the full vertices set of the graph And the induced subgraph is the graph
  // itself
  // This could be a way for checking
  IndicesSetDestroy(&mdset);
  GraphDestroy(&mdset_graph);
  printf("\n");

  printf("Finding a MIN WEIGHT dominating set\n");
  IndicesSet* mwdset = GraphComputeMinWeightDominatingSet(g02);
  IndicesSetDisplay(mwdset);
  printf("The subgraph defined by the MIN WEIGHT dominating set\n");
  Graph* mwdset_graph = GraphGetSubgraph(g02, mwdset);
  GraphDisplayDOT(mwdset_graph);
  IndicesSetDestroy(&mwdset);
  GraphDestroy(&mwdset_graph);
  printf("\n");
  // Creating another graph

  printf(GREEN"========== G03 =========="RESET"\n");

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

  printf("Finding a MIN dominating set\n");
  mdset = GraphComputeMinDominatingSet(g03);
  IndicesSetDisplay(mdset);
  printf("The subgraph defined by the MIN dominating set\n");
  mdset_graph = GraphGetSubgraph(g03, mdset);
  GraphDisplayDOT(mdset_graph);

  // testing the GraphComputeMinWeightDominatingSet() function

  // Student made tests
  printf(GREEN"========== Student made tests ========="RESET"\n");

  // Create a new weighted graph
  Graph* g04 = GraphCreate(6, 0, 1);
  // VERTEX 0
  GraphAddWeightedEdge(g04, 0, 1, 1);
  GraphAddWeightedEdge(g04, 0, 2, 2);
  GraphAddWeightedEdge(g04, 0, 3, 4);
  // VERTEX 1
  GraphAddWeightedEdge(g04, 1, 2, 1);
  // VERTEX 2
  GraphAddWeightedEdge(g04, 2, 3, 1);
  GraphAddWeightedEdge(g04, 2, 5, 3);
  // VERTEX 3
  GraphAddWeightedEdge(g04, 3, 4, 1);
  GraphAddWeightedEdge(g04, 3, 5, 2);
  // VERTEX 4
  GraphAddWeightedEdge(g04, 4, 5, 1);
  GraphDisplayDOT(g04);

  printf(GREEN"========== Compute Min Weight Dominating Set G04 =========="RESET"\n");

  IndicesSet* minWeightSet = GraphComputeMinWeightDominatingSet(g04);
  IndicesSetDisplay(minWeightSet); 

  Graph* mdsG04 = GraphGetSubgraph(g04, minWeightSet);
  GraphDisplayDOT(mdsG04);
  GraphDestroy(&mdsG04);

  printf(GREEN"========== Compute Min Dominating Set G04 =========="RESET"\n");

  IndicesSet* minDSet = GraphComputeMinDominatingSet(g04);
  IndicesSetDisplay(minDSet);
  
  Graph* mwdsG04 = GraphGetSubgraph(g04, minDSet);
  GraphDisplayDOT(mwdsG04);
  GraphDestroy(&mwdsG04);

  printf(GREEN"========== Is Dominating Set G04 =========="RESET"\n");

  printf("The full set is a dominating set? %d\n",
         GraphIsDominatingSet(g04, minWeightSet));
  printf("The full set is a dominating set? %d\n",
         GraphIsDominatingSet(g04, minDSet));


  IndicesSetDestroy(&minWeightSet);
  IndicesSetDestroy(&minDSet);

  Graph* g01 = GraphCreate(6, 0, 0);
  GraphAddEdge(g01, 1, 2);
  GraphAddEdge(g01, 1, 4);
  GraphAddEdge(g01, 3, 4);

  printf(GREEN"========== G01 =========="RESET"\n");

  printf(GREEN"========== Compute Min Weight Dominating Set G01 =========="RESET"\n");

  minWeightSet = GraphComputeMinWeightDominatingSet(g01);
  IndicesSetDisplay(minWeightSet); 

  Graph* mdsG01 = GraphGetSubgraph(g01, minWeightSet);
  GraphDisplayDOT(mdsG01);
  GraphDestroy(&mdsG01);

  printf(GREEN"========== Compute Min Dominating Set G01 =========="RESET"\n");

  minDSet = GraphComputeMinDominatingSet(g01);
  IndicesSetDisplay(minDSet);
  
  Graph* mwdsG01 = GraphGetSubgraph(g01, minDSet);
  GraphDisplayDOT(mwdsG01);
  GraphDestroy(&mwdsG01);

  IndicesSetDestroy(&minWeightSet);
  IndicesSetDestroy(&minDSet);

  // The union of the mdset with the set of neighbors of each mdset vertex MUST
  // BE the full vertices set of the graph and the induced subgraph is the graph
  // itself
  // This could be a way for checking

  // POSSO PEDIR O CONNECTED DOMINATING SET --- POR CAUSA DA APLICAÇÃO NAS REDES

  IndicesSetDestroy(&mdset);
  GraphDestroy(&mdset_graph);
  printf("\n");

  // Clearing
  GraphDestroy(&g01);
  GraphDestroy(&g02);
  GraphDestroy(&g03);
  GraphDestroy(&g04);

  return 0;
}
