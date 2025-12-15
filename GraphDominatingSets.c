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
// FUNCTION FOR CONVENIENCE
//
// calculate the sum of the weigths of all vertices in a graph
//
static double GraphCalculateTotalVertexWeight(const Graph* g) {
  double result = 0;
  double* vertexWeights = GraphComputeVertexWeights(g);

  for (int i = 0; i < sizeof(vertexWeights) / sizeof(double); i++) {
    result += vertexWeights[i];
  }

  return result;
}


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
  // if the set difference is an empty set, vertSet is a dominating set
  if (IndicesSetIsEmpty(setsDifference)) return 1;

  // getting the set union
  IndicesSet* setsUnion = IndicesSetCreateCopy(GraphGetSetVertices(g));
  IndicesSetUnion(setsUnion, vertSet);

  int currentElement = IndicesSetGetNextElem(setsDifference);
  while(currentElement != -1) {

    // get vertexes adjacent to the current vertex
    IndicesSet* adjacentVertices = GraphGetSetAdjacentsTo(g, currentElement);
    int currentAdjElement;

    currentAdjElement = IndicesSetGetNextElem(adjacentVertices);
    while((currentAdjElement = IndicesSetGetNextElem(adjacentVertices)) != -1) {
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

    currentElement = IndicesSetGetNextElem(setsDifference);
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
// A dominating set is a set of graph vertices such that every other
// graph vertex not in the set is adjacent to a graph vertex in the set
//
IndicesSet* GraphComputeMinDominatingSet(const Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);

  //
  // TODO TO BE COMPLETED
  //
  
  uint16_t n = GraphGetVertexRange(g);

  // best solution so far
  IndicesSet* result = IndicesSetCreateFull(n);

  // working subset
  IndicesSet* workingSubset = IndicesSetCreateEmpty(n);

  do {
    // ignore the set when empty 
    if (IndicesSetIsEmpty(workingSubset)) continue;

    // prune: no need to test if already worse than best
    if (IndicesSetGetNumElems(workingSubset) >= IndicesSetGetNumElems(result)) {
      continue;
    }

    if (GraphIsDominatingSet(g, workingSubset)) {
      IndicesSetDestroy(&result);
      result = IndicesSetCreateCopy(workingSubset);
    }

  } while (IndicesSetNextSubset(workingSubset));

  IndicesSetDestroy(&workingSubset);
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
  
  uint16_t n = GraphGetVertexRange(g);

  // best solution so far
  IndicesSet* result = IndicesSetCreateFull(n);

  // working subset
  IndicesSet* workingSubset = IndicesSetCreateEmpty(n);

  // vertex weights array
  // the indices are the IDs of each vertex
  double* vertexWeights = GraphComputeVertexWeights(g);

  // uses a static function defined at the top of this file
  // initially, we'll assume the dominating set with the least weight is the set of all vertices in the graph
  double lastTotalWeight = GraphCalculateTotalVertexWeight(g);

  do {
    // ignore the set when empty 
    if (IndicesSetIsEmpty(workingSubset)) continue;

    // iterate over the subset and calculate the total weight of its vertices
    double totalWeight = 0;
    int currentSubsetElement = IndicesSetGetNextElem(workingSubset);
    while (currentSubsetElement != -1) {
      totalWeight += vertexWeights[currentSubsetElement];

      currentSubsetElement = IndicesSetGetNextElem(workingSubset);
    }

    // prune: no need to test if already worse than best
    if (totalWeight >= lastTotalWeight) {
      continue;
    }

    if (GraphIsDominatingSet(g, workingSubset)) {
      IndicesSetDestroy(&result);
      result = IndicesSetCreateCopy(workingSubset);
    }

    lastTotalWeight = totalWeight;

  } while (IndicesSetNextSubset(workingSubset));

  IndicesSetDestroy(&workingSubset);
  return result;
}
