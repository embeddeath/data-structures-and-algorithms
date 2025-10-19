#pragma once
/***********************************************************
    File: Graph.hpp
    Description: Abstract class for graph data structure. 
    Author: Miguel Márquez
    Date: 18/10/2025

************************************************************/
/***********************************************************
    Includes
************************************************************/

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
class Graph
{
    protected:
        int numVertices; 
    
    public:
        /*
        The constructor is used with an initializer list, This tells the compiler
        "When constructing this object, initialize numVertices directly with vertices
        before the constructor body executes". 
        */
        Graph(int vertices) : numVertices(vertices){}
        virtual ~Graph() = default; 
        
        /* When declaring virtual methods, if you equal them to 0, you force them to be overriden
        in the derived classes. Prevents Graph to be instanced directly*/
        virtual void addEdge(int u, int v, int weight = 1) = 0; 
        virtual void addVertex(void) = 0; 
        virtual void removeEdge(int u, int v) = 0; 
        virtual bool isEdge(int u, int v) const = 0; 
        virtual void print(void) const = 0; 
        virtual void printDot(void) const = 0; 
        virtual void exportDot(void) const = 0; 
};
/***********************************************************
    Function Definitions
************************************************************/
