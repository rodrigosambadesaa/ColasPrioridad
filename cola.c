#include "cola.h"

#include <stdlib.h>

void queue_init(queue_t *queue)
{
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

int queue_is_empty(const queue_t *queue)
{
    return queue->head == NULL;
}

int queue_enqueue(queue_t *queue, process_id_t value)
{
    queue_node_t *new_node = (queue_node_t *)malloc(sizeof(queue_node_t));
    if (new_node == NULL)
    {
        return 0;
    }

    new_node->value = value;
    new_node->sig = NULL;

    if (queue->tail == NULL)
    {
        queue->head = new_node;
        queue->tail = new_node;
    }
    else
    {
        queue->tail->sig = new_node;
        queue->tail = new_node;
    }

    queue->size++;
    return 1;
}

int queue_peek(const queue_t *queue, process_id_t *value)
{
    if (queue_is_empty(queue))
    {
        return 0;
    }

    if (value != NULL)
    {
        *value = queue->head->value;
    }
    return 1;
}

int queue_dequeue(queue_t *queue, process_id_t *value)
{
    queue_node_t *tmp;

    if (queue_is_empty(queue))
    {
        return 0;
    }

    tmp = queue->head;
    if (value != NULL)
    {
        *value = tmp->value;
    }

    queue->head = tmp->sig;
    if (queue->head == NULL)
    {
        queue->tail = NULL;
    }

    free(tmp);
    queue->size--;
    return 1;
}

void queue_free(queue_t *queue)
{

    while (queue_dequeue(queue, NULL))
    {
    }
}
