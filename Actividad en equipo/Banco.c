#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int saldo = 1000;

pthread_mutex_t lock;

void* retirar(void* arg) {
    int cantidad = *(int*)arg;

    pthread_mutex_lock(&lock);
    if (saldo >= cantidad) {
        printf("Retirando %d...\n", cantidad);
        saldo -= cantidad;
        printf("Saldo después del retiro: %d\n", saldo);
    } else {
        printf("Saldo insuficiente para retirar %d\n", cantidad);
    }
    pthread_mutex_unlock(&lock);

    return NULL;
}

void* depositar(void* arg) {
    int cantidad = *(int*)arg;

    pthread_mutex_lock(&lock);
    printf("Depositando %d...\n", cantidad);
    saldo += cantidad;
    printf("Saldo después del depósito: %d\n", saldo);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_mutex_init(&lock, NULL);

    int monto_retiro = 500;
    int monto_deposito = 300;

    pthread_t hilo_retiro, hilo_deposito;

    pthread_create(&hilo_retiro, NULL, retirar, &monto_retiro);
    pthread_create(&hilo_deposito, NULL, depositar, &monto_deposito);

    pthread_join(hilo_retiro, NULL);
    pthread_join(hilo_deposito, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}
