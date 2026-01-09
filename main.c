#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOMBRE_ARCHIVO "tareas.dat"

typedef struct Tarea {
    int id;
    char descripcion[100];
    int completada;
    struct Tarea *siguiente;
} Tarea;

// Prototipado
int agregar_tarea(Tarea **cabeza, char *desc);
void listar_tareas(Tarea *cabeza);
int marcar_completada(Tarea *cabeza, int id);
int eliminar_tarea(Tarea **cabeza, int id);
void guardar_en_archivo(Tarea *cabeza);
void cargar_desde_archivo(Tarea **cabeza);
void liberar_lista(Tarea *cabeza);

int main() {
    Tarea *lista = NULL;
    int opcion, id;
    char desc[100];

    cargar_desde_archivo(&lista);

    do {
        printf("\n--- GESTOR DE TAREAS C ---\n");
        printf("1. Agregar tarea\n2. Listar tareas\n3. Marcar completada\n4. Eliminar tarea\n5. Salir\n");
        printf("Opcion: ");
        if (scanf("%d", &opcion) != 1) break;
        getchar(); // IMPORTANTE: Limpia el buffer para el próximo fgets

        switch (opcion) {
            case 1:
                printf("Descripcion: ");
                fgets(desc, 100, stdin);
                desc[strcspn(desc, "\n")] = 0;
                agregar_tarea(&lista, desc);
                break;
            case 2:
                listar_tareas(lista);
                break;
            case 3:
                printf("ID a marcar: ");
                scanf("%d", &id);
                if (!marcar_completada(lista, id)) printf("No encontrado.\n");
                break;
            case 4:
                printf("ID a eliminar: ");
                scanf("%d", &id);
                if (!eliminar_tarea(&lista, id)) printf("No encontrado.\n");
                break;
            case 5:
                guardar_en_archivo(lista);
                liberar_lista(lista);
                printf("Guardado y saliendo...\n");
                break;
        }
    } while (opcion != 5);
    return 0;
}

// --- Implementación de Funciones ---

int agregar_tarea(Tarea **cabeza, char *desc) {
    Tarea *nueva = (Tarea *)malloc(sizeof(Tarea));
    if(nueva == NULL) return 0;

    static int contador_id = 1;
    nueva->id = contador_id++;
    strncpy(nueva->descripcion, desc, 99);
    nueva->descripcion[99] = '\0';
    nueva->completada = 0;
    nueva->siguiente = *cabeza;
    *cabeza = nueva;
    return 1;
}

void listar_tareas(Tarea *cabeza) {
    if(cabeza == NULL) {
        printf("La lista esta vacia!\n");
        return;
    }
    printf("\n--- Lista de Tareas: ---\n");
    Tarea *actual = cabeza;
    while(actual != NULL) {
        printf("[%d] %s - %s\n", actual->id, actual->descripcion,
               actual->completada ? "COMPLETADA" : "PENDIENTE");
        actual = actual->siguiente;
    }
}

int marcar_completada(Tarea *cabeza, int id) {
    Tarea *actual = cabeza;
    while (actual != NULL) {
        if(actual->id == id) {
            actual->completada = 1;
            return 1;
        }
        actual = actual->siguiente;
    }
    return 0;
}

int eliminar_tarea(Tarea **cabeza, int id) {
    Tarea *actual = *cabeza;
    Tarea *anterior = NULL;
    while(actual != NULL) {
        if(actual->id == id) {
            if(anterior == NULL) *cabeza = actual->siguiente;
            else anterior->siguiente = actual->siguiente;
            free(actual);
            return 1;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return 0;
}

void guardar_en_archivo(Tarea *cabeza) {
    FILE *f = fopen(NOMBRE_ARCHIVO, "wb");
    if(f == NULL) return;
    Tarea *actual = cabeza;
    while(actual != NULL) {
        fwrite(actual, sizeof(Tarea) - sizeof(struct Tarea *), 1, f);
        actual = actual->siguiente;
    }
    fclose(f);
}

void cargar_desde_archivo(Tarea **cabeza) {
    FILE *f = fopen(NOMBRE_ARCHIVO, "rb");
    if(f == NULL) return;
    Tarea temp;
    while(fread(&temp, sizeof(Tarea) - sizeof(struct Tarea *), 1, f)) {
        agregar_tarea(cabeza, temp.descripcion);
        (*cabeza)->completada = temp.completada;
    }
    fclose(f);
}

void liberar_lista(Tarea *cabeza) {
    Tarea *temp;
    while(cabeza != NULL) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp);
    }
}
