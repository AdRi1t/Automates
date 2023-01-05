#include "automate.h"

void init_automate(Automate* automate){
	automate->nb_states = 0;
	automate->nb_alphabet = 0;
	automate->nb_transition = 0;
	automate->States = (State*)malloc(sizeof(State)*1);
	automate->alphabet = (char*)calloc(1,sizeof(char));
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
	for(i=0;i<automate.nb_alphabet;i++){
		printf("%c ",automate.alphabet[i]);
	}
	printf("\n");
	for(i=0;i<automate.nb_transition;i++){
		printf("%d %c %d\n",automate.Transitions[i].initial->id,automate.Transitions[i].read_character,automate.Transitions[i].end->id);
	}
}

void add_state(State* state,Automate* automate){
	automate->States = (State*)realloc(automate->States,(automate->nb_states+1) * sizeof(State));
	automate->States[automate->nb_states] = *state;
	automate->nb_states += 1;
}

void add_transition(State* start_state,char read_character,State* end_state,Automate* automate){
	Transition transition;
	transition.initial = start_state;
	transition.read_character = read_character;
	transition.end = end_state;
	automate->Transitions = (Transition*)realloc(automate->Transitions,(automate->nb_transition+1) * sizeof(Transition));
	automate->Transitions[automate->nb_transition] = transition;
	automate->nb_transition += 1;	
}

void add_character(char letter,Automate* automate){
	automate->alphabet = (char*)realloc(automate->alphabet,(automate->nb_alphabet+1)*sizeof(char));
	automate->alphabet[automate->nb_alphabet] = letter;
	automate->nb_alphabet += 1;
}

int word_execution2(Automate automate,const char* word,State state,int len){
	int i=0;
	int j=0;
	int result = 0;
	int loop_without_transition = TRUE;
	if(strlen(word) == 0 ){
		if(state.acceptor == TRUE){
			printf("(%d, ) |- ",state.id);
			printf("OK\n");
			return TRUE;
		}else{
			printf("(%d, %s) |- ",state.id,word);
			printf("KO\n");
			for(j=0;j<len;j++){
				printf(" ");
			}
			return FALSE;
		}
	}
	for(i=0;i<automate.nb_transition;i++){
		if(automate.Transitions[i].initial->id == state.id){
			if(automate.Transitions[i].read_character == *word){
				printf("(%d,%s) |- ",automate.Transitions[i].initial->id,word);
				loop_without_transition = FALSE;
				len += (8 + strlen(word));
				result = word_execution2(automate,word+1,*(automate.Transitions[i].end),len);
				if(result == TRUE){
					return TRUE;
				}
			}
		}
	}
	if(loop_without_transition == TRUE){
		printf("(%d,%s) |- KO \n",state.id,word);
		for(j=0;j<len;j++){
			printf(" ");
		}
	}
	return FALSE;
}

int word_execution(Automate automate, const char* word){
	int i=0;
	State current_state = automate.States[0];
	int loop_without_transition;
	char* cursor = NULL;
	int success = TRUE;
	cursor = (char*)calloc(sizeof(word),sizeof(char));
	strcpy(cursor,word);
	
	while(*cursor != '\0'){
		loop_without_transition += 1;
		for(i=0;i<automate.nb_transition;i++){
			if(automate.Transitions[i].initial->id == current_state.id){
				if(automate.Transitions[i].read_character == *cursor){
					current_state = *(automate.Transitions[i].end);
					printf("(%d,%s) |- ",automate.Transitions[i].initial->id,cursor);
					loop_without_transition = 0;
					if(current_state.acceptor == FALSE){
						success = FALSE;
					}else{
						success = TRUE;
					}
				}
			}
		}
		if(loop_without_transition == 0){
			cursor++;
		}
		if(loop_without_transition == 1){
			success = FALSE;
			break;
		}
	}
	if(success == TRUE){
		printf("(%d, ) |- ",current_state.id);
		printf("ok\n");
		return TRUE;
	}else{
		printf("(%d, %s) |- ",current_state.id,cursor);
		printf("ko\n");
		return FALSE;
	}
	return 0;
}

Set_State find_end(char character_test, Automate automate, Set_State states_test){
	int i = 0;
	int j = 0;
	Set_State end_states;
	init_set(&end_states);
	for(i=0;i<states_test.size;i++){
		for(j=0;j<automate.nb_transition;j++){
			if(states_test.list[i].id == automate.Transitions[j].initial->id
			&& character_test == automate.Transitions[j].read_character){
				if(is_in_set(end_states,*(automate.Transitions[j].end)) == FALSE){
					add_state_set(&end_states,*(automate.Transitions[j].end));
				}
			}
		}
	}
	return end_states;
}
