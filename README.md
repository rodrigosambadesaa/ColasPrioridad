# Cola de prioridad en C

Implementacion de una cola de prioridad para simular planificacion de procesos.
La estructura principal se construye con 100 colas FIFO contiguas en memoria.

## Objetivo

El ejercicio modela un scheduler simple de sistema operativo:

- Cada proceso se inserta con una prioridad entre 1 y 100.
- La ejecucion global siempre atiende primero la prioridad mas alta.
- Dentro de una misma prioridad se mantiene orden FIFO.
- La localizacion de la cola destino se hace con busqueda binaria.

## Caracteristicas

- 100 buckets de prioridad contiguos en memoria (arreglo dinamico).
- Cola FIFO enlazada por cada bucket.
- Insercion por prioridad con busqueda binaria en O(log n), con n = 100.
- Extraccion del siguiente proceso global recorriendo de prioridad alta a baja.
- API simple de creacion, insercion, consulta, extraccion y destruccion.

## Estructura del proyecto

- cola.h / cola.c: implementacion de cola FIFO enlazada.
- colaprio.h / colaprio.c: capa de cola de prioridad.
- main.c: demo automatica y modo consola interactivo.
- Makefile: compilacion local.
- Dockerfile: compilacion y ejecucion en contenedor.

## Requisitos

### Opcion 1: Docker

- Docker instalado.

### Opcion 2: compilacion local

- Compilador C compatible con C11 (gcc recomendado).
- make.

Nota para Windows:

- El objetivo clean del Makefile usa rm, por lo que conviene ejecutar desde Git Bash, MSYS2 o WSL.

## Compilar y ejecutar

### Con Docker

Construir imagen:

	docker build -t colas-prioridad .

Ejecutar demo por defecto:

	docker run --rm colas-prioridad

Ejecutar modo consola interactivo:

	docker run -it --rm colas-prioridad ./app --console

### Local

Compilar:

	make

Ejecutar demo por defecto:

	./app

Ejecutar modo consola interactivo:

	./app --console

Limpiar artefactos:

	make clean

## Modo de ejecucion

### 1) Demo automatica (por defecto)

Al ejecutar sin argumentos, se cargan procesos de ejemplo y se muestra el orden de ejecucion segun prioridad.

### 2) Consola interactiva

Con --console se habilita un menu:

1. Insertar proceso
2. Ver siguiente proceso
3. Ejecutar (eliminar) siguiente proceso
4. Consultar si esta vacia
5. Ejecutar demo predefinida
0. Salir

## API principal

Funciones publicas de la cola de prioridad:

- priority_queue_create(const int priorities[PRIORITY_QUEUE_COUNT])
- priority_queue_destroy(priority_queue_t *priority_queue)
- priority_queue_is_empty(priority_queue_t priority_queue)
- priority_queue_peek(priority_queue_t priority_queue, process_id_t *process)
- priority_queue_pop(priority_queue_t priority_queue)
- priority_queue_push(priority_queue_t priority_queue, process_id_t process, int priority)

Convencion de retorno:

- 1: operacion exitosa.
- 0: error o condicion no satisfecha (por ejemplo, cola vacia o prioridad inexistente).

## Complejidad (resumen)

Con n = 100 prioridades y m elementos en la cola FIFO de una prioridad:

- push: O(log n) por busqueda binaria + O(1) en enqueue.
- peek: O(n) en el peor caso para hallar la prioridad no vacia mas alta + O(1) para leer frente.
- pop: O(n) en el peor caso para hallar la prioridad no vacia mas alta + O(1) en dequeue.
- is_empty: O(n).

## Ejemplo rapido

Si se insertan:

- (1122, prioridad 100)
- (2555, prioridad 100)
- (7777, prioridad 45)
- (4567, prioridad 34)

El orden de salida sera:

1. 1122
2. 2555
3. 7777
4. 4567

## Posibles mejoras

- Mantener un indice de prioridad maxima no vacia para acelerar peek/pop/is_empty.
- Agregar tests unitarios (por ejemplo con Criterion o Unity).
- Permitir rango de prioridades configurable.
