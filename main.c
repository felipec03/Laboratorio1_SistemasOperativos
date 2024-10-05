#include "archivos.h"

int main() {
    char filename[256];

    // Solicitar al usuario que ingrese el nombre del archivo
    printf("Por favor, ingresa el nombre del archivo CSV: ");
    scanf("%255s", filename);

    // Leer el archivo CSV proporcionado por el usuario
    read_csv(filename);

    return 0;
}

//gcc main.c archivos.c -o programa -> para que lo corras en la terminal
//./programa -> para que lo corras en la terminal
