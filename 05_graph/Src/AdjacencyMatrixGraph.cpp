/***********************************************************
    File: AdjacencyMatrixGraph.cpp
    Description: Adjacency Matrix-based Graph interfaces.
    Author: Miguel Márquez
    Date: 18/10/2025

************************************************************/

/***********************************************************
    Includes
************************************************************/
#include "AdjacencyMatrixGraph.hpp"
#include <iostream>
#include <fstream>
#include <string>

using std::vector; 
using std::cout; 
using std::endl;
using std::ofstream;
using std::string; 
using std::cerr;
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

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int vertices)

    :   Graph(vertices), 
        /* vector<int>(vertices, 0) -> creates a 1d vector of integers with vertices elements and inits them to zero*/
        /* Outer part constructs matrix, a vector of vectors, with vertices number of rows and each row is a copy of vector<int>(vertices, 0) */
        matrix(vertices, vector<int>(vertices, 0))
{
    /* Everything is already initialized, no need to do anything.*/
}

void AdjacencyMatrixGraph::addEdge(int u, int v, int weight)
{
    matrix[u][v] = weight; 
    matrix[v][u] = weight; 
}

void AdjacencyMatrixGraph::addVertex()
{

    numVertices++; 

    /* Add a new row with zeroes*/
    matrix.push_back(vector<int>(numVertices, 0)); 

    /* Add a new column with zero to each existing row*/
    for (int i = 0; i < numVertices - 1; i++)
    {
        matrix[i].push_back(0);
    }
}

void AdjacencyMatrixGraph::removeEdge(int u, int v)
{
    matrix[u][v] = 0; 
    matrix[v][u] = 0; 
}

void AdjacencyMatrixGraph::removeVertex(int v)
{
    if (v < 0 || v >= numVertices)
    {
        cerr << "Error: Vertex " << v << "does not exist. \n"; 
    }

    /* Remove row*/
    matrix.erase(matrix.begin() + v);

    /* Remove column */
    for(unsigned int i = 0; i < matrix.size(); i++)
    { 
        matrix[i].erase(matrix[i].begin() + v);
        
    }

    numVertices--; 
}

bool AdjacencyMatrixGraph::isEdge(int u, int v) const
{
    return matrix[u][v] != 0; 
}

int AdjacencyMatrixGraph::getOutDegree(int u) const
{
    if (u < 0 || u >= numVertices)
    {
        cerr << "Error: Vertex " << u << " does not exist.\n";
        return -1;
    }

    int degree = 0;

    for (int v = 0; v < numVertices; v++)
    {
        if (matrix[u][v] != 0)
        {
            degree++;
        }
    }
    return degree;
}

/* Return vertexes that are directly connected.*/
vector<int> AdjacencyMatrixGraph::getOutAdjacency(int u) const
{
    if (u < 0 || u >= numVertices)
    {
        cerr << "Error: Vertex " << u << " does not exist.\n";
        return {};
    }

    std::vector<int> adjacency;

    for (int v = 0; v < numVertices; v++)
    {
        if (matrix[u][v] != 0)
        {
            adjacency.push_back(v);
        }
    }

    return adjacency;
}

void AdjacencyMatrixGraph::print() const
{
    cout << "Adjacency Matrix" << endl; 
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            cout << matrix[i][j] << " "; 
        }
        cout << endl; 
    }
    
}

void AdjacencyMatrixGraph::printDot() const 
{
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = i; j < numVertices; j++) /* j starts at i to avoid duplicates*/
        {
            if (matrix[i][j] != 0) /* For unidirected graph matrix[i][j] == matrix[j][i], therefore we can iterate the upper triangle*/
            {
                cout << "   " << i << " -- " << j; 
                if (matrix[i][j] != 1)
                {
                    cout << " [label= " << matrix[i][j] << "]"; 
                }
                cout << ";" << endl;    
            }
        }
    }
}

void AdjacencyMatrixGraph::exportDot() const {

    string filename = "graph.dot";
    
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    file << "graph G {\n";

    for (int i = 0; i < numVertices; i++) {
        for (int j = i; j < numVertices; j++) {
            if (matrix[i][j] != 0) {
                file << "    " << i << " -- " << j;
                if (matrix[i][j] != 1) {
                    file << " [label=" << matrix[i][j] << "]";
                }
                file << ";\n";
            }
        }
    }

    file << "}\n";
    file.close();

    cout << "DOT file written to " << filename << endl;
}
/***********************************************************
    Function Definitions
************************************************************/



