# Act10_LabGrafos

# Laboratorio: Focos de Contagio
**ELO320 – Estructuras de Datos y Algoritmos**

Código base para el laboratorio de **grafos y Heavy Hitters**.  
El objetivo es construir un grafo de contactos en dos representaciones distintas, y luego identificar los grupos de personas que concentran más del 20 % de la carga infecciosa total.

El laboratorio se divide en dos tandas. En cada una deberás completar los bloques marcados con `TODO` en los archivos de código base, medir tiempos de ejecución, calcular la memoria consumida usando Valgrind y responder preguntas de reflexión.

---

## Estructura del repositorio

```
lab_focos/
├── grafo.h           # Structs y firmas compartidas (no modificar)
├── grafo_lista.c     # TODO Tanda 1 y 2: lista de adyacencia
├── grafo_matriz.c    # TODO Tanda 1 y 2: matriz de adyacencia
├── main.c            # Carga de archivos y lógica principal (completo)
├── data/
│   ├── personas_small.csv
│   ├── contactos_small.csv
│   ├── personas_medium.csv
│   ├── contactos_medium.csv
│   ├── personas_large.csv
│   ├── contactos_large.csv
│   ├── personas_xlarge.csv
│   └── contactos_xlarge.csv
└── README_respuestas.md   # Tus respuestas a las preguntas de reflexión
```

---

## Compilación

```bash
gcc -Wall -Wextra -o focos grafo_lista.c grafo_matriz.c main.c
```

---

## Ejecución

El programa recibe el directorio de datos y la representación a usar:

```bash
./focos data/ -lista
./focos data/ -matriz
```

Para probar con distintos tamaños de dataset, el directorio de datos contiene cuatro pares de archivos (`small`, `medium`, `large`, `xlarge`). Puedes indicar el prefijo del dataset con un tercer argumento:

```bash
./focos data/ -lista small
./focos data/ -matriz xlarge
```

Si no se indica el tamaño, el programa usa `small` por defecto.

---

## Verificación y medición de memoria

```bash
valgrind --leak-check=full ./focos data/ -lista
valgrind --leak-check=full ./focos data/ -matriz
```

Valgrind no debe reportar fugas (`0 bytes lost`) en ninguno de los dos casos.

Para medir memoria consumida, usa `massif`, que es la herramienta de Valgrind para perfilar uso de memoria:

```bash
valgrind --tool=massif --massif-out-file=massif_lista.out ./focos data/ -lista
ms_print massif_lista.out

valgrind --tool=massif --massif-out-file=massif_matriz.out ./focos data/ -matriz
ms_print massif_matriz.out
```

Registra en `README_respuestas.md` el consumo máximo de memoria reportado por `massif` para ambas representaciones, idealmente para los distintos tamaños de dataset.

---

## Tanda 1: Construcción e impresión del grafo

Completa los `TODO` de **construcción** en `grafo_lista.c` y `grafo_matriz.c`:

| Función | Archivo | Qué implementar |
|---|---|---|
| `lista_crear` | `grafo_lista.c` | Reservar arreglos dinámicos de personas y vecinos |
| `lista_agregar_persona` | `grafo_lista.c` | Asignar campos con `strdup` para el nombre |
| `lista_agregar_arista` | `grafo_lista.c` | Insertar nodos al inicio de las listas de vecinos |
| `lista_imprimir` | `grafo_lista.c` | Recorrer la lista de vecinos de cada nodo |
| `lista_liberar` | `grafo_lista.c` | Liberar vecinos, nombres y el grafo |
| `matriz_crear` | `grafo_matriz.c` | Reservar arreglo de personas y matriz n×n inicializada en 0 |
| `matriz_agregar_persona` | `grafo_matriz.c` | Asignar campos con `strdup` para el nombre |
| `matriz_agregar_arista` | `grafo_matriz.c` | Marcar `matriz[a][b]` y `matriz[b][a]` en 1 |
| `matriz_imprimir` | `grafo_matriz.c` | Recorrer la fila de cada nodo buscando valores distintos de 0 |
| `matriz_liberar` | `grafo_matriz.c` | Liberar filas, matriz, nombres y el grafo |

La salida esperada al imprimir el grafo es:

```
=== Red de Contagio ===
Personas  : 8
Contactos : 7
Representacion: lista de adyacencia

Nodo 0 | Ana Perez       (5 dias) -> [1, 2]
Nodo 1 | Luis Mora       (3 dias) -> [0, 2]
...

[Construccion del grafo: X.XXX ms]
```

Con los cuatro datasets, registra los tiempos y la memoria consumida en `README_respuestas.md` y responde las preguntas de reflexión de la Tanda 1 (ver enunciado).

---

## Tanda 2: Búsqueda de focos de contagio

Completa los `TODO` de **Heavy Hitters** en `grafo_lista.c` y `grafo_matriz.c`:

| Función | Archivo | Qué implementar |
|---|---|---|
| `lista_bfs` | `grafo_lista.c` | BFS recorriendo listas de vecinos |
| `lista_encontrar_focos` | `grafo_lista.c` | Iterar componentes y aplicar umbral del 20 % |
| `matriz_bfs` | `grafo_matriz.c` | BFS recorriendo filas de la matriz |
| `matriz_encontrar_focos` | `grafo_matriz.c` | Iterar componentes y aplicar umbral del 20 % |

La salida esperada es:

```
Total dias contagiosos: 32

=== Focos de Contagio (> 20.0% del total) ===

Foco 1 (3 personas, 16 dias, 50.0%):
  - Ana Perez    : 5 dias
  - Luis Mora    : 3 dias
  - Carla Vega   : 8 dias

Foco 2 (3 personas, 10 dias, 31.2%):
  - Tomas Arce   : 2 dias
  - Sofia Munoz  : 7 dias
  - Andres Leon  : 1 dias

Componente {Diego Rios, Paula Soto}: 6 dias (18.8%) -> no es foco.

[Busqueda de focos: X.XXX ms]
```

Con los cuatro datasets, registra los tiempos y la memoria consumida en `README_respuestas.md` y responde las preguntas de reflexión de la Tanda 2 (ver enunciado).

---

## Plantilla de respuestas

Crea el archivo `README_respuestas.md` con la siguiente estructura:

```markdown
# Respuestas — Laboratorio Focos de Contagio

## Tanda 1

### Tabla de tiempos de construcción

| Dataset  |  V  |  E  | t_lista (ms) | t_matriz (ms) |
|----------|-----|-----|--------------|---------------|
| small    |     |     |              |               |
| medium   |     |     |              |               |
| large    |     |     |              |               |
| xlarge   |     |     |              |               |

### Tabla de memoria de construcción

| Dataset  | mem_lista (KB) | mem_matriz (KB) |
|----------|----------------|-----------------|
| small    |                |                 |
| medium   |                |                 |
| large    |                |                 |
| xlarge   |                |                 |

### Preguntas
1. ...
2. ...
3. (tabla completada arriba)
4. ...

## Tanda 2

### Tabla de tiempos de búsqueda de focos

| Dataset  |  V  |  E  | t_lista (ms) | t_matriz (ms) |
|----------|-----|-----|--------------|---------------|
| small    |     |     |              |               |
| medium   |     |     |              |               |
| large    |     |     |              |               |
| xlarge   |     |     |              |               |

### Tabla de memoria de búsqueda de focos

| Dataset  | mem_lista (KB) | mem_matriz (KB) |
|----------|----------------|-----------------|
| small    |                |                 |
| medium   |                |                 |
| large    |                |                 |
| xlarge   |                |                 |

### Preguntas
1. ...
2. ...
3. (tabla completada arriba)
4. ...
5. ...
```
