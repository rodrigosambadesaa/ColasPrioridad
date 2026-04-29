# Cola de prioridad en C (dockerizada)

Implementacion de una biblioteca de cola por prioridad basada en 100 colas contiguas en memoria,
segun el enunciado del ejercicio.

## Operaciones implementadas

- `EsColaVaciaPrio(TCOLAPRIO tcp)`
- `primeroColaPrio(TCOLAPRIO tcp, PID *proceso)`
- `eliminarColaPrio(TCOLAPRIO tcp)`
- `anadirColaPrio(TCOLAPRIO tcp, PID proceso, int prioridad)`

`anadirColaPrio` usa **busqueda binaria** sobre el arreglo de 100 prioridades.

## Estructura

- `cola.h` / `cola.c`: cola FIFO enlazada convencional
- `colaprio.h` / `colaprio.c`: cola por prioridad
- `main.c`: demo de uso
- `Dockerfile`: construccion y ejecucion en contenedor

## Uso con Docker

```bash
docker build -t colas-prioridad .
docker run --rm colas-prioridad
```

## Uso local (sin Docker)

```bash
make
./app
```
