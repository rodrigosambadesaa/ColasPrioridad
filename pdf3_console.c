#include <stdio.h>
#include <string.h>

#include "pdf3_queue.h"
#include "pdf3_sergas.h"

static person_data_t make_person(const char *name,
                                 const char *dni,
                                 const char *nationality,
                                 unsigned short age,
                                 unsigned short vaccines_received)
{
    person_data_t person;

    memset(&person, 0, sizeof(person));
    snprintf(person.name, sizeof(person.name), "%s", name);
    snprintf(person.dni, sizeof(person.dni), "%s", dni);
    snprintf(person.nationality, sizeof(person.nationality), "%s", nationality);
    person.age = age;
    person.vaccines_received = vaccines_received;
    return person;
}

static int load_sample_data(sergas_list_t list)
{
    return sergas_list_push_back(list, make_person("Ana", "11111111", "España", 82U, 2U)) &&
           sergas_list_push_back(list, make_person("Brais", "22222222", "España", 85U, 3U)) &&
           sergas_list_push_back(list, make_person("Carla", "33333333", "Portugal", 49U, 1U)) &&
           sergas_list_push_back(list, make_person("Diego", "44444444", "España", 91U, 1U)) &&
           sergas_list_push_back(list, make_person("Eva", "55555555", "Francia", 30U, 4U));
}

static int test_pointer_queue_ops(void)
{
    pointer_queue_t queue;
    queue_element_t value;

    pointer_queue_init(&queue);

    if (!pointer_queue_push_back(&queue, 10) ||
        !pointer_queue_push_back(&queue, 20) ||
        !pointer_queue_push_back(&queue, 30))
    {
        return 0;
    }

    if (!pointer_queue_pop_front(&queue, &value) || value != 10)
    {
        return 0;
    }

    if (!pointer_queue_pop_front(&queue, &value) || value != 20)
    {
        return 0;
    }

    if (!pointer_queue_pop_front(&queue, &value) || value != 30)
    {
        return 0;
    }

    if (pointer_queue_pop_front(&queue, &value))
    {
        return 0;
    }

    return 1;
}

static int test_vaccination_priority_queue(void)
{
    sergas_list_t list = sergas_list_create();
    vaccine_priority_queue_t queue = vaccine_priority_queue_create();
    person_data_t current;

    if (list == NULL || queue == NULL)
    {
        sergas_list_destroy(&list);
        vaccine_priority_queue_destroy(&queue);
        return 0;
    }

    if (!load_sample_data(list) || !build_vaccination_queue_from_sergas(list, queue))
    {
        sergas_list_destroy(&list);
        vaccine_priority_queue_destroy(&queue);
        return 0;
    }

    if (!vaccine_priority_queue_pop(queue, &current) || strcmp(current.name, "Ana") != 0)
    {
        return 0;
    }
    if (!vaccine_priority_queue_pop(queue, &current) || strcmp(current.name, "Diego") != 0)
    {
        return 0;
    }
    if (!vaccine_priority_queue_pop(queue, &current) || strcmp(current.name, "Brais") != 0)
    {
        return 0;
    }
    if (!vaccine_priority_queue_pop(queue, &current) || strcmp(current.name, "Carla") != 0)
    {
        return 0;
    }
    if (!vaccine_priority_queue_is_empty(queue))
    {
        return 0;
    }

    if (count_elderly_with_less_than_three(list) != 2U)
    {
        return 0;
    }

    if (!exists_foreign_with_less_than_three(list, "Portugal"))
    {
        return 0;
    }

    if (exists_foreign_with_less_than_three(list, "Italia"))
    {
        return 0;
    }

    sergas_list_destroy(&list);
    vaccine_priority_queue_destroy(&queue);
    return 1;
}

static void run_demo(void)
{
    sergas_list_t list = sergas_list_create();
    vaccine_priority_queue_t queue = vaccine_priority_queue_create();
    person_data_t person;

    if (list == NULL || queue == NULL)
    {
        printf("No se pudo iniciar la demo.\n");
        sergas_list_destroy(&list);
        vaccine_priority_queue_destroy(&queue);
        return;
    }

    if (!load_sample_data(list) || !build_vaccination_queue_from_sergas(list, queue))
    {
        printf("No se pudo cargar la demo.\n");
        sergas_list_destroy(&list);
        vaccine_priority_queue_destroy(&queue);
        return;
    }

    printf("Orden de llamada para vacunacion:\n");
    while (vaccine_priority_queue_pop(queue, &person))
    {
        printf("- %s (%s), edad %hu, vacunas %hu\n",
               person.name,
               person.nationality,
               person.age,
               person.vaccines_received);
    }

    sergas_list_destroy(&list);
    vaccine_priority_queue_destroy(&queue);
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "--test") == 0)
    {
        if (test_pointer_queue_ops() && test_vaccination_priority_queue())
        {
            printf("Pruebas PDF3: OK\n");
            return 0;
        }

        printf("Pruebas PDF3: ERROR\n");
        return 1;
    }

    run_demo();
    printf("Ejecuta con --test para lanzar las pruebas automáticas.\n");
    return 0;
}
