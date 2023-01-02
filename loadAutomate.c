#include "automate.h"


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

void init_automate(Automate* automate){
	automate->nb_states = 0;
	automate->nb_transition = 0;
	automate->States = (State*)malloc(sizeof(State)*1);
	automate->Transitions = (Transition*)malloc(sizeof(Transition)*1);
}

void print_automate(Automate automate){
	int i=0;
	printf("%d\n",automate.nb_states);
	for(i=0;i<automate.nb_states;i++){
		if(automate.States[i].acceptor == TRUE){
			printf("%d ",automate.States[i].id);
		}
	}
	printf("\n");
	for(i=0;i<automate.nb_transition;i++){
		printf("%d %c %d\n",automate.Transitions[i].initial->id,automate.Transitions[i].read_character,automate.Transitions[i].end->id);
	}
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
