#include "archivos.h"

// Funciones de string artesanal

// strcspn artesanal, considera saltos de linea
// Hasta encotnrar el /n almacena en la cadena destino
// Entrada: dos cadenas de caracteres
// Salida: tamaño de la cadena cómo estructura size_t
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

// String copy casero
// Entrada: dos cadenas de caracteres
// Salida: void, hace un proceso.
void my_strcpy(char *dest, const char *src) {
	// Copiar cada caracter de la cadena fuente a la cadena destino
    while (*src != '\0') {
        *dest++ = *src++;
    }
    // Añadir el terminador nulo al final de la cadena destino
    *dest = '\0';
}

// Implementación artesanal de strcat
// Entrada: dos cadenas de caracteres
// Salida: concatenación de las dos cadenas
char* my_strcat(char* dest, const char* src) {
	// Mover el puntero al final de la cadena destino
	while (*dest != '\0') {
		dest++;
	}

	// Copiar cada caracter de la cadena fuente a la cadena destino
	while (*src != '\0') {
		*dest++ = *src++;
	}

	// Añadir el terminador nulo al final de la cadena destino
	*dest = '\0';
	return dest;
}

// Función auxiliar para obtener la longitud de una cadena
// Entrada: una cadena de caracteres
// Salida: tamaño de la cadena cómo entero
int my_strlen(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}


// Funciones de CSV
// ----------------------------

// Entrada: nombre del archivo y estructura donde se almacenarán los datos
// Salida: void, hace un proceso.
// Función que lee un archivo CSV y almacena las líneas en una estructura
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
// Netamente para revisar si es que se leyó correctamente
void print_csv(const CSVData *data) {
    for (int i = 0; i < data->line_count; ++i) {
        printf("%s\n", data->lines[i]);
    }
}
