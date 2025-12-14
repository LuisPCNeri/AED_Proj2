//
// Algoritmos e Estruturas de Dados --- 2025/2026
//
// Joaquim Madeira - Nov 2025
//
// GraphDominatingSets - Computing Vertex Dominating Sets for UNDIRECTED graphs
//

// Student Name : Luís Pedro Costa Néri Correia
// Student Number : 125264
// Student Name : Guilherme Mendes Martins
// Student Number : 125260

/*** COMPLETE THE GraphIsDominatingSet FUNCTION ***/
/*** COMPLETE THE GraphMinDominatingSet FUNCTION ***/
/*** COMPLETE THE GraphMinWeightDominatingSet FUNCTION ***/

#include "GraphDominatingSets.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IndicesSet.h"
#include "instrumentation.h"

//
// TO BE COMPLETED
//
// Check if the given set is a dominating set for the graph
// Return 1 if true, or 0 otherwise
//
// A dominating set is a set of graph vertices such that every other
// graph vertex not in the set is adjacent to a graph vertex in the set
//
int GraphIsDominatingSet(const Graph* g, IndicesSet* vertSet) {
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);
  assert(IndicesSetIsEmpty(vertSet) == 0);

  //
  // TODO TO BE COMPLETED
  //
  
  // getting the set difference, vertSet - [g's vertexes] = all vertices in g that are not in vertSet
  IndicesSet* setsDifference = IndicesSetCreateCopy(GraphGetSetVertices(g));
  IndicesSetDifference(setsDifference, vertSet);

  // getting the set union
  IndicesSet* setsUnion = IndicesSetCreateCopy(GraphGetSetVertices(g));
  IndicesSetUnion(setsUnion, vertSet);

  uint16_t currentElement;
  while((currentElement = IndicesSetGetNextElem(setsDifference)) != -1) {
      // get vertexes adjacent to the current vertex
      IndicesSet* adjacentVertices = GraphGetSetAdjacentsTo(g, currentElement);

      uint16_t currentAdjElement;
      while((currentElement = IndicesSetGetNextElem(adjacentVertices)) != -1) {
        // if at least one of the adjacent vertexes is both in g and in vertSet, break this loop and move on  
        if (IndicesSetContains(setsUnion, currentAdjElement)) {
            break;
          }
      }
      // if the loop looked through all vertices and none was both in g and in vertSet:
      // the set is not dominating, return 0
      if (currentAdjElement == -1) {
        return 0;
      }
  }

  // else, the set IS dominant: return 1
  return 1;
}

//
// TO BE COMPLETED
//
// Compute a MIN VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the/a dominating set
//
IndicesSet* GraphComputeMinDominatingSet(const Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);

  //
  // TODO TO BE COMPLETED
  //

  // Change this according to your algorithm
  IndicesSet* result = IndicesSetCreateEmpty(GraphGetVertexRange(g));

  return result;
}

//
// TO BE COMPLETED
//
// Compute a MIN WEIGHT VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the dominating set
//
IndicesSet* GraphComputeMinWeightDominatingSet(const Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);

  //
  // TODO TO BE COMPLETED
  //

  // Change this according to your algorithm
  IndicesSet* result = IndicesSetCreateEmpty(GraphGetVertexRange(g));

  return result;
}
