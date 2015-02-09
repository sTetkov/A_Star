#ifndef HEURISTICFUNCTIONS_H_INCLUDED
#define HEURISTICFUNCTIONS_H_INCLUDED

#include "DataStructures.h"

///\brief: returns 0 every time
size_t DijkstraHeuristic(Node*,Node*);

///\brief: if the targetNode is a neighbor returns 1, 2 otherwise
size_t OneNodeNeighborHeuristic(Node*,Node*);

///\brief: if the targetNode is a neighbor returns 1, if it is the neighbor of a neighbor 2,
///        otherwise it returns 3
size_t TwoNodesNeighborHeuristic(Node*,Node*);

///\brief: Heuristic for a grid
///
/// Returns the euclidean distance and considers the target node the one in
/// the upper right corner, meaning that the width of the grid is the ID of
/// the target node.
size_t EuclideanHeuristic(Node*,Node*);

#endif // HEURISTICFUNCTIONS_H_INCLUDED
