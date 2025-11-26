/***********************************************************
    File: AdjacencyListGraph.cpp
    Description: Adjacency List-based Graph implementation.
    Author: Miguel Márquez
    Date: 22/10/2025
************************************************************/

/***********************************************************
    Includes
************************************************************/
#include "AdjacencyListGraph.hpp"
#include <iostream>
#include <fstream>
#include <algorithm> // for remove_if
#include <string>
#include <queue>
#include <stack>

using std::cout;
using std::endl;
using std::ofstream;
using std::cerr;
using std::string; 
using std::queue; 
using std::priority_queue; 
using std::stack; 
/***********************************************************
    Class Definitions
************************************************************/

AdjacencyListGraph::AdjacencyListGraph(int vertices)
    : Graph(vertices),
      adjList(vertices)
{
    /* Each vertex starts with an empty adjacency list. */
}

void AdjacencyListGraph::addEdge(int u, int v, int weight)
{
    if (u < 0 || v < 0 || u >= numVertices || v >= numVertices)
    {
        cerr << "Error: Invalid vertex index.\n";
        return;
    }

    // Add edge in both directions (undirected)
    adjList[u].push_back({v, weight});
    adjList[v].push_back({u, weight});
}

void AdjacencyListGraph::addVertex()
{
    numVertices++;
    adjList.push_back({});
}

void AdjacencyListGraph::removeEdge(int u, int v)
{
    if (u < 0 || v < 0 || u >= numVertices || v >= numVertices)
    {
        cerr << "Error: Invalid vertex index.\n";
        return;
    }

    // Remove edge from u to v
    for (unsigned int i = 0; i < adjList[u].size(); i++)
    {
        if (adjList[u][i].first == v)
        {
            adjList[u].erase(adjList[u].begin() + i);
            break; // stop after removing (optional)
        }
    }

    // Remove edge from v to u (for undirected graph)
    for (unsigned int i = 0; i < adjList[v].size(); i++)
    {
        if (adjList[v][i].first == u)
        {
            adjList[v].erase(adjList[v].begin() + i);
            break;
        }
    }
}

void AdjacencyListGraph::removeVertex(int v)
{
    if (v < 0 || v >= numVertices)
    {
        cerr << "Error: Vertex " << v << " does not exist.\n";
        return;
    }

    // Step 1: Remove all edges incident to vertex v from its neighbors' lists.
    for (int u = 0; u < numVertices; u++)
    {
        // Skip the list we are about to delete in Step 2
        if (u == v) 
            continue;

        for (unsigned int i = 0; i < adjList[u].size(); i++)
        {
            // The pair's 'first' element is the target vertex ID (v)
            if (adjList[u][i].first == v)
            {
                adjList[u].erase(adjList[u].begin() + i);
                i--; // Crucial: Adjust index to re-examine the new element that shifted into position
            }
        }
    }

    // Step 2: Remove the adjacency list of vertex v itself.
    // This action causes the index shift for all vertices > v.
    adjList.erase(adjList.begin() + v);

    // Step 3: Decrement total vertex count.
    numVertices--;

    // Update all remaining neighbor IDs. 
    // Fix all edge targets (neighbor IDs) that were originally greater than v.
    for (int u = 0; u < numVertices; u++) // Loop through the remaining vertices
    {
        for (unsigned int i = 0; i < adjList[u].size(); i++)
        {
            // If the target vertex ID is greater than the removed vertex 'v'
            if (adjList[u][i].first > v)
            {
                // Decrement the stored ID to point to the correct, new index
                adjList[u][i].first--; 
            }
        }
    }
}
bool AdjacencyListGraph::isEdge(int u, int v) const
{
    if (u < 0 || v < 0 || u >= numVertices || v >= numVertices)
        return false;

    for (const auto &edge : adjList[u])
    {
        if (edge.first == v)
            return true;
    }

    return false;
}

int AdjacencyListGraph::getOutDegree(int u) const
{
    if (u < 0 || u >= numVertices)
        return -1;

    return adjList[u].size();
}

vector<int> AdjacencyListGraph::getOutAdjacency(int u) const
{
    vector<int> neighbors;
    if (u < 0 || u >= numVertices)
        return neighbors;

    for (const auto &edge : adjList[u])
    {
        neighbors.push_back(edge.first);
    }

    return neighbors;
}

void AdjacencyListGraph::print() const
{
    cout << "Adjacency List" << endl;

    for (int i = 0; i < numVertices; i++)
    {
        cout << i << ": ";
        for (const auto &edge : adjList[i])
        {
            cout << "(" << edge.first << ", w=" << edge.second << ") ";
        }
        cout << endl;
    }
}

void AdjacencyListGraph::printDot() const
{
    for (int i = 0; i < numVertices; i++)
    {
        for (const auto &edge : adjList[i])
        {
            if (i < edge.first) // to avoid duplicates in undirected graph
            {
                cout << "    " << i << " -- " << edge.first;
                if (edge.second != 1)
                    cout << " [label=" << edge.second << "]";
                cout << ";" << endl;
            }
        }
    }
}

void AdjacencyListGraph::exportDot(string filename) const
{
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    file << "graph G {\n";

    // 1. Imprimir todas las aristas
    for (int i = 0; i < numVertices; i++)
    {
        for (const auto &edge : adjList[i])
        {
            if (i < edge.first)
            {
                file << "    " << i << " -- " << edge.first;
                if (edge.second != 1)
                    file << " [label=" << edge.second << "]";
                file << ";\n";
            }
        }
    }

    // 2. Imprimir nodos desconectados:
    //    Si un nodo no tiene ninguna arista, se imprime solo.
    for (int i = 0; i < numVertices; i++)
    {
        if (adjList[i].empty())  // sin vecinos
        {
            file << "    " << i << ";\n";
        }
    }

    file << "}\n";
    file.close();

    cout << "DOT file written to " << filename << endl;
}


/***********************************************************
     DFS Pathfinding Implementation
************************************************************/

// Función auxiliar recursiva para DFS con construcción de la tabla de padres.
void AdjacencyListGraph::DFSPathUtil(int u, int target, vector<bool>& visited, vector<int>& parent, bool& found) const
{
    if (found) return; // Si el destino ya fue encontrado, se detiene la recursión

    visited[u] = true;

    if (u == target)
    {
        found = true;
        return;
    }

    // Recorrer todos los vecinos (aristas) del vértice 'u'
    for (unsigned int i = 0; i < adjList[u].size(); i++)
    {
        int neighbor = adjList[u][i].first; 

        if (!visited[neighbor])
        {
            // ¡Clave! Registrar que 'u' es el padre de 'neighbor'
            parent[neighbor] = u; 
            DFSPathUtil(neighbor, target, visited, parent, found);
            if (found) return; // Propagar la señal de encontrado hacia arriba
        }
    }
}

// Función pública para encontrar y reconstruir el camino.
vector<int> AdjacencyListGraph::findPathDFS(int startVertex, int endVertex) const
{
    vector<int> path;
    if (startVertex < 0 || endVertex < 0 || startVertex >= numVertices || endVertex >= numVertices)
    {
        cerr << "Error: Invalid start or end vertex for path search.\n";
        return path;
    }
    if (startVertex == endVertex)
    {
        path.push_back(startVertex);
        return path;
    }

    // 1. Inicializar estructuras
    vector<bool> visited(numVertices, false);
    // Inicializar la tabla de padres con -1 (o algún valor inválido)
    vector<int> parent(numVertices, -1); 
    bool found = false;
    
    // 2. Ejecutar la búsqueda (que ahora también construye la tabla de padres)
    DFSPathUtil(startVertex, endVertex, visited, parent, found);
    
    // 3. Reconstruir el camino a partir de la tabla de padres (retrocediendo)
    if (found)
    {
        int curr = endVertex;
        // Se detiene al llegar al nodo inicial, cuyo padre es -1.
        while (curr != -1) 
        {
            path.push_back(curr);
            curr = parent[curr];
        }
        // El camino se construyó de destino a origen, por lo que se invierte.
        std::reverse(path.begin(), path.end()); 
    }

    return path;
}

/* Dijkstra */
DijkstraResult_t AdjacencyListGraph::dijkstra(int source) const
{
    const int INF = 1e9;
    vector<int> dist(numVertices, INF);
    vector<int> parent(numVertices, -1);
    vector<bool> visited(numVertices, false);

    dist[source] = 0;

    for (int count = 0; count < numVertices - 1; count++)
    {
        int u = -1;
        int minDist = INF;

        // 1. Elegir el nodo no visitado con menor distancia
        for (int i = 0; i < numVertices; i++)
        {
            if (!visited[i] && dist[i] < minDist)
            {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        visited[u] = true;

        // 2. Relajar sus vecinos
        for (const auto &edge : adjList[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (!visited[v] && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                parent[v] = u;  // guardar el camino
            }
        }
    }

    return {dist, parent};
}

vector<int> AdjacencyListGraph::getPath(const vector<int> &parent, int source, int target) const
{
    vector<int> path;

    for (int v = target; v != -1; v = parent[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    // Si el camino no empieza en la fuente, no existe
    if (path[0] != source)
        return {};

    return path;
}

bool AdjacencyListGraph::BFSPathUtil(int start, int target, vector<int>& parent) const
{
    // 1. Inicializar estructuras
    vector<bool> visited(numVertices, false);
    queue<int> q; // Utiliza una cola para BFS (Amplitud)

    visited[start] = true;
    parent[start] = -1; // El nodo inicial no tiene padre
    q.push(start);

    // 2. Proceso de Búsqueda
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        // Si encontramos el objetivo, regresamos inmediatamente
        if (u == target)
        {
            return true;
        }

        // Recorrer todos los vecinos (aristas) del vértice 'u'
        for (unsigned int i = 0; i < adjList[u].size(); i++)
        {
            int neighbor = adjList[u][i].first;

            if (!visited[neighbor])
            {
                // ¡Clave! Registrar el padre
                visited[neighbor] = true;
                parent[neighbor] = u; 
                q.push(neighbor);
            }
        }
    }
    
    return false; // El destino no fue alcanzado
}

/**
 * @brief Encuentra el camino más corto (en número de aristas) entre dos vértices usando BFS.
 * @param startVertex Vértice inicial.
 * @param endVertex Vértice destino.
 * @return Un vector con el camino encontrado, o un vector vacío si no existe.
 */
vector<int> AdjacencyListGraph::findPathBFS(int startVertex, int endVertex) const
{
    vector<int> path;
    if (startVertex < 0 || endVertex < 0 || startVertex >= numVertices || endVertex >= numVertices)
    {
        cerr << "Error: Invalid start or end vertex for path search.\n";
        return path;
    }
    if (startVertex == endVertex)
    {
        path.push_back(startVertex);
        return path;
    }

    // Inicializar la Tabla de Padres (Parent Table)
    vector<int> parent(numVertices, -1); 
    
    // Ejecutar la búsqueda BFS
    bool found = BFSPathUtil(startVertex, endVertex, parent);
    
    // Reconstruir el camino si fue encontrado
    if (found)
    {
        int curr = endVertex;
        // Retrocede desde el destino hasta el origen (cuyo padre es -1)
        while (curr != -1) 
        {
            path.push_back(curr);
            curr = parent[curr];
        }
        // Invertir el camino para que vaya de inicio a fin
        std::reverse(path.begin(), path.end()); 
    }

    return path;
}

vector<Edge> AdjacencyListGraph::primMST(int startVertex) const
{
    vector<Edge> mstEdges;

    // 1. Validación y configuración inicial
    if (startVertex < 0 || startVertex >= numVertices)
    {
        cerr << "Error: Invalid starting vertex for Prim's algorithm.\n";
        return mstEdges;
    }

    // Cola de prioridad: Se utiliza la clase comparadora CompareEdge
    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    vector<bool> visited(numVertices, false);
    
    visited[startVertex] = true;

    // Agregar todas las aristas del vértice inicial
    for (unsigned int i = 0; i < adjList[startVertex].size(); i++)
    {
        const auto& edge = adjList[startVertex][i];
        pq.push({startVertex, edge.first, edge.second});
    }

    // 2. Proceso de Prim
    while (!pq.empty())
    {
        Edge currentEdge = pq.top();
        pq.pop();

        int v_dest = currentEdge.to;

        // Si el destino ya está en el MST, ignorar
        if (visited[v_dest])
        {
            continue;
        }

        // Añadir la arista al MST y marcar el nodo como visitado
        visited[v_dest] = true;
        mstEdges.push_back(currentEdge);

        // Optimización
        if (mstEdges.size() == (unsigned int)numVertices - 1)
        {
            break;
        }

        // 3. Explorar vecinos del nuevo vértice 'v_dest'
        for (unsigned int i = 0; i < adjList[v_dest].size(); i++)
        {
            const auto& nextEdge = adjList[v_dest][i];
            int neighbor = nextEdge.first;
            int weight = nextEdge.second;

            if (!visited[neighbor])
            {
                // Agregar la nueva arista a la cola
                pq.push({v_dest, neighbor, weight});
            }
        }
    }
    
    return mstEdges;
}


bool AdjacencyListGraph::DFSPathUtil(int u, int target, int limit,
                                     std::vector<bool>& visited, std::vector<int>& parent, bool& found) const
{
    // CÓDIGO DE DLS: La verificación del límite es el punto clave
    if (limit < 0) {
        return false; 
    }
    
    if (u == target)
    {
        found = true;
        return true;
    }

    visited[u] = true;

    for (unsigned int i = 0; i < adjList[u].size(); i++)
    {
        int neighbor = adjList[u][i].first; 

        if (!visited[neighbor])
        {
            parent[neighbor] = u;
            
            // Llamada recursiva A LA MISMA FUNCIÓN SOBRECARGADA (limit - 1)
            if (DFSPathUtil(neighbor, target, limit - 1, visited, parent, found))
            {
                return true; 
            }
        }
    }
    return false;
}

std::vector<int> AdjacencyListGraph::findPathDLS(int startVertex, int endVertex, int limit) const
{
    std::vector<int> path;

    // 1. Validaciones
    if (startVertex < 0 || startVertex >= numVertices || endVertex < 0 || endVertex >= numVertices) 
    {
        return path; // Retorna vacío si está fuera de rango
    }
    if (startVertex == endVertex)
    {
        return {startVertex};
    }

    // 2. Inicializar estructuras
    std::vector<bool> visited(numVertices, false);
    std::vector<int> parent(numVertices, -1);
    bool found = false;
    
    parent[startVertex] = startVertex; 

    // 3. Llamada a la función auxiliar (DLS)
    DFSPathUtil(startVertex, endVertex, limit, visited, parent, found);
    
    // 4. Reconstrucción del Camino
    if (found)
    {
        int curr = endVertex;
        // La condición de parada es: 
        // 1. curr == -1 (nunca debería pasar si 'found' es true)
        // 2. parent[curr] == curr (Hemos llegado al nodo inicial)
        while (curr != -1 && parent[curr] != curr) 
        {
            path.push_back(curr);
            curr = parent[curr];
        }
        
        // Agregar el nodo inicial (el bucle se detuvo justo antes de agregarlo)
        if (curr != -1)
        {
             path.push_back(curr);
        }

        // El camino se construyó de fin a inicio, se revierte.
        std::reverse(path.begin(), path.end()); 
    }

    return path;
}

vector<int> AdjacencyListGraph::findPathDFSIterative(int startVertex, int endVertex) const
{
    vector<int> path;

    // 1. Validaciones y Casos Base
    if (startVertex < 0 || startVertex >= numVertices || endVertex < 0 || endVertex >= numVertices) 
    {
        return path;
    }
    if (startVertex == endVertex)
    {
        return {startVertex};
    }

    // 2. Inicializar estructuras
    // Pila explícita para la búsqueda: almacena los nodos a visitar.
    stack<int> s; 
    
    // Rastrea los nodos visitados y el predecesor para reconstruir el camino.
    vector<bool> visited(numVertices, false);
    vector<int> parent(numVertices, -1);
    
    // Inicializar el nodo de partida
    s.push(startVertex);
    visited[startVertex] = true;
    parent[startVertex] = startVertex; // Marcar como el nodo raíz para la reconstrucción

    bool found = false;

    // 3. Proceso Iterativo de DFS
    while (!s.empty())
    {
        int u = s.top();
        s.pop();

        // Si encontramos el objetivo
        if (u == endVertex)
        {
            found = true;
            break; 
        }

        // Recorrer vecinos: la clave es empujar los vecinos a la pila.
        // Ojo: Para obtener el mismo orden de DFS que la recursiva (que a menudo 
        // visita el primer vecino primero), a veces es necesario recorrer 
        // la lista de adyacencia al revés si se usa una lista estándar. 
        // Aquí asumiremos que el orden estándar es suficiente.
        for (const auto& edge : adjList[u])
        {
            int neighbor = edge.first;
            
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = u;
                s.push(neighbor);
            }
        }
    }

    // 4. Reconstrucción del Camino (la misma lógica usada en el DLS corregido)
    if (found)
    {
        int curr = endVertex;
        while (curr != -1 && parent[curr] != curr) 
        {
            path.push_back(curr);
            curr = parent[curr];
        }
        
        if (curr != -1)
        {
             path.push_back(curr);
        }

        reverse(path.begin(), path.end()); 
    }

    return path;
}
