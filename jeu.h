/*
SAE 1
Jeu "Gobblet Gobblers":

Réalisé par :
Schneider Clément
Lerosier Alexandre

TP2.1
2022
*/

#include "board.h"

#ifndef H_JEU_H
#define H_JEU_H

/*
Fait :
Cette fonction permet de vider le buffer.
*/
void vider_buffer();

/*
Fait : 
Cette fonction demande un nombre compris entre un nombre minimum et maximum.

Param :
- max : Nombre max.
- min : Nombre min.

Return :
- Nombre entré par l'utilisateur.
*/
int demander_nombre(int min, int max);

/*
Fait : 
Cette fonction permet de regarder si on peut placer une pièce aux coordonnées entrées en paramètre.

Param :
- jeu : Plateau de jeu.
- ligne : Ligne sur le plateau.
- colonne : Colonne sur le plateau.

*/
void placer_coordonnees(board jeu, int * ligne, int * colonne);

/*
Fait : 
Cette fonction permet de placer une pièce.

Param :
- jeu : Plateau de jeu.
- joueur : Joueur actuel.
*/
void placer_piece(board jeu, player joueur);

/*
Fait : 
Cette fonction permet de prendre les coordonnées de la pièce à déplacer.

Param :
- jeu : Plateau de jeu.
- ligne : Ligne sur le plateau.
- colonne : Colonne sur le plateau.
- joueur : Joueur actuel.
*/
void prendre_coordonnees(board jeu, int * ligne, int * colonne, player joueur);

/*
Fait : 
Cette fonction regarde si le joueur à la possibilité de déplacer une pièce sur le plateau.

Param :
- jeu : Plateau de jeu.
- joueur : Joueur actuel.

Return :
- 0 pour Faux.
- 1 pour Vrai.
*/
int deplacer(player joueur, board jeu);

/*
Fait : 
Cette fonction permet de corriger une éventuelle erreur de frappe par l'utilisateur.

Param :
- string : Chaine de caractères.
- n : Taille de la chaine.
*/
void lire(char string[], int n);

/*
Fait : 
Cette fonction demande les prénoms des 2 utilisateurs.

Param :
- nom_joueur1 : Nom du premier joueur.
- nom_joueur2 : Nom du second joueur.
*/
void demander_prenom(char nom_joueur1[], char nom_joueur2[]);

/*
Fait : 
Cette fonction déplace la pièce du joueur entré en paramètre.

Param :
- jeu : Plateau de jeu.
- joueur : Joueur actuel.

*/
void deplacer_piece(board jeu, player joueur);

/*
Fait : 
Cette fonction permet de lancer et terminer la partie joueur contre joueur.

Param :
- load : si oui la partie précédente est chargée.
*/
void partie(int load);


/*
Fait : 
Cette fonction permet de lancer et terminer la partie joueur contre bot.
*/
void bot();

/*
Fait : 
Cette fonction permet de sélectionner le type de partie.
*/
void menu();
#endif
