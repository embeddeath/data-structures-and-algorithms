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
#include "AdjacencyListGraph.hpp"
#include "RyanAirGraph.hpp"
#include "fstream"


using std::cout; 
using std::endl; 
using std::cerr; 
using std::fstream; 
using std::string; 
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
    g.addEdge(0, 1, 3);
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

void testAdjacencyMatrixGraph()
{
    cout << "=== Graph Test Start ===" << endl;

    // Create graph with 4 vertices
    AdjacencyMatrixGraph g(4);

    // Add some edges
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 2);

    cout << "\nInitial graph:" << endl;
    g.print();

    // Test adjacency
    cout << "\nIs there an edge between 0 and 2? " 
         << (g.isEdge(0, 2) ? "Yes" : "No") << endl;

    cout << "Is there an edge between 2 and 3? " 
         << (g.isEdge(2, 3) ? "Yes" : "No") << endl;

    // Test out-degree and adjacency list
    cout << "\nOut-degree of vertex 0: " << g.getOutDegree(0) << endl;

    auto adj = g.getOutAdjacency(0);

    cout << "Out-adjacency of vertex 0: ";
    for (int v : adj)
        cout << v << " ";
    cout << endl;

    // Add a new vertex
    cout << "\nAdding new vertex (vertex 4)..." << endl;
    g.addVertex();
    g.addEdge(2, 4, 5);
    g.print();

    // Remove an edge
    cout << "\nRemoving edge (0, 2)..." << endl;
    g.removeEdge(0, 2);
    g.print();

    // Remove a vertex
    cout << "\nRemoving vertex 1..." << endl;
    g.removeVertex(1);
    g.print();

    // Export to DOT file
    cout << "\nExporting to DOT..." << endl;
    g.exportDot();

    cout << "=== Graph Test End ===" << endl;
}

void testAdjacencyListGraph() {
    cout << "=== TEST DE GRAFO ===" << endl;

    // 1. Crear grafo con 4 vértices
    AdjacencyListGraph g(4);

    // 2. Añadir aristas
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 1);

    cout << "\nGrafo inicial:" << endl;
    g.print();

    // 3. Revisar si existen aristas
    cout << "\nRevisar aristas:" << endl;
    cout << "0-1? " << g.isEdge(0, 1) << endl;
    cout << "1-3? " << g.isEdge(1, 3) << endl;

    // 4. Obtener grado de salida
    for (int i = 0; i < 4; i++)
        cout << "Out-degree de " << i << ": " << g.getOutDegree(i) << endl;

    // 5. Obtener vecinos
    for (int i = 0; i < 4; i++)
    {
        vector<int> neighbors = g.getOutAdjacency(i);
        cout << "Vecinos de " << i << ": ";
        for (int n : neighbors) cout << n << " ";
        cout << endl;
    }

    // 6. Añadir un vértice extra
    g.addVertex();
    g.addEdge(4, 0, 7);
    cout << "\nGrafo tras agregar vértice 4 y arista 4-0:" << endl;
    g.print();

    // 7. Eliminar una arista
    g.removeEdge(0, 2);
    cout << "\nGrafo tras eliminar arista 0-2:" << endl;
    g.print();

    // 8. Eliminar un vértice
    g.removeVertex(1);
    cout << "\nGrafo tras eliminar vértice 1:" << endl;
    g.print();

    // 9. Imprimir DOT en consola
    cout << "\nDOT representation:" << endl;
    g.printDot();

    // 10. Exportar DOT a archivo
    g.exportDot();

    cout << "\n=== FIN DE PRUEBA ===" << endl;
}

void test2()
{
    AdjacencyListGraph g(4); 
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.exportDot(); 
}


void ryanAirGraphTest()
{
    RyanAirGraph myGraph(0);
    
    myGraph.parseAndre(); 
    myGraph.exportDot(); 
}




int main (int argc, char* argv[])
{
    //test2(); 
    ryanAirGraphTest(); 
}
