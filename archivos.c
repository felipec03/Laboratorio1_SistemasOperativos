// csv_reader.c
#include "archivos.h"

void read_csv(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];

    // Leer cada línea del archivo
    while (fgets(line, sizeof(line), file)) {
        // Reemplazar el salto de línea al final
        line[strcspn(line, "\n")] = 0;

        // Separar los valores usando ; como delimitador
        char *token = strtok(line, ";");

        while (token != NULL) {
            printf("%s\t", token);  // Procesar el token
            token = strtok(NULL, ";");
        }

        printf("\n");
    }

    // Cerrar el archivo
    fclose(file);
}
