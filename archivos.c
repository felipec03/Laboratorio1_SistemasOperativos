#include "archivos.h"

size_t my_strcspn(const char *str, const char *reject) {
    const char *p, *r;
    size_t count = 0;

    for (p = str; *p != '\0'; ++p) {
        for (r = reject; *r != '\0'; ++r) {
            if (*p == *r)
                return count;
        }
        ++count;
    }

    return count;
}


void my_strcpy(char *dest, const char *src) {
    while (*src != '\0') {
        *dest++ = *src++;
    }
    *dest = '\0';  // Añadir el terminador nulo al final
}


void read_csv(const char *filename, CSVData *data) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    data->line_count = 0;  // Inicializar contador de líneas

    // Leer cada línea del archivo
    while (fgets(line, sizeof(line), file)) {
        // Eliminar el salto de línea al final de la línea
        line[my_strcspn(line, "\n")] = 0;

        // Copiar la línea al arreglo de líneas de la estructura
        my_strcpy(data->lines[data->line_count], line);
        data->line_count++;
    }

    // Cerrar el archivo
    fclose(file);
}

// Función que muestra las líneas almacenadas del archivo
void print_csv(const CSVData *data) {
    for (int i = 0; i < data->line_count; ++i) {
        printf("%s\n", data->lines[i]);
    }
}
