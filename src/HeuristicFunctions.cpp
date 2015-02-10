#include "HeuristicFunctions.h"
#include <cmath>

size_t DijkstraHeuristic(Node* n, Node* target)
{
    return 0;
}

size_t OneNodeNeighborHeuristic(Node* n, Node* target)
{
    for(size_t i=0; i<n->Edges.size();i++)
        if(n->Edges[i].second==target)
            return 1;
    return 2;
}

size_t TwoNodesNeighborHeuristic(Node* n, Node* target)
{
    for(size_t i=0; i<n->Edges.size();i++)
        if(n->Edges[i].second==target)
            return 1;
        else
            for(size_t j=0;j<n->Edges[i].second->Edges.size();j++)
                if(n->Edges[i].second->Edges[j].second==target)
                    return 2;
    return 3;
}

size_t EuclideanHeuristic(Node* node,Node* targetNode)
{
    size_t xDist=(node->ID/targetNode->ID)*10;
    size_t yDist=(targetNode->ID-(node->ID%targetNode->ID))*10;
    return floor(sqrt(xDist*xDist+yDist*yDist));
}

size_t EuclideanHeuristic2(Node* node,Node* targetNode)
{
    size_t xDist=(node->ID/targetNode->ID)*10;
    size_t yDist=(targetNode->ID-(node->ID%targetNode->ID))*10;
    return xDist+yDist;
}
