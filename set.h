/**
 * @file set.h
 * @author Adrien Taberner & Othmane Abdimi
 * @date 2023-01-09
 * 
 * Déclaration des structures et fonctions utiles pour les sets
 * 
 */



#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include "automate.h"

/*Permets d'avoir une liste d'etats avec sa taille*/
typedef struct{
	int size;
	State* list;
}Set_State;

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

/*Trouve l'index de l'états dans l'ensemble des états*/
int index_in_set(Set_State set,State test_state);

/*Trouve l'index d'un set dans une liste de set*/
int index_in_set_list(Set_State* set_list, Set_State test_set,int len);

/*Ajoute un set dans une liste de Set*/
void add_set_list(Set_State** set_list,Set_State set,int* len);

/*Supprime le dernier indice d'une liste de set*/
Set_State pop_set_list(Set_State** set_list,int* len);

/*Renvoie les états atteint quand on part d'une liste d'états pour lire un caractère*/
Set_State find_end(char character_test, Automate automate, Set_State states_test);

#endif