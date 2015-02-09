#ifndef DATASTRUCTURES_H_INCLUDED
#define DATASTRUCTURES_H_INCLUDED

#include <vector>
#include <cstddef>
#include <tuple>

struct Node;

///\brief: Definition of an Edge as a pair composed from distance and target Node
typedef std::pair<size_t,Node*> Edge;

///\brief: A pathEdge is a tuple containing the total distance from the startNode, the parentNode and the current TargetNode
typedef std::tuple<size_t,Node*,Node*> PathEdge;

///\brief: A node has an unique ID and a std::vector of edges indicating the reachable nodes
struct Node
{
    size_t ID;
    std::vector<Edge> Edges;

    bool operator==(Node* n){return ID==n->ID;}
    //if adding an already existing edge, it updates only the distance
    void addEdge(size_t distance,Node* target)
    {
        for(size_t i=0;i<Edges.size();i++)
            if(Edges[i].second==target)
            {
                Edges[i].first=distance;
                return;
            }
        Edges.push_back(Edge(distance,target));
    }

    //if adding an already existing edge, it updates only the distance
    void addUndirectedEdge(size_t distance,Node* target)
    {
        for(size_t i=0;i<Edges.size();i++)
            if(Edges[i].second==target)
            {
                Edges[i].first=distance;
                target->addEdge(distance,this);
                return;
            }
        Edges.push_back(Edge(distance,target));
        target->addEdge(distance,this);
    }
};

#endif // DATASTRUCTURES_H_INCLUDED
