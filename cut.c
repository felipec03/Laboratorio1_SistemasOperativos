#include "cut.h"
#include "archivos.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// Función que separa las columnas de un archivo CSV en la estructura CSVColumns
// Entrada: Puntero a la estructura CSVData, delimitador, puntero a la estructura CSVColumns
// Salida: Estructura CSVColumns con las columnas separadas, pasada como argumento.
void split(CSVData *data, const char delimiter, CSVColumns *columns_data) {
	// Inicializamos el delimitador actual
    char actual_delimiter = delimiter == '\0' ? '\t' : delimiter;

    // Inicializamos el contador de lineas
    columns_data->line_count = data->line_count;
    columns_data->columns = (char ***)malloc(sizeof(char **) * data->line_count);
    columns_data->column_count = (int *)malloc(sizeof(int) * data->line_count);

    // Ciclo que itera sobre cada línea
    for (int i = 0; i < data->line_count; i++) {
    	// Variables en scope de la función
        char *line = data->lines[i];
        int line_len = 0;
        int has_delimiter = 0;

        // Contamos los caracteres de la línea hasta el final
        while (line[line_len] != '\0') {
            if (line[line_len] == actual_delimiter) {
            	// Detectamos delimitador
                has_delimiter = 1;
            }
            line_len++;
        }

        // Consideramos casos de borde
        if (!has_delimiter) {
            // Si no se encontró el delimitador, tratamos toda la línea como una sola columna
            columns_data->columns[i] = (char **)malloc(sizeof(char *));
            columns_data->columns[i][0] = (char *)malloc(sizeof(char) * (line_len + 1));
            for (int j = 0; j < line_len; j++) {
                columns_data->columns[i][0][j] = line[j];
            }
            columns_data->columns[i][0][line_len] = '\0';
            // Solo una columna
            columns_data->column_count[i] = 1;
        } else {
            // Aquí haces la separación normal si se encontró el delimitador
            char **columns = (char **)malloc(sizeof(char *) * line_len);
            int col_count = 0;
            int start = 0;

            for (int j = 0; j <= line_len; j++) {
                if (line[j] == actual_delimiter || line[j] == '\0') {
                    int word_len = j - start;
                    columns[col_count] = (char *)malloc(sizeof(char) * (word_len + 1));
                    for (int k = 0; k < word_len; k++) {
                        columns[col_count][k] = line[start + k];
                    }
                    columns[col_count][word_len] = '\0';
                    col_count++;
                    start = j + 1;
                }
            }
            columns_data->columns[i] = columns;
            columns_data->column_count[i] = col_count;
        }
    }
}


// Función cut que selecciona columnas objetivo de un arreglo de líneas y columnas
// Entrada: Puntero a la estructura CSVColumns,
// puntero a un arreglo de índices de columnas objetivo,
// número de columnas objetivo
// Salida: Arreglo de líneas y columnas seleccionadas
char ***cut(CSVColumns *columns_data, int *col_obj, int num_cobj) {
    int num_lines = columns_data->line_count;

    // Asignamos memoria al resultado
    char ***result = (char ***)malloc(num_lines * sizeof(char **));

    // Iteramos sobre cada línea
    for (int i = 0; i < num_lines; i++) {
    	// Almacenar las columnas seleccionadas por linea
        result[i] = (char **)malloc(num_cobj * sizeof(char *));

        // Iterar sobre los indices de las columnas objetivo
        for (int j = 0; j < num_cobj; j++) {
        	// Indice de la columna que queremos extraer
            int col_index = col_obj[j];

            // Verificar que el índice de la columna objetivo exista en esta línea
            // Si la columna existe, asignarla al resultado
            if (col_index < columns_data->column_count[i]) {
                // Longitud de la columna
                int len = my_strlen(columns_data->columns[i][col_index]);
                // Asignar memoria
                result[i][j] = (char *)malloc((len + 1) * sizeof(char));
                // Copiar contenido
                my_strcpy(result[i][j], columns_data->columns[i][col_index]);
            } else {
                // Si la columna no existe, asignar un espacio vacío
                result[i][j] = (char *)malloc(2 * sizeof(char));
                result[i][j][0] = '\0';  // Cadena vacía
            }
        }
    }
    return result;
}

// Función para escribir el resultado de cut en un archivo CSV
void out(char ***cut_data, int num_lines, int num_cols, const char *filename, char delimiter) {
    // Abrimos el archivo en modo de agregar
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", filename);
        return;
    }

    // Iteramos sobre las líneas
    for (int i = 0; i < num_lines; i++) {
        for (int j = 0; j < num_cols; j++) {
            // Si la celda está vacía, escribir una celda vacía
            if (cut_data[i][j] == NULL || cut_data[i][j][0] == '\0') {
                fprintf(file, "");
            } else {
                // Escribir el contenido de la celda
                fprintf(file, "%s", cut_data[i][j]);
            }

            // Agregar el delimitador después de cada columna, excepto la última
            if (j < num_cols - 1) {
                fprintf(file, "%c", delimiter);
            }
        }
        // Escribir una nueva línea al final de cada línea
        fprintf(file, "\n");
    }

    // Cerrar el archivo
    fclose(file);
}

int main(int argc, char *argv[]) {
    CSVData data;
    CSVColumns columns_data;

    // Variable propia de getopt y unistd
    int opt;

    // Variables para el nombre de los archivos y los strings
    char* archivoEntrada = NULL;
    char* archivoSalida = NULL;
    char* delimitador = NULL;
    char* stringColumnas = NULL;
    // Ciclo para leer las opciones de los flags
    while((opt = getopt(argc, argv, "d:c:i:o:")) != -1)
    {
        switch(opt) {
	       	// Opción para el string objetivo
	       	case 'd':
	            delimitador = optarg;
	            break;

	            // Opción para el string nuevo
	        case 'c':
	            stringColumnas = optarg;
	            break;

	            // Opción  para archivo de entrada
	        case 'i':
	           	archivoEntrada = optarg;
	                break;

	            // Opción para archivo de salida
	        case 'o':
				archivoSalida = optarg;
				break;

            // En cualquier otro caso, alertar al usuario
            default:
                fprintf(stderr, "Forma de comando: %s -i input -o output -d delimitador -c columnas separadas por coma\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Typecasting del delimitador y de las columnas para procesamiento adecuado
    const char delimitadorChar = delimitador[0];

    int numStringColumnas = my_strlen(stringColumnas);
    int* arrayColumnas = (int*)malloc(numStringColumnas * sizeof(int));
    int numColumnas = 0;
    for(int i = 0; i<my_strlen(stringColumnas); i++){
    	if(stringColumnas[i] != ','){
    		arrayColumnas[i] = stringColumnas[i] - '0';
      		arrayColumnas[i]--;
      		printf("%d\n", arrayColumnas[i]);
      		numColumnas++;
     	}
    }
    printf("Numero de columnas: %d\n", numColumnas);

    // Leer el archivo CSV original
    read_csv(archivoEntrada, &data);

    // Separar las líneas del CSV utilizando el delimitador de getopt
    // Queda guardado en parametro columns_data
    split(&data, delimitadorChar, &columns_data);

    // Aplicar la función cut para extraer las columnas objetivo
    char ***resultado_cut = cut(&columns_data, arrayColumnas, numColumnas);

    // Escribir el resultado en un archivo CSV de salida
    out(resultado_cut, columns_data.line_count, numColumnas, archivoSalida, delimitadorChar);

    // Liberar memoria
    for (int i = 0; i < columns_data.line_count; i++) {
        for (int j = 0; j < numColumnas; j++) {
            free(resultado_cut[i][j]);
        }
        free(resultado_cut[i]);
    }
    free(resultado_cut);

    return 0;
}
