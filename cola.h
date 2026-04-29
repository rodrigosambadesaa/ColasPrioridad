#ifndef COLA_H
#define COLA_H

#include <stddef.h>

typedef long PID;

typedef struct nodo_cola
{
    PID valor;
    struct nodo_cola *sig;
} NodoCola;

typedef struct
{
    NodoCola *frente;
    NodoCola *fondo;
    size_t tam;
} TCola;

void inicializarCola(TCola *c);
int esColaVacia(const TCola *c);
int encolar(TCola *c, PID valor);
int primeroCola(const TCola *c, PID *valor);
int desencolar(TCola *c, PID *valor);
void liberarCola(TCola *c);

#endif
