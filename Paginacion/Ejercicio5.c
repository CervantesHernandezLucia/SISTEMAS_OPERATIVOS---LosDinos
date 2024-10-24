#include <stdio.h>

typedef struct {
  int presente;
  int modificado;
  int marco; 
} Pagina;

Pagina tablaPaginas[8] = {
  {1, 0, 1},
  {0, 0, 8},
  {1, 1, 9},
  {1, 0, 14},
  {1, 0, 5},
  {1, 0, 7},
  {0, 0, 25},
  {0, 1, 16}
};

int direccionFisica(int direccionVirtual) {
  int indicePagina = direccionVirtual >> 12;
  int desplazamiento = direccionVirtual & 0xFFF; 

  if (tablaPaginas[indicePagina].presente == 1) {
    return (tablaPaginas[indicePagina].marco << 12) | desplazamiento;
  } else {
    printf("Error: Falla de página\n");
    return -1;
  }
}

int main() {
  int direccionVirtual = 0x00005B83; 

  int direccionFisicaObtenida = direccionFisica(direccionVirtual);

  printf("Dirección física: 0x%x\n", direccionFisicaObtenida);

  return 0;
}
