#include "colaprio.h"

#include <stdlib.h>

static int buscarIndicePrioridad(TCOLAPRIO tcp, int prioridad)
{
    int izq = 0;
    int der = NUM_COLAS_PRIO - 1;

    while (izq <= der)
    {
        int medio = izq + (der - izq) / 2;
        int p = tcp[medio].prioridad;

        if (p == prioridad)
        {
            return medio;
        }
        if (p < prioridad)
        {
            izq = medio + 1;
        }
        else
        {
            der = medio - 1;
        }
    }

    return -1;
}

TCOLAPRIO crearColaPrio(const int prioridades[NUM_COLAS_PRIO])
{
    int i;
    ColaIndividual *tcp = (ColaIndividual *)malloc(sizeof(ColaIndividual) * NUM_COLAS_PRIO);
    if (tcp == NULL)
    {
        return NULL;
    }

    for (i = 0; i < NUM_COLAS_PRIO; i++)
    {
        tcp[i].prioridad = prioridades[i];
        inicializarCola(&tcp[i].cola);
    }

    return tcp;
}

void destruirColaPrio(TCOLAPRIO *tcp)
{
    int i;

    if (tcp == NULL || *tcp == NULL)
    {
        return;
    }

    for (i = 0; i < NUM_COLAS_PRIO; i++)
    {
        liberarCola(&(*tcp)[i].cola);
    }

    free(*tcp);
    *tcp = NULL;
}

int EsColaVaciaPrio(TCOLAPRIO tcp)
{
    int i;

    if (tcp == NULL)
    {
        return 1;
    }

    for (i = NUM_COLAS_PRIO - 1; i >= 0; i--)
    {
        if (!esColaVacia(&tcp[i].cola))
        {
            return 0;
        }
    }
    return 1;
}

int primeroColaPrio(TCOLAPRIO tcp, PID *proceso)
{
    int i;

    if (tcp == NULL || proceso == NULL)
    {
        return 0;
    }

    for (i = NUM_COLAS_PRIO - 1; i >= 0; i--)
    {
        if (!esColaVacia(&tcp[i].cola))
        {
            return primeroCola(&tcp[i].cola, proceso);
        }
    }

    return 0;
}

int eliminarColaPrio(TCOLAPRIO tcp)
{
    int i;

    if (tcp == NULL)
    {
        return 0;
    }

    for (i = NUM_COLAS_PRIO - 1; i >= 0; i--)
    {
        if (!esColaVacia(&tcp[i].cola))
        {
            return desencolar(&tcp[i].cola, NULL);
        }
    }

    return 0;
}

int anadirColaPrio(TCOLAPRIO tcp, PID proceso, int prioridad)
{
    int indice;

    if (tcp == NULL)
    {
        return 0;
    }

    indice = buscarIndicePrioridad(tcp, prioridad);
    if (indice < 0)
    {
        return 0;
    }

    return encolar(&tcp[indice].cola, proceso);
}
