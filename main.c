#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"

#define UMBRAL_FOCO 0.20
#define RUTA_MAX 4096

static void imprimir_uso(const char *programa) {
    fprintf(stderr,
            "Uso: %s <directorio_datos> <-lista|-matriz> [small|medium|large|xlarge]\n",
            programa);
}

static void construir_ruta(char *destino, size_t tam_destino,
                           const char *directorio,
                           const char *prefijo,
                           const char *tamano) {
    int escritos = snprintf(destino, tam_destino, "%s/%s_%s.csv",
                            directorio, prefijo, tamano);
    if (escritos < 0 || (size_t)escritos >= tam_destino) {
        fprintf(stderr, "Ruta demasiado larga para %s_%s.csv\n", prefijo, tamano);
        exit(1);
    }
}

static FILE *abrir_csv(const char *ruta) {
    FILE *archivo = fopen(ruta, "r");
    if (!archivo) {
        perror(ruta);
        exit(1);
    }
    return archivo;
}

static int linea_vacia(const char *linea) {
    while (*linea != '\0') {
        if (*linea != ' ' && *linea != '\t' && *linea != '\n' && *linea != '\r')
            return 0;
        linea++;
    }
    return 1;
}

static int contar_personas(const char *ruta_personas) {
    FILE *archivo = abrir_csv(ruta_personas);
    char linea[512];
    int total = 0;

    if (!fgets(linea, sizeof(linea), archivo)) {
        fprintf(stderr, "Archivo vacio: %s\n", ruta_personas);
        fclose(archivo);
        exit(1);
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        if (!linea_vacia(linea))
            total++;
    }

    fclose(archivo);
    return total;
}

static void parsear_persona(const char *linea, int *id,
                            char *nombre, size_t tam_nombre,
                            int *dias_contagioso) {
    if (sscanf(linea, "%d,%127[^,],%d", id, nombre, dias_contagioso) != 3) {
        fprintf(stderr, "Linea invalida en personas.csv: %s", linea);
        exit(1);
    }

    nombre[tam_nombre - 1] = '\0';
}

static void parsear_contacto(const char *linea, int *origen, int *destino) {
    if (sscanf(linea, "%d,%d", origen, destino) != 2) {
        fprintf(stderr, "Linea invalida en contactos.csv: %s", linea);
        exit(1);
    }
}

static void cargar_personas_lista(GrafoLista *g, const char *ruta_personas) {
    FILE *archivo = abrir_csv(ruta_personas);
    char linea[512];

    if (!fgets(linea, sizeof(linea), archivo)) {
        fprintf(stderr, "Archivo vacio: %s\n", ruta_personas);
        fclose(archivo);
        exit(1);
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        int id;
        int dias_contagioso;
        char nombre[128];

        if (linea_vacia(linea))
            continue;

        parsear_persona(linea, &id, nombre, sizeof(nombre), &dias_contagioso);
        lista_agregar_persona(g, id, nombre, dias_contagioso);
    }

    fclose(archivo);
}

static void cargar_contactos_lista(GrafoLista *g, const char *ruta_contactos) {
    FILE *archivo = abrir_csv(ruta_contactos);
    char linea[256];

    if (!fgets(linea, sizeof(linea), archivo)) {
        fprintf(stderr, "Archivo vacio: %s\n", ruta_contactos);
        fclose(archivo);
        exit(1);
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        int origen;
        int destino;

        if (linea_vacia(linea))
            continue;

        parsear_contacto(linea, &origen, &destino);
        lista_agregar_arista(g, origen, destino);
    }

    fclose(archivo);
}

static void cargar_personas_matriz(GrafoMatriz *g, const char *ruta_personas) {
    FILE *archivo = abrir_csv(ruta_personas);
    char linea[512];

    if (!fgets(linea, sizeof(linea), archivo)) {
        fprintf(stderr, "Archivo vacio: %s\n", ruta_personas);
        fclose(archivo);
        exit(1);
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        int id;
        int dias_contagioso;
        char nombre[128];

        if (linea_vacia(linea))
            continue;

        parsear_persona(linea, &id, nombre, sizeof(nombre), &dias_contagioso);
        matriz_agregar_persona(g, id, nombre, dias_contagioso);
    }

    fclose(archivo);
}

static void cargar_contactos_matriz(GrafoMatriz *g, const char *ruta_contactos) {
    FILE *archivo = abrir_csv(ruta_contactos);
    char linea[256];

    if (!fgets(linea, sizeof(linea), archivo)) {
        fprintf(stderr, "Archivo vacio: %s\n", ruta_contactos);
        fclose(archivo);
        exit(1);
    }

    while (fgets(linea, sizeof(linea), archivo)) {
        int origen;
        int destino;

        if (linea_vacia(linea))
            continue;

        parsear_contacto(linea, &origen, &destino);
        matriz_agregar_arista(g, origen, destino);
    }

    fclose(archivo);
}

static void ejecutar_lista(const char *ruta_personas, const char *ruta_contactos) {
    int n = contar_personas(ruta_personas);
    clock_t inicio = clock();
    GrafoLista *g = lista_crear(n);
    double tiempo_construccion;
    double tiempo_focos;

    cargar_personas_lista(g, ruta_personas);
    cargar_contactos_lista(g, ruta_contactos);
    tiempo_construccion = ms_desde(inicio);

    printf("=== Red de Contagio ===\n");
    printf("Personas  : %d\n", g->n);
    printf("Contactos : %d\n", g->m);
    lista_imprimir(g);
    printf("\n[Construccion del grafo: %.3f ms]\n\n", tiempo_construccion);

    inicio = clock();
    lista_encontrar_focos(g, UMBRAL_FOCO);
    tiempo_focos = ms_desde(inicio);
    printf("\n[Busqueda de focos: %.3f ms]\n", tiempo_focos);

    lista_liberar(g);
}

static void ejecutar_matriz(const char *ruta_personas, const char *ruta_contactos) {
    int n = contar_personas(ruta_personas);
    clock_t inicio = clock();
    GrafoMatriz *g = matriz_crear(n);
    double tiempo_construccion;
    double tiempo_focos;

    cargar_personas_matriz(g, ruta_personas);
    cargar_contactos_matriz(g, ruta_contactos);
    tiempo_construccion = ms_desde(inicio);

    printf("=== Red de Contagio ===\n");
    printf("Personas  : %d\n", g->n);
    printf("Contactos : %d\n", g->m);
    matriz_imprimir(g);
    printf("\n[Construccion del grafo: %.3f ms]\n\n", tiempo_construccion);

    inicio = clock();
    matriz_encontrar_focos(g, UMBRAL_FOCO);
    tiempo_focos = ms_desde(inicio);
    printf("\n[Busqueda de focos: %.3f ms]\n", tiempo_focos);

    matriz_liberar(g);
}

int main(int argc, char *argv[]) {
    char ruta_personas[RUTA_MAX];
    char ruta_contactos[RUTA_MAX];
    const char *directorio_datos;
    const char *representacion;
    const char *tamano = "small";

    if (argc < 3 || argc > 4) {
        imprimir_uso(argv[0]);
        return 1;
    }

    directorio_datos = argv[1];
    representacion = argv[2];

    if (argc == 4)
        tamano = argv[3];

    construir_ruta(ruta_personas, sizeof(ruta_personas),
                   directorio_datos, "personas", tamano);
    construir_ruta(ruta_contactos, sizeof(ruta_contactos),
                   directorio_datos, "contactos", tamano);

    if (strcmp(representacion, "-lista") == 0) {
        ejecutar_lista(ruta_personas, ruta_contactos);
        return 0;
    }

    if (strcmp(representacion, "-matriz") == 0) {
        ejecutar_matriz(ruta_personas, ruta_contactos);
        return 0;
    }

    imprimir_uso(argv[0]);
    return 1;
}