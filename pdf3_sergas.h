#ifndef PDF3_SERGAS_H
#define PDF3_SERGAS_H

#include <stddef.h>

typedef struct
{
    char name[100];
    char dni[10];
    char nationality[100];
    unsigned short age;
    unsigned short vaccines_received;
} person_data_t;

typedef struct sergas_list *sergas_list_t;
typedef struct sergas_position *sergas_position_t;

typedef struct vaccine_priority_queue *vaccine_priority_queue_t;

sergas_list_t sergas_list_create(void);
void sergas_list_destroy(sergas_list_t *list);
int sergas_list_push_back(sergas_list_t list, person_data_t person);
int sergas_list_is_empty(sergas_list_t list);
sergas_position_t sergas_list_first(sergas_list_t list);
sergas_position_t sergas_list_end(sergas_list_t list);
sergas_position_t sergas_list_next(sergas_list_t list, sergas_position_t position);
int sergas_list_get(sergas_list_t list, sergas_position_t position, person_data_t *out_person);

vaccine_priority_queue_t vaccine_priority_queue_create(void);
void vaccine_priority_queue_destroy(vaccine_priority_queue_t *queue);
int vaccine_priority_queue_is_empty(vaccine_priority_queue_t queue);
int vaccine_priority_queue_push(vaccine_priority_queue_t queue, person_data_t person, unsigned int priority);
int vaccine_priority_queue_peek(vaccine_priority_queue_t queue, person_data_t *out_person);
int vaccine_priority_queue_pop(vaccine_priority_queue_t queue, person_data_t *out_person);

int build_vaccination_queue_from_sergas(sergas_list_t people_list, vaccine_priority_queue_t vaccine_queue);
size_t count_elderly_with_less_than_three(sergas_list_t people_list);
int exists_foreign_with_less_than_three(sergas_list_t people_list, const char *nationality);

#endif