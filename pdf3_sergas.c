#include "pdf3_sergas.h"

#include <stdlib.h>
#include <string.h>

typedef struct sergas_position
{
    person_data_t person;
    struct sergas_position *next;
} sergas_node_t;

struct sergas_list
{
    sergas_node_t *head;
    sergas_node_t *tail;
};

typedef struct person_queue_node
{
    person_data_t person;
    struct person_queue_node *next;
} person_queue_node_t;

typedef struct
{
    unsigned int priority;
    person_queue_node_t *head;
    person_queue_node_t *tail;
} priority_bucket_t;

typedef struct bucket_node
{
    priority_bucket_t bucket;
    struct bucket_node *next;
} bucket_node_t;

struct vaccine_priority_queue
{
    bucket_node_t *head;
};

static int is_elderly(const person_data_t *person)
{
    return person->age > 80U;
}

static int has_less_than_three(const person_data_t *person)
{
    return person->vaccines_received < 3U;
}

static unsigned int compute_vaccine_priority(const person_data_t *person)
{
    if (is_elderly(person) && has_less_than_three(person))
    {
        return 3U;
    }

    if (is_elderly(person))
    {
        return 2U;
    }

    if (has_less_than_three(person))
    {
        return 1U;
    }

    return 0U;
}

sergas_list_t sergas_list_create(void)
{
    sergas_list_t list = (sergas_list_t)malloc(sizeof(*list));
    if (list == NULL)
    {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    return list;
}

void sergas_list_destroy(sergas_list_t *list)
{
    sergas_node_t *current;

    if (list == NULL || *list == NULL)
    {
        return;
    }

    current = (*list)->head;
    while (current != NULL)
    {
        sergas_node_t *next = current->next;
        free(current);
        current = next;
    }

    free(*list);
    *list = NULL;
}

int sergas_list_push_back(sergas_list_t list, person_data_t person)
{
    sergas_node_t *new_node;

    if (list == NULL)
    {
        return 0;
    }

    new_node = (sergas_node_t *)malloc(sizeof(*new_node));
    if (new_node == NULL)
    {
        return 0;
    }

    new_node->person = person;
    new_node->next = NULL;

    if (list->tail == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    return 1;
}

int sergas_list_is_empty(sergas_list_t list)
{
    return list == NULL || list->head == NULL;
}

sergas_position_t sergas_list_first(sergas_list_t list)
{
    if (list == NULL)
    {
        return NULL;
    }

    return list->head;
}

sergas_position_t sergas_list_end(sergas_list_t list)
{
    (void)list;
    return NULL;
}

sergas_position_t sergas_list_next(sergas_list_t list, sergas_position_t position)
{
    (void)list;
    if (position == NULL)
    {
        return NULL;
    }

    return position->next;
}

int sergas_list_get(sergas_list_t list, sergas_position_t position, person_data_t *out_person)
{
    (void)list;
    if (position == NULL || out_person == NULL)
    {
        return 0;
    }

    *out_person = position->person;
    return 1;
}

vaccine_priority_queue_t vaccine_priority_queue_create(void)
{
    vaccine_priority_queue_t queue = (vaccine_priority_queue_t)malloc(sizeof(*queue));
    if (queue == NULL)
    {
        return NULL;
    }

    queue->head = NULL;
    return queue;
}

void vaccine_priority_queue_destroy(vaccine_priority_queue_t *queue)
{
    bucket_node_t *bucket_current;

    if (queue == NULL || *queue == NULL)
    {
        return;
    }

    bucket_current = (*queue)->head;
    while (bucket_current != NULL)
    {
        person_queue_node_t *person_current = bucket_current->bucket.head;
        while (person_current != NULL)
        {
            person_queue_node_t *person_next = person_current->next;
            free(person_current);
            person_current = person_next;
        }

        {
            bucket_node_t *bucket_next = bucket_current->next;
            free(bucket_current);
            bucket_current = bucket_next;
        }
    }

    free(*queue);
    *queue = NULL;
}

int vaccine_priority_queue_is_empty(vaccine_priority_queue_t queue)
{
    return queue == NULL || queue->head == NULL;
}

int vaccine_priority_queue_push(vaccine_priority_queue_t queue, person_data_t person, unsigned int priority)
{
    bucket_node_t *current;
    bucket_node_t *previous = NULL;
    person_queue_node_t *new_person_node;

    if (queue == NULL || priority < 1U)
    {
        return 0;
    }

    current = queue->head;
    while (current != NULL && current->bucket.priority > priority)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL || current->bucket.priority != priority)
    {
        bucket_node_t *new_bucket = (bucket_node_t *)malloc(sizeof(*new_bucket));
        if (new_bucket == NULL)
        {
            return 0;
        }

        new_bucket->bucket.priority = priority;
        new_bucket->bucket.head = NULL;
        new_bucket->bucket.tail = NULL;
        new_bucket->next = current;

        if (previous == NULL)
        {
            queue->head = new_bucket;
        }
        else
        {
            previous->next = new_bucket;
        }

        current = new_bucket;
    }

    new_person_node = (person_queue_node_t *)malloc(sizeof(*new_person_node));
    if (new_person_node == NULL)
    {
        return 0;
    }

    new_person_node->person = person;
    new_person_node->next = NULL;

    if (current->bucket.tail == NULL)
    {
        current->bucket.head = new_person_node;
        current->bucket.tail = new_person_node;
    }
    else
    {
        current->bucket.tail->next = new_person_node;
        current->bucket.tail = new_person_node;
    }

    return 1;
}

int vaccine_priority_queue_peek(vaccine_priority_queue_t queue, person_data_t *out_person)
{
    if (vaccine_priority_queue_is_empty(queue) || out_person == NULL)
    {
        return 0;
    }

    *out_person = queue->head->bucket.head->person;
    return 1;
}

int vaccine_priority_queue_pop(vaccine_priority_queue_t queue, person_data_t *out_person)
{
    bucket_node_t *head_bucket;
    person_queue_node_t *head_person;

    if (vaccine_priority_queue_is_empty(queue))
    {
        return 0;
    }

    head_bucket = queue->head;
    head_person = head_bucket->bucket.head;

    if (out_person != NULL)
    {
        *out_person = head_person->person;
    }

    head_bucket->bucket.head = head_person->next;
    if (head_bucket->bucket.head == NULL)
    {
        head_bucket->bucket.tail = NULL;
    }

    free(head_person);

    if (head_bucket->bucket.head == NULL)
    {
        queue->head = head_bucket->next;
        free(head_bucket);
    }

    return 1;
}

int build_vaccination_queue_from_sergas(sergas_list_t people_list, vaccine_priority_queue_t vaccine_queue)
{
    sergas_position_t position;

    if (people_list == NULL || vaccine_queue == NULL)
    {
        return 0;
    }

    position = sergas_list_first(people_list);
    while (position != sergas_list_end(people_list))
    {
        person_data_t person;
        unsigned int priority;

        if (!sergas_list_get(people_list, position, &person))
        {
            return 0;
        }

        priority = compute_vaccine_priority(&person);
        if (priority >= 1U && !vaccine_priority_queue_push(vaccine_queue, person, priority))
        {
            return 0;
        }

        position = sergas_list_next(people_list, position);
    }

    return 1;
}

size_t count_elderly_with_less_than_three(sergas_list_t people_list)
{
    size_t total = 0U;
    sergas_position_t position;

    if (people_list == NULL)
    {
        return 0U;
    }

    position = sergas_list_first(people_list);
    while (position != sergas_list_end(people_list))
    {
        person_data_t person;
        if (sergas_list_get(people_list, position, &person) &&
            is_elderly(&person) &&
            has_less_than_three(&person))
        {
            total++;
        }

        position = sergas_list_next(people_list, position);
    }

    return total;
}

int exists_foreign_with_less_than_three(sergas_list_t people_list, const char *nationality)
{
    sergas_position_t position;

    if (people_list == NULL || nationality == NULL)
    {
        return 0;
    }

    position = sergas_list_first(people_list);
    while (position != sergas_list_end(people_list))
    {
        person_data_t person;
        if (sergas_list_get(people_list, position, &person) &&
            strcmp(person.nationality, nationality) == 0 &&
            has_less_than_three(&person))
        {
            return 1;
        }

        position = sergas_list_next(people_list, position);
    }

    return 0;
}
