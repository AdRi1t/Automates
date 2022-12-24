#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "automate.h"


int main(int argc,char** argv){
	Automate automate;
	if(argc == 1){
		printf("Veuillez specifier le fichier de l'automate et un mot\n");
		exit(EXIT_FAILURE);
	}else if(argc == 2)	{
		printf("Aucun mot\n");
		printf("Fichier de l'automate %s \n",argv[1]);
		exit(EXIT_FAILURE);
	}else{
		printf("Fichier de l'automate %s \n",argv[1]);
		printf("Mot: %s \n",argv[2]);
	}
	automate = read_file(argv[1]);
	print_automate(automate);
	return 0;
}

