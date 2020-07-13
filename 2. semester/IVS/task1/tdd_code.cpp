//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     IVAN BOBROV <xbobro01@stud.fit.vutbr.cz>
// $Date:       $2020-03-03
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author IVAN BOBROV
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    // pointer to first list element
    head = NULL;
}

PriorityQueue::~PriorityQueue()
{
    // list destructor
    Element_t *q_head = GetHead();
    Element_t *del_node = NULL;

    while(q_head != NULL) {
        del_node = q_head;
        q_head = q_head->pNext;
        free(del_node);
    }
}


//inserts list element
void PriorityQueue::Insert(int value)
{
    Element_t *new_node = NULL;
    Element_t *tmp_node = GetHead();
    bool is_inserted = false;
    // adding first node
    if (head == NULL) {  
        head = node_ctor(NULL, NULL, value);
    }
    else if (tmp_node->value >= value && tmp_node->pPrev == NULL) {
        // insert as head item
        new_node = node_ctor(NULL, tmp_node, value);
        head = new_node;
        tmp_node->pPrev = new_node;
    }
    else {
        while(tmp_node != NULL && is_inserted == false) {
            // insert node at the middle
            if (tmp_node->value >= value && tmp_node != NULL) {
                new_node = node_ctor(tmp_node->pPrev, tmp_node, value);
                tmp_node->pPrev->pNext = new_node;
                tmp_node->pPrev = new_node;
                is_inserted = true;
            }
            // insert node as last item
            else if(tmp_node->pNext == NULL) {
                new_node = node_ctor(tmp_node, NULL, value);
                tmp_node->pNext = new_node;
                is_inserted = true;
            }
            else {
                // try next node
                tmp_node = tmp_node->pNext;
            }
        }
    }        
}

// remove list item
bool PriorityQueue::Remove(int value)
{
    Element_t *del_node = NULL;
    Element_t *tmp_node = GetHead();
    // if list is empty, return false
    if (head == NULL){
        return false;
    }
    while(tmp_node != NULL) {
        // element at the middle of list
        if(tmp_node->value == value  && tmp_node->pNext != NULL && tmp_node->pPrev != NULL){
            del_node = tmp_node;
            tmp_node->pPrev->pNext = tmp_node->pNext;
            tmp_node->pNext->pPrev = tmp_node->pPrev;
            free(tmp_node);
            return true;
        }
        // tail element
        else if(tmp_node->value == value && tmp_node->pNext == NULL && tmp_node->pPrev != NULL) {
            del_node = tmp_node;
            tmp_node = tmp_node->pPrev;
            tmp_node->pNext = NULL;
            // head = tmp_node->pPrev;
            free(del_node);
            return true;
        }
        // first element
        else if(tmp_node->value == value && tmp_node->pPrev == NULL && tmp_node->pNext != NULL) {
            head = tmp_node->pNext;
            tmp_node->pNext->pPrev = NULL;
            free(tmp_node);
            return true;
        }
        // if only one element exist
        else if(tmp_node->value == value && tmp_node->pNext == NULL && tmp_node->pPrev == NULL) {
            head = NULL;
            free(tmp_node);
            return true;
        }
        // try next node
        else {
            tmp_node = tmp_node->pNext;
        }
    }
    return false;
}

// find node by it's value
PriorityQueue::Element_t *PriorityQueue::Find(int value)
{

    Element_t *tmp_node = GetHead();
    Element_t *founded_node = NULL;

    while(tmp_node != NULL) {
        if(tmp_node->value == value) {
            return tmp_node;
        }
        else {
            tmp_node = tmp_node->pNext;
        }
    }
    return NULL;
}

// get pointer to first element
PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return head;
}

// list node creator
PriorityQueue::Element_t *PriorityQueue::node_ctor(Element_t *prev, Element_t *next, int value)
{
    Element_t *node = (Element_t*)malloc(sizeof(Element_t));
    
    node->pPrev = prev;
    node->pNext = next;
    node->value = value;
    return node;
}
/*** Konec souboru tdd_code.cpp ***/
