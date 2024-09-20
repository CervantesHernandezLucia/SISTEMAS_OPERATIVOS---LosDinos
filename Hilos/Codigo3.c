#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h> // Para usar rand() y srand()

#define NUM_CORREDORES 3

// Estructura para almacenar información sobre cada corredor
typedef struct {
    int id;
    int tiempo_carrera;
} Corredor;

// Función que simula la carrera de un corredor
void *correr(void *arg) {
    Corredor *corredor = (Corredor *) arg;
    
    printf("Corredor %d comienza a correr...\n", corredor->id);

    // Simular la carrera con un retraso aleatorio
    sleep(corredor->tiempo_carrera);

    printf("Corredor %d ha llegado a la meta!\n", corredor->id);

    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[NUM_CORREDORES];
    Corredor corredores[NUM_CORREDORES];

    // Inicializar la semilla para números aleatorios
    srand(time(NULL));

    // Crear los corredores y asignarles tiempos de carrera aleatorios
    for (int i = 0; i < NUM_CORREDORES; i++) {
        corredores[i].id = i + 1;
        corredores[i].tiempo_carrera = rand() % 5 + 1; // Tiempo aleatorio entre 1 y 5 segundos
    }

    // Iniciar la carrera
    for (int i = 0; i < NUM_CORREDORES; i++) {
        pthread_create(&hilos[i], NULL, correr, (void *)&corredores[i]);
    }

    // Esperar a que todos los corredores terminen
    for (int i = 0; i < NUM_CORREDORES; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("¡La carrera ha terminado!\n");

    return 0;
}