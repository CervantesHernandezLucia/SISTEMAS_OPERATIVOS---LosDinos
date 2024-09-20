#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // Para usar la función sleep()

// Función para simular una tarea
void *tarea(void *arg) {
    int tarea_id = *((int *) arg);

    switch (tarea_id) {
        case 1:
            printf("Lavando los platos...\n");
            // Simulación de la tarea: lavar los platos durante 3 segundos
            sleep(3);
            printf("Platos lavados!\n");
            break;
        case 2:
            printf("Poniendo la lavadora...\n");
            // Simulación de la tarea: poner la lavadora durante 2 segundos
            sleep(2);
            printf("Lavadora puesta!\n");
            break;
        // Puedes agregar más casos para simular otras tareas
        default:
            printf("Tarea desconocida.\n");
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[2];
    int tareas[] = {1, 2};

    // Crear hilos para cada tarea
    for (int i = 0; i < 2; i++) {
        if (pthread_create(&hilos[i], NULL, tarea, (void *) &tareas[i])) {
            fprintf(stderr, "Error al crear el hilo %d\n", i);
            return 1; // Indica un error
        }
    }

    // Esperar a que ambas tareas terminen
    for (int i = 0; i < 2; i++) {
        if (pthread_join(hilos[i], NULL)) {
            fprintf(stderr, "Error al esperar al hilo %d\n", i);
            return 1; // Indica un error
        }
    }

    printf("¡Todas las tareas completadas!\n");
    return 0;
}
