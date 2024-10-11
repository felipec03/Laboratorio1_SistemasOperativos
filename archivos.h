#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

// Estructura para almacenar las líneas del archivo CSV
// En el fondo, es una matriz de caracteres
typedef struct {
    char lines[100][MAX_LINE_LENGTH];
    int line_count;
} CSVData;

// Declaración de la función para leer un archivo CSV y almacenar las líneas
void read_csv(const char *filename, CSVData *data);

// Declaración de la función para imprimir las líneas almacenadas
void print_csv(const CSVData *data);

// Declaración de la función manual de strcspn
size_t my_strcspn(const char *str, const char *reject);

// Declaración de la función manual de strcpy
void my_strcpy(char *dest, const char *src);

#endif // ARCHIVOS_H
