#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "extension.h"
#include "board.h"
#include "jeu.h"

#define MOT_TAILLE 20
#define TAB_SCORE_NBL 100
#define TAB_SCORE_NBC 2

#define TABLEAU_SCORE "scoreboard.txt"

size plus_grande_piece(board game, player joueur){
	for(int i = NB_SIZE - 1; i >= 0; i--){
		if(get_nb_piece_in_house(game, joueur, i+1) > 0) return i+1;
	}
	return 0;
}

int bot_peut_gagner(board game, player joueur){
	size piece = plus_grande_piece(game, joueur);
	if(piece == NONE) return 0;

	//Cherche un placement de pièce gagante.
	for(int l = 0; l < DIMENSIONS; l++){
		for(int c = 0; c < DIMENSIONS; c++){
			board jeu_b = copy_game(game);
			
			if(place_piece(jeu_b, piece, l, c) == OK){
				if(get_winner(jeu_b) == joueur){
					place_piece(game, piece, l, c);
					return 1;
				}
			}
			
			destroy_game(jeu_b);
		}
	}
	
	//Déplacement de pièce.
	for(int l_cible = 0; l_cible < DIMENSIONS; l_cible++)
	for(int c_cible = 0; c_cible < DIMENSIONS; c_cible++)
	for(int l_source = 0; l_source < DIMENSIONS; l_source++)
	for(int c_source = 0; c_source < DIMENSIONS; c_source++){
		board jeu_b = copy_game(game);
		
		if(move_piece(jeu_b, l_source, c_source, l_cible, c_cible) == OK){
			if(get_winner(jeu_b) == joueur){
				move_piece(game, l_source, c_source, l_cible, c_cible);
				return 1;
			}
		}
		
		destroy_game(jeu_b);
	}
	
	return 0;
}

int bot_facile(board game, player joueur){
	if(bot_peut_gagner(game, joueur)) return 1;

	int compteur = 0;
	enum return_code res = TARGET;
	
	while(res != OK){
		board game_b = copy_game(game);
		
		if(rand()%2 == 0){
			int ligne = rand()%3;
			int colonne = rand()%3;
			res = place_piece(game_b, (rand()%3)+1, ligne, colonne);
			
			if(res == OK){
				place_piece(game, (rand()%3)+1, ligne, colonne);
				return 1;
			}
		}
		if(rand()%2 == 1){
			int ligne_source = rand()%3;
			int colonne_source = rand()%3;
			int ligne_cible = rand()%3;
			int colonne_cible = rand()%3;
			res = move_piece(game_b, ligne_source, colonne_source, ligne_cible, colonne_cible);
			
			if(res == OK){
				move_piece(game, ligne_source, colonne_source, ligne_cible, colonne_cible);
				return 1;
			}
		}
		
		destroy_game(game_b);
		compteur ++;
		if(compteur >= 10e6) return 0;
	}
	
	return 0;
}

//----------------------------------------------------------------------

int string_longueur(char string[]){
	int i = 0;
	while(string[i] != '\0'){
		i++;
	}
	return i+1;
}

int string_egaux(char string_a[], char string_b[]){
	if(string_longueur(string_a) != string_longueur(string_b))
		return 0;
	
	int i = 0;
	while(string_a[i] != '\0' && string_b[i] != '\0'){
		if(string_a[i] != string_b[i]) return 0;
		i++;
	}
	return 1;
}

void string_copier(char chaine_source[], char chaine_but[]){
	int i = 0;
	while(chaine_source[i] != '\0'){
		chaine_but[i] = chaine_source[i];
		i++;
	}
	chaine_but[i] = '\0';
}

void trier_tableau_2D(int tab[][TAB_SCORE_NBC], int n, int c_trie){
	int j = 0;
	while(j < n){
		for(int i = j; i < n; i++){
			if(tab[j][c_trie] < tab[i][c_trie]){
				for(int c = 0; c < TAB_SCORE_NBC; c++){
					int t = tab[i][c];
					tab[i][c] = tab[j][c];
					tab[j][c] = t;
				}
			}
		}
		j++;
	}
}

void decompte_points(char nom_player_1[], char nom_player_2[], player gagnant){
	FILE *fichier = fopen(TABLEAU_SCORE, "r");
	if(fichier == NULL)
		printf("Le fichier n'a pas pu être ouvert.\n(extension.c -décompte_points)\n");
	
	int present[2] = {0, 0};
	
	char temp_points[MOT_TAILLE];
	char temp_nom[MOT_TAILLE];
	
	int nbl = 0;
	
	// Un tableau d'objets avec comme propriété nom et score aurait été plus simple.
	char tab_scores[TAB_SCORE_NBL][TAB_SCORE_NBC][MOT_TAILLE]; 
	
	// Sauvegarde du fichier dans un tableau.
	while(fscanf(fichier, "%s %s\n", temp_nom, temp_points) != EOF){
		string_copier(temp_nom, &tab_scores[nbl][0][0]);
		
		if(string_egaux(temp_nom, nom_player_1)){
			sprintf(temp_points, "%d", (atoi(temp_points) + ((gagnant == 1)? 10: -8)));
			present[0] = 1;
		}
		if(string_egaux(temp_nom, nom_player_2)){
			sprintf(temp_points, "%d", (atoi(temp_points) + ((gagnant == 2)? 10: -8)));
			present[1] = 1;
		}
		string_copier(temp_points, &tab_scores[nbl][1][0]);
		nbl++;
	}
	fclose(fichier);
	
	// On complète le tableau avec les joueurs absents.
	if(!present[0]){
		string_copier(nom_player_1, &tab_scores[nbl][0][0]);
		sprintf(temp_points, "%d", ((gagnant == 1)? 10: -8));
		
		string_copier(temp_points, &tab_scores[nbl][1][0]);
		nbl++;
	}
	if(!present[1]){
		string_copier(nom_player_2, &tab_scores[nbl][0][0]);
		sprintf(temp_points, "%d", ((gagnant == 2)? 10: -8));
		
		string_copier(temp_points, &tab_scores[nbl][1][0]);
		nbl++;
	}
	
	// On remplie le fichier avec le tableau trié.
	int tab_trier[TAB_SCORE_NBL][TAB_SCORE_NBC];
	for(int i = 0; i < nbl; i++){
		tab_trier[i][0] = i;
		tab_trier[i][1] = atoi(&tab_scores[i][1][0]);
	}
	
	trier_tableau_2D(tab_trier, nbl, 1);
	
	// Vérifie que le tableau est trié.
	/*for(int i = nbl -1; i >= 0; i--){
		printf("%d ", tab_trier[i][1]);
	}
	printf("\n");*/
	
	FILE *fichier_b = fopen(TABLEAU_SCORE, "w");
	if(fichier_b == NULL)
		printf("Le fichier n'a pas pu être ouvert.\n(extension.c -décompte_points)\n");
		
	for(int i = 0; i < nbl; i++){
		int l = tab_trier[i][0];
		fprintf(fichier_b, "%s %s\n"
		, &tab_scores[ l ][ 0 ][ 0 ]
		, &tab_scores[ l ][ 1 ][ 0 ]);
	}
	
	fclose(fichier_b);
}


void leaderboard(){
	FILE *fichier = fopen(TABLEAU_SCORE, "r");
	if(fichier == NULL)
		printf("Le fichier n'a pas pu être ouvert.\n(extension.c -leaderboard)\n");
	
	int score, i = 1;
	char noms[MOT_TAILLE];
	
	printf("\n");
	while(fscanf(fichier, "%s %d\n", noms, &score) != EOF){
		printf("%d. ", i);
		printf("%s : ", noms);
		printf("%d point(s)\n", score);
		i++;
	}	
}
	
/*

int bot_difficile(board game){

}

int bot_moyen(board game){

}

*/
