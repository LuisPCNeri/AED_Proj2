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

#define ITERCOUNTER InstrCount[0]
#define COMPCOUNT InstrCount[1]

#define RESET "\033[0m"
#define RED "\033[31m"

//
// FUNCTION FOR CONVENIENCE
//
// calculate the sum of the weigths of all vertices in a graph
//
static double GraphCalculateTotalVertexWeight(const Graph* g) {
  double result = 0;
  double* vertexWeights = GraphComputeVertexWeights(g);

  for (unsigned int i = 0; i < GraphGetNumVertices(g); i++) {
    result += vertexWeights[i];
  }

  // Free memory of array
  free(vertexWeights);

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

  IndicesSet* gSetVertices = GraphGetSetVertices(g);

  IndicesSet* setsDifference = IndicesSetCreateCopy(gSetVertices);
  IndicesSetDifference(setsDifference, vertSet);
  
  InstrName[0] = "itercounter";
  InstrName[1] = "compcount";
  // if the set difference is an empty set, vertSet is a dominating set
  if (IndicesSetIsEmpty(setsDifference)){

    // Clean Up before returning
    IndicesSetDestroy(&gSetVertices);
    IndicesSetDestroy(&setsDifference);

    return 1;
  }

  // getting the set union
  IndicesSet* setsUnion = IndicesSetCreateCopy(gSetVertices);
  IndicesSetUnion(setsUnion, vertSet);

  int currentElement = IndicesSetGetNextElem(setsDifference);
  while(currentElement != -1) {

    // get vertexes adjacent to the current vertex
    IndicesSet* adjacentVertices = GraphGetSetAdjacentsTo(g, currentElement);
    int currentAdjElement;

    // There are no adjacent vertices so for all dominating sets this vertex is A MUST
    if(IndicesSetIsEmpty(adjacentVertices)) {
      if(IndicesSetContains(vertSet, currentElement)) break;

      // Clean Up before returning
      // The set we were checking if it was dominating did NOT contain the vertex with no edges
      // So it cannot be a dominating set
      IndicesSetDestroy(&adjacentVertices);
      IndicesSetDestroy(&setsDifference);
      IndicesSetDestroy(&gSetVertices);
      IndicesSetDestroy(&setsUnion);
      return 0;
    }

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

      // Clean Up before returning
      IndicesSetDestroy(&adjacentVertices);
      IndicesSetDestroy(&setsDifference);
      IndicesSetDestroy(&gSetVertices);
      IndicesSetDestroy(&setsUnion);
      return 0;
    }

    currentElement = IndicesSetGetNextElem(setsDifference);

    // Destroy the indices set for the ajacent vertexes used for this iteration before going to the next
    IndicesSetDestroy(&adjacentVertices);
  }

  // Free indicesSets used to help during the function run time
  IndicesSetDestroy(&setsDifference);
  IndicesSetDestroy(&gSetVertices);
  IndicesSetDestroy(&setsUnion);
  

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

  // Reset macros
  COMPCOUNT = 0;
  ITERCOUNTER = 0;
  
  uint16_t n = GraphGetVertexRange(g);

  // best solution so far
  IndicesSet* result = IndicesSetCreateFull(n);

  // working subset
  IndicesSet* workingSubset = IndicesSetCreateEmpty(n);

  do {
    ITERCOUNTER++;
    // ignore the set when empty 
    COMPCOUNT++;
    if (IndicesSetIsEmpty(workingSubset)) continue;

    COMPCOUNT++;
    // prune: no need to test if already worse than best
    if (IndicesSetGetNumElems(workingSubset) >= IndicesSetGetNumElems(result)) {
      continue;
    }

    COMPCOUNT++;
    if (GraphIsDominatingSet(g, workingSubset)) {
      IndicesSetDestroy(&result);
      result = IndicesSetCreateCopy(workingSubset);
    }

  } while (IndicesSetNextSubset(workingSubset));

  IndicesSetDestroy(&workingSubset);

  printf(RED"===== MIN DOMINATING SET ====="RESET"\n");
  printf(RED"ITERATION COUNT: %lu"RESET"\n", ITERCOUNTER);
  printf(RED"COMPARISONS COUNT: %lu"RESET"\n", COMPCOUNT);

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

  // Reset macros
  COMPCOUNT = 0;
  ITERCOUNTER = 0;
  
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
    ITERCOUNTER++;

    COMPCOUNT++;
    // ignore the set when empty 
    if (IndicesSetIsEmpty(workingSubset)) continue;

    // iterate over the subset and calculate the total weight of its vertices
    double totalWeight = 0;
    int currentSubsetElement = IndicesSetGetFirstElem(workingSubset);
    while (currentSubsetElement != -1) {
      COMPCOUNT++;
      totalWeight += vertexWeights[currentSubsetElement];

      currentSubsetElement = IndicesSetGetNextElem(workingSubset);
    }

    COMPCOUNT++;
    // prune: no need to test if already worse than best
    if (totalWeight >= lastTotalWeight) {
      continue;
    }

    COMPCOUNT++;
    if (GraphIsDominatingSet(g, workingSubset)) {
      IndicesSetDestroy(&result);
      result = IndicesSetCreateCopy(workingSubset);

      lastTotalWeight = totalWeight;
    }

  } while (IndicesSetNextSubset(workingSubset));

  free(vertexWeights);
  IndicesSetDestroy(&workingSubset);

  printf(RED"===== MIN WEIGHT DOMINATING SET ====="RESET"\n");
  printf(RED"ITERATION COUNT: %lu"RESET"\n", ITERCOUNTER);
  printf(RED"COMPARISONS COUNT: %lu"RESET"\n", COMPCOUNT);

  return result;
}
