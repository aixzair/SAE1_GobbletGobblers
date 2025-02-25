#ifndef H_EXT_H
#define H_EXT_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

#define TAB_SCORE_NBC 2

/*
Fait : 
Cette fonction permet d'obtenir la plus grande pièce du joueur.

Param :
- game : Le jeu.
- joueur : Le joueur dont on veut obtenir la plus grande pièce.

Return :
- La taille de la plus grande pièce.
*/
size plus_grande_piece(board game, player joueur);

/*
Fait : 
Cette fonction permet de savoir si le bot peut gagner et le fait si il le peut.

Param :
- game : Le jeu.
- joueur : Le joueur qui joue.

Return :
- 0 pour Faux.
- 1 pour Vrai.
*/
int bot_peut_gagner(board game, player joueur);

/*
Fait : 
Cette fonction permet au joueur de jouer contre un bot de niveau facile.

Param :
- game : Le jeu.

Return :
- 0 si il n'a pas réussi à jouer.
- 1 si il a réussi à jouer.
*/
int bot_facile(board game, player joueur);

/*
Fait : 
Cette fonction permet d'obtenir la longueur d'une chaine de caractère.

Param :
- string : la chaîne de caractère.

Return :
- la longueur.
*/
int string_longueur(char string[]);

/*
Fait : 
Cette fonction permet de savoir si 2 chaînes de caractères sont égales.

Param :
- string_a : la première chaîne.
- string_b : la deuxième chaîne.

Return :
- 0 pour faux.
- 1 pour vrai.
*/
int string_egaux(char string_a[], char string_b[]);

/*
Fait : 
Cette fonction copie une chaine de caractère dans une autre.

Param :
- chaine_source : la chaine que l'on doit copier.
- chaine_but : la chaine où on la copie.
*/
void string_copier(char chaine_source[], char chaine_but[]);

/*
Fait : 
Cette fonction permet de trier le tableau en fonction des scores.

Param :
- tab : le tableau à trier.
- n : nombre de colonnes.
- c_trie : colonne à trier.
*/
void trier_tableau_2D(int tab[][TAB_SCORE_NBC], int n, int c_trie);

/*
Fait : 
Cette fonction permet de mettre à jour le tableau des scores.

Param :
- nom_player_1 : nom du premier joueur.
- nom_player_2 : nom du deuxième joueur.
- gagnant : gagnant du jeu pour changer les points des joueurs.
*/
void decompte_points(char nom_player_1[], char nom_player_2[], player gagnant);

/*
Fait : 
Cette fonction permet d'afficher le tableau des scores.
*/
void leaderboard();

#endif
