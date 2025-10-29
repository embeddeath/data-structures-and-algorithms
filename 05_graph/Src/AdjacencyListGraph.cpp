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

using std::cout;
using std::endl;
using std::ofstream;
using std::cerr;
using std::string; 

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

void AdjacencyListGraph::exportDot() const
{
    string filename = "graph_list.dot";
    ofstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    file << "graph G {\n";

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

    file << "}\n";
    file.close();

    cout << "DOT file written to " << filename << endl;
}
