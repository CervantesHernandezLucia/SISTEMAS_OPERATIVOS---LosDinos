#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>  // Incluye esta línea para evitar la advertencia

int main(void) {
    // Definir dos descriptores de archivo para las tuberías
    int fd[2];
    int fd2[2];

    // Definir una variable para el ID del proceso
    pid_t pid;

    // Definir los mensajes que se enviarán
    char saludoPadre[] = "¿Cuántas tareas tienes hoy?";
    int tamSaludoPadre = strlen(saludoPadre);
    char buffer[tamSaludoPadre];

    char despedidaHijo[50]; // Asegurarse de que sea lo suficientemente grande
    int tamDespedidaHijo = sizeof(despedidaHijo);

    // Crear las tuberías
    pipe(fd);
    pipe(fd2);

    // Crear el proceso hijo
    pid = fork();

    switch (pid) {
        case -1:
            printf("No se ha podido crear hijo...\n");
            exit(-1);
            break;
        case 0: // Proceso hijo
            // Cerrar el descriptor de escritura en la tubería del hijo
            close(fd[1]);

            // Leer el mensaje del padre
            read(fd[0], buffer, tamSaludoPadre);
            printf("\t\t%s\n", buffer);

            // Generar un número aleatorio de tareas
            srand(time(NULL));
            int numTareas = rand() % 11; // Entre 0 y 10
            sprintf(despedidaHijo, "Tengo %d tareas.", numTareas);
            tamDespedidaHijo = strlen(despedidaHijo) + 1;

            // Cerrar el descriptor de lectura en la tubería del hijo
            close(fd[0]);

            // Despedirse del proceso padre
            write(fd2[1], despedidaHijo, tamDespedidaHijo);
            close(fd2[1]); // Cerrar después de escribir
            break;

        default: // Proceso padre
            // Cerrar el descriptor de lectura en la tubería del padre
            close(fd[0]);

            // Escribir el mensaje de saludo al hijo
            write(fd[1], saludoPadre, tamSaludoPadre);

            // Esperar a que el hijo termine
            wait(NULL);

            // Cerrar el descriptor de escritura en la tubería del padre
            close(fd[1]);

            // Leer el mensaje de despedida del hijo
            close(fd2[1]); // Cerrar el extremo de escritura
            read(fd2[0], despedidaHijo, tamDespedidaHijo);
            printf("\t\t%s\n", despedidaHijo);
            break;
    }
    return 0;
}
