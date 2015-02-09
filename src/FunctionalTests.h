#ifndef FUNCTIONAL_TESTS_H
#define	FUNCTIONAL_TESTS_H

#include <vector>
#include "DataStructures.h"
#include "PriorityQueue.h"
#include "A_Star.h"
#include "HeuristicFunctions.h"
#include <functional>


///\brief: Generates a fixed directed graph with size Max 10 nodes
///
/// This function generates a directed Graph with maximal 10 nodes.
/// The graph is always the same, the last node is not connected.
std::vector<Node> generateFixedDirectedGraph(size_t nodeCardinality)
{
    if(nodeCardinality>10)nodeCardinality=10;
    std::vector<Node> res(nodeCardinality);
    switch (nodeCardinality)
    {
        case 10:
            res[9].ID=10;
        case 9:
            res[8].ID=9;
            res[0].addEdge(5,&res[8]);
            res[7].addEdge(1,&res[8]);
            res[8].addEdge(7,&res[2]);
        case 8:
            res[7].ID=8;
            res[2].addEdge(2,&res[7]);
            res[7].addEdge(8,&res[6]);
        case 7:
            res[6].ID=7;
            res[3].addEdge(3,&res[6]);
            res[6].addEdge(1,&res[2]);
        case 6:
            res[5].ID=6;
            res[5].addEdge(2,&res[3]);
            res[4].addEdge(4,&res[5]);
        case 5:
            res[4].ID=5;
            res[3].addEdge(8,&res[4]);
            res[1].addEdge(9,&res[4]);
        case 4:
            res[3].ID=4;
            res[1].addEdge(4,&res[3]);
            res[2].addEdge(10,&res[3]);
        case 3:
            res[2].ID=3;
            res[0].addEdge(3,&res[2]);
            res[1].addEdge(6,&res[2]);
        case 2:
            res[1].ID=2;
            res[0].addEdge(1,&res[1]);
        case 1:
            res[0].ID=1;
        default:
            break;
    }
    return res;
}

std::vector<Node> generateFixedUndirectedGraph(size_t nodeCardinality)
{
    if(nodeCardinality>10)nodeCardinality=10;
    std::vector<Node> res(nodeCardinality);
    switch (nodeCardinality)
    {
        case 10:
            res[9].ID=10;
        case 9:
            res[8].ID=9;
            res[0].addUndirectedEdge(5,&res[8]);
            res[7].addUndirectedEdge(1,&res[8]);
            res[8].addUndirectedEdge(7,&res[2]);
        case 8:
            res[7].ID=8;
            res[2].addUndirectedEdge(2,&res[7]);
            res[7].addUndirectedEdge(8,&res[6]);
        case 7:
            res[6].ID=7;
            res[3].addUndirectedEdge(3,&res[6]);
            res[6].addUndirectedEdge(1,&res[2]);
        case 6:
            res[5].ID=6;
            res[5].addUndirectedEdge(2,&res[3]);
            res[4].addUndirectedEdge(4,&res[5]);
        case 5:
            res[4].ID=5;
            res[3].addUndirectedEdge(8,&res[4]);
            res[1].addUndirectedEdge(9,&res[4]);
        case 4:
            res[3].ID=4;
            res[1].addUndirectedEdge(4,&res[3]);
            res[2].addUndirectedEdge(10,&res[3]);
        case 3:
            res[2].ID=3;
            res[0].addUndirectedEdge(3,&res[2]);
            res[1].addUndirectedEdge(6,&res[2]);
        case 2:
            res[1].ID=2;
            res[0].addUndirectedEdge(1,&res[1]);
        case 1:
            res[0].ID=1;
        default:
            break;
    }
    return res;
}

void TestFixedDirectedGraph(std::function<size_t(Node*,Node*)> heuristic)
{
    std::vector<Node> graph=generateFixedDirectedGraph(10);

    std::vector<PathEdge> res=A_Star(&graph[0],&graph[1],heuristic);
    ASSERT_EQ(std::get<0>(res[0]),1);

    res=A_Star(&graph[0],&graph[2],heuristic);
    ASSERT_EQ(std::get<0>(res[0]),3);

    res=A_Star(&graph[0],&graph[3],heuristic);
    ASSERT_EQ(std::get<0>(res[0]),5);

    res=A_Star(&graph[0],&graph[4],heuristic);
    ASSERT_EQ(std::get<0>(res[0]),10);

    res=A_Star(&graph[0],&graph[5],heuristic);
    ASSERT_EQ(std::get<0>(res[0]),14);

    res=A_Star(&graph[0],&graph[9],heuristic);
    ASSERT_EQ(res.size(),0);
}

void TestFixedUndirectedGraph(std::function<size_t(Node*,Node*)> heuristic)
{
    std::vector<Node> graph=generateFixedUndirectedGraph(10);

    std::vector<PathEdge> res=A_Star(&graph[0],&graph[1],heuristic);
    ASSERT_EQ(std::get<0>(res[0]),1);

    res=A_Star(&graph[0],&graph[2],heuristic);
    ASSERT_EQ(std::get<0>(res[0]),3);

    res=A_Star(&graph[0],&graph[3],heuristic);
    ASSERT_EQ(std::get<0>(res[0]),5);

    res=A_Star(&graph[0],&graph[4],heuristic);
    ASSERT_EQ(std::get<0>(res[0]),10);

    res=A_Star(&graph[0],&graph[5],heuristic);
    ASSERT_EQ(std::get<0>(res[0]),7);

    res=A_Star(&graph[0],&graph[9],heuristic);
    ASSERT_EQ(res.size(),0);
}

TEST (A_StarTest,A_StarDijkstraFunctionalTestFixedDirectedGraph)
{
    TestFixedDirectedGraph(DijkstraHeuristic);
    TestFixedDirectedGraph(OneNodeNeighborHeuristic);
    TestFixedDirectedGraph(TwoNodesNeighborHeuristic);
}

TEST (A_StarTest,A_StarDijkstraFunctionalTestFixedUndirectedGraph)
{
    TestFixedUndirectedGraph(DijkstraHeuristic);
    TestFixedUndirectedGraph(OneNodeNeighborHeuristic);
    TestFixedUndirectedGraph(TwoNodesNeighborHeuristic);
}

#endif	/* DIJKSTRATESTS_H */
