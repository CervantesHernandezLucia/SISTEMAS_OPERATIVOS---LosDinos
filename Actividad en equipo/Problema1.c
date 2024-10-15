#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINEA 1024

void tarea1(int tuberia1[2], int tuberia2[2], char *fichero) {
    FILE *fp = fopen(fichero, "r");
    if (fp == NULL) {
        perror("Error al abrir el fichero");
        exit(1);
    }

    char linea[MAX_LINEA];
    int par = 0;
    while (fgets(linea, MAX_LINEA, fp)) {
        if (par % 2 == 0) {
            write(tuberia1[1], linea, strlen(linea));
        } else {
            write(tuberia2[1], linea, strlen(linea));
        }
        par++;
    }

    fclose(fp);
    close(tuberia1[1]);
    close(tuberia2[1]);
}

void tarea2(int tuberia[2], char *palabra, int tuberia_salida[2]) {
    char linea[MAX_LINEA];
    while (read(tuberia[0], linea, MAX_LINEA)) {
        if (strstr(linea, palabra) != NULL) {
            write(tuberia_salida[1], linea, strlen(linea));
        }
    }

    close(tuberia[0]);
    close(tuberia_salida[1]);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Uso: %s <fichero> <palabra1> <palabra2>\n", argv[0]);
        exit(1);
    }

    int tuberia1[2], tuberia2[2], tuberia3[2], tuberia4[2];
    pipe(tuberia1);
    pipe(tuberia2);
    pipe(tuberia3);
    pipe(tuberia4);

    pid_t pid1, pid2, pid3, pid4;

    pid1 = fork();
    if (pid1 == 0) {
        tarea1(tuberia1, tuberia2, argv[1]);
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        close(tuberia1[1]);
        tarea2(tuberia1, argv[2], tuberia3);
        exit(0);
    }

    pid3 = fork();
    if (pid3 == 0) {
        close(tuberia2[1]);
        tarea2(tuberia2, argv[3], tuberia4);
        exit(0);
    }

    pid4 = fork();
    if (pid4 == 0) {
        close(tuberia3[1]);
        dup2(tuberia3[0], 0);
        close(tuberia3[0]);
        execlp("sort", "sort", NULL);
        perror("Error al ejecutar sort");
        exit(1);
    }

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
    waitpid(pid4, NULL, 0);

    return 0;
}
