#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_VEHICULOS 100
#define NUM_SENTIDOS 2
#define TIEMPO_ESPERA_MAX 20

pthread_mutex_t puente_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condicion_puente[NUM_SENTIDOS];

int sentido_actual = 0; 
int vehiculos_en_puente[NUM_SENTIDOS] = {0, 0}; 

typedef struct {
    int id;
    int sentido;
} vehiculo_t;

void *vehiculo(void *arg) {
    vehiculo_t *vehiculo = (vehiculo_t *)arg;
    int tiempo_espera = rand() % TIEMPO_ESPERA_MAX;

    sleep(tiempo_espera);

    pthread_mutex_lock(&puente_mutex);

    while (sentido_actual != vehiculo->sentido && vehiculos_en_puente[sentido_actual] > 0) {
        pthread_cond_wait(&condicion_puente[vehiculo->sentido], &puente_mutex);
    }

    vehiculos_en_puente[vehiculo->sentido]++;
    sentido_actual = vehiculo->sentido;

    printf("Vehículo %d entra en el puente (sentido %d)\n", vehiculo->id, vehiculo->sentido);

    sleep(1);

    vehiculos_en_puente[vehiculo->sentido]--;
    if (vehiculos_en_puente[vehiculo->sentido] == 0) {
        pthread_cond_broadcast(&condicion_puente[1 - vehiculo->sentido]);
    }

    printf("Vehículo %d abandona el puente (sentido %d)\n", vehiculo->id, vehiculo->sentido);

    pthread_mutex_unlock(&puente_mutex);

    free(vehiculo);

    return NULL;
}

int main() {
    pthread_t hilos[NUM_VEHICULOS];
    vehiculo_t *vehiculos[NUM_VEHICULOS];

    srand(time(NULL));

    for (int i = 0; i < NUM_VEHICULOS; i++) {
        vehiculos[i] = malloc(sizeof(vehiculo_t));
        vehiculos[i]->id = i;
        vehiculos[i]->sentido = i % 2; 
        pthread_create(&hilos[i], NULL, vehiculo, vehiculos[i]);
    }

    for (int i = 0; i < NUM_VEHICULOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}
