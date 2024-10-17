#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "archivos.h"

// Declaración de la función que reemplazará todas las iteraciones de un string objetivo
// a un string nuevo en todas las columnas
// char*** reemplazar_string(CSVData* data, char* objetivo, char* nuevo);

void srep(CSVData *data, char *string_objetivo, char *string_nuevo, char* output_file);

char *my_strncpy(char *dest, const char *src, int n);

char *my_strcpy2(char *dest, const char *src);

char *str_replace(char *orig, char *rep, char *with);
