#include "srep.h"
#include <stdio.h>
#include <stdlib.h>

// Función que reemplaza un string por otro en un archivo CSV
// Entrada: Puntero a la estructura CSVData, string objetivo, string nuevo
// Salida: Archivo CSV con el mismo separador y encabezados, pero con el string
// objetivo reemplazado por el string nuevo

void reemplazar_string(CSVData* data, char* objetivo, char* nuevo){
    print_csv(data);
    printf("String objetivo: %s\n", objetivo);
    printf("String nuevo: %s\n", nuevo);

    free(data);
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
    read_csv(archivoEntrada, inputData);

    // Llamamos a la función reemplazar_string
    reemplazar_string(inputData, stringObjetivo, stringNuevo);


};
