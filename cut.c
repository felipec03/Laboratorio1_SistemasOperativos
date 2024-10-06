#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int opt;

    while((opt = getopt(argc, argv, "abc:")) != -1){
		switch(opt){
			case 'a':
				printf("Option a\n");
				break;
			case 'b':
				printf("Option b\n");
				break;
			case 'c':
				printf("Option c with value %s\n", optarg);
				break;
			default:
				printf("Unknown option\n");
				break;
		}
	}

    return 0;
}
