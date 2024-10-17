#include <stdio.h>

#define PAGES 4
#define FUTURE_REFERENCES 10

// Estructura que representa una página
typedef struct {
    char page;
} Page;

// Función para encontrar el índice de la página que será usada más tarde o no usada
int find_page_to_replace(Page pages[], char future_refs[], int current_ref_index) {
    int replace_index = -1;
    int farthest = current_ref_index;

    for (int i = 0; i < PAGES; i++) {
        int j;
        for (j = current_ref_index; j < FUTURE_REFERENCES; j++) {
            if (pages[i].page == future_refs[j]) {
                if (j > farthest) {
                    farthest = j;
                    replace_index = i;
                }
                break;
            }
        }

        // Si la página no se usará en el futuro, la reemplazamos de inmediato
        if (j == FUTURE_REFERENCES) {
            return i;
        }
    }

    // Si todas las páginas serán usadas en el futuro, reemplazamos la que se usará más tarde
    return (replace_index == -1) ? 0 : replace_index;
}

int main() {
    // Páginas iniciales
    Page pages[PAGES] = {
        {'A'},
        {'B'},
        {'C'},
        {'D'}
    };

    // Referencias futuras de páginas (secuencia de acceso)
    char future_references[FUTURE_REFERENCES] = {'B', 'A', 'E', 'A', 'C', 'F', 'B', 'E', 'D', 'F'};

    printf("Páginas actuales:\n");
    for (int i = 0; i < PAGES; i++) {
        printf("Página: %c\n", pages[i].page);
    }

    // Nueva página a cargar
    char new_page = 'E';
    printf("\nNueva página a cargar: %c\n", new_page);

    // Encontrar la página a reemplazar basada en las referencias futuras
    int replace_index = find_page_to_replace(pages, future_references, 0);
    printf("Reemplazando la página: %c\n", pages[replace_index].page);

    // Reemplazar la página con la nueva
    pages[replace_index].page = new_page;

    // Mostrar el nuevo estado de las páginas
    printf("\nEstado de las páginas después de la carga:\n");
    for (int i = 0; i < PAGES; i++) {
        printf("Página: %c\n", pages[i].page);
    }

    return 0;
}
