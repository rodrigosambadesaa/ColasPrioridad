#include "colaprio.h"

#include <stdlib.h>

static int find_priority_index(priority_queue_t priority_queue, int priority)
{
    int left = 0;
    int right = PRIORITY_QUEUE_COUNT - 1;

    while (left <= right)
    {
        int middle = left + (right - left) / 2;
        int current_priority = priority_queue[middle].prioridad;

        if (current_priority == priority)
        {
            return middle;
        }
        if (current_priority < priority)
        {
            left = middle + 1;
        }
        else
        {
            right = middle - 1;
        }
    }

    return -1;
}

priority_queue_t priority_queue_create(const int priorities[PRIORITY_QUEUE_COUNT])
{
    int index;
    priority_queue_bucket_t *priority_queue =
        (priority_queue_bucket_t *)malloc(sizeof(priority_queue_bucket_t) * PRIORITY_QUEUE_COUNT);

    if (priority_queue == NULL)
    {
        return NULL;
    }

    for (index = 0; index < PRIORITY_QUEUE_COUNT; index++)
    {
        priority_queue[index].prioridad = priorities[index];
        queue_init(&priority_queue[index].queue);
    }

    return priority_queue;
}

void priority_queue_destroy(priority_queue_t *priority_queue)
{
    int index;

    if (priority_queue == NULL || *priority_queue == NULL)
    {
        return;
    }

    for (index = 0; index < PRIORITY_QUEUE_COUNT; index++)
    {
        queue_free(&(*priority_queue)[index].queue);
    }

    free(*priority_queue);
    *priority_queue = NULL;
}

int priority_queue_is_empty(priority_queue_t priority_queue)
{
    int index;

    if (priority_queue == NULL)
    {
        return 1;
    }

    for (index = PRIORITY_QUEUE_COUNT - 1; index >= 0; index--)
    {
        if (!queue_is_empty(&priority_queue[index].queue))
        {
            return 0;
        }
    }
    return 1;
}

int priority_queue_peek(priority_queue_t priority_queue, process_id_t *process)
{
    int index;

    if (priority_queue == NULL || process == NULL)
    {
        return 0;
    }

    for (index = PRIORITY_QUEUE_COUNT - 1; index >= 0; index--)
    {
        if (!queue_is_empty(&priority_queue[index].queue))
        {
            return queue_peek(&priority_queue[index].queue, process);
        }
    }

    return 0;
}

int priority_queue_pop(priority_queue_t priority_queue)
{
    int index;

    if (priority_queue == NULL)
    {
        return 0;
    }

    for (index = PRIORITY_QUEUE_COUNT - 1; index >= 0; index--)
    {
        if (!queue_is_empty(&priority_queue[index].queue))
        {
            return queue_dequeue(&priority_queue[index].queue, NULL);
        }
    }

    return 0;
}

int priority_queue_push(priority_queue_t priority_queue, process_id_t process, int priority)
{
    int index;

    if (priority_queue == NULL)
    {
        return 0;
    }

    index = find_priority_index(priority_queue, priority);
    if (index < 0)
    {
        return 0;
    }

    return queue_enqueue(&priority_queue[index].queue, process);
}
