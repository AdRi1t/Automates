/**
 * @file automate.h
 * @author Adrien Taberner & Othmane Abdimi
 * @date 2023-01-09
 * 
 * Déclaration des structures et fonctions utiles pour 
 * la représentation et la manipulation des automates
 * 
 */


#ifndef AUTOMATE_H
#define AUTOMATE_H

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
int word_execution2(Automate automate,const char* word,State state,int len);

/*Permet de renvoyer une valeur en fonction de word_execution2*/
void print_resultat(int valeur);

/*Ajoute un état a l'automate*/
void add_state(State* state,Automate* automate);

/*Ajoute une transition à l'automate*/
void add_transition(State* start_state,char read_character,State* end_state,Automate* automate);

/*Ajoute un caractère à l'alphabet de l'automate*/
void add_character(char letter,Automate* automate);

/*Donne l'id de l'état final d'une transition pour un état*/
int id_end_state(char character_test, Automate automate, State state_test);

/*Fonction pour la déterminisation*/
Automate automate_determinisation(Automate automate_source);

/*Fonction pour la minimisation*/
Automate minimisation_automate(Automate automate_source,int* first_state);
Automate minimisation_automate_recursive(Automate automate_source);


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

#endif
