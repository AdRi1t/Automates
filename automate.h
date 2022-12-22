#ifndef HEADER_H
#define HEADER_H

typedef struct{
	int id;
	char accepteur;
}Etat;

typedef struct{
	Etat* initiale;
	char caractere_lu;
	Etat* fin;
}Transition;

typedef struct{
	Etat* Etats;
	int nb_etats;
	Transition* Transitions;
}Automate;

int* numbers_from_string(char* str_read, int nb_numbers);
Automate read_file(char*);
int compte_ligne_fichier(FILE*);
Etat* init_etats(int, int*);

#endif
