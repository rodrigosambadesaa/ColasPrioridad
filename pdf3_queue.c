#include "pdf3_queue.h"

#include <stdlib.h>

void pointer_queue_init(pointer_queue_t *queue)
{
    if (queue == NULL)
    {
        return;
    }

    queue->front = NULL;
    queue->back = NULL;
}

int pointer_queue_is_empty(const pointer_queue_t *queue)
{
    return queue == NULL || queue->front == NULL;
}

int pointer_queue_push_back(pointer_queue_t *queue, queue_element_t value)
{
    queue_node_t *new_node;

    if (queue == NULL)
    {
        return 0;
    }

    new_node = (queue_node_t *)malloc(sizeof(*new_node));
    if (new_node == NULL)
    {
        return 0;
    }

    new_node->data = value;
    new_node->next = NULL;

    if (queue->back == NULL)
    {
        queue->front = new_node;
        queue->back = new_node;
    }
    else
    {
        queue->back->next = new_node;
        queue->back = new_node;
    }

    return 1;
}

int pointer_queue_pop_front(pointer_queue_t *queue, queue_element_t *out_value)
{
    queue_node_t *old_front;

    if (pointer_queue_is_empty(queue))
    {
        return 0;
    }

    old_front = queue->front;
    if (out_value != NULL)
    {
        *out_value = old_front->data;
    }

    queue->front = old_front->next;
    if (queue->front == NULL)
    {
        queue->back = NULL;
    }

    free(old_front);
    return 1;
}

void pointer_queue_free(pointer_queue_t *queue)
{
    while (pointer_queue_pop_front(queue, NULL))
    {
    }
}
