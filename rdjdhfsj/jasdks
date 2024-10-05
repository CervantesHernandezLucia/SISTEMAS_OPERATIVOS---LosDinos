#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CLIENTES 100
#define CLIENTES_POR_FURGON 20

sem_t clientes_en_sucursal;
sem_t operacion_en_curso;
pthread_mutex_t mutex;
int clientes = 0;
pthread_cond_t cond_clientes;

void proceso_cliente() {
    usleep(rand() % 3000000);
    pthread_mutex_lock(&mutex);
    clientes++;
    printf("Cliente entró a la sucursal. Clientes en la sucursal: %d\n", clientes);
    if (clientes % CLIENTES_POR_FURGON == 0 && clientes <= MAX_CLIENTES) {
        printf("\n¡El furgón blindado está llegando! La sucursal se está vaciando...\n\n");
        pthread_cond_signal(&cond_clientes); 
    }
    pthread_mutex_unlock(&mutex);
}

void* llegada_cliente(void* arg) {
    while (1) {
        proceso_cliente();
    }
}

void* operacion_furgon(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (clientes == 0) {
            pthread_cond_wait(&cond_clientes, &mutex);
        }
        printf("Furgón blindado realizando la operación de carga/descarga de dinero...\n");
        usleep(rand() % 200000);
        printf("Furgón blindado completó la operación.\n");

        while (clientes > 0) {
            printf("Cliente salió de la sucursal. Clientes en la sucursal: %d\n", clientes - 1);
            clientes--;
        }
        clientes = 0;
        pthread_mutex_unlock(&mutex);

        printf("La sucursal está vacía.\n");
    }
}

int main() {
    pthread_t hilo_clientes, hilo_furgon;

    if (sem_init(&clientes_en_sucursal, 0, 0) != 0 ||
        sem_init(&operacion_en_curso, 0, 1) != 0) {
        fprintf(stderr, "Error al inicializar semáforos\n");
        exit(1);
    }

    if (pthread_create(&hilo_clientes, NULL, llegada_cliente, NULL) != 0 ||
        pthread_create(&hilo_furgon, NULL, operacion_furgon, NULL) != 0) {
        fprintf(stderr, "Error al crear hilos\n");
        exit(1);
    }
    
    pthread_mutex_init(&mutex, NULL);
    pthread_join(hilo_clientes, NULL);
    pthread_join(hilo_furgon, NULL);
    sem_destroy(&clientes_en_sucursal);
    sem_destroy(&operacion_en_curso);

    return 0;
}
