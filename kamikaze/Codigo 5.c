#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/wait.h>

int main(void) {

    int fd[2];
    int fd2[2];

    pid_t pid;


    char saludoPadre[] = "¿Cuántas tareas tienes hoy?";
    int tamSaludoPadre = strlen(saludoPadre);
    char buffer[tamSaludoPadre];

    char despedidaHijo[50];
    int tamDespedidaHijo = sizeof(despedidaHijo);

    pipe(fd);
    pipe(fd2);

    pid = fork();

    switch (pid) {
        case -1:
            printf("No se ha podido crear hijo...\n");
            exit(-1);
            break;
        case 0:
            close(fd[1]);

            read(fd[0], buffer, tamSaludoPadre);
            printf("\t\t%s\n", buffer);

            srand(time(NULL));
            int numTareas = rand() % 11; 
            sprintf(despedidaHijo, "Tengo %d tareas.", numTareas);
            tamDespedidaHijo = strlen(despedidaHijo) + 1;

            close(fd[0]);

            write(fd2[1], despedidaHijo, tamDespedidaHijo);
            close(fd2[1]);
            break;

        default: 
            close(fd[0]);

            write(fd[1], saludoPadre, tamSaludoPadre);

            wait(NULL);

            close(fd[1]);

            close(fd2[1]); 
            read(fd2[0], despedidaHijo, tamDespedidaHijo);
            printf("\t\t%s\n", despedidaHijo);
            break;
    }
    return 0;
}
