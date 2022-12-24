#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "automate.h"


Automate read_file(char* file_tmp){
	char* file_name = NULL;
	char* line = NULL;
	FILE* automate_file = NULL;
	int* id_accepteurs = NULL;
	int nb_etat;
	Automate automate;
	
	line = (char*)calloc(256,sizeof(char));
	file_name = (char*)calloc(FILENAME_MAX,sizeof(char));
	strcpy(file_name,"Automates/");
	strcat(file_name,file_tmp);
	automate_file = fopen(file_name,"r");
	if(automate_file != NULL){
		rewind(automate_file);
		fgets(line,256,automate_file);
		sscanf(line,"%d",&nb_etat);
		automate.nb_etats = nb_etat;
		fgets(line,256,automate_file);
		id_accepteurs = numbers_from_string(line,nb_etat);
		init_etats(nb_etat,id_accepteurs,&automate);
		automate.nb_transition = 0;
		automate.Transitions = (Transition*)malloc(sizeof(Transition)*0);
		while( feof(automate_file) == 0 ){
			fgets(line,256,automate_file);
			add_transition(line,&automate);
		}
	}else{
		perror(file_name);
		exit(EXIT_FAILURE);
	}
	fclose(automate_file);
	free(file_name);
	free(line);
	return automate;
}

int* numbers_from_string(char* str_read, int nb_numbers) {
	char* ptr_str = str_read;
	int* numbers = malloc(nb_numbers*sizeof(int));
	int count = 0;

	while (*ptr_str != '\0') {
		if(count > nb_numbers){
			break;
		}
		if (isdigit(*ptr_str)) {
			numbers[count] = strtol(ptr_str, &ptr_str, 10);
			count += 1;
		} else {
			ptr_str += 1;
		}
		ptr_str += 1;
	}
  return numbers;
}

void add_transition(char* str,Automate* automate){
	char* ptr_str = str;
	int count = 0;
	long id_etat = 0;
	Transition transition;
	while(count != 3){
		if (isalpha(*ptr_str) && count == 1){
			transition.caractere_lu = *ptr_str;
			count += 1;
		}
		if(isdigit(*ptr_str) && count == 0){
			id_etat = strtol(ptr_str, &ptr_str, 10);
			transition.initiale = &(automate->Etats[id_etat]);
			count += 1;
		}
		if(isdigit(*ptr_str) && count == 2){
			id_etat = strtol(ptr_str, &ptr_str, 10);
			transition.fin = &(automate->Etats[id_etat]);
			count += 1;
		}
		ptr_str += 1;
	}
	automate->nb_transition += 1;
	automate->Transitions = (Transition*)realloc(automate->Transitions,(automate->nb_transition+1) * sizeof(Transition));
	automate->Transitions[automate->nb_transition] = transition;
}

void init_etats(int nb_etats, int* id_etats_accepteur,Automate* automate){
	Etat* Etats = NULL;
	Etats = (Etat*)malloc(nb_etats*sizeof(Etat));
	int count = 0;
	int i = 0;
	for(i=0;i<nb_etats;i++){
		if(i == id_etats_accepteur[count]){
			Etats[i].id = i;
			Etats[i].accepteur = 1;
			count += 1 ;
		}else{
			Etats[i].id = i;
			Etats[i].accepteur = 0;
		}
	}
	automate->Etats = Etats;
}

void print_automate(Automate automate){
	int i=0;
	printf("%d\n",automate.nb_etats);
	for(i=0;i<automate.nb_etats;i++){
		if(automate.Etats[i].accepteur == 1){
			printf("%d ",automate.Etats[i].id);
		}
	}
	printf("\n");
	for(i=1;i<automate.nb_transition;i++){
		printf("%d %c %d\n",automate.Transitions[i].initiale->id,automate.Transitions[i].caractere_lu,automate.Transitions[i].fin->id);
	}
}

int compte_ligne_fichier(FILE* fichier){
	char c = '0';
	int lines = 0;
	rewind(fichier);
	while (c!=EOF){
		c=fgetc(fichier);
		if (c=='\n'){	
			lines+=1;
		}
	}
	return lines;
}
