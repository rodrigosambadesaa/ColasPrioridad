#ifndef TCOLAPRIO_LISTA_H
#define TCOLAPRIO_LISTA_H

#include "lista_tad.h"

typedef list_t tcola_prio_t;

tcola_prio_t tcola_prio_create(void);
void tcola_prio_destroy(tcola_prio_t *queue);
int tcola_prio_enqueue(tcola_prio_t queue, long process_id, int priority);

/*
 * Devuelve el primer proceso con mayor prioridad en la lista.
 * Si la cola esta vacia, devuelve -1.
 */
long primero_cola_prio(tcola_prio_t queued_processes);

#endif