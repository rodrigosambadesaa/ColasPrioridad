#include "lista_tad.h"

#include <stdlib.h>

struct list_node
{
    process_entry_t entry;
    struct list_node *next;
};

struct list
{
    list_position_t head;
    list_position_t tail;
    size_t length;
};

list_t list_create(void)
{
    list_t list = (list_t)malloc(sizeof(*list));
    if (list == NULL)
    {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0U;
    return list;
}

void list_destroy(list_t *list)
{
    list_position_t current;

    if (list == NULL || *list == NULL)
    {
        return;
    }

    current = (*list)->head;
    while (current != NULL)
    {
        list_position_t next = current->next;
        free(current);
        current = next;
    }

    free(*list);
    *list = NULL;
}

int list_is_empty(list_t list)
{
    return list == NULL || list->head == NULL;
}

size_t list_length(list_t list)
{
    if (list == NULL)
    {
        return 0U;
    }

    return list->length;
}

list_position_t list_first(list_t list)
{
    if (list == NULL)
    {
        return NULL;
    }

    return list->head;
}

list_position_t list_next(list_t list, list_position_t position)
{
    (void)list;
    if (position == NULL)
    {
        return NULL;
    }

    return position->next;
}

list_position_t list_end(list_t list)
{
    (void)list;
    return NULL;
}

int list_retrieve(list_t list, list_position_t position, process_entry_t *out_entry)
{
    if (list == NULL || position == NULL || out_entry == NULL)
    {
        return 0;
    }

    *out_entry = position->entry;
    return 1;
}

int list_push_back(list_t list, process_entry_t entry)
{
    list_position_t node;

    if (list == NULL)
    {
        return 0;
    }

    node = (list_position_t)malloc(sizeof(*node));
    if (node == NULL)
    {
        return 0;
    }

    node->entry = entry;
    node->next = NULL;

    if (list->tail == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }

    list->length++;
    return 1;
}
