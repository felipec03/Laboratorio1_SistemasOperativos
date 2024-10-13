#include "archivos.h"
#include "cut.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    CSVData data;
    CSVColumns columns_data;
    int cobj[] = {1, 2};  // Ejemplo de las columnas que quieres extraer (columna 0 y 2)
    int num_cobj = sizeof(cobj) / sizeof(cobj[0]);  // Número de columnas objetivo

    // Leer el archivo CSV original
    read_csv("test2.csv", &data);

    // Separar las líneas del CSV utilizando ';' como delimitador
    split(&data, ':', &columns_data);

    // Aplicar la función cut para extraer las columnas objetivo
    char ***resultado_cut = cut(&columns_data, cobj, num_cobj);

    // Escribir el resultado en un archivo CSV de salida
    out(resultado_cut, columns_data.line_count, num_cobj, "out2.csv", ':');

    // Liberar memoria (opcional pero recomendable)
    for (int i = 0; i < columns_data.line_count; i++) {
        for (int j = 0; j < num_cobj; j++) {
            free(resultado_cut[i][j]);  // Liberar cada columna
        }
        free(resultado_cut[i]);  // Liberar la fila
    }
    free(resultado_cut);  // Liberar la matriz de resultados

    return 0;
}
// para compilar: gcc main.c archivos.c cut.c -o testcut
// para ejecutar: ./testcut