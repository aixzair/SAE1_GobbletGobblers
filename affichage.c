#include <stdio.h>

#include "board.h"
#include "affichage.h"

#define TAB_NBL 13
#define TAB_NBC 2 * TAB_NBL - 1

char piece_joueur(player joueur, size taille){
	if(joueur == PLAYER_1){
		if(taille == SMALL) return '+';
		else if (taille == MEDIUM) return 'x';
		else if (taille == LARGE) return 'X';
	}
	else if (joueur == PLAYER_2){
		if(taille == SMALL) return '.';
		else if (taille == MEDIUM) return 'o';
		else if (taille == LARGE) return 'O';
	}
	return ' ';
}

void afficher_tab2_char(int L, int C, char tab[L][C]){
	for(int l = 0; l<L; l++){
	 	for(int c = 0; c<C; c++){
			printf("%c", tab[l][c]);
		}
		printf("\n");
	}
}

void remplir_tab_jeu(board jeu, int L, int C, char tab[L][C]){
	for(int l = 0; l<L; l++){
		for(int c = 0; c<C; c++){
			if ((l == 0 && c == 0) || (l == (L-1) && c == (C-1))){
				tab[l][c] = ' ';
			} else if ((l == 0 && c == (C-1)) || (l == (L-1) && c == 0)){
				tab[l][c] = ' ';
			} else if (l == 0 || l == L-1){
				tab[l][c] = '-';
			} else if (c == 0 || c == C-1){
				tab[l][c] = '|';
			} else if (l%4 == 0 && c%8 == 0){
				tab[l][c] = '+';
			} else if (l%4 == 0){
				tab[l][c] = '-';
			} else if (c%8 == 0){
				tab[l][c] = '|';
			} else if ((l-2)%4 == 0 && (c-4)%8 == 0){
				int l_j = (l-2)/4;
				int c_j = (c-4)/8;
				tab[l][c] = piece_joueur(get_place_holder(jeu, l_j, c_j), get_piece_size(jeu, l_j, c_j));
			} else {
				tab[l][c] = ' ';
			}
		}
	}
}

void afficher_jeu(board jeu, player joueur){
	char cases[TAB_NBL][TAB_NBC];
	remplir_tab_jeu(jeu, TAB_NBL, TAB_NBC, cases);
	afficher_tab2_char(TAB_NBL, TAB_NBC, cases);
}

void afficher_taille_piece(board jeu, player joueur, size taille){
	int nombre = get_nb_piece_in_house(jeu, joueur, taille);
	char * pluriel = (nombre > 1)? "es": "e";
	printf("Vous avez %d pièc%s : '%c'.\n"
	, nombre,  pluriel, piece_joueur(joueur, taille));
}

void afficher_pieces_joueur(board jeu, player joueur){
	afficher_taille_piece(jeu, joueur, SMALL);
	afficher_taille_piece(jeu, joueur, MEDIUM);
	afficher_taille_piece(jeu, joueur, LARGE);
}

