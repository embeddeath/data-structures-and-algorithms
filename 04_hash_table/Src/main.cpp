/***********************************************************
    File: HashTable.cpp
    Author: Miguel Márquez
    Date: 8/14/2024

************************************************************/

/***********************************************************
    Includes
************************************************************/
#include <iostream>
#include "HashTable.hpp"

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



int main()
{
    HashTable ht;

    ht.insert("Miguel");
    ht.insert("Miguel");
    ht.insert("Ruben");
    ht.insert("Mariana");
    ht.insert("Fernanda");

    ht.display();

    std::cout << std::endl;

    if (ht.search("Miguel"))
        std::cout << "Miguel encontrado!\n";
    else
        std::cout << "Miguel no encontrado.\n";

    ht.remove("Miguel");

    if (ht.search("Miguel"))
        std::cout << "Miguel encontrado!\n";
    else
        std::cout << "Miguel no encontrado.\n";

    ht.display();

    return 0;
}