#include <stdio.h>
#include <stdlib.h>

#include "natural.h"

static int read_natural(const char *prompt, natural_t *value)
{
    char buffer[128];
    char *endptr;
    unsigned long parsed;

    if (value == NULL)
    {
        return 0;
    }

    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 0;
    }

    parsed = strtoul(buffer, &endptr, 10);
    if (endptr == buffer)
    {
        return 0;
    }

    *value = (natural_t)parsed;
    return 1;
}

static void print_menu(void)
{
    printf("\n=== TAD Natural (consola) ===\n");
    printf("1) Suma(a, b)\n");
    printf("2) Diferencia(a, b)\n");
    printf("3) Producto(a, b)\n");
    printf("4) Potencia(base, exp)\n");
    printf("5) Sucesor(n) y Antecesor(n)\n");
    printf("0) Salir\n");
    printf("Opcion: ");
}

static int run_self_tests(void)
{
    natural_t out;

    if (natural_suma(3, 4) != 7)
    {
        return 0;
    }

    if (!natural_diferencia(10, 3, &out) || out != 7)
    {
        return 0;
    }

    if (natural_diferencia(3, 10, &out))
    {
        return 0;
    }

    if (natural_producto(6, 5) != 30)
    {
        return 0;
    }

    if (natural_potencia(2, 10) != 1024)
    {
        return 0;
    }

    if (natural_potencia(5, 0) != 1)
    {
        return 0;
    }

    if (!natural_antecesor(1, &out) || out != 0)
    {
        return 0;
    }

    if (natural_antecesor(0, &out))
    {
        return 0;
    }

    return 1;
}

int main(int argc, char **argv)
{
    int option;

    if (argc > 1 && argv[1] != NULL && strcmp(argv[1], "--test") == 0)
    {
        if (run_self_tests())
        {
            printf("Pruebas TAD Natural: OK\n");
            return 0;
        }

        printf("Pruebas TAD Natural: ERROR\n");
        return 1;
    }

    for (;;)
    {
        natural_t a;
        natural_t b;
        natural_t out;

        print_menu();
        if (scanf("%d", &option) != 1)
        {
            printf("Entrada invalida.\n");
            return 1;
        }

        /* Consumir salto de linea pendiente para mezclar scanf/fgets con seguridad. */
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
        }

        if (option == 0)
        {
            printf("Fin del programa.\n");
            break;
        }

        if (option == 1)
        {
            if (!read_natural("a: ", &a) || !read_natural("b: ", &b))
            {
                printf("Datos invalidos.\n");
                continue;
            }
            printf("Suma(%u, %u) = %u\n", a, b, natural_suma(a, b));
            continue;
        }

        if (option == 2)
        {
            if (!read_natural("a: ", &a) || !read_natural("b: ", &b))
            {
                printf("Datos invalidos.\n");
                continue;
            }
            if (!natural_diferencia(a, b, &out))
            {
                printf("Diferencia(%u, %u): error (resultado negativo no pertenece a Natural).\n", a, b);
            }
            else
            {
                printf("Diferencia(%u, %u) = %u\n", a, b, out);
            }
            continue;
        }

        if (option == 3)
        {
            if (!read_natural("a: ", &a) || !read_natural("b: ", &b))
            {
                printf("Datos invalidos.\n");
                continue;
            }
            printf("Producto(%u, %u) = %u\n", a, b, natural_producto(a, b));
            continue;
        }

        if (option == 4)
        {
            if (!read_natural("base: ", &a) || !read_natural("exponente: ", &b))
            {
                printf("Datos invalidos.\n");
                continue;
            }
            printf("Potencia(%u, %u) = %u\n", a, b, natural_potencia(a, b));
            continue;
        }

        if (option == 5)
        {
            if (!read_natural("n: ", &a))
            {
                printf("Dato invalido.\n");
                continue;
            }
            printf("Sucesor(%u) = %u\n", a, natural_sucesor(a));
            if (!natural_antecesor(a, &out))
            {
                printf("Antecesor(%u): error (no definido para cero).\n", a);
            }
            else
            {
                printf("Antecesor(%u) = %u\n", a, out);
            }
            continue;
        }

        printf("Opcion no valida.\n");
    }

    return 0;
}
