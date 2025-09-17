/***********************************************************
    File: HashTable.cpp
    Description: Source file template for OOP class. 
    Author: Miguel Márquez
    Date: 8/14/2024

************************************************************/

/***********************************************************
    Includes
************************************************************/
#include "HashTable.hpp"
#include <iostream>
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
// Constructor
HashTable::HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
        occupied[i] = false;
}

// Función hash simple: key % TABLE_SIZE
int HashTable::hashFunction(int key)
{
    return key % TABLE_SIZE;
}

// Genera una clave a partir del valor (suma de ASCII)
int HashTable::generateKey(const std::string& value)
{
    int key = 0;
    for (char c : value)
        key += c; // Suma de códigos ASCII
    return key;
}

// Insertar valor (clave generada automáticamente)
void HashTable::insert(const std::string& value)
{
    int key = generateKey(value);
    int index = hashFunction(key);
    int startIndex = index;

    while (occupied[index])
    {
        if (values[index] == value)
            return; // Ya existe
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex)
        {
            std::cout << "Tabla llena, no se puede insertar.\n";
            return;
        }
    }

    keys[index] = key;
    values[index] = value;
    occupied[index] = true;
}

// Buscar valor
bool HashTable::search(const std::string& value)
{
    int key = generateKey(value);
    int index = hashFunction(key);
    int startIndex = index;

    while (occupied[index])
    {
        if (values[index] == value)
            return true;
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex)
            break;
    }
    return false;
}

// Eliminar valor
void HashTable::remove(const std::string& value)
{
    int key = generateKey(value);
    int index = hashFunction(key);
    int startIndex = index;

    while (occupied[index])
    {
        if (values[index] == value)
        {
            occupied[index] = false;
            std::cout << "Valor \"" << value << "\" eliminado.\n";
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex)
            break;
    }
    std::cout << "Valor \"" << value << "\" no encontrado.\n";
}

// Mostrar tabla
void HashTable::display()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (occupied[i])
            std::cout << i << " --> (" << keys[i] << ", " << values[i] << ")\n";
        else
            std::cout << i << " --> [vacio]\n";
    }
}
/***********************************************************
    Function Definitions
************************************************************/


