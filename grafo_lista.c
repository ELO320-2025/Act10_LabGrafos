/* =========================================================
 * grafo_lista.c  —  Representación: Lista de Adyacencia
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
 * lista_crear
 * --------------------------------------------------------- */
GrafoLista *lista_crear(int n) {
    GrafoLista *g = malloc(sizeof(GrafoLista));
    if (!g) { perror("malloc GrafoLista"); exit(1); }
    g->n = n;
    g->m = 0;

    /* TODO: reservar g->personas como arreglo dinámico de n Persona.
     * Inicializar cada personas[i].vecinos... espera, los vecinos
     * están en g->vecinos. Reservar g->vecinos como arreglo dinámico
     * de n punteros NodoVecino* e inicializar cada uno en NULL.
     */

    return g;
}

/* ---------------------------------------------------------
 * lista_agregar_persona
 * --------------------------------------------------------- */
void lista_agregar_persona(GrafoLista *g, int id,
                           const char *nombre,
                           int dias_contagioso) {
    /* TODO: asignar los campos de g->personas[id].
     * Usar strdup para el nombre.
     */
}

/* ---------------------------------------------------------
 * lista_agregar_arista
 * --------------------------------------------------------- */
void lista_agregar_arista(GrafoLista *g, int a, int b) {
    /* TODO: insertar b al inicio de g->vecinos[a]
     *       e insertar a al inicio de g->vecinos[b].
     *
     * Pasos para insertar b en g->vecinos[a]:
     *   1. nodo = malloc(sizeof(NodoVecino))
     *   2. nodo->id  = b
     *   3. nodo->sig = g->vecinos[a]
     *   4. g->vecinos[a] = nodo
     *
     * Repetir simétricamente para a en g->vecinos[b].
     */

    g->m++;
}

/* ---------------------------------------------------------
 * lista_imprimir
 * Imprime cada nodo y su lista de vecinos.
 * Formato: Nodo i | Nombre (X dias) -> [v1, v2, ...]
 * --------------------------------------------------------- */
void lista_imprimir(GrafoLista *g) {
    printf("Representacion: lista de adyacencia\n\n");
    for (int i = 0; i < g->n; i++) {
        printf("Nodo %d | %-15s (%d dias) -> [",
               i,
               g->personas[i].nombre,
               g->personas[i].dias_contagioso);

        /* TODO: recorrer g->vecinos[i] e imprimir cada id separado
         * por ", ". No imprimir coma después del último.
         *
         * Pista: usa un flag o mira si el nodo actual es el último.
         */

        printf("]\n");
    }
}

/* ---------------------------------------------------------
 * lista_liberar
 * --------------------------------------------------------- */
void lista_liberar(GrafoLista *g) {
    /* TODO: liberar en orden:
     *   1. Para cada i en [0, n):
     *      a. Recorrer g->vecinos[i] liberando cada NodoVecino.
     *      b. Liberar g->personas[i].nombre.
     *   2. Liberar g->vecinos.
     *   3. Liberar g->personas.
     *   4. Liberar g.
     */
}

/* =========================================================
 * TANDA 2
 * ========================================================= */

/* ---------------------------------------------------------
 * lista_bfs
 * Recorrido en amplitud desde `inicio`.
 * Marca visitados en el arreglo `visitado`.
 * Retorna la componente encontrada.
 * El llamador es responsable de liberar comp.ids.
 * --------------------------------------------------------- */
Componente lista_bfs(GrafoLista *g, int inicio, int *visitado) {
    Componente comp = {NULL, 0, 0};

    int *cola = malloc(g->n * sizeof(int));
    if (!cola) { perror("malloc cola"); exit(1); }

    /* TODO: implementar BFS con lista de adyacencia.
     *
     * Esquema:
     *   frente = 0, fin = 0
     *   cola[fin++] = inicio; visitado[inicio] = 1
     *
     *   mientras frente < fin:
     *       u = cola[frente++]
     *       para cada NodoVecino v en g->vecinos[u]:
     *           si !visitado[v->id]:
     *               visitado[v->id] = 1
     *               cola[fin++] = v->id
     *
     * Al terminar:
     *   comp.ids      = cola        (cola[0..fin-1] son los nodos)
     *   comp.tam      = fin
     *   comp.subtotal = suma de dias_contagioso de cada id en cola
     *
     * No liberes cola aquí.
     */

    return comp;
}

/* ---------------------------------------------------------
 * lista_encontrar_focos
 * --------------------------------------------------------- */
void lista_encontrar_focos(GrafoLista *g, double umbral_pct) {
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
     *     1. comp = lista_bfs(g, i, visitado)
     *     2. pct  = (double)comp.subtotal / total
     *     3. Si pct > umbral_pct:
     *          num_foco++
     *          imprimir encabezado: "Foco N (X personas, Y dias, Z.Z%):"
     *          para cada id en comp.ids:
     *              imprimir "  - Nombre : D dias"
     *     4. Si no supera:
     *          imprimir "Componente {Nombre1, Nombre2}: Y dias (Z.Z%) -> no es foco."
     *     5. free(comp.ids)
     */

    free(visitado);
}
