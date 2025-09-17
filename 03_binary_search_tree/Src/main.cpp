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
#include "Bst.hpp"

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
    BinarySearchTree* bst = new BinarySearchTree();

    bst->insert(10); 
    bst->insert(5);
    bst->insert(30);
    bst->insert(106);
    bst->insert(58);
    bst->insert(390);
    bst->insert(102);
    bst->insert(51);
    bst->insert(33);
    bst->insert(17);
    bst->insert(59);
    bst->insert(99);
    bst->insert(6);
    bst->insert(875);
    bst->insert(34);
    bst->insert(1222);
    bst->insert(5000);
    bst->insert(36);
    bst->insert(16);
    bst->insert(790);
    bst->insert(301);
    std::cout << "In-order traversal: ";
    bst->inorderTraversal(); 
    bst->remove(99);
    bst->remove(1000);
    std::cout<< "In-order traversal: "; 
    bst->inorderTraversal(); 
    
    return 0; 
}