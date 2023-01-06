#include "automate.h"


int main(int argc,char** argv){
	Automate automate;
	Automate automate_determined;
	Automate automate_minimal;
	init_automate(&automate);
	init_automate(&automate_determined);
	init_automate(&automate_minimal);
	
	
	int i = 2;
	char** mots = NULL;
	short nb_mots = 0;
	
	if(getopt(argc,argv,"h") == 'h' ){
		printf("Commande: DetMin [nom du fichier] [mot à tester]\n");
		return 0;
	}
	if(argc == 1){
		printf("Veuillez specifier le fichier de l'automate et un mot\n");
		exit(EXIT_FAILURE);
	}else if(argc == 2)	{
		printf("Aucun mot !\n");
		printf("Fichier de l'automate %s \n",argv[1]);
		exit(EXIT_FAILURE);
	}else{
		printf("Fichier de l'automate %s \n",argv[1]);
		mots = (char**)malloc((argc-2)*sizeof(char*));
		while(argc != i){
			mots[nb_mots] = (char*)malloc(sizeof(argv[i])*sizeof(char));
			strcpy(mots[nb_mots],argv[i]);
			nb_mots++;
			i++;
		}
	}
	automate = read_file(argv[1]);
	print_automate(automate);

	automate_determined = automate_determinisation(automate);
	print_automate(automate_determined);
	word_execution2(automate,mots[0],automate.States[0],0);
	printf("\n");
	word_execution2(automate_determined,mots[0],automate.States[0],0);
	automate_minimal = minimisation_automate(automate_determined);

	return 0;
}

