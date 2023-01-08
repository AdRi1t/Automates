/**
 * @file main.c
 * @author Adrien Taberner & Othmane Abdimi
 * @date 2023-01-09
 * 
 * Fichier principal, on exécute dans l'ordre:
 *   - Lecture de l'automate
 *   - Lecture d'un mot par l'automate
 *   - Determinisation puis exécution sur le mot
 *   - Minimisation puis exécution sur le mot
 * 
 **/


#include "automate.h"
#include "set.h"

int main(int argc,char** argv){
	Automate automate;
	Automate automate_determined;
	Automate automate_minimal;
	
	init_automate(&automate);
	init_automate(&automate_determined);
	init_automate(&automate_minimal);
	
	int i = 2;
	int j = 0;
	
	char** a_mots = NULL;
	short nb_mots = 0;
	
	if(getopt(argc,argv,"h") == 'h' ){
		printf("Commande: DetMin [nom du fichier] [mot à tester]\n");
		return 0;
	}
	
	if(argc == 1){
		printf("Veuillez specifier le fichier de l'automate et un mot\n");
		exit(EXIT_FAILURE);
	}
	else if(argc == 2)	{
		printf("Aucun mot !\n");
		printf("Fichier de l'automate %s \n",argv[1]);
		exit(EXIT_FAILURE);
	}
	else{
		printf("Fichier de l'automate %s \n",argv[1]);
		a_mots = (char**)malloc((argc-2)*sizeof(char*));
		while(argc != i){
			a_mots[nb_mots] = (char*)malloc(sizeof(argv[i])*sizeof(char));
			strcpy(a_mots[nb_mots],argv[i]);
			nb_mots++;
			i++;
		}
	}
	
	automate = read_file(argv[1]);
	automate_determined = automate_determinisation(automate);
	automate_minimal = minimisation_automate_recursive(automate_determined);
	for(j=0;j<3;j++)
	{
		for(i=0;i<nb_mots;i++){
			
			if(j==0)
			{
				if(i==0)
				{
					print_automate(automate);
				}
				
				print_resultat(word_execution2(automate,a_mots[i],automate.States[0],0));
			}
			else if(j==1)
			{
				if(i==0)
				{
					print_automate2(automate_determined);
				}
				print_resultat(word_execution2(automate_determined,a_mots[i],automate.States[0],0));
			}
			else
			{
				if(i==0)
				{
					print_automate2(automate_minimal);
				}
				print_resultat(word_execution2(automate_minimal,a_mots[i],automate.States[0],0));
			}
			
		}
	}
	
	return 0;
}
