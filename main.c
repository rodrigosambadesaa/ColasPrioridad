#include <stdio.h>

#include "colaprio.h"

static void cargarPrioridades(int prioridades[NUM_COLAS_PRIO])
{
    int i;
    for (i = 0; i < NUM_COLAS_PRIO; i++)
    {
        prioridades[i] = i + 1;
    }
}

int main(void)
{
    int prioridades[NUM_COLAS_PRIO];
    TCOLAPRIO cola_prio;
    PID proceso;

    cargarPrioridades(prioridades);
    cola_prio = crearColaPrio(prioridades);
    if (cola_prio == NULL)
    {
        fprintf(stderr, "No se pudo crear la cola de prioridad.\n");
        return 1;
    }

    anadirColaPrio(cola_prio, 4567, 34);
    anadirColaPrio(cola_prio, 6789, 34);
    anadirColaPrio(cola_prio, 2290, 34);

    anadirColaPrio(cola_prio, 7777, 45);
    anadirColaPrio(cola_prio, 2323, 45);
    anadirColaPrio(cola_prio, 9999, 45);
    anadirColaPrio(cola_prio, 9897, 45);

    anadirColaPrio(cola_prio, 1122, 100);
    anadirColaPrio(cola_prio, 2555, 100);
    anadirColaPrio(cola_prio, 1001, 100);
    anadirColaPrio(cola_prio, 1003, 100);

    printf("Orden de ejecucion esperado: 1122, 2555, 1001, 1003, 7777...\n");
    while (primeroColaPrio(cola_prio, &proceso))
    {
        printf("Siguiente proceso: %ld\n", proceso);
        eliminarColaPrio(cola_prio);
    }

    destruirColaPrio(&cola_prio);
    return 0;
}
