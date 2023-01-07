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
	init_transition(&transition);
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

void print_resultat(int valeur)
{
	if(valeur == TRUE){
		printf("\n");
		printf("OK\n");
		printf("\n");
	}
	else{
		printf("\n");
		printf("KO\n");
		printf("\n");
	}
	
	return;
}

void print_automate2(Automate automate)
{
	int i,j;
	
	printf("%d\n",automate.nb_states);
	for(i=0;i<automate.nb_states;i++){
		if(automate.States[i].acceptor == TRUE){
			printf("%d ",automate.States[i].id);
		}
	}
	printf("\n");
	
	printf("  ");
	for(i=0;i<automate.nb_alphabet;i++){
		printf("%c ",automate.alphabet[i]);
	}
	printf("\n");
	
	for(i=0;i<automate.nb_transition;i=i+automate.nb_alphabet){
		
		printf("%d ",automate.Transitions[i].initial->id);
		for(j=0;j<automate.nb_alphabet;j++){
			
			printf("%d ",automate.Transitions[i+j].end->id);
		}
		printf("\n");
	}
	printf("\n");
	
	return;
}


void print_alphabet(Automate automate)
{
	printf("---------- Alphabet de l'automate ----------------\n");
	int i = 0;
	
	for(i=0;i<automate.nb_alphabet;i++){
		
		printf(" %c\n",automate.alphabet[i]);
	}
	return 0;
}

int id_end_state(char character_test, Automate automate, State state_test){
	int i = 0;
	int end_state = -1;
	for(i=0;i<automate.nb_transition;i++){
		if(automate.Transitions[i].initial->id == state_test.id){
			if(automate.Transitions[i].read_character == character_test){
				end_state = automate.Transitions[i].end->id;
			}
		}
	}
	return end_state;
}


void print_alphabet(Automate automate)
{
	printf("---------- Alphabet de l'automate ----------------\n");
	int i = 0;
	
	for(i=0;i<automate.nb_alphabet;i++)
	{
		printf(" %c\n",automate.alphabet[i]);
	}
	printf("---------------------------------------------------\n");
}


Automate automate_determinisation(Automate automate_source){
 
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	Automate automate_determined;
	State new_state;
	State null_state;
	/*Ensemble d'état de départ d'une transition*/
	Set_State start_set;
	/*Ensemble d'état de fin d'une transition*/
	Set_State end_set;
	/*Pile des états découvert mais pas encore traité*/
	Set_State* discovered;
	int nb_discovered = 0;
	/*Tableau des états d'arrivé pour un caractére donné et un etats de départ*/
	Set_State* processed;
	int nb_processed= 0;
	/*Tableau des nouveau ensemble états qui on été traité*/
	Set_State* translate;
	int nb_translate = 0;
	
	discovered = (Set_State*)malloc(sizeof(Set_State)*1);
	processed = (Set_State*)malloc(sizeof(Set_State)*1);
	translate = (Set_State*)malloc(sizeof(Set_State)*1);
	
	null_state.id = -1;
	null_state.acceptor = FALSE;
	
	init_automate(&automate_determined);
	automate_determined.nb_alphabet = automate_source.nb_alphabet;
	automate_determined.alphabet = automate_source.alphabet;
	
	init_set(&start_set);
	automate_determined.nb_states = 0;
	add_state_set(&start_set,automate_source.States[0]);
	add_set_list(&discovered,start_set,&nb_discovered);
	
	/*Tant que on découvre des nouveau ensemble d'état on continue*/
	while( nb_discovered > 0){

		for(i=0;i<automate_source.nb_alphabet;i++){
			end_set = find_end(automate_source.alphabet[i],automate_source,start_set);
			
			if( is_in_set_list(translate,end_set,nb_translate) == TRUE ){
				add_set_list(&processed,end_set,&nb_processed);
			}else if(is_in_set_list(translate,end_set,nb_translate) == FALSE ){
				if( is_in_set_list(discovered,end_set,nb_discovered) == FALSE ){
					add_set_list(&discovered,end_set,&nb_discovered);
				}
				add_set_list(&processed,end_set,&nb_processed);
			}
		}
		/*On a fini de traité l'état*/
		if(is_in_set_list(translate,start_set,nb_translate)== FALSE){
			add_set_list(&translate,start_set,&nb_translate);
		}
		/*On prend un nouvelle état*/
		do{
			start_set = pop_set_list(&discovered,&nb_discovered);
		}while(is_in_set_list(translate,start_set,nb_translate));
	}
	/*On construit les états de base de l'automate deterministe avec l'indice des ensemble d'états testé*/
	for(j=0;j<nb_translate;j++){
		State* p_new_state = (State*)malloc(sizeof(State));
		p_new_state->id = index_in_set_list(translate,translate[j],nb_translate);
		p_new_state->acceptor = FALSE;
		add_state(p_new_state,&automate_determined);
	}
	/*On construit les états accepteurs*/
	for(i=0;i<nb_translate;i++){
		for(j=0;j<translate[i].size;j++){
			if(is_acceptor(translate[i].list[j],automate_source)){
				automate_determined.States[i].acceptor=TRUE;
			}
		}
	}
	/*On construit les Transitions*/
	k = 0 ;
	for(i=0;i<nb_translate;i++){
		for(j=0;j<automate_determined.nb_alphabet;j++){
			l = index_in_set_list(translate,processed[k],nb_translate);
			add_transition(&automate_determined.States[i],automate_determined.alphabet[j],&automate_determined.States[l],&automate_determined);
			k += 1;
		}
	}
	return automate_determined;
}

Automate minimisation_automate_recursive(Automate automate_source){
	Automate automate_minimal;
	int first_state;
	int index;
	init_automate(&automate_minimal);
	automate_minimal = minimisation_automate(automate_source,&first_state);
	if(automate_minimal.nb_states == automate_source.nb_states){
		State tmp;
		index = first_state;
		tmp = automate_minimal.States[0];
		automate_minimal.States[0] = automate_minimal.States[index];
		automate_minimal.States[index] = tmp;
		return automate_minimal;
	}else{
		return minimisation_automate_recursive(automate_minimal);
	}
}


Automate minimisation_automate(Automate automate_source,int* first_state){
	int i=0;
	int j=0;
	int k=0;
	int ii = 0;
	int jj = 0;
	int kk = 0;
	
	/*compte les nouveaux états*/
	int group_index = 0;
	int same_state = FALSE;
	int different_state = FALSE;
	Automate automate_minimal;
	State new_state;
	/*Contient l'ID des nouveaus états minimisée, leur position est leur ancien ID*/
	Set_State minimal_set;
	
	init_automate(&automate_minimal);
	init_set(&minimal_set);
	automate_minimal.nb_alphabet = automate_source.nb_alphabet; 
	automate_minimal.alphabet = automate_source.alphabet;

	/*Séparation des états accepteur et non accepteur*/
	for(i=0;i<automate_source.nb_states;i++){
		if(automate_source.States[i].acceptor == TRUE){
			State new_state;
			new_state.id = 0;
			new_state.acceptor = TRUE;
			add_state_set(&minimal_set,new_state);
		}else{
			State new_state;
			new_state.id = 1;
			new_state.acceptor = FALSE;
			add_state_set(&minimal_set,new_state);
		}
	}
	group_index += 1;
	
	/*On parcours les états de base 2 à 2*/
	for(i=0;i<automate_source.nb_states;i++){
		for(j=i+1;j<automate_source.nb_states;j++){
			/*Si il ne sont pas different dans le nouveau set minimal*/
			if(minimal_set.list[i].id == minimal_set.list[j].id){
				different_state = FALSE;
				for(k=0;k<automate_source.nb_alphabet;k++){
					/*On vérifie que les états d'arrivé sont bien identique*/
					if(id_end_state(automate_source.alphabet[k],automate_source,automate_source.States[i]) == id_end_state(automate_source.alphabet[k],automate_source,automate_source.States[j])){
						
					}else{
						different_state = TRUE;
					}
				}
				if(different_state == TRUE){
					/*On différencie les nouveau états minimal*/
					group_index += 1;
					minimal_set.list[i].id = group_index;
					/*On cherche les etats avec les meme etats d'arrivé que celui qu'on vient de changer*/
					/*Comme ça les groupes sont conservée*/
					for(ii=i;ii<automate_source.nb_states;ii++){
						same_state = TRUE;
						for(kk=0;kk<automate_source.nb_alphabet;kk++){
							if(id_end_state(automate_source.alphabet[kk],automate_source,automate_source.States[i]) == id_end_state(automate_source.alphabet[kk],automate_source,automate_source.States[ii])){					
								
							}else{
								same_state = FALSE;
							}
						}
						if(same_state == TRUE){
							minimal_set.list[ii].id = minimal_set.list[i].id;
						}					
					}
				}
			}else{
				same_state = TRUE;
				for(kk=0;kk<automate_source.nb_alphabet;kk++){
					if(id_end_state(automate_source.alphabet[kk],automate_source,automate_source.States[i]) == id_end_state(automate_source.alphabet[kk],automate_source,automate_source.States[j])){							
						
					}else{
						same_state = FALSE;
					}
				}
				if(same_state == TRUE){
					minimal_set.list[j].id = minimal_set.list[i].id;
				}						
			}
		}
	}
	
	/*On construit les états de base de l'automate deterministe avec l'indice des ensemble d'états testé*/
	for(i=0;i<=group_index;i++){
		State* p_new_state = (State*)malloc(sizeof(State));
		p_new_state->id = i;
		p_new_state->acceptor = FALSE;
		add_state(p_new_state,&automate_minimal);
	}

	/*On construit les états accepteurs*/
	for(i=0;i<=group_index;i++){
		j = index_in_set(minimal_set,automate_minimal.States[i]);
		automate_minimal.States[i].acceptor = automate_source.States[j].acceptor;
	}
	
	/*On construit les Transitions*/
	k = 0 ;
	kk = 0;
	for(i=0;i<automate_minimal.nb_states;i++){
		k = index_in_set(minimal_set,automate_minimal.States[i]);
		for(j=0;j<automate_minimal.nb_alphabet;j++){
			kk = id_end_state(automate_minimal.alphabet[j],automate_source,automate_source.States[k]);
			add_transition(&automate_minimal.States[i],automate_minimal.alphabet[j],&automate_minimal.States[minimal_set.list[kk].id],&automate_minimal);
		}
	}
	
	*first_state = minimal_set.list[0].id;
	
	printf("\nminimal_set:\n");
	for(i=0;i<minimal_set.size;i++){
		printf("ancien:%d minimal:%d\n",i,minimal_set.list[i].id);
	}
	printf("\n");

	return automate_minimal;
}
