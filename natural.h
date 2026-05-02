#ifndef NATURAL_H
#define NATURAL_H

/* Representacion practica del TAD Natural para ejecutar operaciones del enunciado. */
typedef unsigned int natural_t;

natural_t natural_cero(void);
natural_t natural_sucesor(natural_t n);
int natural_es_cero(natural_t n);
int natural_igual(natural_t a, natural_t b);
natural_t natural_suma(natural_t a, natural_t b);
int natural_antecesor(natural_t n, natural_t *out);
int natural_diferencia(natural_t a, natural_t b, natural_t *out);

/* Operaciones anadidas en el ultimo ejercicio. */
natural_t natural_producto(natural_t a, natural_t b);
natural_t natural_potencia(natural_t base, natural_t exponente);

#endif
