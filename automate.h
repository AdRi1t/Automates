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
	int nb_alphabet;
	State* States;
	Transition* Transitions;
	char* alphabet;
}Automate;

/*Permets d'avoir une liste d'etats avec sa taille*/
typedef struct{
	int size;
	State* list;
}Set_State;

/***automate.c***/

/*Initialise l'automate*/
void init_automate(Automate* automate);

/* Initialise Transition */
void init_transition(Transition* transition);

/* Affiche les données d'automate*/
void print_automate(Automate automate);

/* Affiche les donnés d'un automate v2 */
void print_automate2(Automate automate);

/* Affiche l'alphabet d'un automate en entrée */
void print_alphabet(Automate automate);

/*Permet de faire une exécution sur un mot*/
int word_execution(Automate automate,const char* word);

/*Permet de faire une exécution sur un mot*/
int word_execution2(Automate automate,const char* word,State state,int len);

/*Permet de renvoyer une valeur en fonction de word_execution2*/
void print_resultat(int valeur);

/*Renvoie les états atteint quand on part d'une liste d'états pour lire un caractère*/
Set_State find_end(char character_test, Automate automate, Set_State states_test);

/*Ajoute un état a l'automate*/
void add_state(State* state,Automate* automate);

/*Ajoute une transition à l'automate*/
void add_transition(State* start_state,char read_character,State* end_state,Automate* automate);

/*Ajoute un caractère à l'alphabet de l'automate*/
void add_character(char letter,Automate* automate);

int id_end_state(char character_test, Automate automate, State state_test);

/***loadAutomate.c***/

/*Renvoie un automate initialiser à partir d'un fichier*/
Automate read_file(char* file_name);

/*Initialise la liste des états à partir du nombre d'états et de la liste des états accepteur*/
void init_states(int nb_states, int* acceptor_states,Automate* automate);

/*Lit une transition et l'ajoute à l'automate*/
void set_transition(char* line, Automate* automate);	

/*Ajoute un character si il n'est pas déja dans l'alphabet*/
void set_character(char letter,Automate* automate);

/*Lit un ensemble de nombres depuis une chaine caractère*/
int* numbers_from_string(char* line, int nb_of_int);	

/*Fonction qui renvoye un automate déterministe*/
Automate automate_determinisation(Automate automate_source);

/*Fonction qui renvoye un automate déterministe minimisé*/
Automate minimisation_automate(Automate automate_source);

/***set.c***/

/*Initialise un set avec un espace de mémoire*/
void init_set(Set_State* set);

/*Ajoute un etat dans un set*/
void add_state_set(Set_State* set,State state);

/* Renvoie vrai si un etat se trouve dans un ensemble d'etats*/
int is_in_set(Set_State set, State test_state);

/* Renvoie vrai si un etat est accepteur */
int is_acceptor(State state,Automate AF);

/*Renvoie vrai si un ensemble d'etats est présent dans une liste d'ensemble d'etats*/
int is_in_set_list(Set_State* set_list, Set_State test_set,int len);

/*Trouve l'index d'un set dans une liste de set*/
int index_in_set_list(Set_State* set_list, Set_State test_set,int len);

/*Ajoute un set dans une liste de Set*/
void add_set_list(Set_State** set_list,Set_State set,int* len);

/*Supprime le dernier indice d'une liste de set*/
Set_State pop_set_list(Set_State** set_list,int* len);

/*Renvoie les états atteint quand on part d'une liste d'états pour lire un caractère*/
Set_State find_end(char character_test, Automate automate, Set_State states_test);
#endif
