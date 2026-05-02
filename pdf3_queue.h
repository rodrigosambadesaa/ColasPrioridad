#ifndef PDF3_QUEUE_H
#define PDF3_QUEUE_H

typedef int queue_element_t;

typedef struct queue_node
{
    queue_element_t data;
    struct queue_node *next;
} queue_node_t;

typedef struct
{
    queue_node_t *front;
    queue_node_t *back;
} pointer_queue_t;

void pointer_queue_init(pointer_queue_t *queue);
int pointer_queue_is_empty(const pointer_queue_t *queue);
int pointer_queue_push_back(pointer_queue_t *queue, queue_element_t value);
int pointer_queue_pop_front(pointer_queue_t *queue, queue_element_t *out_value);
void pointer_queue_free(pointer_queue_t *queue);

#endif