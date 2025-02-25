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

#ifndef H_AFFICHAGE_H
#define H_AFFICHAGE_H

/*
Fait : 
Cette fonction renvoie le caractère demandé pour l'afficher.

Param :
- joueur : Joueur actuel.
- taille : Taille de la pièce demandée.

Return :
- Caractère représentant la pièce.

*/
char piece_joueur(player joueur, size taille);

/*
Fait : 
Affiche un tableau de deux dimensions de char.

Param :
- L : Ligne.
- C : Colonne.
- tab : Tableau à afficher.
*/
void afficher_tab2_char(int L, int C, char tab[L][C]);

/*
Fait : 
Cette fonction permet de remplir faire une copie affichable du plateau de jeu.

Param :
- jeu : Plateau de jeu.
- L : Ligne.
- C : Colonne.
- tab : Tableau à remplir.

*/
void remplir_tab_jeu(board jeu, int L, int C, char tab[L][C]);

/*
Fait : 
Cette fonction permet d'afficher le plateau pendant une partie.

Param :
- jeu : Plateau de jeu.
- joueur : Joueur actuel.
*/
void afficher_jeu(board jeu, player joueur);

/*
Fait : 
Cette fonction permet d'afficher le nombre de pièces de la pièce demandée du joueur entré en paramètre.

Param :
- jeu : Plateau de jeu.
- joueur : Joueur actuel.
- taille : Taille de la pièce.
*/
void afficher_taille_piece(board jeu, player joueur, size taille);

/*
Fait : 
Cette fonction permet d'afficher toutes les pièces du joueur entré en paramètre.

Param :
- jeu : Plateau de jeu.
- joueur : Joueur actuel.
*/
void afficher_pieces_joueur(board jeu, player joueur);

#endif
