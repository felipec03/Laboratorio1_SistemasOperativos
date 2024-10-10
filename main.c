#include "archivos.h"
#include "count.h"

int main() {
    CSVData data;

    // Leer el archivo CSV y almacenar las líneas en la estructura `data`
    read_csv("test.csv", &data);

    // Llamar a diferentes funciones que trabajen con las líneas almacenadas
    int lineas = contar_lineas(&data);
    int caracteres = contar_caracteres(&data);
    // En este caso, mostramos las líneas utilizando la función print_csv
    print_csv(&data);
    printf("\nnumero total de lineas del archivo: %d", lineas);
    printf("\nnumero total de caracteres del archivo: %d", caracteres);
    return 0;
}

// Para compilar: gcc main.c archivos.c count.c -o programa
// Para ejecutar: ./programa
