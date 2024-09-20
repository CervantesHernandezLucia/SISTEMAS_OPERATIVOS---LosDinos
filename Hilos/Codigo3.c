#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h> 

#define NUM_CORREDORES 3

typedef struct {
    int id;
    int tiempo_carrera;
} Corredor;

// Función que simula la carrera de un corredor
void *correr(void *arg) {
    Corredor *corredor = (Corredor *) arg;
    
    printf("Corredor %d comienza a correr...\n", corredor->id);

    sleep(corredor->tiempo_carrera);

    printf("Corredor %d ha llegado a la meta!\n", corredor->id);

    pthread_exit(NULL);
}

int main() {
    pthread_t hilos[NUM_CORREDORES];
    Corredor corredores[NUM_CORREDORES];

    srand(time(NULL));

    for (int i = 0; i < NUM_CORREDORES; i++) {
        corredores[i].id = i + 1;
        corredores[i].tiempo_carrera = rand() % 5 + 1; 
    }

    for (int i = 0; i < NUM_CORREDORES; i++) {
        pthread_create(&hilos[i], NULL, correr, (void *)&corredores[i]);
    }

    for (int i = 0; i < NUM_CORREDORES; i++) {
        pthread_join(hilos[i], NULL);
    }

    printf("¡La carrera ha terminado!\n");

    return 0;
}
