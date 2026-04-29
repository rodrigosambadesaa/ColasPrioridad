#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colaprio.h"

static void load_priorities(int priorities[PRIORITY_QUEUE_COUNT])
{
    int index;

    for (index = 0; index < PRIORITY_QUEUE_COUNT; index++)
    {
        priorities[index] = index + 1;
    }
}

static void load_demo_data(priority_queue_t priority_queue)
{
    priority_queue_push(priority_queue, 4567, 34);
    priority_queue_push(priority_queue, 6789, 34);
    priority_queue_push(priority_queue, 2290, 34);

    priority_queue_push(priority_queue, 7777, 45);
    priority_queue_push(priority_queue, 2323, 45);
    priority_queue_push(priority_queue, 9999, 45);
    priority_queue_push(priority_queue, 9897, 45);

    priority_queue_push(priority_queue, 1122, 100);
    priority_queue_push(priority_queue, 2555, 100);
    priority_queue_push(priority_queue, 1001, 100);
    priority_queue_push(priority_queue, 1003, 100);
}

static void run_demo_mode(priority_queue_t priority_queue)
{
    process_id_t process;

    load_demo_data(priority_queue);
    printf("Orden de ejecucion esperado: 1122, 2555, 1001, 1003, 7777...\n");

    while (priority_queue_peek(priority_queue, &process))
    {
        printf("Siguiente proceso: %ld\n", process);
        priority_queue_pop(priority_queue);
    }
}

static void print_console_menu(void)
{
    printf("\n=== Cola de Prioridad (modo consola) ===\n");
    printf("1) Insertar proceso\n");
    printf("2) Ver siguiente proceso\n");
    printf("3) Ejecutar (eliminar) siguiente proceso\n");
    printf("4) Consultar si esta vacia\n");
    printf("5) Ejecutar demo predefinida\n");
    printf("0) Salir\n");
    printf("Selecciona una opcion: ");
}

static int read_int_value(const char *prompt, int *value)
{
    char buffer[128];
    char *endptr;
    long parsed_value;

    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 0;
    }

    parsed_value = strtol(buffer, &endptr, 10);
    if (endptr == buffer)
    {
        return 0;
    }

    *value = (int)parsed_value;
    return 1;
}

static void run_console_mode(priority_queue_t priority_queue)
{
    int option;
    int priority;
    int process_as_int;
    process_id_t process;

    for (;;)
    {
        print_console_menu();
        if (!read_int_value("", &option))
        {
            printf("Entrada no valida.\n");
            continue;
        }

        if (option == 0)
        {
            printf("Saliendo del modo consola.\n");
            break;
        }

        if (option == 1)
        {
            if (!read_int_value("PID del proceso: ", &process_as_int) ||
                !read_int_value("Prioridad (1-100): ", &priority))
            {
                printf("Datos invalidos.\n");
                continue;
            }

            if (!priority_queue_push(priority_queue, (process_id_t)process_as_int, priority))
            {
                printf("No se pudo insertar: prioridad no encontrada o error de memoria.\n");
            }
            else
            {
                printf("Proceso insertado.\n");
            }
            continue;
        }

        if (option == 2)
        {
            if (priority_queue_peek(priority_queue, &process))
            {
                printf("Siguiente proceso: %ld\n", process);
            }
            else
            {
                printf("La cola esta vacia.\n");
            }
            continue;
        }

        if (option == 3)
        {
            if (priority_queue_peek(priority_queue, &process))
            {
                priority_queue_pop(priority_queue);
                printf("Ejecutado proceso: %ld\n", process);
            }
            else
            {
                printf("La cola esta vacia.\n");
            }
            continue;
        }

        if (option == 4)
        {
            printf("Estado: %s\n", priority_queue_is_empty(priority_queue) ? "vacia" : "con procesos");
            continue;
        }

        if (option == 5)
        {
            run_demo_mode(priority_queue);
            continue;
        }

        printf("Opcion no valida.\n");
    }
}

int main(int argc, char **argv)
{
    int priorities[PRIORITY_QUEUE_COUNT];
    priority_queue_t priority_queue;

    load_priorities(priorities);
    priority_queue = priority_queue_create(priorities);
    if (priority_queue == NULL)
    {
        fprintf(stderr, "No se pudo crear la cola de prioridad.\n");
        return 1;
    }

    if (argc > 1 && strcmp(argv[1], "--console") == 0)
    {
        run_console_mode(priority_queue);
    }
    else
    {
        run_demo_mode(priority_queue);
    }

    priority_queue_destroy(&priority_queue);
    return 0;
}
