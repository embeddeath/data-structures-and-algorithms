/***********************************************************
    File: RyanAirGraph.cpp
    Description: Adjacency List-based Graph implementation tailored for ryanAir routes..
    Author: Miguel Márquez
    Date: 22/10/2025
************************************************************/

/***********************************************************
    Includes
************************************************************/
#include "RyanAirGraph.hpp"
#include <iostream>
#include <fstream>
#include <algorithm> // for remove_if
#include <string>

using std::cout;
using std::endl;
using std::fstream;
using std::cerr;
using std::string; 
using std::stoi; 

/***********************************************************
    Class Definitions
************************************************************/
 

int RyanAirGraph::parseAndre()
{
    fstream inputFile("grafo.txt"); 
    if (!inputFile.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    string line;

    /* Fill cities until we find the # delimiter. */
    while (getline(inputFile, line) && line.compare("#") != 0) {
        fillCities(line);
    }
 
    /* Save where the list starts. */
    double beginningOfList = inputFile.tellg(); 

    unsigned int previousCity = 0xDEADBEEF; 
    unsigned int currentCity = 0;
    unsigned int destination; 
    unsigned int weight;  

    string buf; 
    unsigned int spaceIndex; 

    /* All vertices need to exist before filling in edges. */
    while (getline(inputFile, line))
    {
        /* Get index of first space to delimit City*/
        spaceIndex = line.find(' '); 
        buf = line.substr(0, spaceIndex);
        /* buf now holds city index in string*/
        currentCity = stoi(buf); 
        
        if (currentCity != previousCity)
        {
            addVertex();
        }
        
        previousCity = currentCity; 
    }  

    cout << "Number of vertexes " << numVertices << endl; 
    cout << "Beginning of list " << beginningOfList << endl; 
    /* Go to the start of the list and reiterate. */
    inputFile.clear(); 
    inputFile.seekg(beginningOfList); 
    //getline(inputFile, line);


    while (getline(inputFile, line))
    {

        /* Get index of first space to delimit City*/
        spaceIndex = line.find(' '); 
        buf = line.substr(0, spaceIndex);
        /* buf now holds city index in string*/
        currentCity = stoi(buf); 

        /* Delete city index from list*/
        line.erase(0, spaceIndex + 1); 

        /* Get destination*/
        spaceIndex = line.find(' '); 
        buf = line.substr(0, spaceIndex);
        destination = stoi(buf); 

        /* Delete destination from entry*/
        line.erase(0, spaceIndex + 1); 

        /* Get weight (Only information that is still in the string) */
        weight = stoi(line); 

        addEdge(currentCity, destination, weight); 

        /* In theory this should work*/

    }
     
    inputFile.close(); // Cerrar archivo
    return 0;
}

void RyanAirGraph::fillCities(string data)
{
    /* Remove numbers, we don't need them.*/
    data.erase(0, data.find(' ')); 
    cities.push_back(data); 
}

void RyanAirGraph::printCities()
{
    for (unsigned int i = 0; i < cities.size(); i++)
    {
        cout << cities[i]; 
    }
    
}

