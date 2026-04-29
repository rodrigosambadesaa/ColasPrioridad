#ifndef COLAPRIO_H
#define COLAPRIO_H

#include "cola.h"

#define NUM_COLAS_PRIO 100

typedef struct colaindividual
{
    int prioridad;
    TCola cola;
} ColaIndividual;

typedef ColaIndividual *TCOLAPRIO;

TCOLAPRIO crearColaPrio(const int prioridades[NUM_COLAS_PRIO]);
void destruirColaPrio(TCOLAPRIO *tcp);

int EsColaVaciaPrio(TCOLAPRIO tcp);
int primeroColaPrio(TCOLAPRIO tcp, PID *proceso);
int eliminarColaPrio(TCOLAPRIO tcp);
int anadirColaPrio(TCOLAPRIO tcp, PID proceso, int prioridad);

#endif
