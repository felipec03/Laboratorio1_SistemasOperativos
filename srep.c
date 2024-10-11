#include "srep.h"
int main(int argc, char *argv[]){
	// Variable propia de getopt y unistd
    int opt;

    // Variables para el nombre de los archivos y los strings
    char* archivoEntrada = NULL;
    char* archivoSalida = NULL;
    char* stringObjetivo = NULL;
    char* stringNuevo = NULL;
    // Ciclo para leer las opciones de los flags
    while((opt = getopt(argc, argv, "s:S:i:o:")) != -1)
    {
        switch(opt)
        {
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
				abort();
        }
    }

    printf("String objetivo: %s\n", stringObjetivo);
    printf("String nuevo: %s\n", stringNuevo);
    printf("Archivo de entrada: %s\n", archivoEntrada);
    printf("Archivo de salida: %s\n", archivoSalida);
};
