#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int opt;

    while((opt = getopt(argc, argv, "iCL:")) != -1){
		switch(opt){
			case 'i':
				printf("Option c with value %s\n", optarg);
				break;
			case 'C':
				printf("Option a\n");
				break;
			case 'L':
				printf("Option b\n");
				break;
			default:
				printf("Unknown option\n");
				break;
		}
	}
    return 0;
}
