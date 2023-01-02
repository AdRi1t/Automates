#include "automate.h"


void add_State(State state,Automate* automate){
	automate->States = (State*)realloc(automate->States,(automate->nb_states+1) * sizeof(State));
	automate->States[automate->nb_states] = state;
	automate->nb_states += 1;
}

int is_in_set(Set_State set, State test_state){
	int is_in = FALSE;
	int i=0;
	for(i=0;i<set.size;i++){
		if(set.list[i].id == test_state.id){
			is_in = TRUE;
		}
	}
	return is_in;
}

int is_in_set_list(Set_State* set_list, Set_State test_set,int len){
	int is_in = FALSE;
	int i=0;
	int j=0;
	for(i=0;i<len;i++){
		if(set_list[i].size == test_set.size){
			for(j=0;j<test_set.size;j++){
				if(is_in_set(set_list[i],test_set.list[j]) == FALSE){
					break;
				}
				if( j+1 == test_set.size){
					is_in = TRUE;
				}
			}
		}
	}
	return is_in;
}


Set_State find_end(char character_test, Automate automate, Set_State states_test){
	int i = 0;
	int j = 0;
	Set_State end_states;
	end_states.size = 0;
	for(i=0;i<states_test.size;i++){
		for(j=0;j<automate.nb_transition;j++){
			if(states_test.list[i].id == automate.Transitions[j].initial->id
			&& character_test == automate.Transitions[j].read_character){
				if(is_in_set(end_states,states_test.list[i]) == FALSE){
					end_states.list = realloc(end_states.list,(end_states.size+1)*sizeof(State));
					end_states.list[end_states.size] = *(automate.Transitions[j].end);
					end_states.size += 1;
				}
			}
		}
	}
	return end_states;
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

Automate automate_determination(Automate automate_source){
	Automate automate_determined;
	int i = 0;
	int j = 0;
	int end = FALSE;
	
	init_automate(&automate_determined);
	automate_determined.nb_states = 0;
	add_State(automate_source.States[0],&automate_determined);
	
	/*
	while( end == FALSE){
		for(j=0;j<LEN_ALPHABET;j++){
		}
	}*/
	State s1,s2,s3;
	Set_State state_set;
	Set_State set_list[3];
	s1.id = 0;
	s2.id = 2;
	State states1[] = {s1,s2};
	state_set.list = states1;
	state_set.size = 2;
	set_list[0]=state_set; 
	
	s1.id = 1;
	s2.id = 4;
	State states2[] = {s1,s2};
	state_set.list = states2;
	state_set.size = 2;
	set_list[1]=state_set; 
	
	s1.id = 1;
	s2.id = 2;
	s3.id = 3;
	State states3[] = {s1,s2,s3};
	state_set.list = states3;
	state_set.size = 3;
	set_list[2]=state_set; 
	
	/*printf("%d ",is_in_set_list*/ //TO-DO
	
	Set_State S_end;
	
	S_end = find_end('b',automate_source,state_set);
	printf("end size : %ld\n",S_end.size);
	printf("end : %d\n",S_end.list[0].id);
	printf("end : %d\n",S_end.list[1].id);
	

	return automate_determined;
}


