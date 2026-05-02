# Resolucion razonada de enunciados

## 1) Preguntas tipo test

1. Enunciado: La ventaja fundamental de un Tipo Abstracto de Dato (TAD) reside:
- a) en unir sintaxis, semantica e implementacion en un mismo modulo o fichero
- b) que la misma implementacion pueda corresponderse con distintas especificaciones del TAD
- c) que los programas se abstraen de la implementacion del TAD y si la implementacion cambia no es necesario cambiar los programas que usan el TAD
- d) ninguna de las anteriores

Respuesta: c
Razon: la ventaja clave de un TAD es separar especificacion e implementacion; el codigo cliente depende de la interfaz, no de los detalles internos.

2. Enunciado: Un TAD pila:
- a) es tan flexible como un TAD lista y ademas incorpora meter/sacar por la cima
- b) puede implementarse internamente mediante un TAD lista, restringiendo el uso a las operaciones de pila
- c) permite acceso a cualquier elemento independientemente de su posicion
- d) ninguna de las anteriores

Respuesta: b
Razon: una pila puede implementarse sobre una lista, limitando operaciones a apilar y desapilar (LIFO).

3. Enunciado: La busqueda binaria:
- a) es mas efectiva que la busqueda lineal con centinela
- b) es menos efectiva que la busqueda lineal sin centinela
- c) tiene orden equivalente a la busqueda lineal con centinela
- d) ninguna de las anteriores

Respuesta: a
Razon: la busqueda binaria tiene coste O(log n), mejor que la lineal (con o sin centinela), que es O(n).

4. Enunciado: Para un mismo problema disponemos de algoritmos de orden n log n, n!, 2^n y n^10. Cual elegimos?
- a) el polinomico (n^10)
- b) el de orden n^n
- c) el de orden n!
- d) ninguna de las anteriores

Respuesta: d
Razon: entre las opciones no aparece n log n, que es el mejor entre los ordenes citados en el enunciado.

5. Enunciado: El orden exacto de complejidad (Theta) nos da:
- a) exclusivamente una cota inferior
- b) exclusivamente una cota superior
- c) una cota superior y una cota inferior
- d) ninguna de las anteriores

Respuesta: c
Razon: Theta acota por arriba y por abajo (cota ajustada), no solo una de ellas.

6. Enunciado: Por que se suele analizar algoritmos en el peor caso?
- a) no se analiza de ese modo
- b) porque asi tenemos acotado el tiempo maximo que tardara para cualquier entrada
- c) porque peor y mejor caso suelen ser equivalentes
- d) ninguna de las anteriores

Respuesta: b
Razon: analizar peor caso garantiza un limite maximo de tiempo para cualquier entrada.

7. Enunciado: El algoritmo quicksort:
- a) para tallas pequenas puede ser menos eficiente temporalmente que burbuja
- b) es sublineal
- c) es cuadratico
- d) ninguna de las anteriores

Respuesta: a
Razon: en tallas pequenas, el overhead de quicksort puede hacerlo peor en tiempo real que algoritmos simples.

8. Enunciado: Los algoritmos de fuerza bruta:
- a) suelen implicar bajo coste computacional
- b) suelen encontrar siempre la solucion al problema
- c) realizan una poda del espacio de busqueda
- d) ninguna de las anteriores

Respuesta: b
Razon: la fuerza bruta explora sistematicamente posibilidades; en problemas finitos encuentra solucion si existe.

9. Enunciado: Un algoritmo voraz:
- a) es un caso especial de divide y venceras
- b) suele ser mas eficiente temporalmente que uno de fuerza bruta
- c) es un caso especial de programacion dinamica
- d) ninguna de las anteriores

Respuesta: b
Razon: un enfoque voraz normalmente reduce exploracion frente a fuerza bruta, por lo que suele ser mas rapido.

10. Enunciado: La programacion dinamica:
- a) suele consistir en almacenar datos tabularmente para reutilizar resultados
- b) consiste en sacrificar tiempo para mejorar memoria
- c) consiste en decidir dinamicamente entre ahorrar memoria o tiempo
- d) ninguna de las anteriores

Respuesta: a
Razon: programacion dinamica reutiliza subresultados (memoizacion o tablas) para evitar recomputaciones.

## 2) Diferencia entre complejidad espacial y temporal

Enunciado: Explica brevemente la diferencia entre complejidad espacial y complejidad temporal.

Respuesta razonada:
- Complejidad temporal: mide como crece el tiempo de ejecucion con el tamano de entrada N.
- Complejidad espacial: mide como crece la memoria adicional necesaria con N.

Ejemplo: un algoritmo puede ser rapido pero usar mucha memoria (mejor tiempo, peor espacio), o al reves.

## 3) Lista en bloque contiguo de memoria

Enunciado: Explica ventajas y desventajas de utilizar un bloque de memoria contigua para almacenar una lista de elementos. Que operaciones del TAD lista son mas problematicas y cuales mas sencillas? Por que?

Respuesta razonada:
Ventajas:
- Acceso por indice en O(1).
- Muy buena localidad de cache, normalmente mejor rendimiento practico en recorridos.
- Menor sobrecarga por elemento (sin punteros extra por nodo).

Desventajas:
- Inserciones y borrados en posiciones intermedias requieren desplazar elementos: O(n).
- Redimensionar puede implicar reservar nuevo bloque y copiar.
- Riesgo de infra/sobredimensionamiento de capacidad.

Operaciones mas problematicas:
- Insertar/eliminar en cabeza o zona media (desplazamientos).
- Inserciones frecuentes cuando no queda capacidad.

Operaciones mas sencillas:
- Lectura/escritura por posicion.
- Recorrido secuencial.
- Insercion al final amortizada O(1) cuando hay capacidad.

## 4) Complejidad de multiplicacion de matrices cuadradas

Enunciado: En multiplicacion iterativa directa de matrices cuadradas, que orden de complejidad hay respecto a N (filas/columnas) y por que? En la version divide y venceras del esquema visto, que orden tiene y por que?

Respuesta razonada:
Sea N el numero de filas/columnas.

Implementacion iterativa directa (3 bucles anidados):
- Cada celda C[i][j] hace una suma de N productos.
- Hay N^2 celdas.
- Coste total: Theta(N^3).

Implementacion divide y venceras clasica (particion en 4 submatrices):
- Recurrencia tipica: T(N) = 8T(N/2) + Theta(N^2) (sumas de bloques).
- Por Master theorem, T(N) = Theta(N^3).

Conclusion: en orden asintotico, ambas son cubicas.

## 5) Orden superior O e inferior Omega

Enunciado: Dados los programas A, B y C, determinar O y Omega siendo N la talla del problema.

### Programa A

Enunciado (resumen de codigo): en main se ejecuta f1(N) si N % 55 == 0, en caso contrario f2(N). f1 tiene tres bucles anidados con limite 10000, N, N. f2 tiene dos bucles anidados N, N.

Respuesta razonada:
- f1(N): 10000 * N * N iteraciones => Theta(N^2).
- f2(N): N * N iteraciones => Theta(N^2).
- main llama a una u otra segun N % 55, pero en ambos casos domina N^2.

Resultado:
- O(N^2)
- Omega(N^2)

### Programa B

Enunciado (resumen de codigo): f1(num) se define recursivamente como 2 * f1(num-1) * f1(num-2), y main llama a f1(N).

Respuesta razonada:
- Tiempo sin memoizacion: T(N) = T(N-1) + T(N-2) + O(1).
- Mismo patron de crecimiento que Fibonacci recursivo.
- T(N) = Theta(phi^N), con phi = (1 + sqrt(5)) / 2.

Resultado:
- O(phi^N)
- Omega(phi^N)

### Programa C

Enunciado (resumen de codigo): main calcula k = f2(N) y, si k > 1000, suma f1(N). f2 tiene un bucle simple hasta N. f1 tiene doble bucle N x N.

Respuesta razonada:
- f2(N) = Theta(N) y k = N(N-1)/2.
- Para N suficientemente grande, k > 1000 siempre se cumple.
- Entonces se ejecuta f1(N) = Theta(N^2), que domina.

Resultado:
- O(N^2)
- Omega(N^2)

## 6) Ampliacion formal del TAD Natural con Producto y Potencia

Enunciado: Partiendo de la especificacion formal del TAD Natural, completarla incorporando las operaciones producto y potencia.

Respuesta razonada:

Sintaxis (anadidos):
- Producto(Natural, Natural) -> Natural
- Potencia(Natural, Natural) -> Natural

Semantica (anadidos), para todo m, n en Natural:
- Producto(Cero, n) => Cero
- Producto(Sucesor(m), n) => Suma(n, Producto(m, n))
- Potencia(n, Cero) => Sucesor(Cero)
- Potencia(n, Sucesor(m)) => Producto(n, Potencia(n, m))

Nota: Sucesor(Cero) representa el 1 en esta construccion.
