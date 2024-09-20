#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *tarea(void *arg) {
    int tarea_id = *((int *) arg);

    switch (tarea_id) {
        case 1:
            printf("Lavando los platos...\n");
            sleep(3);
            printf("Platos lavados!\n");
            break;
        case 2:
            printf("Poniendo la lavadora...\n");
            sleep(2);
            printf("Lavadora puesta!\n");
            break;
        default:
            printf("Tarea desconocida.\n");
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[2];
    int tareas[] = {1, 2};

    for (int i = 0; i < 2; i++) {
        if (pthread_create(&hilos[i], NULL, tarea, (void *) &tareas[i])) {
            fprintf(stderr, "Error al crear el hilo %d\n", i);
            return 1; // Indica un error
        }
    }

    for (int i = 0; i < 2; i++) {
        if (pthread_join(hilos[i], NULL)) {
            fprintf(stderr, "Error al esperar al hilo %d\n", i);
            return 1; // Indica un error
        }
    }

    printf("¡Todas las tareas completadas!\n");
    return 0;
}
