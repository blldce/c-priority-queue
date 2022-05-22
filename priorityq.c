
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue init_queue_stack(void)
{
    struct queue ret_queue = {.dequeue = dequeue, .enqueue = enqueue, .peek = peek, .head_node = (void(*))0, .size = 0};

    return ret_queue;
}

struct queue *init_queue_heap(void)
{
    struct queue(*ret_queue_ptr) = (struct queue(*))malloc(sizeof(struct queue));
    ret_queue_ptr->dequeue = dequeue;
    ret_queue_ptr->enqueue = enqueue;
    ret_queue_ptr->peek = peek;
    ret_queue_ptr->size = 0;
    ret_queue_ptr->head_node = (void(*))0;
    return ret_queue_ptr;
}

int enqueue(struct queue(*queue_ptr), int data, enum priority priority)
{
    struct node(*new_node) = (struct node(*))malloc(sizeof(struct node));
    new_node->data = data;
    new_node->priority = priority;

    if (queue_ptr->head_node == (void(*))0) // not first time?
        queue_ptr->head_node = new_node;
    else
    {
        struct node(*lower_priority_node) = queue_ptr->head_node;
        struct node(*pre_lower_priority_node) = lower_priority_node;
        char is_head = 1;  // starting from head
        while (lower_priority_node != (void(*))0)
        {
            if (priority >= lower_priority_node->priority) // iterate through greater priorties
                break;
            is_head = 0;
            pre_lower_priority_node = lower_priority_node;
            lower_priority_node = lower_priority_node->previous_node;
        }
        // we found lower priority than new node!
        if (lower_priority_node != (void(*))0)
        {
            new_node->previous_node = lower_priority_node;
            if (is_head)
                queue_ptr->head_node = new_node;
            else
                pre_lower_priority_node->previous_node = new_node;
        }
        else // there is no lower priority than new node! new node is lowest priority!
            pre_lower_priority_node->previous_node = new_node;
    }
    queue_ptr->size++;
    return 1;
}

int dequeue(struct queue(*queue_ptr))
{
    if (queue_ptr->size == 0)
        return 0;
    if (queue_ptr->size == 1) // we're in head
    {
        queue_ptr->head_node = (void(*))0;
        queue_ptr->size--;
        return 1;
    }
    struct node(*iter) = queue_ptr->head_node;
    struct node(*prev_node_ptr) = iter;
    while (iter->previous_node != (void(*))0)
    {
        prev_node_ptr = iter;
        iter = iter->previous_node;
    }
    prev_node_ptr->previous_node = (void(*))0;
    queue_ptr->size--;
    return 1;
}

int peek(struct queue(*queue_ptr), int data)
{
    if (queue_ptr->size == 0)
        return 0;
    struct node(*iter) = queue_ptr->head_node;
    while (iter != (void(*))0)
    {
        if (iter->data == data)
            return 1; // founded!
        iter = iter->previous_node;
    }
    return 0; // not found!
}

void print_items(struct queue(*queue_ptr))
{
    if (queue_ptr->size == 0)
        return;
    printf("*********************\n");
    struct node(*iter) = queue_ptr->head_node;
    int size = queue_ptr->size;
    while (iter != (void(*))0)
    {
        printf("Priority : %d -- Address : %p -- Value : %d -- Prev : %p \n", iter->priority, iter, iter->data, iter->previous_node);
        iter = iter->previous_node;
    }
    return;
}
