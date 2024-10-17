#include "srep.h"
#include "archivos.h"
#include <string.h>

// Funcion artesanal de strstr() encuentra la primera ocurrencia de la subcadena, "aguja en un pajar"
// Entrada: dos cadenas de caracteres
// Salida: puntero a caracter de la primera ocurrencia de la subcadena en la objetivo
char* my_strstr(const char *objetivo, const char *busqueda) {
	// Si es nulo, retornar
    if (*busqueda == '\0') {
        return (char *)objetivo;
    }

    // Iteramos sobre la cadena objetivo
    for (; *objetivo != '\0'; objetivo++) {
        if (*objetivo == *busqueda) {
        	// Se definen variables temporales para comparar
            const char *objetivoTemp = objetivo;
            const char *reemplazoTemp = busqueda;
            // Mientras no se llegue al final de la cadena objetivo y reemplazo y sean iguales
            while (*objetivoTemp != '\0' && *reemplazoTemp != '\0' && *objetivoTemp == *reemplazoTemp) {
                objetivoTemp++;
                reemplazoTemp++;
            }
            // Si se termina, entonces retornamos objetivo
            if (*reemplazoTemp == '\0') {
                return (char *)objetivo;
            }
        }
    }

    return NULL;
}

// Parecido a strcpy, a diferencia de la implementacion en archivos, esta devuelve un puntero a caracter
// Entrada: dos cadenas de caracteres
// Salida: puntero a caracter de la cadena destino
char* my_strcpy2(char *dest, const char *src) {
    char* original_dest = dest;
    while ((*dest++ = *src++) != '\0');
    return original_dest;
}

// Implementacion artesanal de strncpy
// Entrada: dos cadenas de caracteres y un entero que representa el tamaño
// Salida: puntero a caracter de la cadena destino
char *my_strncpy(char *dest, const char *src, int n) {
    int i;
    // Copiar cada caracter de la cadena fuente a la cadena destino
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    // Añadir el fin de linea al final de la cadena destino
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

// Función str_replace modificada usando funciones personalizadas de cadenas
char *str_replace(char *orig, char *rep, char *with) {
    char *result;  // Cadena resultante
    char *ins;     // Punto de inserción actual
    char *tmp;     // Variable temporal
    int len_rep;   // Longitud de la cadena a reemplazar
    int len_with;  // Longitud de la cadena de reemplazo
    int len_front; // Distancia entre el inicio y la ocurrencia de 'rep'
    int count;     // Número de reemplazos

    // Verificaciones de seguridad
    if (!orig || !rep)
        return NULL;

    len_rep = my_strlen(rep);
    // Evita bucle infinito si 'rep' está vacío
    if (len_rep == 0)
        return NULL;

    // Si 'with' es NULL, usa cadena vacía
    if (!with)
        with = "";
    len_with = my_strlen(with);

    // Cuenta el número de reemplazos necesarios
    ins = orig;
    for (count = 0; (tmp = my_strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    // Asigna memoria para la cadena resultante, si falla memoria, retorna NULL
    tmp = result = malloc(my_strlen(orig) + (len_with - len_rep) * count + 1);
    if (!result)
        return NULL;

    // Realiza los reemplazos
    while (count--) {
        ins = my_strstr(orig, rep);
        len_front = ins - orig;
        tmp = my_strncpy(tmp, orig, len_front) + len_front;
        tmp = my_strcpy2(tmp, with) + len_with;
        orig += len_front + len_rep;
    }

    // Copia el resto de la cadena original
    my_strcpy(tmp, orig);
    return result;
}

// Función que reemplaza un string por otro en un archivo CSV y escribe el resultado en un nuevo archivo
// Entrada: Puntero a la estructura CSVData, string objetivo, string nuevo, nombre del archivo de salida
// Salida: Archivo de texto plano con el string objetivo reemplazado por el string nuevo
void srep(CSVData *data, char *string_objetivo, char *string_nuevo, char* output_file) {
    // Abrir el archivo de salida en write mode "w"
    FILE *fp = fopen(output_file, "w");
    // Manejo de error
    if (fp == NULL) {
        printf("Error al abrir el archivo de salida, inténtelo de nuevo...\n");
        return;
    }

    // Iteramos sobre lineas de la estructura archivo
    for (int i = 0; i < data->line_count; i++) {
    	// Variables auxiliares
        char* aux = data->lines[i];
        char* resultLine = str_replace(aux, string_objetivo, string_nuevo);

        // Si linea no esta vacia...
        if (resultLine != NULL) {
            // Escribir la línea modificada en el archivo
            fprintf(fp, "%s\n", resultLine);

            // Liberar la memoria asignada por str_replace
            free(resultLine);
        } else {
            // Si str_replace falla, escribir la línea original
            fprintf(fp, "%s\n", aux);
        }
    }

    // Cerrar el archivo
    fclose(fp);
    printf("El archivo %s ha sido generado exitosamente.\n", output_file);
}

int main(int argc, char *argv[]){
	// Variable propia de getopt y unistd
    int opt;

    // Variables para el nombre de los archivos y los strings
    char* archivoEntrada = NULL;
    char* archivoSalida = NULL;
    char* stringObjetivo = NULL;
    char* stringNuevo = NULL;
    // Ciclo para leer las opciones de los flags
    while((opt = getopt(argc, argv, "s:S:i:o:")) != -1){
        switch(opt){
        	// Opción para el string objetivo
        	case 's':
                stringObjetivo = optarg;
                break;

            // Opción para el string nuevo
            case 'S':
                stringNuevo = optarg;
                break;

            // Opción  para archivo de entrada
            case 'i':
            	archivoEntrada = optarg;
                break;

            // Opción para archivo de salida
            case 'o':
				archivoSalida = optarg;
				break;

            // En cualquier otro caso, abortar
            default:
                fprintf(stderr, "Forma de comando: %s -i input -o output -s objetivo -S nuevo\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Ahora, debemos leer el archivo de entrada tomando en consideración el input del getopt
    // Además, tenemos que inicializar un archivo de salida
    // Inicializamos la estructura CSVData
    CSVData* inputData = malloc(sizeof(CSVData));

    // Llamamos a la función read_csv
    read_csv(archivoEntrada, inputData);

    // Llamamos a la función srep, que tiene por finalidad leer y escribir
    srep(inputData, stringObjetivo, stringNuevo, archivoSalida);

}
