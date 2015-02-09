#ifndef PERFORMANCETESTS_H_INCLUDED
#define PERFORMANCETESTS_H_INCLUDED

#include <vector>
#include "DataStructures.h"
#include "A_Star.h"
#include "HeuristicFunctions.h"
#include <functional>
#include <random>
#include <string>

#include <assert.h>

#include "cMeter.h"
#include "cMeterDataDump.h"

#define MIN_SIZE_GRAPH 10
#define MAX_SIZE_GRAPH 1000
#define MIN_SIZE_GRID_GRAPH 10
#define MAX_SIZE_GRID_GRAPH 15000
#define BATCH_SIZE 5
#define MIN_EDGE_COST 1
#define MAX_EDGE_COST 5
#define EDGE_DENSITY 0.5f
#define EDGE_VARIATION 0.6f

#define _CPU_CYCLES_MEASUREMENT "CPU_CYCLES"
#define VECTOR_BASED_PRIORITY_QUEUE "vector_based_pQueue"

std::vector<Node> GenerateDirectedRandomGraph(size_t graphSize, size_t minEdgeCost=1, size_t maxEdgeCost=1, float EdgeDensity=0.1f, float variability=0.5f, int seed=42)
{
    assert(variability>=0.0f && variability<=1.0f);
    assert(EdgeDensity>=0.0f && EdgeDensity<=1.0f);
    assert(minEdgeCost<=maxEdgeCost);

    std::vector<Node> res(graphSize);
    size_t medianEdgeCardinality=graphSize*EdgeDensity;
    size_t edgeNumberVariation=medianEdgeCardinality*variability;

    std::mt19937 gen;
    gen.seed(seed);
    std::uniform_int_distribution<> EdgeDis(0, edgeNumberVariation);
    std::uniform_int_distribution<> NodeDis(0, graphSize-1);
    std::uniform_int_distribution<> PosNegDis(0,1);
    std::uniform_int_distribution<> DistDis(minEdgeCost,maxEdgeCost);

    for (size_t i=0; i<graphSize;i++)
    {
        res[i].ID=i;
        size_t edges=EdgeDis(gen);
        int posNeg=PosNegDis(gen);
        if(!posNeg) posNeg=-1;
        edges=posNeg*edges+medianEdgeCardinality; //this gives us the number of edges for the node i
        for(size_t j=0;j<edges;j++)
        {
	    size_t targetNodeIdx=NodeDis(gen);
            res[i].addEdge(DistDis(gen),&res[targetNodeIdx]);
        }
    }

    return res;
}

#define RND_NUMBER_GRANULARITY 1000000

std::vector<bool> generateWalls(size_t width, size_t height, float wallFrequency=0.01f, int seed=42)
{
    std::mt19937 gen;
    gen.seed(seed);
    std::uniform_int_distribution<> EdgeDis(0, RND_NUMBER_GRANULARITY-1);

    std::vector<bool> res(width*height);
    for(size_t y=0;y<height;y++)
        for(size_t x=0;x<width;x++)
            if(EdgeDis(gen) > (RND_NUMBER_GRANULARITY*wallFrequency))
                res[x+y*width]=false;
            else
                res[x+y*width]=true;
    return res;
}

///\brief: generates a gridGraph with random walls
std::vector<Node> GenerateRandomGrid(size_t width, size_t height, float wallFrequency=0.01f, int seed=42)
{
    assert(wallFrequency>=0.0f && wallFrequency<1.0f);

    std::vector<bool> walls=generateWalls(width,height,wallFrequency,seed);
    std::vector<Node> res(width*height);
    for(size_t y=0;y<height;y++)
    {
        for(size_t x=0;x<width;x++)
        {
            size_t idx=x+y*width;
            res[idx].ID=idx;
            if(walls[idx])  continue;
            if(x!=0 && !walls[idx-1]) 
	      res[idx].addUndirectedEdge(1,&res[idx-1]);
            if(x!=width-1 && !walls[idx+1]) 
	      res[idx].addUndirectedEdge(1,&res[idx+1]);
            if(y!=0 && !walls[idx-width]) 
	      res[idx].addUndirectedEdge(1,&res[idx-width]);
            if(y!=height-1 && !walls[idx+width]) 
	      res[idx].addUndirectedEdge(1,&res[idx+width]);
        }
    }
    return res;
}

///\brief: generates a filename for the performance data dump
std::string generateFileName(std::string MeasurementType, std::string attributes, std::string algorithm)
{
  std::string res=MeasurementType+"_"+attributes+"_"+algorithm;
  return res;

}

template<typename T>
void PerformanceTestCycle(std::string heuristicName,std::function<size_t(Node*,Node*)> heuristic,cMeterDataDump<T> &dataDump)
{
    dataDump.setFilename(generateFileName(_CPU_CYCLES_MEASUREMENT,VECTOR_BASED_PRIORITY_QUEUE,heuristicName));
    std::vector<PathEdge> res;
    for (size_t i=MIN_SIZE_GRAPH; i<MAX_SIZE_GRAPH; i+=((i-MIN_SIZE_GRAPH)/10)+1)
    {
        for (size_t j=0;j<BATCH_SIZE;j++)
            {
                std::vector<Node> graph=GenerateDirectedRandomGraph(i,MIN_EDGE_COST,MAX_EDGE_COST,EDGE_DENSITY,EDGE_VARIATION);
                dataDump.StartMeter();
                res=A_Star(&graph[0],&graph[i-1],heuristic);
                dataDump.StopMeter();
            }
        dataDump.StoreBatch();
    }
    dataDump.dumpData();
    dataDump.resetData();
}

#include <chrono>

TEST (A_StarTest,A_StarDirectedGraphPerformanceTest)
{
     std::function<uint64_t(void)> stopWatchFunc =[] (){
      auto now = std::chrono::high_resolution_clock::now();
      uint64_t nanos = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count());
      return nanos;

    };

    cMeter<uint64_t> timeMeter(stopWatchFunc);

    timeMeter.setUnitName("time");
    timeMeter.setUnitSymbol("ns");
    cMeterDataDump<uint64_t> timeDataDump(&timeMeter);

    PerformanceTestCycle<uint64_t>("Dijkstra",DijkstraHeuristic,timeDataDump);
    PerformanceTestCycle<uint64_t>("OneNodeNeighborHeuristic",OneNodeNeighborHeuristic,timeDataDump);
    PerformanceTestCycle<uint64_t>("TwoNodesNeighborHeuristic",TwoNodesNeighborHeuristic,timeDataDump);
}

template<typename T>
void PerformanceGridGraphTestCycle(std::string heuristicName,std::function<size_t(Node*,Node*)> heuristic,cMeterDataDump<T> &dataDump)
{
    dataDump.setFilename(generateFileName(_CPU_CYCLES_MEASUREMENT,VECTOR_BASED_PRIORITY_QUEUE,heuristicName));
    std::vector<PathEdge> res;
    for (size_t i=MIN_SIZE_GRID_GRAPH; i<MAX_SIZE_GRID_GRAPH; i+=((i-MIN_SIZE_GRID_GRAPH)/10)+1)
    {
        size_t width=sqrt(i);
        size_t height=i/width;
        for (size_t j=0;j<BATCH_SIZE;j++)
            {
                std::vector<Node> graph=GenerateRandomGrid(width,height);
                dataDump.StartMeter();
                res=A_Star(&graph[(height-1)*width],&graph[width-1],heuristic);
                dataDump.StopMeter();
            }
        dataDump.StoreBatch();
    }
    dataDump.dumpData();
    dataDump.resetData();
}

TEST (A_StarTest,A_StarGridGraphPerformanceTest)
{
     std::function<uint64_t(void)> stopWatchFunc =[] (){
      auto now = std::chrono::high_resolution_clock::now();
      uint64_t nanos = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count());
      return nanos;};

    cMeter<uint64_t> timeMeter(stopWatchFunc);

    timeMeter.setUnitName("time");
    timeMeter.setUnitSymbol("ns");
    cMeterDataDump<uint64_t> timeDataDump(&timeMeter);

    PerformanceGridGraphTestCycle<uint64_t>("Dijkstra_grid",DijkstraHeuristic,timeDataDump);
    PerformanceGridGraphTestCycle<uint64_t>("Euclidean_grid",EuclideanHeuristic,timeDataDump);
}
#endif // PERFORMANCETESTS_H_INCLUDED
