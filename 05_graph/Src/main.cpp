/***********************************************************
    File: main.cpp
    Author: Miguel Márquez
    Date: 8/14/2024

************************************************************/

/***********************************************************
    Includes
************************************************************/
#include <iostream>
#include "AdjacencyMatrixGraph.hpp"

using std::cout; 
using std::endl; 
/***********************************************************
    Type Definitions
************************************************************/

/***********************************************************
    Macro Definitions
************************************************************/

/***********************************************************
    Unit-Internal Function Declarations
************************************************************/

/***********************************************************
    Global Variable Definitions
************************************************************/

/***********************************************************
    Class Declarations and Definitions
************************************************************/

/***********************************************************
    Function Definitions
************************************************************/

void test1()
{
    // Create a graph with 3 vertices (0,1,2)
    AdjacencyMatrixGraph g(3);

    // Add some initial edges
    g.addEdge(0, 1);
    g.addEdge(1, 2);

    cout << "Initial adjacency matrix:\n";
    g.print();

    // Dynamically add a new vertex (vertex 3)
    g.addVertex();
    cout << "\nAfter adding vertex 3:\n";
    g.print();

    // Add an edge to the new vertex
    g.addEdge(2, 3, 2);
    cout << "\nAfter adding edge 2-3 with weight 2:\n";
    g.print();

    // Print in DOT format
    cout << "\nDOT format output:\n";
    g.exportDot();

}

void circularGraphTest()
{
    // Create a graph with 4 vertices (0,1,2,3)
    AdjacencyMatrixGraph g(4);

    // Add edges to form a circular graph
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 0);

    // Print adjacency matrix
    cout << "Circular graph adjacency matrix:\n";
    g.print();

    // Generate DOT file
    g.exportDot();

    cout << "\n'graph.dot' created. Use Graphviz to generate PDF.\n";

}

int main (int argc, char* argv[])
{
    circularGraphTest();
    return 0;
}
