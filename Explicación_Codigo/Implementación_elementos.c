#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/mman.h> 

#define MAX_BLOCKS 8
#define MAX_TASKS 10
#define MAX_BLOCK_SIZE 128  

typedef struct MemoryBlock {
    int id;
    size_t size;
    struct MemoryBlock *next;
} MemoryBlock;

MemoryBlock *taskList = NULL; 
sem_t sem;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
uint8_t *bitmap; 
int pipe_fd[2];

MemoryBlock* createMemoryBlock(int id, size_t size) {
    MemoryBlock *block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
    if (block != NULL) {
        block->id = id;
        block->size = size;
        block->next = NULL;
    }
    return block;
}

void freeMemoryBlock(MemoryBlock *block) {
    free(block);
}

void swapMemory(int id) {
    printf("Intercambiando memoria para la tarea con ID: %d\n", id);
}

int allocateMemoryFIFO(size_t size) {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (bitmap[i] == 0 && size <= MAX_BLOCK_SIZE) {
            bitmap[i] = 1;  
            return i;    
        }
    }
    return -1; 
}

void freeMemoryWithBitmap(int index, size_t size) {
    bitmap[index] = 0;
}

void printMemoryList() {
    MemoryBlock *current = taskList;
    printf("Lista de bloques de memoria:\n");
    while (current != NULL) {
        printf("ID: %d, Tamaño: %zu\n", current->id, current->size);
        current = current->next;
    }
}

void cleanUp() {
    MemoryBlock *current = taskList;
    while (current != NULL) {
        MemoryBlock *toFree = current;
        current = current->next;
        freeMemoryWithBitmap(toFree->id - 1, toFree->size); 
        freeMemoryBlock(toFree);
    }
}

void* memoryTask(void* arg) {
    int taskId = *(int*)arg;  
    int blockIndex;
    printf("Hilo %d intentando asignar memoria.\n", taskId);  
    sem_wait(&sem);  
    pthread_mutex_lock(&mutex);  
    blockIndex = allocateMemoryFIFO(64);
    if (blockIndex != -1) {
        MemoryBlock *newTask = createMemoryBlock(taskId, 64);
        newTask->next = taskList;  
        taskList = newTask;  
        printf("Tarea creada con ID: %d, Bloque asignado: %d\n", newTask->id, blockIndex);
        write(pipe_fd[1], &taskId, sizeof(taskId));
    } else {
        swapMemory(taskId);
        printf("No hay bloques disponibles para la tarea %d, utilizando memoria de intercambio.\n", taskId);
    }
    pthread_mutex_unlock(&mutex);  
    sem_post(&sem);  
    free(arg);  
    pthread_exit(NULL);
}

void processTask(int taskId) {
    printf("Proceso %d accediendo a la memoria compartida.\n", taskId);
    sem_wait(&sem);  
    pthread_mutex_lock(&mutex); 
    if (bitmap[taskId % MAX_BLOCKS] == 1) {
        printf("Proceso %d encontró un bloque asignado en la posición %d.\n", taskId, taskId % MAX_BLOCKS);
    } else {
        printf("Proceso %d no encontró un bloque asignado.\n", taskId);
    }
    pthread_mutex_unlock(&mutex);  
    sem_post(&sem);  
}

int main() {
    pthread_t threads[MAX_TASKS];
    bitmap = mmap(NULL, MAX_BLOCKS * sizeof(uint8_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (bitmap == MAP_FAILED) {
        perror("Error al asignar memoria compartida");
        exit(EXIT_FAILURE);
    }
    sem_init(&sem, 1, 1);  
    if (pipe(pipe_fd) == -1) {
        perror("Error al crear la tubería");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAX_TASKS; i++) {
        int *arg = malloc(sizeof(*arg)); 
        if (arg == NULL) {
            perror("Error al asignar memoria");
            exit(EXIT_FAILURE);
        }
        *arg = i + 1;  
        if (pthread_create(&threads[i], NULL, memoryTask, arg) != 0) {
            perror("Error al crear hilo");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == 0) {  
            processTask(i + 1);
            exit(0);
        }
    }
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
    close(pipe_fd[1]);
    for (int i = 0; i < MAX_TASKS; i++) {
        int taskId;
        while (read(pipe_fd[0], &taskId, sizeof(taskId)) > 0) {
            printf("Mensaje recibido de la tarea con ID: %d\n", taskId);
        }
    }
    for (int i = 0; i < MAX_TASKS; i++) {
        pthread_join(threads[i], NULL);
    }
    printMemoryList();
    cleanUp();
    munmap(bitmap, MAX_BLOCKS * sizeof(uint8_t)); 
    sem_destroy(&sem);  
    close(pipe_fd[0]);  

    return 0;
}
