#ifndef CUT_H
#define CUT_H

#include "archivos.h"

// Estructura para almacenar las columnas de cada línea
typedef struct {
    char ***columns;  // Arreglo de arreglos (columnas por línea)
    int *column_count;  // Número de columnas por cada línea
    int line_count;  // Número de líneas
} CSVColumns;

// Declaración de la función split que separará las líneas según el delimitador
void split(CSVData *data, const char delimiter, CSVColumns *columns_data);

// Declaración de la función cut que cortará las columnas especificadas
char ***cut(CSVColumns *columns_data, int *cobj, int num_cobj);

// Funciones auxiliares para manejar cadenas
int my_strlen(const char *str);

// Declaración de la función que escribirá la salida en un archivo
// Función para escribir el resultado en un archivo CSV
void out(char ***cut_data, int num_lines, int num_cols, const char *filename, char delimiter);

#endif // CUT_H
