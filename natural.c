#include "natural.h"

natural_t natural_cero(void)
{
    return 0U;
}

natural_t natural_sucesor(natural_t n)
{
    return n + 1U;
}

int natural_es_cero(natural_t n)
{
    return n == 0U;
}

int natural_igual(natural_t a, natural_t b)
{
    return a == b;
}

natural_t natural_suma(natural_t a, natural_t b)
{
    if (natural_es_cero(a))
    {
        return b;
    }

    return natural_sucesor(natural_suma(a - 1U, b));
}

int natural_antecesor(natural_t n, natural_t *out)
{
    if (natural_es_cero(n) || out == 0)
    {
        return 0;
    }

    *out = n - 1U;
    return 1;
}

int natural_diferencia(natural_t a, natural_t b, natural_t *out)
{
    if (out == 0 || b > a)
    {
        return 0;
    }

    *out = a - b;
    return 1;
}

natural_t natural_producto(natural_t a, natural_t b)
{
    if (natural_es_cero(a))
    {
        return natural_cero();
    }

    return natural_suma(b, natural_producto(a - 1U, b));
}

natural_t natural_potencia(natural_t base, natural_t exponente)
{
    if (natural_es_cero(exponente))
    {
        return natural_sucesor(natural_cero());
    }

    return natural_producto(base, natural_potencia(base, exponente - 1U));
}
