#include <stdio.h>

#define NUM_PAGINAS 4
#define NUM_ITERACIONES 5

typedef struct {
    char pagina;
    int bit_uso;
    int bit_modificacion;
} Pagina;

void reemplazar_pagina(Pagina paginas[], char nueva_pagina) {
    int clase[4] = {0, 0, 0, 0}; 
    int indice_clase[4]; 
    

    for (int i = 0; i < NUM_PAGINAS; i++) {
        if (paginas[i].bit_uso == 0 && paginas[i].bit_modificacion == 0) {
            clase[0]++;
            indice_clase[0] = i;
        } else if (paginas[i].bit_uso == 0 && paginas[i].bit_modificacion == 1) {
            clase[1]++;
            indice_clase[1] = i;
        } else if (paginas[i].bit_uso == 1 && paginas[i].bit_modificacion == 0) {
            clase[2]++;
            indice_clase[2] = i;
        } else {
            clase[3]++;
            indice_clase[3] = i;
        }
    }
    
  
    for (int i = 0; i < 4; i++) {
        if (clase[i] > 0) {
            printf("Reemplazando la página %c por la página %c\n", paginas[indice_clase[i]].pagina, nueva_pagina);
            paginas[indice_clase[i]].pagina = nueva_pagina;
            paginas[indice_clase[i]].bit_uso = 1;
            paginas[indice_clase[i]].bit_modificacion = 0; 
            break;
        }
    }
}

int main() {
    Pagina paginas[NUM_PAGINAS] = {
        {'A', 1, 0},
        {'B', 0, 1},
        {'C', 1, 0},
        {'D', 0, 0}
    };


    char nuevas_paginas[NUM_ITERACIONES] = {'E', 'F', 'G', 'H', 'I'};
    
    printf("Estado inicial de las páginas:\n");
    for (int i = 0; i < NUM_PAGINAS; i++) {
        printf("Página: %c, Bit de uso: %d, Bit de modificación: %d\n", paginas[i].pagina, paginas[i].bit_uso, paginas[i].bit_modificacion);
    }
    
    
    for (int i = 0; i < NUM_ITERACIONES; i++) {
        printf("\nIteración %d: Cargando la nueva página %c\n", i + 1, nuevas_paginas[i]);
        reemplazar_pagina(paginas, nuevas_paginas[i]);
        
        printf("Estado de las páginas después de la iteración %d:\n", i + 1);
        for (int j = 0; j < NUM_PAGINAS; j++) {
            printf("Página: %c, Bit de uso: %d, Bit de modificación: %d\n", paginas[j].pagina, paginas[j].bit_uso, paginas[j].bit_modificacion);
        }
    }

    return 0;
}
