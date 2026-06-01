#ifndef GRAFO_H
#define GRAFO_H

/* =========================================================
 * grafo.h  —  Red de Contagio
 * ELO320 Laboratorio: Focos de Contagio
 * =========================================================
 * Structs y firmas compartidas por ambas representaciones.
 * No modifiques este archivo.
 * ========================================================= */

#include <time.h>

/* ---------------------------------------------------------
 * Persona: nodo del grafo
 * --------------------------------------------------------- */
typedef struct {
    int   id;
    char *nombre;           /* reservado con strdup        */
    int   dias_contagioso;
} Persona;

/* ---------------------------------------------------------
 * Nodo de lista enlazada (para lista de adyacencia)
 * --------------------------------------------------------- */
typedef struct NodoVecino {
    int               id;
    struct NodoVecino *sig;
} NodoVecino;

/* ---------------------------------------------------------
 * Grafo con lista de adyacencia
 * --------------------------------------------------------- */
typedef struct {
    int        n;           /* número de personas          */
    int        m;           /* número de contactos         */
    Persona   *personas;    /* arreglo dinámico [0..n-1]   */
    NodoVecino **vecinos;   /* arreglo de listas enlazadas */
} GrafoLista;

/* ---------------------------------------------------------
 * Grafo con matriz de adyacencia
 * --------------------------------------------------------- */
typedef struct {
    int      n;
    int      m;
    Persona *personas;      /* arreglo dinámico [0..n-1]   */
    int    **matriz;        /* matriz dinámica n x n       */
} GrafoMatriz;

/* ---------------------------------------------------------
 * Componente conexa (resultado del BFS)
 * --------------------------------------------------------- */
typedef struct {
    int *ids;       /* arreglo dinámico con ids de la componente */
    int  tam;       /* cantidad de personas                      */
    int  subtotal;  /* suma de dias_contagioso                   */
} Componente;

/* ---------------------------------------------------------
 * Prototipos — Lista de adyacencia (grafo_lista.c)
 * --------------------------------------------------------- */
GrafoLista *lista_crear(int n);
void        lista_agregar_persona(GrafoLista *g, int id,
                                  const char *nombre,
                                  int dias_contagioso);
void        lista_agregar_arista(GrafoLista *g, int a, int b);
void        lista_imprimir(GrafoLista *g);
void        lista_liberar(GrafoLista *g);

Componente  lista_bfs(GrafoLista *g, int inicio, int *visitado);
void        lista_encontrar_focos(GrafoLista *g, double umbral_pct);

/* ---------------------------------------------------------
 * Prototipos — Matriz de adyacencia (grafo_matriz.c)
 * --------------------------------------------------------- */
GrafoMatriz *matriz_crear(int n);
void         matriz_agregar_persona(GrafoMatriz *g, int id,
                                    const char *nombre,
                                    int dias_contagioso);
void         matriz_agregar_arista(GrafoMatriz *g, int a, int b);
void         matriz_imprimir(GrafoMatriz *g);
void         matriz_liberar(GrafoMatriz *g);

Componente   matriz_bfs(GrafoMatriz *g, int inicio, int *visitado);
void         matriz_encontrar_focos(GrafoMatriz *g, double umbral_pct);

/* ---------------------------------------------------------
 * Utilidad para medir tiempo
 * --------------------------------------------------------- */
static inline double ms_desde(clock_t inicio) {
    return 1000.0 * (clock() - inicio) / CLOCKS_PER_SEC;
}

#endif /* GRAFO_H */
