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
	Etat* Etats = NULL;
	
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
		Etats = init_etats(nb_etat,id_accepteurs);
		automate.Etats = Etats;
		while( feof(automate_file) == 0 ){
			fgets(line,256,automate_file);
			printf(line);
		}
	}else{
		perror(file_name);
		exit(EXIT_FAILURE);
	}
	free(file_name);
	free(line);
	return automate;
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

Etat* init_etats(int nb_etats, int* id_etats_accepteur){
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
	return Etats;
}
