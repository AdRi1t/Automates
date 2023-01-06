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
	printf("%d %c %d\n",start_state->id,read_character,end_state->id);
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

Automate determinisation_automate(Automate AFN)
{
	// Création et initialisation d'un automate
	Automate AFD;
	init_automate(&AFD);
	AFD.nb_alphabet = AFN.nb_alphabet;
	AFD.alphabet = AFN.alphabet;
	add_state(&AFN.States[0],&AFD);
	
	printf("Etat initiale : %d\n",AFD.States[0].id);
	
	Set_State* tab_transition = (Set_State*)malloc(sizeof(Set_State)*100); // Va nous servir à stocker toutes les transitions
	
	State new_state;
	new_state.id = 0;
	new_state.acceptor = FALSE;
	
	int i=0;
	int j=0;
	int k=0; 
	
	//Parcourt l'ensembles des états de AFN
	for(i=0;i<AFN.nb_states;i++)
	{
		init_set(&tab_transition[i]);
		// Parcourt l'ensemble des caractère de l'alphabet
		for(j=0;j<AFD.nb_alphabet;j++)
		{
			// Parcourt l'ensemble des transition de AFN
			for(k=0;k<AFN.nb_transition;k++)
			{	
				if((AFN.Transitions[k].initial->id == AFN.States[i].id)
				&&(AFD.alphabet[j] == AFN.Transitions[k].read_character))
				{
					// Si on trouve une transition
					add_state_set(&tab_transition[i],*(AFN.Transitions[k].end));
					
					printf("---------------------------------------\n");
					printf("Transition trouvé !!! : Ajoute d'un élément dans la liste [%d][%c]\n",i,AFD.alphabet[j]);
					printf("Valeur ajouté à la liste [%d][%c] : %d\n",i,AFD.alphabet[j],AFN.Transitions[k].end->id);
					printf("---------------------------------------\n");
					
					//On vérifie que le nouvel est un état accepeteur
					// Si l'élément ajouté est dans la liste des éltats accepteur
					if(is_acceptor(*(AFN.Transitions[k].end),AFN) == TRUE)
					{
						new_state.acceptor = TRUE;
						printf(" %d est accepteur !!!\n",AFN.Transitions[k].end->id);
					}
					else
					{
						new_state.acceptor = FALSE;
					}
				}
				else
				{		
				}
				
			}
			// Lorsque l'on a fini de faire toutes les transitions
			// On créer un lien entre l'état actuelle AFN et le nouvelle état obtenue pour AFD
			new_state.id = AFD.nb_states + 1;
			add_state(&new_state,&AFD);
			State start_state;
			start_state.id = AFN.Transitions[k].initial->id;
			start_state.acceptor = AFN.Transitions[k].initial->acceptor;
			add_transition(&start_state,AFD.alphabet[j],&new_state,&AFD);
		}
		
	}
	
	printf("Fin du Programme\n");
	return AFD;
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
	
	new_state.id = 0;
	new_state.acceptor = TRUE;
	null_state.id = -1;
	
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
			
			if( is_in_set_list(translate,end_set,nb_translate)== TRUE && end_set.size > 0){
				printf("A\n");
				add_set_list(&processed,end_set,&nb_processed);
			}else if(is_in_set_list(translate,end_set,nb_translate)== FALSE && end_set.size > 0){
				printf("B\n");
				add_set_list(&discovered,end_set,&nb_discovered);
				add_set_list(&processed,end_set,&nb_processed);
			}else{
				printf("C\n");
				State state;
				state.id = -1;
				add_state_set(&end_set,state);
				add_set_list(&processed,end_set,&nb_processed);
			}
		}
		printf("\n fin Boucle\n");
		/*On prend un nouvelle état*/
		start_set = pop_set_list(&discovered,&nb_discovered);
		/*On a fini de traité état*/
		add_set_list(&translate,start_set,&nb_translate);
	}
	/*On construit les états de base de l'automate deterministe avec l'indice des ensemble d'états testé*/
	for(j=0;j<nb_translate;j++){
		State new_state;
		new_state.id = index_in_set_list(translate,translate[j],nb_translate);
		new_state.acceptor = FALSE;
		add_state(&new_state,&automate_determined);
	}
	/*On construit les états accepteurs*/
	for(i=0;i<nb_translate;i++){
		for(j=0;j<translate[i].size;j++){
			if(is_acceptor(translate[i].list[j],automate_source)){
				automate_determined.States[i].acceptor=TRUE;
			}
		}
	}
	/*On construit les Transition*/
	k = 0 ;
	for(i=0;i<nb_translate;i++){
		for(j=0;j<automate_determined.nb_alphabet;j++){
			if( is_in_set(processed[k],null_state) == FALSE){
				l = index_in_set_list(translate,processed[k],nb_translate);
				add_transition(&automate_determined.States[i],automate_determined.alphabet[j],&automate_determined.States[l],&automate_determined);
			}
			k += 1;
		}
	}
	
	/*
	printf("k:%d\n",k);
	for(j=0;j<nb_processed;j++){
		printf("processed set: %d ",j);
		for(k=0;k<processed[j].size;k++){
			printf(" etat:%d",processed[j].list[k].id);
		}
		printf("\n");
	}
	for(j=0;j<nb_translate;j++){
		printf("translate set: %d ",j);
		for(k=0;k<translate[j].size;k++){
			printf(" etat:%d",translate[j].list[k].id);
		}
		printf("\n");
	}
	*/
	return automate_determined;

}
