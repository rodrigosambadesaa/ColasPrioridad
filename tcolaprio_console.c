#include <stdio.h>
#include <string.h>

#include "tcolaprio_lista.h"

static int run_example_from_statement(void)
{
    tcola_prio_t queue = tcola_prio_create();
    long result;

    if (queue == NULL)
    {
        return 0;
    }

    if (!tcola_prio_enqueue(queue, 1234L, 2) ||
        !tcola_prio_enqueue(queue, 345L, 1) ||
        !tcola_prio_enqueue(queue, 1245L, 3) ||
        !tcola_prio_enqueue(queue, 8888L, 3))
    {
        tcola_prio_destroy(&queue);
        return 0;
    }

    result = primero_cola_prio(queue);
    printf("Primer proceso con mayor prioridad: %ld\n", result);

    tcola_prio_destroy(&queue);
    return result == 1245L;
}

static int run_additional_test(void)
{
    tcola_prio_t queue = tcola_prio_create();
    long result;

    if (queue == NULL)
    {
        return 0;
    }

    if (!tcola_prio_enqueue(queue, 10L, 1) ||
        !tcola_prio_enqueue(queue, 20L, 2) ||
        !tcola_prio_enqueue(queue, 30L, 2))
    {
        tcola_prio_destroy(&queue);
        return 0;
    }

    result = primero_cola_prio(queue);
    tcola_prio_destroy(&queue);
    return result == 20L;
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "--test") == 0)
    {
        if (run_example_from_statement() && run_additional_test())
        {
            printf("Pruebas TCOLAPRIO (lista): OK\n");
            return 0;
        }

        printf("Pruebas TCOLAPRIO (lista): ERROR\n");
        return 1;
    }

    if (!run_example_from_statement())
    {
        printf("Error ejecutando el ejemplo.\n");
        return 1;
    }

    printf("Ejecuta con --test para lanzar todas las pruebas.\n");
    return 0;
}
