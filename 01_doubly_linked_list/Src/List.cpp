/***********************************************************
    File: List.cpp
    Description: Doubly linked list class implementation.  
    Author: Miguel Márquez
    Date: 8/14/2024

************************************************************/

/***********************************************************
    Includes
************************************************************/
#include "List.h"
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

/***********************************************************
    Function Definitions
************************************************************/


/*****************************************************************************
 *
 * Method:    List
 *
 * Description: List constructor, its primary responsibility is to create
 *              a valid, empty List object
 *
 *
 * Caveats:
 *    
 *
 *****************************************************************************/
List::List()
{
    this->head = nullptr;
    this->tail = nullptr;
}

/*****************************************************************************
 *
 * Method:    ~List
 *
 * Description: Prevent memory leaks by iterating through the list and deleting 
 *              each node. 
 *
 *
 * Caveats:
 *    
 *
 *****************************************************************************/
List::~List()
{
    Node* current = this->head;

    while (current != nullptr)
    {
        Node* next_node = current->getNext();
        delete current;
        current = next_node;
    } 
    head = tail = nullptr; 

}

/*****************************************************************************
 *
 * Method:    push
 *
 * Description: Insert a new node at the beginning of the list.
 *
 * Parameters:
 *      data - The data to be stored in the new node.
 *
 * Caveats:
 *    
 *
 *****************************************************************************/

void List::push(float data)
{
    /* Instance a new node and save a pointer to it*/
    Node* newNode = new Node(data); 

    if(this->isEmpty())
    {
        /* First element of the list, head == tail*/
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        /* Point the new node next pointer to the current head*/
        newNode->setNext(this->head); 

        /* Point the head previous pointer to the new node*/
        this->head->setPrev(newNode); 
        
        /* Update head*/
        this->head = newNode;
    }

    this->size++; 
}


/*****************************************************************************
 *
 * Method:    append
 *
 * Description: Insert a new node at the end of the list.
 *
 * Parameters:
 *      data - The data to be stored in the new node.
 *
 * Caveats:
 *    
 *
 *****************************************************************************/

void List::append(float data)
{
    /* Instance a new node and save a pointer to it*/
    Node* newNode = new Node(data); 

    if(this->isEmpty())
    {
        /* First element of the list, head == tail*/
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        /* Point current tail towards new node*/
        this->tail->setNext(newNode);

        /* Point newNode towards old tail*/
        newNode->setPrev(this->tail);

        /* Update tail.*/
        this->tail = newNode; 
    }

    this->size++; 
}


/*****************************************************************************
 *
 * Method:    append
 *
 * Description: Insert a new node at the end of the list.
 *
 * Parameters:
 *      data - The data to be stored in the new node.
 *
 * Caveats:
 *    
 *
 *****************************************************************************/

void List::print()
{

    if (this->isEmpty())
    {
        std::cout << "The list is empty. " << std::endl;
        return; 
    }

    Node* currentNode = this->head; 

    while (currentNode != nullptr)
    {
        std::cout << currentNode->getData() << " -> "; 
        currentNode = currentNode->getNext(); 
    }

    std::cout << std::endl; 

}


/*****************************************************************************
 *
 * Method:    isEmpty
 *
 * Description: determines if the list is empty. 
 *
 * Parameters:
 *      None
 * 
 * Return: 
 *      Bool
 *
 * Caveats:
 *    
 *
 *****************************************************************************/

bool List::isEmpty()
{
    bool retVal = false; 

    if (this->head == nullptr)
    {
        retVal = true; 
    }

    return retVal; 
    
}

/*****************************************************************************
 *
 * Method:    getSize
 *
 * Description: Returns list size. 
 *
 * Parameters:
 *      None
 * 
 * Return: 
 *      Bool
 *
 * Caveats:
 *    
 *
 *****************************************************************************/

int List::getSize(void)
{
    return this->size; 
}


/*****************************************************************************
 *
 * Method:    removeAtEnd
 *
 * Description:  Removes the tail element
 *
 * Parameters:
 *      None
 * 
 * Return: 
 *      None
 *
 * Caveats:
 *    
 *
 *****************************************************************************/

void List::removeAtEnd(void)
{
    if(this->isEmpty())
    {
        std::cout << "Nothing to remove, the list is empty." << std::endl;
        return; 
    }
    else if (this->head == this->tail) /* List has only one element*/
    {
        //delete this->head;  We need at least one member.
        this->head = nullptr; 
        this->tail = nullptr;
        this->size--; 
    }
    else
    {
        /* List has more than one element*/
        Node* newTail = this->tail->getPrev();
        newTail->setNext(nullptr);

        Node* nodeToDelete = this->tail; 
        delete nodeToDelete;

        this->tail = newTail; 
        this->size--;  
    }
}

/*****************************************************************************
 *
 * Method:    removeAtFront
 *
 * Description:  Removes the head element.
 *
 * Parameters:
 *      None
 * 
 * Return: 
 *      None
 *
 * Caveats:
 *    
 *
 *****************************************************************************/

void List::removeAtFront(void)
{
    if(this->isEmpty())
    {
        std::cout << "Nothing to remove, the list is empty." << std::endl;
        return; 
    }
    else if (this->head == this->tail) /* List has only one element*/
    {
        //delete this->head; We need at least one member 
        this->head = nullptr; 
        this->tail = nullptr;
        this->size--; 
    }
    else
    {
        /* List has more than one element*/
        Node* oldHead = this->head; 
        this->head = this->head->getNext(); 
        this->head->setPrev(nullptr);

        delete oldHead;
        this->size--;  
    }
}


