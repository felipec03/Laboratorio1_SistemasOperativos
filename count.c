#include "count.h"
// Función que cuenta el número de líneas en el archivo
int contar_lineas(CSVData *data){
    return data->line_count;
}

// Función que cuenta el número de caracteres en todas las líneas
int contar_caracteres(CSVData *data){
    int contador = 0;
    for(int i = 0; i < data->line_count; i++){
        for(int j = 0; data->lines[i][j] != '\0'; j++){
            contador++;
        }
    }
    return contador;
}
