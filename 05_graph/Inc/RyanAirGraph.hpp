#include "AdjacencyListGraph.hpp"
#include "vector"
#include "string"

using std::vector; 
using std::string; 

class RyanAirGraph : public AdjacencyListGraph
{
    private: 
        vector<string>cities; 
        void fillCities(string data); 
        void printCities();
    
    public: 
        RyanAirGraph(int v) : AdjacencyListGraph(v)
        {
            
        }
        int parseAndre();

};