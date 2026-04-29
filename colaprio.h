#ifndef COLAPRIO_H
#define COLAPRIO_H

#include "cola.h"

#define PRIORITY_QUEUE_COUNT 100

typedef struct colaindividual
{
    int prioridad;
    queue_t queue;
} priority_queue_bucket_t;

typedef priority_queue_bucket_t *priority_queue_t;

priority_queue_t priority_queue_create(const int priorities[PRIORITY_QUEUE_COUNT]);
void priority_queue_destroy(priority_queue_t *priority_queue);

int priority_queue_is_empty(priority_queue_t priority_queue);
int priority_queue_peek(priority_queue_t priority_queue, process_id_t *process);
int priority_queue_pop(priority_queue_t priority_queue);
int priority_queue_push(priority_queue_t priority_queue, process_id_t process, int priority);

#endif
