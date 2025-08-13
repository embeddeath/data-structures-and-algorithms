/***********************************************************
    File: Node.cpp
    Description: DLL Node Class implementation. 
    Author: Miguel Márquez
    Date: 8/14/2024

************************************************************/

/***********************************************************
    Includes
************************************************************/
#include "Node.h"

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

Node::Node(float new_data)
{
    data = new_data;
    next = nullptr;
    prev = nullptr;
}

void Node::setData(float new_data)
{
    data = new_data;
}

float Node::getData(void)
{
    return data;
}

Node* Node::getNext(void)
{
    return next;
}

void Node::setNext(Node* new_next)
{
    next = new_next;
}

Node* Node::getPrev(void)
{
    return prev;
}

void Node::setPrev(Node* new_prev)
{
    prev = new_prev;
}