#ifndef COLA_H
#define COLA_H

#include <stddef.h>

typedef long process_id_t;

typedef struct nodo_cola
{
    process_id_t value;
    struct nodo_cola *sig;
} queue_node_t;

typedef struct
{
    queue_node_t *head;
    queue_node_t *tail;
    size_t size;
} queue_t;

void queue_init(queue_t *queue);
int queue_is_empty(const queue_t *queue);
int queue_enqueue(queue_t *queue, process_id_t value);
int queue_peek(const queue_t *queue, process_id_t *value);
int queue_dequeue(queue_t *queue, process_id_t *value);
void queue_free(queue_t *queue);

#endif
