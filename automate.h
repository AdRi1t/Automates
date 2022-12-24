#ifndef HEADER_H
#define HEADER_H

/*structure pour un état*/
typedef struct{
	int id;
	char accepteur;
}Etat;

/*les transitions ne stockent pas les états seulement un pointeur vers eux*/
typedef struct{
	Etat* initiale;
	char caractere_lu;
	Etat* fin;
}Transition;

/*un automate est représenté par une liste d'état et une liste de transition*/
typedef struct{
	int nb_etats;
	int nb_transition;
	Etat* Etats;
	Transition* Transitions;
}Automate;

Automate read_file(char*);	/*Renvoie un automate initialiser à partir d'un fichier*/
void init_etats(int, int*,Automate*);	/*initialise la liste des états à partir du nombre d'états et de la liste des états accepteur*/
void add_transition(char*,Automate*);	/*lit une transition et l'ajoute à l'automate*/
void print_automate(Automate);	/*lit une transition et l'ajoute à l'automate*/
int* numbers_from_string(char*, int);	/*lit un ensemble de nombres depuis une chaine caractère*/
int compte_ligne_fichier(FILE*);

#endif
