#include "count.h"
#include "count.h"

// Función que cuenta el número de líneas en el archivo
// Entrada: Puntero a la estructura CSVData
// Salida: Número de líneas en el archivo
int contar_lineas(CSVData *data){
    return data->line_count;
}

// Función que cuenta el número de caracteres en todas las líneas
// Entrada: Puntero a la estructura CSVData
// Salida: Número de caracteres en todas las líneas
int contar_caracteres(CSVData *data){
    int contador = 0;
    for(int i = 0; i < data->line_count; i++){
        for(int j = 0; data->lines[i][j] != '\0'; j++){
            contador++;
        }
    }
    return contador;
}

int main(int argc, char *argv[])
{
	// Variable propia de getopt y unistd
    int opt;

    // Variables para las opciones de flags
    int opcionC = 0;
    int opcionL = 0;
    // Variable para el nombre del archivo
    char* filename = NULL;

    // Ciclo para leer las opciones de los flags
    while((opt = getopt(argc, argv, "CLi:")) != -1)
    {
        switch(opt)
        {
        	// Opción para el nombre del archivo
        	case 'i':
                filename = optarg;
                break;

            // Opción para contar el número de caracteres
            case 'C':
                opcionC = 1;
                break;

            // Opción para contar el número de líneas
            case 'L':
            	opcionL = 1;
                break;

            // En cualquier otro caso, abortar
            default:
				abort();
        }
    }

    CSVData data;

    // Leer el archivo CSV y almacenar las líneas en la estructura `data`
    read_csv(filename, &data);

    // Llamamos funciones de archivos.c
    int lineas = contar_lineas(&data);
    int caracteres = contar_caracteres(&data);

    // Opciones de impresión por flags
    if((opcionC == 1) && (opcionL == 0)){
    	printf("%d\n", caracteres);
    }

    if ((opcionL == 1) && (opcionC == 0)){
		printf("%d\n", lineas);
	}

    if((opcionL == 1) && (opcionC == 1)){
    	printf("%d %d\n", lineas, caracteres);
    }

    return 0;
}
