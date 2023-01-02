#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define ALPHABET {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'}
#define LEN_ALPHABET 26

/*structure pour un état*/
typedef struct{
	int id;
	char acceptor;
}State;

/*les transitions ne stockent pas les états seulement un pointeur vers eux*/
typedef struct{
	State* initial;
	char read_character;
	State* end;
}Transition;

/*un automate est représenté par une liste d'état et une liste de transition*/
typedef struct{
	int nb_states;
	int nb_transition;
	State* States;
	Transition* Transitions;
}Automate;

typedef struct{
	size_t size;
	State* list;
}Set_State;

/***automate.c***/

/*Permet de faire une exécution sur un mot*/
int word_execution(Automate automate,const char* word);

/*Fait la déterminisation d'un automate*/
Automate automate_determination(Automate automate_source);

/*Ajoute un état a l'automate*/
void add_State(State state,Automate* automate);

/*Renvoie les états atteint quand on part d'une liste d'états pour lire un caractère*/
Set_State find_end(char character_test, Automate automate, Set_State states_test);

int is_in_set(Set_State set, State test_state);

/***loadAutomate.c***/

/*Renvoie un automate initialiser à partir d'un fichier*/
Automate read_file(char* file_name);

/*initialise la liste des états à partir du nombre d'états et de la liste des états accepteur*/
void init_states(int nb_states, int* acceptor_states,Automate* automate);

/*lit une transition et l'ajoute à l'automate*/
void add_transition(char* line, Automate* automate);	

/*initialise l'automate*/
void init_automate(Automate* automate);

/*lit une transition et l'ajoute à l'automate*/
void print_automate(Automate automate);	

/*lit un ensemble de nombres depuis une chaine caractère*/
int* numbers_from_string(char* line, int nb_of_int);	

#endif
