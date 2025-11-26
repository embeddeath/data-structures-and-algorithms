#pragma once
/***********************************************************
    File: AdjacencyListGraph.hpp
    Description: Adjacency List-based Graph interfaces.  
    Author: Miguel Márquez
    Date: 22/10/2025

************************************************************/
/***********************************************************
    Includes
************************************************************/
#include "Graph.hpp"
#include <vector>
#include <utility>

using std::vector;
using std::pair;  
/***********************************************************
    Type Definitions
************************************************************/

/***********************************************************
    Macro Definitions
************************************************************/

/***********************************************************
    External Interface Function Declarations
************************************************************/


/***********************************************************
    Global Variable Definitions
************************************************************/

/***********************************************************
    Class Declarations and Definitions
************************************************************/

/**
 * AdjacencyListGraph
 * Implements an undirected graph using an adjacency list.
 *
 * Provides methods to add/remove edges, check if an edge exists,
 * and print the list matrix. Inherits from the abstract Graph class.
 */


typedef struct DijkstraResult {
    vector<int> dist;
    vector<int> parent;
}DijkstraResult_t;

class AdjacencyListGraph : public Graph
{
private:
    vector<vector<pair<int,int>>> adjList;
    DijkstraResult_t DijkstraResult; 
    /* Search algorithm helpers*/
    void DFSPathUtil(int u, int target, vector<bool>& visited, vector<int>& parent, bool& found) const;
    bool BFSPathUtil(int start, int target, vector<int>& parent) const;
public:

    explicit AdjacencyListGraph(int vertices);

    void addEdge(int u, int v, int weight = 1) override;
    void addVertex() override;
    void removeEdge(int u, int v) override;
    void removeVertex(int v) override;
    bool isEdge(int u, int v) const override;
    int getOutDegree(int u) const override;
    vector<int> getOutAdjacency(int u) const override;
    void print() const override;
    void printDot(void) const override;
    void exportDot(string filename) const override;

    /* Search algorithms*/
    /* DFS*/
    vector<int> findPathDFS(int startVertex, int endVertex) const;
    /* Dijkstra*/
    DijkstraResult_t dijkstra(int source) const;
    vector<int> getPath(const vector<int> &parent, int source, int target) const;
    
    /* BFS*/
    vector<int> findPathBFS(int startVertex, int endVertex) const;
};



/***********************************************************
    Function Definitions
************************************************************/
