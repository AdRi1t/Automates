#include "automate.h"

void init_set(Set_State* set){
	set->size = 0;
	set->list = (State*)malloc(sizeof(State)*1);
}

void init_transition(Transition* transition){
	transition->initial = NULL;
	transition->read_character = "";
	transition->end = NULL;
}

void add_state_set(Set_State* set,State state){
	set->list = realloc(set->list,(set->size+1)*sizeof(State));
	set->list[set->size] = state;
	set->size += 1;
}

void add_set_list(Set_State** set_list,Set_State set,int* len){
	*set_list = (Set_State*)realloc(*set_list,(*len+1)*sizeof(Set_State));
	(*set_list)[*len] = set;
	*len += 1;
}

Set_State pop_set_list(Set_State** set_list,int* len){
	Set_State set;
	init_set(&set);
	if(*len > 0) {
		*len += -1;
		set = (*set_list)[*len];
		*set_list = (Set_State*)realloc(*set_list,sizeof(Set_State)*(*len+1));
	}
	return set;
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

int is_acceptor(State state,Automate AF)
{
	int is_acceptor = FALSE;
	int i=0;
	for(i=0;i<AF.nb_states;i++)
	{
		if((AF.States[i].id == state.id)&&(AF.States[i].acceptor == TRUE ))
		{
			return TRUE;
		}
	}
	return is_acceptor;
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

int index_in_set_list(Set_State* set_list, Set_State test_set,int len){
	int index = -1;
	int i=0;
	int j=0;
	for(i=0;i<len;i++){
		if(set_list[i].size == test_set.size){
			for(j=0;j<test_set.size;j++){
				if(is_in_set(set_list[i],test_set.list[j]) == FALSE){
					break;
				}
				if( j+1 == test_set.size){
					index = i;
				}
			}
		}
	}
	return index;
}

/*
int is_unique()
{
	int i,j;
	int count; // Compte les ocurrences
	
	for(i=0;i<sizeofliste1;i++)
	{
		for(j=0;i<sizeofliste2;j++)
		{
			if(elementliste1 = elementliste2)
			{
				count += 1;
				if(count == sizeofliste1)
				{
					return false;
				}
			}
			else
			{
			}
		}
	}
}*/
