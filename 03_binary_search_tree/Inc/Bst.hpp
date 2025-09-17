#pragma once
/***********************************************************
    File: Bst.hpp
    Description: Header file template. 
    Author: Miguel Márquez
    Date: 8/14/2024

************************************************************/
/***********************************************************
    Includes
************************************************************/
#include "Node.hpp"
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
class BinarySearchTree
{
    private: 
        Node* root; 
        Node* insertRecursive(Node* node, int data); 
        Node* searchRecursive(Node* node, int data);
        void  inorderTraversalRecursive(Node* node); 
        Node* deleteRecursive(Node* node, int data);
        Node* minValueNode(Node* node);

    public:
        BinarySearchTree(void); 
        void insert(int data);
        bool search(int data); 
        void inorderTraversal(void); 
        void remove(int data);
};

/***********************************************************
    Function Definitions
************************************************************/
