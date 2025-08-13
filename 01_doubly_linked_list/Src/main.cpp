/***********************************************************
    File: main.cpp
    Author: Miguel Márquez
    Date: 8/14/2024

************************************************************/

/***********************************************************
    Includes
************************************************************/
#include <iostream>
#include <string>
#include "List.h"

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


int main (int argc, char* argv[])
{
    List* myList = new List(); 

    myList->append(10.0f); 
    myList->append(20.0f);
    myList->append(30.0f);

    myList->print();  
    std::cout << "List size is: " << myList->getSize() << std::endl;

    myList->removeAtEnd(); 

    myList->print(); 
    std::cout << "List size is: " << myList->getSize() << std::endl;


    myList->removeAtFront(); 

    myList->print(); 
    std::cout << "List size is: " << myList->getSize() << std::endl;
    
    return 0; 
}