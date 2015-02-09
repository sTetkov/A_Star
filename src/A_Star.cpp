#include "A_Star.h"
#include "PriorityQueue.h"
#include "Set.h"
#include "PriorityQueue.cpp"
#include "Set.cpp"

///\brief: returns the complete path form the PathEdge p to the starting node
std::vector<PathEdge> getPathVector(PathEdge p,Set<PathEdge> closedSet)
{
    std::vector<PathEdge> res;
    Node* node=std::get<2>(p);
    do
    {
        p=closedSet.getElement(PathEdge(0,NULL,node));
        res.push_back(p);
	node=std::get<1>(p);
    } while(node!=NULL);

    return res;
}

///\brief: A* algorithm, given a starting node, a target node and a heuristic. If the heuristic
///        returns 0 everytime it is equivalent to Dijkstra's algorithm.
std::vector<PathEdge> A_Star(Node* startNode,Node* targetNode,std::function<size_t(Node*,Node*)> heuristic)
{
    ///two nodes are the same if they have the same ID
    std::function<bool(PathEdge,PathEdge)> isEqual=[](PathEdge a,PathEdge b){ return std::get<2>(a)->ID==std::get<2>(b)->ID;};
    ///If path to a node is shorter, use new path
    std::function<bool(PathEdge,PathEdge)> isToUpdate=[](PathEdge newVal,PathEdge oldVal){return std::get<0>(newVal) < std::get<0>(oldVal);};
    PriorityQueue<PathEdge,size_t> pQueue;
    pQueue.setIsEqualFunction(isEqual);
    pQueue.setIsToUpdateFunction(isToUpdate);

    Set<PathEdge> closedSet;
    closedSet.setIsEqualFunction(isEqual);

    pQueue.AddElement(PathEdge(0,NULL,startNode),heuristic(startNode,targetNode));

    while(!pQueue.isEmpty())
    {
        PathEdge p=pQueue.Pop();
        closedSet.AddElement(p);
        if(std::get<2>(p)->ID==targetNode->ID)
            return getPathVector(p,closedSet);

        for(size_t i=0; i<std::get<2>(p)->Edges.size();i++)
        {
            if(!closedSet.Contains(PathEdge(0,NULL,std::get<2>(p)->Edges[i].second)))
            {
                ///Length of the path + lenght of the last edge + heuristic estimation
                size_t pLenght=std::get<0>(p)+std::get<2>(p)->Edges[i].first+heuristic(std::get<2>(p)->Edges[i].second,targetNode);
                ///If we find a shorter path we update the existing nodes
                pQueue.AddOrUpdateElement(PathEdge(std::get<0>(p)+std::get<2>(p)->Edges[i].first,
                                                   std::get<2>(p),
                                                   std::get<2>(p)->Edges[i].second),pLenght);
            }
        }
    }

    return std::vector<PathEdge>(0);
}
