#include <stdio.h>
#include <stdlib.h>

#ifndef _STACK_QUEUE_H
#define _STACK_QUEUE_H 1

#define ACT_AS_QUEUE 2
#define ACT_AS_STACK 4

/// @brief An abstaract node to implement a linked list
typedef struct _abstract_node
{
    void *data;                  // pointer to data inside the node
    struct _abstract_node *next; // the next node
    struct _abstract_node *prev; // the prev node

} abstract_node, *p_abstract_node;

/// @brief An abstract list
typedef struct _abstract_list
{
    size_t elements;       // number of elements in queue
    p_abstract_node rear;  // pointer to the previous element
    p_abstract_node front; // pointer to the next element

} abstract_list, *p_abstract_list;

/// @brief Return a new heap allocate abstract_node.
///
/// @return The pointer to heap.
///
void *get_node()
{
    return calloc(1, sizeof(abstract_node));
}

/// @brief Return a new heap allocate abstract_list.
///
/// @return The pointer to heap.
///
void *get_list()
{
    return calloc(1, sizeof(abstract_list));
}

/// @brief Add a element to the list.
///
/// @param q The list where to add.
/// @param e The element to add.
///
/// @return
///
int push(p_abstract_list q, void *e)
{
    // allocate a new node
    p_abstract_node n = (p_abstract_node)get_node();

    // fail fast if no memory
    if (!n)
    {
        return 1;
    }

    // assign the data to it
    n->data = e;

    q->elements++;

    // if the node is the first
    if (q->rear == NULL)
    {
        q->rear = n;
        q->front = n;

        return 0;
    }

    // last node next become the new last node
    q->rear->next = n;

    // last node prev become the rear
    n->prev = q->rear;

    // the new last node become the new rear
    q->rear = n;

    return 0;
}

static void *_pop_poll(p_abstract_list q, int action)
{
    // if the list is void exit fast
    if (!q->elements)
    {
        return NULL;
    }

    // the node will be returned
    p_abstract_node n;

    switch (action)
    {
    case ACT_AS_QUEUE:
        // get the node
        n = q->front;
        // detach the node from the list
        q->front = q->front->next;
        break;

    case ACT_AS_STACK:
        // get the node
        n = q->rear;
        // detach the node from the list
        q->rear = q->rear->prev;
        break;

    default:
        return NULL;
        break;
    }

    //decrement the number of the elements in queue
    q->elements--;

    // if last element removed
    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    // get the pointer to the data carried by element
    void *e = n->data;
    // remove the pointer to the data
    n->data = NULL;
    // free pointer after set the link
    free(n);

    return e;
}

/// @brief Remove the oldest inserted element of the list
///
/// @param q The list where to remove.
///
/// @return The removed element.
///
void *poll(p_abstract_list q)
{
    return _pop_poll(q, ACT_AS_QUEUE);
}

/// @brief Remove the oldest element of the list
///
/// @param q The list where to remove.
///
/// @return The removed element.
///
void *pop(p_abstract_list q)
{
    return _pop_poll(q, ACT_AS_STACK);
}

#endif /* stack_queue.h */