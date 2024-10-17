#include "srep.h"
#include "archivos.h"
#include <string.h>

// Funcion artesanal de strstr() encuentra la primera ocurrencia de la subcadena, "aguja en un pajar"
// Entrada: dos cadenas de caracteres
// Salida: puntero a caracter de la primera ocurrencia de la subcadena en la objetivo
char *my_strstr(const char *objetivo, const char *busqueda) {
	// Si es nulo, retornar
    if (*busqueda == '\0') {
        return (char *)objetivo;
    }

    // Mientras no se llegue al final de la cadena objetivo
    for (; *objetivo != '\0'; objetivo++) {
        if (*objetivo == *busqueda) {
        	// Se definen variables temporales para comparar
            const char *objetivoTemp = objetivo;
            const char *reemplazoTemp = busqueda;
            while (*objetivoTemp != '\0' && *reemplazoTemp != '\0' && *objetivoTemp == *reemplazoTemp) {
                objetivoTemp++;
                reemplazoTemp++;
            }
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
char *my_strcpy2(char *dest, const char *src) {
    char *original_dest = dest;
    while ((*dest++ = *src++) != '\0');
    return original_dest;
}

// Implementacion artesanal de strncpy
// Entrada: dos cadenas de caracteres y un entero que representa el tamaño
// Salida: puntero a caracter de la cadena destino
char *my_strncpy(char *dest, const char *src, int n) {
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return dest;
}

// Modified str_replace function using custom string functions
char *str_replace(char *orig, char *rep, char *with) {
    char *result;
    char *ins;
    char *tmp;
    int len_rep;
    int len_with;
    int len_front;
    int count;

    if (!orig || !rep)
        return NULL;

    len_rep = my_strlen(rep);
    if (len_rep == 0)
        return NULL;

    if (!with)
        with = "";
    len_with = my_strlen(with);

    ins = orig;
    for (count = 0; (tmp = my_strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(my_strlen(orig) + (len_with - len_rep) * count + 1);
    if (!result)
        return NULL;

    while (count--) {
        ins = my_strstr(orig, rep);
        len_front = ins - orig;
        tmp = my_strncpy(tmp, orig, len_front) + len_front;
        tmp = my_strcpy2(tmp, with) + len_with;
        orig += len_front + len_rep;
    }
    my_strcpy(tmp, orig);
    return result;
}
// Función que reemplaza un string por otro en un archivo CSV
// Entrada: Puntero a la estructura CSVData, string objetivo, string nuevo
// Salida: Archivo CSV con el mismo separador y encabezados, pero con el string objetivo reemplazado por el string nuevo
void srep(CSVData *data, char *string_objetivo, char *string_nuevo){
	for(int i = 0; i<data->line_count;i++){
		char* aux = data->lines[i];
		char* resultLine = str_replace(aux, string_objetivo, string_nuevo);
		printf("%s\n", resultLine);
	}

	/*
	for(int i = 0; i<data->line_count; i++){
		for(int j = 0; j < my_strlen(data->lines[i]); j++){
			printf("%c", data->lines[i][j]);
		}
	}
	*/
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

    printf("Archivo de entrada: %s\n", archivoEntrada);
    printf("Archivo de salida: %s\n", archivoSalida);
    // Inicializamos la estructura CSVData
    CSVData* inputData = malloc(sizeof(CSVData));

    // Llamamos a la función read_csv
    read_csv(archivoEntrada, inputData);

    // Llamamos a la función srep
    srep(inputData, stringObjetivo, stringNuevo);

}
