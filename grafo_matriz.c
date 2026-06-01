/* =========================================================
 * grafo_matriz.c  —  Representación: Matriz de Adyacencia
 * ELO320 Laboratorio: Focos de Contagio
 * =========================================================
 * Completa los bloques marcados con TODO.
 * No agregues variables globales.
 * ========================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

/* ---------------------------------------------------------
 * matriz_crear
 * --------------------------------------------------------- */
GrafoMatriz *matriz_crear(int n) {
    GrafoMatriz *g = malloc(sizeof(GrafoMatriz));
    if (!g) { perror("malloc GrafoMatriz"); exit(1); }
    g->n = n;
    g->m = 0;

    /* TODO: reservar g->personas como arreglo dinámico de n Persona.
     *
     * TODO: reservar g->matriz como arreglo dinámico de n punteros int*.
     *   Luego, para cada fila i, reservar g->matriz[i] como arreglo
     *   de n enteros e inicializar todos en 0 con calloc.
     *
     * Pista: g->matriz = malloc(n * sizeof(int *))
     *        g->matriz[i] = calloc(n, sizeof(int))
     */

    return g;
}

/* ---------------------------------------------------------
 * matriz_agregar_persona
 * --------------------------------------------------------- */
void matriz_agregar_persona(GrafoMatriz *g, int id,
                            const char *nombre,
                            int dias_contagioso) {
    /* TODO: asignar los campos de g->personas[id].
     * Usar strdup para el nombre.
     */
}

/* ---------------------------------------------------------
 * matriz_agregar_arista
 * --------------------------------------------------------- */
void matriz_agregar_arista(GrafoMatriz *g, int a, int b) {
    /* TODO: marcar la arista (a, b) en la matriz.
     * El grafo es no dirigido, por lo que debes marcar:
     *   g->matriz[a][b] = 1
     *   g->matriz[b][a] = 1
     */

    g->m++;
}

/* ---------------------------------------------------------
 * matriz_imprimir
 * Imprime cada nodo y sus vecinos según la matriz.
 * Formato: Nodo i | Nombre (X dias) -> [v1, v2, ...]
 * --------------------------------------------------------- */
void matriz_imprimir(GrafoMatriz *g) {
    printf("Representacion: matriz de adyacencia\n\n");
    for (int i = 0; i < g->n; i++) {
        printf("Nodo %d | %-15s (%d dias) -> [",
               i,
               g->personas[i].nombre,
               g->personas[i].dias_contagioso);

        /* TODO: recorrer la fila g->matriz[i] e imprimir el índice j
         * de cada celda con valor distinto de 0, separando con ", ".
         * No imprimir coma después del último vecino.
         *
         * Pista: usa una variable `primero = 1` para controlar
         * si debes imprimir la coma antes del elemento actual.
         */

        printf("]\n");
    }
}

/* ---------------------------------------------------------
 * matriz_liberar
 * --------------------------------------------------------- */
void matriz_liberar(GrafoMatriz *g) {
    /* TODO: liberar en orden:
     *   1. Para cada i en [0, n):
     *      a. Liberar g->matriz[i].
     *      b. Liberar g->personas[i].nombre.
     *   2. Liberar g->matriz.
     *   3. Liberar g->personas.
     *   4. Liberar g.
     */
}

/* =========================================================
 * TANDA 2
 * ========================================================= */

/* ---------------------------------------------------------
 * matriz_bfs
 * Recorrido en amplitud desde `inicio`.
 * Marca visitados en el arreglo `visitado`.
 * Retorna la componente encontrada.
 * El llamador es responsable de liberar comp.ids.
 * --------------------------------------------------------- */
Componente matriz_bfs(GrafoMatriz *g, int inicio, int *visitado) {
    Componente comp = {NULL, 0, 0};

    int *cola = malloc(g->n * sizeof(int));
    if (!cola) { perror("malloc cola"); exit(1); }

    /* TODO: implementar BFS con matriz de adyacencia.
     *
     * Esquema idéntico al de lista, pero al expandir vecinos
     * de u debes recorrer TODA la fila g->matriz[u]:
     *
     *   para j en [0, n):
     *       si g->matriz[u][j] != 0 y !visitado[j]:
     *           visitado[j] = 1
     *           cola[fin++] = j
     *
     * Al terminar:
     *   comp.ids      = cola
     *   comp.tam      = fin
     *   comp.subtotal = suma de dias_contagioso de cada id en cola
     *
     * No liberes cola aquí.
     */

    return comp;
}

/* ---------------------------------------------------------
 * matriz_encontrar_focos
 * --------------------------------------------------------- */
void matriz_encontrar_focos(GrafoMatriz *g, double umbral_pct) {
    /* Calcular total */
    int total = 0;
    for (int i = 0; i < g->n; i++)
        total += g->personas[i].dias_contagioso;

    printf("Total dias contagiosos: %d\n\n", total);
    if (total == 0) { printf("Sin dias contagiosos.\n"); return; }

    int *visitado = calloc(g->n, sizeof(int));
    if (!visitado) { perror("calloc"); exit(1); }

    printf("=== Focos de Contagio (> %.1f%% del total) ===\n\n",
           umbral_pct * 100.0);

    int num_foco = 0;

    /* TODO: recorrer todos los nodos no visitados.
     *   Para cada nodo i no visitado:
     *     1. comp = matriz_bfs(g, i, visitado)
     *     2. pct  = (double)comp.subtotal / total
     *     3. Si pct > umbral_pct:
     *          num_foco++
     *          imprimir encabezado: "Foco N (X personas, Y dias, Z.Z%):"
     *          para cada id en comp.ids:
     *              imprimir "  - Nombre : D dias"
     *     4. Si no supera:
     *          imprimir "Componente {Nombre1, Nombre2}: Y dias (Z.Z%) -> no es foco."
     *     5. free(comp.ids)
     *
     * Nota: la lógica es idéntica a lista_encontrar_focos.
     * Solo cambia la función BFS que se invoca.
     */

    free(visitado);
}