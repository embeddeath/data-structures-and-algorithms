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
    g.exportDot("file.dot");

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
    g.exportDot("file.dot");

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
    g.exportDot("file.dot");

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
    g.exportDot("file.dot");

    cout << "\n=== FIN DE PRUEBA ===" << endl;
}

void test2()
{
    AdjacencyListGraph g(4); 
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.exportDot("file.dot"); 
}


void ryanAirGraphTest()
{
    RyanAirGraph myGraph(0);
    
    myGraph.parseAndre(); 
    myGraph.exportDot("file.dot"); 
}


void DFStest()
{
    cout << "========================================" << endl;
    cout << "         INICIO DE PRUEBAS DFS PATH" << endl;
    cout << "========================================" << endl;

    // 1. Creación del Grafo de Prueba (7 vértices: 0 a 6)
    AdjacencyListGraph g(7);

    // Añadir aristas 
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 5);

    cout << "--- Estructura del Grafo ---" << endl;
    g.print();
    g.exportDot("dfspathtest.txt"); 
    // 2. Prueba de Búsqueda de Camino (Función findPathDFS)

    // Caso A: Camino Existente (0 -> 5)
    int startA = 0;
    int endA = 5;
    cout << "\n--- Prueba de Camino Existente (" << startA << " -> " << endA << ") ---" << endl;
    vector<int> pathA = g.findPathDFS(startA, endA);
    
    if (!pathA.empty())
    {
        cout << "Camino encontrado: ";
        for (unsigned int i = 0; i < pathA.size(); ++i)
        {
            cout << pathA[i];
            if (i < pathA.size() - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }
    else
    {
        cout << "Error: No se encontró el camino, pero debería existir." << endl;
    }

    // Caso B: Camino No Existente (Vértice 6 es nuevo y está desconectado)
    g.addVertex(); // Nuevo vértice 6
    int startB = 0;
    int endB = 6;
    cout << "\n--- Prueba de Camino No Existente (" << startB << " -> " << endB << ") ---" << endl;
    
    vector<int> pathB = g.findPathDFS(startB, endB);
    
    if (pathB.empty())
    {
        cout << "Prueba Exitosa: El camino entre " << startB << " y " << endB << " NO se encontró (esperado)." << endl;
    }
    else
    {
        cout << "Error: Se encontró un camino, lo cual no debería haber ocurrido." << endl;
    }
    
    cout << "========================================" << endl;
    cout << "         FIN DE PRUEBAS DFS PATH" << endl;
    cout << "========================================" << endl;
}

void Dijkstratest()
{
    cout << "========================================" << endl;
    cout << "        INICIO DE PRUEBAS DIJKSTRA" << endl;
    cout << "========================================" << endl;

    // 1. Crear el Grafo (7 vértices: 0 a 6)
    // El nodo 6 quedará completamente desconectado
    AdjacencyListGraph g(7);

    // Aristas para probar rutas óptimas
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 5);
    g.addEdge(4, 5, 1);

    // Nodo 6 se queda completamente desconectado

    cout << "--- Estructura del Grafo ---" << endl;
    g.print();

    // -------------------------------------------------
    // Caso A: Camino EXISTENTE (0 -> 5)
    // -------------------------------------------------
    int startA = 0;
    int endA   = 5;

    cout << "\n--- Prueba de Camino Existente (" 
         << startA << " -> " << endA << ") ---" << endl;

    DijkstraResult resultA = g.dijkstra(startA);
    vector<int> pathA = g.getPath(resultA.parent, startA, endA);

    if (!pathA.empty())
    {
        cout << "Distancia mínima: " << resultA.dist[endA] << endl;

        cout << "Camino encontrado: ";
        for (unsigned int i = 0; i < pathA.size(); ++i)
        {
            cout << pathA[i];
            if (i < pathA.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    }
    else
    {
        cout << "Error: No se encontró el camino, pero debería existir." << endl;
    }

    // -------------------------------------------------
    // Caso B: Camino NO existente (0 -> 6)
    // Nodo 6 está desconectado desde el inicio
    // -------------------------------------------------
    int startB = 0;
    int endB   = 6;

    cout << "\n--- Prueba de Camino No Existente ("
         << startB << " -> " << endB << ") ---" << endl;

    DijkstraResult resultB = g.dijkstra(startB);
    vector<int> pathB = g.getPath(resultB.parent, startB, endB);

    if (pathB.empty())
    {
        cout << "Prueba Exitosa: El camino entre " 
             << startB << " y " << endB 
             << " NO se encontró (esperado)." << endl;
    }
    else
    {
        cout << "Error: Se encontró un camino, lo cual NO debería ocurrir." << endl;
    }

    // Exportar el grafo hasta el final 
    g.exportDot("dijkstratest.dot");

    cout << "========================================" << endl;
    cout << "        FIN DE PRUEBAS DIJKSTRA" << endl;
    cout << "========================================" << endl;
}

void BFStest()
{
    cout << "\n========================================" << endl;
    cout << "         INICIO DE PRUEBAS BFS PATH" << endl;
    cout << "========================================" << endl;

    // 1. Creación del Grafo de Prueba (6 vértices: 0 a 5)
    AdjacencyListGraph g(6);

    // Añadir aristas 
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 4, 1);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 1);
    // Añadimos una arista que crea un camino más corto en saltos (0->5)
    g.addEdge(0, 5, 10); 

    cout << "--- Estructura del Grafo (Lista de Adyacencia) ---" << endl;
    g.print();
    
    // 2. Prueba de Búsqueda de Camino (Función findPathBFS)

    // Caso A: Camino Existente (0 -> 5). BFS encuentra el camino con el menor número de aristas.
    int startA = 0;
    int endA = 5;
    cout << "\n--- Prueba de Camino Existente (" << startA << " -> " << endA << ") ---" << endl;
    vector<int> pathA = g.findPathBFS(startA, endA);
    
    if (!pathA.empty())
    {
        cout << "Camino más corto (en saltos) encontrado: ";
        for (unsigned int i = 0; i < pathA.size(); ++i)
        {
            cout << pathA[i];
            if (i < pathA.size() - 1)
            {
                cout << " -> ";
            }
        }
        cout << " (Longitud: " << pathA.size() - 1 << " aristas)" << endl;
    }
    else
    {
        cout << "Error: No se encontró el camino, pero debería existir." << endl;
    }

    // Caso B: Camino No Existente (Se intenta buscar un camino a un vértice fuera del rango inicial)
    // El vértice 6 NO existe, por lo que la comprobación de límites debería fallar.
    int startB = 0;
    int endB = 6; 
    cout << "\n--- Prueba de Camino No Existente (" << startB << " -> " << endB << ") ---" << endl;
    
    vector<int> pathB = g.findPathBFS(startB, endB);
    
    if (pathB.empty())
    {
        cout << "Prueba Exitosa: El camino entre " << startB << " y " << endB << " NO se encontró (esperado, índice fuera de rango)." << endl;
    }
    else
    {
        cout << "Error: Se encontró un camino, lo cual no debería haber ocurrido." << endl;
    }
    
    // 3. Exportar en formato DOT 
    cout << "\n--- Exportación en Formato DOT ---" << endl;
    g.exportDot("bfstest.dot");


    cout << "========================================" << endl;
    cout << "         FIN DE PRUEBAS BFS PATH" << endl;
    cout << "========================================" << endl;
}

void PrimTest()
{
    cout << "\n========================================" << endl;
    cout << "       INICIO DE PRUEBAS MST (Prim)" << endl;
    cout << "========================================" << endl;

    // 1. Creación del Grafo de Prueba (6 vértices: 0 a 5)
    AdjacencyListGraph g(6);

    // Añadir aristas y pesos
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5); 
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4); 
    g.addEdge(2, 4, 12);
    g.addEdge(3, 4, 11);
    g.addEdge(4, 5, 8); 

    cout << "--- Estructura del Grafo (Lista de Adyacencia) ---" << endl;
    g.print();
    
    // 2. Ejecutar Prim desde el nodo 3
    int startNode = 3;
    cout << "\n--- Ejecutando Algoritmo de Prim desde el nodo " << startNode << " ---" << endl;
    
    vector<Edge> mst = g.primMST(startNode); 
    
    // 3. Mostrar el resultado
    int totalWeight = 0;
    cout << "Aristas del Arbol de Expansion Minima (MST):" << endl;
    for (const auto& edge : mst)
    {
        cout << "  Arista: " << edge.from << " -- " << edge.to << " (Peso: " << edge.weight << ")" << endl;
        totalWeight += edge.weight;
    }
    
    cout << "\nPeso Total del MST: " << totalWeight << " (Esperado: 38)" << endl;
    
    // 4. Exportar en formato DOT
    cout << "\n--- Exportación en Formato DOT ---" << endl;

    g.exportDot("primtest.dot");

    cout << "========================================" << endl;
    cout << "         FIN DE PRUEBAS MST (Prim)" << endl;
    cout << "========================================" << endl;
}

// DLSTest.cpp (o donde guardes tus funciones de prueba)

#include "AdjacencyListGraph.hpp" 
#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

/**
 * @brief Muestra el resultado de la búsqueda de camino.
 */
void printPathResult(const vector<int>& path, int start, int end, int limit)
{
    if (!path.empty())
    {
        cout << "  [EXITO]: Camino encontrado (Longitud: " << path.size() - 1 << "): ";
        for (size_t i = 0; i < path.size(); ++i)
        {
            cout << path[i] << (i < path.size() - 1 ? " -> " : "");
        }
        cout << endl;
    }
    else
    {
        cout << "  [FALLO]: No se encontró camino de " << start << " a " << end 
             << " con límite " << limit << "." << endl;
    }
}

/**
 * @brief Función de prueba para verificar la funcionalidad de la Búsqueda con Límite (DLS).
 */
void DLSTest()
{
    cout << "\n========================================" << endl;
    cout << "       INICIO DE PRUEBAS DLS" << endl;
    cout << "========================================" << endl;

    // Grafo de Prueba (6 vértices: 0 a 5)
    AdjacencyListGraph g(6);

    // Conexiones: 
    g.addEdge(0, 1, 1); 
    g.addEdge(1, 3, 1);
    g.addEdge(3, 5, 1); // Camino corto: 0 -> 1 -> 3 -> 5 (3 saltos)

    g.addEdge(0, 2, 1);
    g.addEdge(2, 4, 1); 
    g.addEdge(4, 5, 1); // Camino 0 -> 2 -> 4 -> 5 (3 saltos)
    
    // Arista para crear un camino más largo: 0 -> 1 -> 3 -> 4 -> 5 (4 saltos)
    g.addEdge(3, 4, 1); 

    cout << "--- Estructura del Grafo ---" << endl;
    g.print();
    
    int start = 0;
    int end = 5;

    // --- Caso 1: Límite Insuficiente ---
    // El camino más corto es de 3 saltos. Límite = 2.
    int limit1 = 2;
    cout << "\n--- Prueba 1: Límite " << limit1 << " (Insuficiente) ---" << endl;
    vector<int> path1 = g.findPathDLS(start, end, limit1);
    printPathResult(path1, start, end, limit1);

    // --- Caso 2: Límite Justo (Suficiente) ---
    // Límite = Longitud del camino más corto.
    int limit2 = 3; 
    cout << "\n--- Prueba 2: Límite " << limit2 << " (Justo) ---" << endl;
    vector<int> path2 = g.findPathDLS(start, end, limit2);
    printPathResult(path2, start, end, limit2);

    // --- Caso 3: Límite Amplio (DFS Normal) ---
    // El límite es grande.
    int limit3 = 10; 
    cout << "\n--- Prueba 3: Límite " << limit3 << " (Amplio) ---" << endl;
    vector<int> path3 = g.findPathDLS(start, end, limit3);
    printPathResult(path3, start, end, limit3);

    // 4. Exportar en formato DOT
    g.exportDot("dlstest.dots"); 


    cout << "========================================" << endl;
    cout << "         FIN DE PRUEBAS DLS" << endl;
    cout << "========================================" << endl;
}

int main(int argc, char* argv[])
{
    DFStest(); 
    Dijkstratest();
    BFStest();
    PrimTest(); 
    DLSTest();
}
