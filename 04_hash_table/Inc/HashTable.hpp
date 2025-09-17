#pragma once
/***********************************************************
    File: HashTable.hpp
    Description: Header file template. 
    Author: Miguel Márquez
    Date: 8/14/2024

************************************************************/
/***********************************************************
    Includes
************************************************************/
#include <string>
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


const int TABLE_SIZE = 10;

class HashTable
{
private:
    int keys[TABLE_SIZE];
    std::string values[TABLE_SIZE];
    bool occupied[TABLE_SIZE];

    int hashFunction(int key);       // Función hash
    int generateKey(const std::string& value); // Genera clave a partir del valor

public:
    HashTable();
    void insert(const std::string& value);    // Inserta solo con el valor
    bool search(const std::string& value);    // Busca por valor
    void remove(const std::string& value);    // Elimina por valor
    void display();
};
/***********************************************************
    Function Definitions
************************************************************/
