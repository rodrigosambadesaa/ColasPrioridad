# Resolucion razonada de enunciados

## 1) Especificacion formal de un TAD bono bus

Enunciado: definir un TAD que permita crear bono, insertar dinero (natural), comprobar si hay dinero y gastar un viaje de 1 euro.

Sintaxis propuesta:
- Crear() -> BonoBus
- Recargar(BonoBus, Natural) -> BonoBus
- HaySaldo(BonoBus) -> Boolean
- GastarViaje(BonoBus) -> BonoBus
- Saldo(BonoBus) -> Natural

Semantica propuesta (para todo b en BonoBus, n en Natural):
- Saldo(Crear()) => 0
- Saldo(Recargar(b, n)) => Saldo(b) + n
- HaySaldo(b) => (Saldo(b) > 0)
- GastarViaje(b) => error, si Saldo(b) = 0
- Saldo(GastarViaje(b)) => Saldo(b) - 1, si Saldo(b) > 0

Comentario: el dominio de euros es natural, por lo que no hay saldos negativos.

## 2) Cola implementada con punteros

Enunciado:
- (a) implementar funcion que elimina el primer elemento de la cola.
- (b) implementar funcion que inserta un elemento al final de la cola.

Resolucion implementada en consola:
- Insercion al final: pointer_queue_push_back(...)
- Eliminacion del primero: pointer_queue_pop_front(...)

Archivos:
- pdf3_queue.h
- pdf3_queue.c

## 3) Generar cola de prioridad para vacunacion

Enunciado: con una lista de personas (edad, nacionalidad, vacunas), generar cola priorizada:
- Grupo mas prioritario: mayores de 80 con menos de 3 vacunas.
- Siguiente prioridad: mayores de 80.
- Menor prioridad: personas con menos de 3 vacunas.
- Dentro de cada prioridad, mantener orden de aparicion en lista.

Resolucion implementada:
- Se recorre la lista una sola vez.
- Se calcula prioridad por persona:
  - 3 si edad > 80 y vacunas < 3
  - 2 si edad > 80
  - 1 si vacunas < 3
  - 0 si no debe convocarse
- Se inserta en cola priorizada manteniendo FIFO en cada prioridad.

Archivos:
- pdf3_sergas.h
- pdf3_sergas.c
- pdf3_console.c

## 4) Complejidad temporal para contar mayores con menos de 3 vacunas

Enunciado: calcular complejidad del proceso de computo en mejor, peor y promedio.

Si la lista no esta indexada por esos campos, hay que revisar elementos y contar.

Resultado:
- Mejor caso: Theta(n)
- Peor caso: Theta(n)
- Caso promedio: Theta(n)

Razon: para garantizar el conteo exacto hay que inspeccionar todos los elementos.

## 5) Buscar si existe ciudadano de una nacionalidad con menos de 3 vacunas

Enunciado: implementacion mas eficiente posible para conocer si existe al menos uno.

Con lista lineal sin indices:
- Mejor caso: Theta(1), si el primer elemento ya cumple.
- Peor caso: Theta(n), si no existe o aparece al final.
- Caso promedio: Theta(n).

Implementado en:
- exists_foreign_with_less_than_three(...)

## 6) Busqueda secuencial vs busqueda binaria

Enunciado:
- (a) tecnica algoritmica
- (b) cota superior/inferior
- (c) prerrequisitos
- (d) cual usar en produccion
- (e) si la opcion elegida siempre es mas rapida

Respuesta:
- Secuencial: tecnica iterativa de recorrido lineal.
- Binaria: tecnica divide y venceras sobre espacio ordenado.
- Secuencial: O(n), Omega(1).
- Binaria: O(log n), Omega(1).
- Prerrequisitos:
  - Secuencial: ninguno especial.
  - Binaria: estructura ordenada y acceso eficiente al punto medio.
- En produccion:
  - Si datos ordenados o se puede mantener orden: binaria.
  - Si no hay orden y no compensa ordenar: secuencial.
- No siempre binaria sera mas rapida en tiempo real:
  - En colecciones muy pequenas, secuencial puede rendir igual o mejor por menor coste constante.

## 7) Relacion con divide y venceras y multiplicacion de enteros grandes

Enunciado:
- (a) significado de k, c y t.
- (b) comparar dos variantes de multiplicacion.

Marco teorico:
- Recurrencia tipica: T(n) = k*T(n/c) + O(n^t)
- k: numero de subproblemas.
- c: factor de reduccion del tamano de subproblema.
- t: exponente del coste de combinar/dividir.

Interpretacion:
- Queremos k bajo, c alto (reduce mas), t bajo.
- Segun Teorema Maestro:
  - Si k < c^t, domina combinar: O(n^t)
  - Si k = c^t, frontera: O(n^t log n)
  - Si k > c^t, domina recursion: O(n^(log_c k))

Comparacion de variantes:
- Variante 1 usa 4 multiplicaciones de tamano n/2 (ac, ad, bc, bd): k=4, c=2.
- Variante 2 reescribe para usar 3 multiplicaciones de tamano n/2: k=3, c=2.
- Con coste de combinacion polinomico similar, la variante 2 es mas eficiente asintoticamente (estilo Karatsuba): reduce k.

## Programas de consola incluidos

- pdf3_console --test
  - Valida cola con punteros (insertar final y eliminar primero).
  - Valida construccion de cola priorizada de vacunacion y orden de salida.
  - Valida funciones auxiliares de conteo y busqueda.
