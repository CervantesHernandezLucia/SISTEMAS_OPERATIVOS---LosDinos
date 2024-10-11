#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
                                                                                                                            // Estructura para representar un bloque de memoria
typedef struct MemoryBlock {
    int id;                                                                                                                 // Identificador único del bloque
    size_t size;                                                                                                            // Tamaño del bloque en bytes
    struct MemoryBlock *next;                                                                                               // Puntero al siguiente bloque en la lista enlazada
} MemoryBlock;
                                                                                                                            // Función para crear un nuevo bloque de memoria
MemoryBlock* createMemoryBlock(int id, size_t size) {
                                                                                                                            // Asigna memoria para el nuevo bloque
    MemoryBlock *block = (MemoryBlock *)malloc(sizeof(MemoryBlock));
                                                                                                                            // Verifica si la asignación de memoria fue exitosa
    if (block != NULL) {
                                                                                                                            // Inicializa los campos del bloque
        block->id = id;
        block->size = size;
        block->next = NULL;                                                                                                 // El último bloque apunta a nulo
    }
    return block;
}
                                                                                                                            // Función para liberar un bloque de memoria
void freeMemoryBlock(MemoryBlock *block) {
                                                                                                                            // Libera la memoria asociada al bloque
    free(block);
}
                                                                                                                            // Función para simular el intercambio de memoria para una tarea
void swapMemory(int id) {
    printf("Intercambiando memoria para la tarea con ID: %d\n", id);
}
                                                                                                                            // Define el número máximo de bloques
#define MAX_BLOCKS 8
                                                                                                                            // Crea un mapa de bits para rastrear la disponibilidad de bloques
uint8_t bitmap[MAX_BLOCKS] = {0};
                                                                                                                            // Función para asignar memoria usando el mapa de bits
int allocateMemoryWithBitmap(size_t size) {
                                                                                                                            // Itera sobre el mapa de bits para encontrar un bloque disponible
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (bitmap[i] == 0) {                                                                                               // El bloque está disponible
                                                                                                                            // Marca el bloque como ocupado
            bitmap[i] = 1;
            return i;                                                                                                       // Devuelve el índice del bloque asignado
        }
    }
                                                                                                                            // Si no hay bloques disponibles, devuelve -1
    return -1;
}
                                                                                                                            // Función para liberar memoria usando el mapa de bits
void freeMemoryWithBitmap(int index) {
                                                                                                                            // Marca el bloque como disponible
    bitmap[index] = 0;
}
                                                                                                                            // Función para imprimir la lista de bloques de memoria
void printMemoryList(MemoryBlock *head) {
    MemoryBlock *current = head;                                                                                            // Comienza desde el inicio de la lista enlazada
    printf("Lista de bloques de memoria:\n");

                                                                                                                            // Itera sobre la lista enlazada e imprime la información de cada bloque
    while (current != NULL) {
        printf("ID: %d, Tamaño: %zu\n", current->id, current->size);
        current = current->next;                                                                                            // Pasa al siguiente bloque
    }
}
                                                                                                                            // Función para limpiar y liberar todos los bloques de memoria
void cleanUp(MemoryBlock *head) {
    MemoryBlock *current = head;
                                                                                                                            // Itera sobre la lista enlazada y libera cada bloque
    while (current != NULL) {
        MemoryBlock *toFree = current;                                                                                      // Almacena el bloque actual para liberarlo
        current = current->next;                                                                                            // Pasa al siguiente bloque
        freeMemoryWithBitmap(toFree->id - 1);                                                                               // Libera la entrada correspondiente en el mapa de bits
        freeMemoryBlock(toFree);                                                                                            // Libera el bloque de memoria
    }
}
                                                                                                                            // Función principal
int main() {
    MemoryBlock *taskList = NULL;                                                                                           // Inicializa la lista enlazada para almacenar tareas
    int taskId = 1;                                                                                                         // Inicializa el ID de la tarea
                                                                                                                            // Crea y asigna memoria para tareas
    for (int i = 0; i < 10; i++) {
        int blockIndex = allocateMemoryWithBitmap(64);
        if (blockIndex != -1) {                                                                                             // El bloque fue asignado exitosamente
            MemoryBlock *newTask = createMemoryBlock(taskId++, 64);
            newTask->next = taskList;                                                                                       // Agrega la nueva tarea al inicio de la lista enlazada
            taskList = newTask;
            printf("Tarea creada con ID: %d, Bloque asignado: %d\n", newTask->id, blockIndex);
        } else {                                                                                                            // No había bloques disponibles
            swapMemory(taskId);
            printf("No hay bloques disponibles para la tarea %d, utilizando memoria de intercambio.\n", taskId);
        }
    }
                                                                                                                            // Imprime la lista de bloques de memoria
    printMemoryList(taskList);
                                                                                                                            // Limpia y libera toda la memoria
    cleanUp(taskList);
    return 0;
}
