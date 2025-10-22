#pragma once
/***********************************************************
    File: AdjacencyMatrixGraph.hpp
    Description: Adjacency Matrix-based Graph interfaces.  
    Author: Miguel Márquez
    Date: 18/10/2025

************************************************************/
/***********************************************************
    Includes
************************************************************/
#include "Graph.hpp"
#include <vector>

using std::vector; 
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
 * AdjacencyMatrixGraph
 * Implements an undirected graph using an adjacency matrix.
 *
 * Provides methods to add/remove edges, check if an edge exists,
 * and print the adjacency matrix. Inherits from the abstract Graph class.
 */
class AdjacencyMatrixGraph : public Graph
{
    private:
        vector<vector<int>> matrix; 
    
    public: 
        explicit AdjacencyMatrixGraph(int vertices); 

        /* override ensures we are implementing a virtual function from Graph*/
        void addEdge(int u, int v, int weight = 1) override; 
        void addVertex(void) override;
        void removeEdge(int u, int v) override;
        void removeVertex(int v) override;  
        bool isEdge(int u, int v) const override; /* const prevents the method to modify the object*/
        int getOutDegree(int u) const override; 
        vector<int> getOutAdjacency(int u) const override; 
        void print(void) const override; 
        void printDot(void) const override;
        void exportDot(void) const override; 
    
};
/***********************************************************
    Function Definitions
************************************************************/
