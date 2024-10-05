// csv_reader.c
#include "archivos.h"

// Implementación manual de strcspn
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

// Implementación manual de strchr
char* my_strchr(const char *str, int c) {
    while (*str) {
        if (*str == (char)c) {
            return (char*)str;
        }
        str++;
    }
    return NULL;
}

void read_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];

    // Leer cada línea del archivo
    while (fgets(line, sizeof(line), file)) {
        // Reemplazar el salto de línea al final usando la implementación manual de strcspn
        line[my_strcspn(line, "\n")] = 0;

        // Separar los valores usando ; como delimitador sin strtok
        char *start = line;
        char *end;

        while ((end = my_strchr(start, ';')) != NULL) {
            *end = '\0'; // Terminar el string donde está el delimitador
            printf("%s\t", start);  // Procesar el token
            start = end + 1; // Mover el puntero al siguiente carácter después del delimitador
        }

        // Imprimir el último token después del último delimitador
        if (*start != '\0') {
            printf("%s\t", start);
        }

        printf("\n");
    }

    // Cerrar el archivo
    fclose(file);
}
