// Archivos de cabezera para "contrato" de cut y archivos
#include "cut.h"

// Funcion para separar las columnas de un archivo CSV en una estructura CSVColumns
// Entrada: Puntero a la estructura CSVData, delimitador, puntero donde se quiera guardar output
// Salida: void, queda como parametro de entrada la estructura CSVColumns con las columnas separadas
void split(CSVData *data, const char delimiter, CSVColumns *columns_data) {
	// IF resumido para el caso de que el delimitador sea '\0'
    char actual_delimiter = delimiter == '\0' ? '\t' : delimiter;

    // Inicializamos el contador de líneas
    columns_data->line_count = data->line_count;
    // Asignamos memoria para columnas y column_count
    columns_data->columns = (char ***)malloc(sizeof(char **) * data->line_count);
    columns_data->column_count = (int *)malloc(sizeof(int) * data->line_count);

    // Recorremos las lineas del archivo
    for (int i = 0; i < data->line_count; i++) {
    	// Variables para la linea actual, largo de linea y flag delimitador
        char *line = data->lines[i];
        int line_len = 0;
        int has_delimiter = 0;

        // Contamos los caracteres de la línea hasta el final
        while (line[line_len] != '\0') {
            if (line[line_len] == actual_delimiter) {
            	// Detectamos la presencia del delimitador
                has_delimiter = 1;
            }
            line_len++;
        }

        // Casos bordes
        if (!has_delimiter) {
            // Si no se encontró el delimitador, tratamos toda la línea como una sola columna
            columns_data->columns[i] = (char **)malloc(sizeof(char *));
            columns_data->columns[i][0] = (char *)malloc(sizeof(char) * (line_len + 1));
            // Se copia la línea completa
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

            // Iteramos sobre la línea para separar las columnas
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

// Funcion cut que selecciona columnas objetivo de un arreglo de lineas y columnas
// Entrada: columns_data: datos de las columnas, cobj: indices de las columnas objetivo, num_cobj: numero de columnas objetivo
// Salida: result: datos cortados.
char ***cut(CSVColumns *columns_data, int *cobj, int num_cobj) {
    int num_lines = columns_data->line_count;

    // Crear el resultado que contendra las columnas seleccionadas
    char ***result = (char ***)malloc(num_lines * sizeof(char **));

    // Iterar sobre cada línea
    for (int i = 0; i < num_lines; i++) {
    	// Almacenar las columnas seleccionadas por linea
        result[i] = (char **)malloc(num_cobj * sizeof(char *));
        // Iterar sobre indices de las columnas objetivo
        for (int j = 0; j < num_cobj; j++) {
        	// Indice de la columna que queremos extraer
         	// Desplazada por 1 para que no haya desfase con indice
            int col_index = cobj[j] - 1;

            // Verificar que el índice de la columna objetivo exista en esta línea
            if (col_index < columns_data->column_count[i]) {
                // Si la columna existe, asignarla al resultado
                // Largo de la columna
                int len = my_strlen(columns_data->columns[i][col_index]);
                // Asignar memoria
                result[i][j] = (char *)malloc((len + 1) * sizeof(char));
                // Copiar contenido con funcion artesanal
                my_strcpy(result[i][j], columns_data->columns[i][col_index]);
            } else {
                // Si columna no existe => asignar un espacio vacio
                result[i][j] = (char *)malloc(2 * sizeof(char));
                // Cadena vacia, end of file
                result[i][j][0] = '\0';
            }
        }
    }
    return result;
}

// Función para escribir el resultado de cut en un archivo CSV
// Entrada: cut_data: datos cortados, num_lines: número de líneas, num_cols: número de columnas, filename: nombre del archivo, delimiter: delimitador
// Salida: void, procesa un archivo de texto con los datos cortados
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
                fprintf(file, " ");
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

//funcion para copiar un archivo a otro
void copyarch(FILE *file1, FILE *file2) {
    char c;
    while ((c = fgetc(file1)) != EOF) {
        fputc(c, file2);
    }
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
	            // Si no se proporciona argumento para -c, optarg será NULL
                if (optarg == NULL || *optarg == '\0') {
                    stringColumnas = NULL; // No se han pasado columnas
                } else {
                    stringColumnas = optarg;
                }
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
    // Abrir los archivos para copiar en caso de que no se especifiquen columnas
    FILE *inputFile = fopen(archivoEntrada, "r");
    FILE *outputFile = fopen(archivoSalida, "a");
    if (stringColumnas == NULL) {
        // Si no se especifica la opción -c o si es una cadena vacía, copiar el archivo completo
        if (inputFile == NULL || outputFile == NULL) {
            fprintf(stderr, "Error al abrir los archivos\n");
            exit(EXIT_FAILURE);
        }

        // Llamar a la función copyarch para copiar el contenido
        copyarch(inputFile, outputFile);

        // Cerrar los archivos
        fclose(inputFile);
        fclose(outputFile);
        return 0;
    }
    // Typecasting del delimitador y de las columnas para procesamiento adecuado
    const char delimitadorChar = delimitador[0];

    // Convertir el string de columnas a un arreglo de enteros
    int numStringColumnas = my_strlen(stringColumnas);
    int arrayColumnas[numStringColumnas];
    int numColumnas = 0;
    // Sale de archivo.c
    transform_string_to_array(stringColumnas, arrayColumnas, &numColumnas);

    // Leer el archivo CSV original
    read_csv(archivoEntrada, &data);

    // Separar las lineas del CSV utilizando el delimitador de getopt
    // Queda guardado en parametro columns_data
    split(&data, delimitadorChar, &columns_data);

    // Aplicar la funcion cut para extraer las columnas objetivo
    char ***resultado_cut = cut(&columns_data, arrayColumnas, numColumnas);
    //escribir el resultado en un archivo
    out(resultado_cut, columns_data.line_count, numColumnas, archivoSalida, delimitadorChar);
    // Liberar memoria, buena practica =)
    for (int i = 0; i < columns_data.line_count; i++) {
        for (int j = 0; j < numColumnas; j++) {
            free(resultado_cut[i][j]);
        }
        free(resultado_cut[i]);
    }
    free(resultado_cut);

    return 0;
}
