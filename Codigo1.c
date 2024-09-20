#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *cocinar_pasta(void *arg) {
    printf("Cocinando la pasta...\n");
    sleep(5); // Simula 5 segundos de cocción
    printf("Pasta lista!\n");
    pthread_exit(NULL);
}

void *cortar_verduras(void *arg) {
    printf("Cortando las verduras...\n");
    sleep(3); // Simula 3 segundos de corte
    printf("Verduras listas!\n");
    pthread_exit(NULL);
}

void *calentar_pan(void *arg) {
    printf("Calentando el pan...\n");
    sleep(2); // Simula 2 segundos de calentamiento
    printf("Pan listo!\n");
    pthread_exit(NULL);
}

void *poner_mesa(void *arg) {
    printf("Poniendo la mesa...\n");
    sleep(4); // Simula 4 segundos de preparación
    printf("Mesa lista!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[4];

    // Crear los hilos para cada tarea
    pthread_create(&hilos[0], NULL, cocinar_pasta, NULL);
    pthread_create(&hilos[1], NULL, cortar_verduras, NULL);
    pthread_create(&hilos[2], NULL, calentar_pan, NULL);
    pthread_create(&hilos[3], NULL, poner_mesa, NULL);

    // Esperar a que todas las tareas terminen
    for (int i = 0; i < 4; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("¡La cena está servida!\n");
    return 0;
}