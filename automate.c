#include "automate.h"

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
