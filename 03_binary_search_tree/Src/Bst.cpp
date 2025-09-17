/***********************************************************
    File: Bst.cpp
    Description: Source file template for OOP class. 
    Author: Miguel Márquez
    Date: 8/14/2024

************************************************************/
/***********************************************************

    Includes
************************************************************/
#include "Bst.hpp"
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

BinarySearchTree::BinarySearchTree(void)
{
    root = nullptr; 
}

Node* BinarySearchTree::insertRecursive(Node* node, int data)
{
    if (node == nullptr)
    {
        return new Node(data); 
    }
    if(data < node->data)
    {
        node->left = insertRecursive(node->left, data); 
    }
    else if (data > node->data)
    {
        node->right = insertRecursive(node->right, data);
    }

    return node; 
}

Node* BinarySearchTree::searchRecursive(Node* node , int data)
{
    if(node == nullptr || node->data == data)
    {
        return node; 
    }
    
    if (data < node->data)
    {
        return searchRecursive(node->left, data);
    } 
    else
    {
        return searchRecursive(node->right, data);
    }
}


void BinarySearchTree::inorderTraversalRecursive(Node* node)
{
    if (node == nullptr)
    {
        return; 
    }

    inorderTraversalRecursive(node->left);
    std::cout << node->data << " ";
    inorderTraversalRecursive(node->right);
}


void BinarySearchTree::insert(int data)
{
    root = insertRecursive(root, data); 
}

bool BinarySearchTree::search(int data)
{
    return searchRecursive(root, data); 
}

void BinarySearchTree::inorderTraversal(void)
{
    inorderTraversalRecursive(root);
    std::cout << std::endl;
}

Node* BinarySearchTree::deleteRecursive(Node* node, int data)
{
    if (node == nullptr)
    {
        return node;
    }

    if (data < node->data)
    {
        node->left = deleteRecursive(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = deleteRecursive(node->right, data);
    }
    else
    {
        // Caso 1: Nodo sin hijos
        if (node->left == nullptr && node->right == nullptr)
        {
            delete node;
            return nullptr;
        }
        // Caso 2: Un solo hijo
        else if (node->left == nullptr)
        {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        // Caso 3: Dos hijos

        /*
            Cuando eliminamos un nodo con dos hijos en un BST, necesitamos reemplazarlo por otro valor que mantenga el orden ascendente del árbol.

            Ese valor se toma del mínimo del subárbol derecho:

                El subárbol derecho es el que cuelga del hijo derecho del nodo a eliminar.

                El mínimo es el nodo más a la izquierda dentro de ese subárbol.

            Ese nodo es el sucesor inorden, es decir, el siguiente en el recorrido ordenado.

            Al usarlo como reemplazo, el árbol conserva la propiedad de BST.

            Ese sucesor nunca cae en caso 3 (dos hijos), porque al ser el más a la izquierda no puede tener hijo izquierdo → solo será hoja (caso 1) o tendrá un hijo derecho (caso 2).
        */
        else
        {
            Node* successor = minValueNode(node->right);
            node->data = successor->data;
            node->right = deleteRecursive(node->right, successor->data);
        }
    }
    return node;
}

Node* BinarySearchTree::minValueNode(Node* node)
{
    Node* current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

void BinarySearchTree::remove(int data)
{
    root = deleteRecursive(root, data);
}
/***********************************************************
    Function Definitions
************************************************************/

