#include "tcolaprio_lista.h"

tcola_prio_t tcola_prio_create(void)
{
    return list_create();
}

void tcola_prio_destroy(tcola_prio_t *queue)
{
    list_destroy(queue);
}

int tcola_prio_enqueue(tcola_prio_t queue, long process_id, int priority)
{
    process_entry_t entry;

    if (priority < 1 || priority > 3)
    {
        return 0;
    }

    entry.process_id = process_id;
    entry.priority = priority;
    return list_push_back(queue, entry);
}

long primero_cola_prio(tcola_prio_t queued_processes)
{
    list_position_t position;
    process_entry_t current_entry;
    long first_process_with_max_priority = -1;
    int max_priority = 0;

    if (queued_processes == NULL || list_is_empty(queued_processes))
    {
        return -1;
    }

    position = list_first(queued_processes);
    while (position != list_end(queued_processes))
    {
        if (!list_retrieve(queued_processes, position, &current_entry))
        {
            return -1;
        }

        if (current_entry.priority > max_priority)
        {
            max_priority = current_entry.priority;
            first_process_with_max_priority = current_entry.process_id;

            if (max_priority == 3)
            {
                break;
            }
        }

        position = list_next(queued_processes, position);
    }

    return first_process_with_max_priority;
}
