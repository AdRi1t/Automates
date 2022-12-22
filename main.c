#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "automate.h"


int main(int argc,char** argv){
	Automate automate;
	int i=0;
	if(argc == 1){
		printf("Veuillez specifier le fichier de l'automate et un mot \n");
	}else if(argc == 2)	{
		printf("Aucun mot !\n");
		printf("Fichier de l'automate %s \n",argv[1]);
	}else{
		printf("Fichier de l'automate %s \n",argv[1]);
		printf("Mot: %s \n",argv[2]);
	}
	automate = read_file(argv[1]);
	for(i=0;i<automate.nb_etats;i++){
		printf("Etats : %d -> %d\n",automate.Etats[i].id,automate.Etats[i].accepteur);
	}
	return 0;
}

