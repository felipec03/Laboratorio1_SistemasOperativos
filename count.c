#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	int option;

	while( (option = getopt(argc, argv, "LCi:") ) != -1){
		switch(option){
			case 'L':
				printf("Opción L, líneas. \n");
				break;
			case 'C':
				printf("Option C, columnas. \n");
				break;
			case 'i':
				printf("Opcion i, input de archivo de nombre: %s\n", optarg);
				break;
			case '?':
				printf("Opción desconocida, intentar nuevamente. %c\n", optopt);
				break;
		}
	}

	for(int i = optind; i < argc; i++){
		printf("Argumento: %d: %s\n", i, argv[i]);
	}

	return 0;
}
