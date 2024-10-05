#include "archivos.h"

int main() {
    CSVData data;

    // Leer el archivo CSV y almacenar las líneas en la estructura `data`
    read_csv("test.csv", &data);

    // Llamar a diferentes funciones que trabajen con las líneas almacenadas
    // En este caso, mostramos las líneas utilizando la función print_csv
    print_csv(&data);

    return 0;
}

// Para compilar: gcc main.c archivos.c -o programa
// Para ejecutar: ./programa
