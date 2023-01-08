/**
 * @file loadAutomate.c
 * @author Adrien Taberner & Othmane Abdimi
 * @date 2023-01-09
 * 
 * Fonction pour construire l'automate depuis un fichier
 * 
 */

#include "automate.h"
#include "set.h"

/* Renvoie l'automate contenu dans le fichier dont le nom est passé en paramètre*/
Automate read_file(char* file_tmp){
	char* file_name = NULL;
	char* line = NULL;
	FILE* automate_file = NULL;
	int* id_acceptor = NULL;
	int nb_states;
	Automate automate;
	
	init_automate(&automate);
	line = (char*)calloc(256,sizeof(char));
	file_name = (char*)calloc(FILENAME_MAX,sizeof(char));
	strcpy(file_name,"Automates/");
	strcat(file_name,file_tmp);
	automate_file = fopen(file_name,"r");
	if(automate_file != NULL){
		rewind(automate_file);
		fgets(line,256,automate_file);
		sscanf(line,"%d",&nb_states);
		automate.nb_states = nb_states;
		fgets(line,256,automate_file);
		id_acceptor = numbers_from_string(line,nb_states);
		init_states(nb_states,id_acceptor,&automate);
		while( feof(automate_file) == 0 ){
			fgets(line,256,automate_file);
			if(strlen(line) > 1){
				set_transition(line,&automate);
			}
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

/* Prends un string qui contient un ensemble de nombres prend en paramètre le nombre de nombre à lire */
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

/* Prends une chaine de caractère et la transforme en transition pour ensuite l'ajouter à automate*/
void set_transition(char* str,Automate* automate){
	char* ptr_str = str;
	int count = 0;
	long id_etat = 0;
	Transition transition;
	while(count != 3){
		if (isalpha(*ptr_str) && count == 1){
			set_character(*ptr_str,automate);
			transition.read_character = *ptr_str;
			count += 1;
		}
		if(isdigit(*ptr_str) && count == 0){
			id_etat = strtol(ptr_str, &ptr_str, 10);
			transition.initial = &(automate->States[id_etat]);
			count += 1;
		}
		if(isdigit(*ptr_str) && count == 2){
			id_etat = strtol(ptr_str, &ptr_str, 10);
			transition.end = &(automate->States[id_etat]);
			count += 1;
		}
		ptr_str += 1;
	}
	automate->Transitions = (Transition*)realloc(automate->Transitions,(automate->nb_transition+1) * sizeof(Transition));
	automate->Transitions[automate->nb_transition] = transition;
	automate->nb_transition += 1;
}

void set_character(char letter,Automate* automate){
	int i = 0;
	for(i=0;i<automate->nb_alphabet;i++){
		 if(automate->alphabet[i] == letter){
			return;
		}
	}
	add_character(letter,automate);
}

/* Initialise les états. On lui donne la liste des ID accepteurs */
void init_states(int nb_etats, int* id_etats_accepteur,Automate* automate){
	State* States = NULL;
	States = (State*)malloc(nb_etats*sizeof(State));
	int count = 0;
	int i = 0;
	for(i=0;i<nb_etats;i++){
		if(i == id_etats_accepteur[count]){
			States[i].id = i;
			States[i].acceptor = TRUE;
			count += 1 ;
		}else{
			States[i].id = i;
			States[i].acceptor = FALSE;
		}
	}
	automate->States = States;
}


int cmpt_line_file(FILE* file){
	char c = '0';
	int lines = 0;
	rewind(file);
	while (c!=EOF){
		c=fgetc(file);
		if (c=='\n'){	
			lines+=1;
		}
	}
	return lines;
}
