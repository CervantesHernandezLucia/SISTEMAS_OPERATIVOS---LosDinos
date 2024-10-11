#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct {
    int entradaLista;
    int platoPrincipalListo;
    int bebidaLista;
} Pedido;

void prepararEntrada(Pedido* pedido) {
    printf("Preparando entrada...\n");
    sleep(2);
    pedido->entradaLista = 1;
    printf("Entrada lista.\n");
}

void prepararPlatoPrincipal(Pedido* pedido) {
    while (!pedido->entradaLista); // Esperar a que la entrada esté lista
    printf("Preparando plato principal...\n");
    sleep(3);
    pedido->platoPrincipalListo = 1;
    printf("Plato principal listo.\n");
}

void prepararBebida(Pedido* pedido) {
    printf("Preparando bebida...\n");
    sleep(1);
    pedido->bebidaLista = 1;
    printf("Bebida lista.\n");
}

int main() {
    key_t key = IPC_PRIVATE;
    int shmid = shmget(key, sizeof(Pedido), IPC_CREAT | 0666);
    Pedido* pedido = shmat(shmid, NULL, 0);

    pedido->entradaLista = 0;
    pedido->platoPrincipalListo = 0;
    pedido->bebidaLista = 0;

    if (fork() == 0) {
        prepararEntrada(pedido);
        exit(0);
    }
    if (fork() == 0) {
        prepararPlatoPrincipal(pedido);
        exit(0);
    }
    if (fork() == 0) {
        prepararBebida(pedido);
        exit(0);
    }

    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    printf("Pedido completo.\n");

    shmdt(pedido);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
