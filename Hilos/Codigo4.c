#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define GREEN_LIGHT "Verde"
#define YELLOW_LIGHT "Amarillo"
#define RED_LIGHT "Rojo"


void initialize_semaphore(char *shared_memory) {
    strcpy(shared_memory, GREEN_LIGHT);
}

void change_state(char *shared_memory) {
    // Lógica más compleja para cambiar el estado, considerando eventos externos
    if (strcmp(shared_memory, GREEN_LIGHT) == 0) {
        strcpy(shared_memory, YELLOW_LIGHT);
    } else if (strcmp(shared_memory, YELLOW_LIGHT) == 0) {
        strcpy(shared_memory, RED_LIGHT);
    } else {
        strcpy(shared_memory, GREEN_LIGHT);
    }
}

void show_state(char *shared_memory) {
    printf("El semáforo está en: %s\n", shared_memory);
}

int main() {
    int fd[2];
    pid_t pid;
    char *shared_memory;
    int shmid;

    // Crear la tubería y la memoria compartida
    if (pipe(fd) == -1 || (shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666)) < 0) {
        perror("Error creando tubería o memoria compartida");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, NULL, 0);

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Proceso padre: Simula el paso del tiempo y eventos
        close(fd[0]);

        while (1) {
            write(fd[1], "tick", 4); // Envía un "tick" cada segundo
            sleep(1);

            // Simular eventos (por ejemplo, detectar vehículos)
            if (rand() % 10 == 0) {
                write(fd[1], "event", 5);
            }
        }
    } else { // Proceso hijo: Gestiona el semáforo
        close(fd[1]);
        char buffer[5];
        int seconds = 0;

        initialize_semaphore(shared_memory);

        while (1) {
            read(fd[0], buffer, 4);
            seconds++;

            if (strcmp(buffer, "event") == 0) {
                change_state(shared_memory);
                seconds = 0; // Reiniciar contador al ocurrir un evento
            } else if (seconds == 30 && strcmp(shared_memory, GREEN_LIGHT) == 0) {
                change_state(shared_memory);
                seconds = 0;
            } else if (seconds == 5 && strcmp(shared_memory, YELLOW_LIGHT) == 0) {
                change_state(shared_memory);
                seconds = 0;
            }

            show_state(shared_memory);
        }
    }

    return 0;
}