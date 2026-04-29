#include "cola.h"

#include <stdlib.h>

void inicializarCola(TCola *c)
{
    c->frente = NULL;
    c->fondo = NULL;
    c->tam = 0;
}

int esColaVacia(const TCola *c)
{
    return c->frente == NULL;
}

int encolar(TCola *c, PID valor)
{
    NodoCola *nuevo = (NodoCola *)malloc(sizeof(NodoCola));
    if (nuevo == NULL)
    {
        return 0;
    }

    nuevo->valor = valor;
    nuevo->sig = NULL;

    if (c->fondo == NULL)
    {
        c->frente = nuevo;
        c->fondo = nuevo;
    }
    else
    {
        c->fondo->sig = nuevo;
        c->fondo = nuevo;
    }

    c->tam++;
    return 1;
}

int primeroCola(const TCola *c, PID *valor)
{
    if (esColaVacia(c))
    {
        return 0;
    }

    if (valor != NULL)
    {
        *valor = c->frente->valor;
    }
    return 1;
}

int desencolar(TCola *c, PID *valor)
{
    NodoCola *tmp;

    if (esColaVacia(c))
    {
        return 0;
    }

    tmp = c->frente;
    if (valor != NULL)
    {
        *valor = tmp->valor;
    }

    c->frente = tmp->sig;
    if (c->frente == NULL)
    {
        c->fondo = NULL;
    }

    free(tmp);
    c->tam--;
    return 1;
}

void liberarCola(TCola *c)
{
    PID dummy;
    while (desencolar(c, &dummy))
    {
    }
}
