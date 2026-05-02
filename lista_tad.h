#ifndef LISTA_TAD_H
#define LISTA_TAD_H

#include <stddef.h>

typedef struct
{
    long process_id;
    int priority;
} process_entry_t;

typedef struct list_node list_node_t;
typedef struct list *list_t;
typedef list_node_t *list_position_t;

list_t list_create(void);
void list_destroy(list_t *list);
int list_is_empty(list_t list);
size_t list_length(list_t list);

list_position_t list_first(list_t list);
list_position_t list_next(list_t list, list_position_t position);
list_position_t list_end(list_t list);

int list_retrieve(list_t list, list_position_t position, process_entry_t *out_entry);
int list_push_back(list_t list, process_entry_t entry);

#endif