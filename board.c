#include <stdio.h>
#include <stdlib.h>
#include "board.h"

/**
 * \file board.c
 *
 * \brief Source code associated with \ref board.h
 *
 * \TD2 Lerosier Alexandre Schneider Clément
 */

/**
 * @brief The board of the game.
 */

struct Piece {
 	player joueur;
 	size taille;
};

struct board_s {
	player joueur;
	struct Piece pieces[DIMENSIONS][DIMENSIONS][NB_SIZE];
	int maison[NB_PLAYERS][NB_SIZE];
};

board new_game(){
	board new_board = malloc(sizeof(struct board_s));
	
	if(new_board == NULL){
		printf("Le plateau n'a pas pu être créé. Fonction new_game().\n");
		return NULL;
	}
	
	// Initialise le joueur.
	new_board->joueur = PLAYER_1;
	
	// Initialise les cases.
	for(int i = 0; i < DIMENSIONS; i++){
		for(int j = 0; j < DIMENSIONS; j++){
			for(int k = 0; k < NB_SIZE; k++){
				board new_board = malloc(sizeof(struct board_s));
				new_board->pieces[i][j][k].taille = NONE;
				new_board->pieces[i][j][k].joueur = NO_PLAYER;
			}
		}
	}
	
	// Initialise la maison.
	for(int i = 0; i < NB_PLAYERS; i ++){
		for(int j = 0; j < NB_SIZE; j++){
			new_board->maison[i][j] = NB_INITIAL_PIECES;
			//printf("i = %d, j = %d, nb = %d\n", i, j, NB_INITIAL_PIECES);
		}
	}
	
	return new_board;
}

board copy_game(board original_game){
	board new_board = malloc(sizeof(struct board_s));
	
	if(new_board == NULL){
		printf("Le plateau n'a pas pu être créé. Fonction new_game().\n");
		return NULL;
	}
	
	// Copie le joueur en cours.
	new_board->joueur = original_game->joueur;
	
	// Copie les pièces de jeux.
	for(int i = 0; i < DIMENSIONS; i++){
		for(int j = 0; j < DIMENSIONS; j++){
			for(int k = 0; k < NB_SIZE; k++){
				new_board->pieces[i][j][k].joueur = original_game->pieces[i][j][k].joueur;
				new_board->pieces[i][j][k].taille = original_game->pieces[i][j][k].taille;
			}
		}
	}
	
	// Copie la maison.
	for(int i = 0; i < NB_PLAYERS; i ++){
		for(int j = 0; j < NB_SIZE; j++){
			new_board->maison[i][j] = original_game->maison[i][j];
		}
	}
	
	return new_board;
}

void destroy_game(board game){
	free(game);
};

player next_player(board game){
	if(game->joueur == PLAYER_1)
		return PLAYER_2;
	else if(game->joueur == PLAYER_2)
		return PLAYER_1;
	else
		return NO_PLAYER;
}

player get_place_holder(board game, int line, int column){
	int etage = 0;
	
	// Cherche la pièce à l'étage le plus haut.
	for(int i = 0; i < NB_SIZE; i++){
		if(game->pieces[line][column][i].taille != NONE)
			etage = i;
	}
	
	// Renvoie à qui est la pièce.
	return game->pieces[line][column][etage].joueur;
}

size get_piece_size(board game, int line, int column){
	int etage = 0;
	
	// Cherche la pièce la plus grande.
	for(int i = 0; i < NB_SIZE; i++){
		if(game->pieces[line][column][i].taille != NONE)
			etage = i;
	}
	
	// Renvoie la taille de la pièce.
	return game->pieces[line][column][etage].taille;
}

player get_winner(board game){
	int gagnant[2] = {0, 0};
	
	// Cherche une ligne gagnante.
	for(int i = 0; i < DIMENSIONS; i++){
		int j = 0;
		
		if(get_place_holder(game, i, j) == get_place_holder(game, i, j+1)
		&& get_place_holder(game, i, j) == get_place_holder(game, i, j+2)){
			player joueur = get_place_holder(game, i, j);
			
			if(joueur != NO_PLAYER)
				gagnant[joueur-1] += 1;
		}
	}
	
	// Cherche une colonne gagnante.
	for(int j = 0; j < DIMENSIONS; j++){
		int i = 0;
		
		if(get_place_holder(game, i, j) == get_place_holder(game, i+1, j) 
		&& get_place_holder(game, i, j) == get_place_holder(game, i+2, j)){
			player joueur = get_place_holder(game, i, j);
			
			if(joueur != NO_PLAYER)
				gagnant[joueur-1] += 1;
		}
	}
	
	// Vérifie si la diagonal est gagnante.
	if(get_place_holder(game, 0, 0) == get_place_holder(game, 1, 1) 
	&& get_place_holder(game, 0, 0) == get_place_holder(game, 2, 2)){
		player joueur = get_place_holder(game, 0, 0);
			
		if(joueur != NO_PLAYER)
			gagnant[joueur-1] += 1;
	}
	
	// Vérifie si la seconde diagonal est gagnante.	
	if(get_place_holder(game, 0, 2) == get_place_holder(game, 1, 1) 
	&& get_place_holder(game, 0, 2) == get_place_holder(game, 2, 0)){
		player joueur = get_place_holder(game, 0, 2);
			
		if(joueur != NO_PLAYER)
			gagnant[joueur-1] += 1;
	}
	
	if(gagnant[0] == gagnant[1]){
		return NO_PLAYER;
	} else if(gagnant[0] != 0) {
		return PLAYER_1;
	} else {
		return PLAYER_2;
	}
}

int get_nb_piece_in_house(board game, player checked_player, size piece_size){
	if(checked_player < 1 || checked_player > 2){
		printf("Votre joueur n'est pas valide !\n(checked_player = %d)", checked_player);
		exit(EXIT_SUCCESS);
	} else if(piece_size < 1 || piece_size > 3){
		printf("Votre taille de piece n'est pas valide !\nboard.c get_nb_piece_in_house() -> (piece_size = %d)\n", piece_size);
		exit(EXIT_SUCCESS);
	}
	return game->maison[checked_player-1][piece_size-1];
}

enum return_code place_piece(board game, size piece_size, int line, int column){
	// Vérifie si tous est bon.
	int taille = get_piece_size(game, line, column);
	if(line < 0 || line > 2)
		return POSITION;
	if(column < 0 || column > 2)
		return POSITION;
	if(get_nb_piece_in_house(game, game->joueur, piece_size) == 0)
		return SOURCE;
	if(taille >= piece_size)
		return TARGET;
	
	// Place la pièce.
	int etage;
	if(game->pieces[line][column][0].taille == NONE) etage = 0;
	else if(game->pieces[line][column][1].taille == NONE) etage = 1;
	else etage = 2;
	
	game->pieces[line][column][etage].taille = piece_size;
	game->pieces[line][column][etage].joueur = game->joueur;

	// Enlève la pièce.
	game->maison[game->joueur-1][piece_size-1] -= 1;
	
	// Change le joueur.
	if(game->joueur == PLAYER_1)
		game->joueur = PLAYER_2;
	else if(game->joueur == PLAYER_2)
		game->joueur = PLAYER_1;
		
	return OK;
}


enum return_code move_piece(board game, int source_line, int source_column, int target_line, int target_column){
	// Vérifie si tous est bon.
	int source_taille = get_piece_size(game, source_line, source_column);
	int joueur_source = get_place_holder(game, source_line, source_column);
	int target_taille = get_piece_size(game, target_line, target_column);
	
	if(source_line < 0 || source_line > 2)
		return POSITION;
	if(source_column < 0 || source_column > 2)
		return POSITION;
	if(joueur_source == NO_PLAYER || joueur_source == next_player(game))
		return SOURCE;
		
	if(target_line < 0 || target_line > 2)
		return POSITION;
	if(target_column < 0 || target_column > 2)
		return POSITION;
	if(get_nb_piece_in_house(game, game->joueur, joueur_source) == 0)
		return SOURCE;
	if(target_taille >= source_taille)
		return TARGET;
		
	int etage;
	if(game->pieces[source_line][source_column][0].taille == NONE) etage = 0;
	else if(game->pieces[source_line][source_column][1].taille == NONE) etage = 0;
	else if(game->pieces[source_line][source_column][2].taille == NONE) etage = 1;
	else etage = 2;
	

	size piece_size = game->pieces[source_line][source_column][etage].taille;
		
	// Déplace la piece.
	game->maison[game->joueur-1][piece_size-1] += 1;
	
	game->pieces[source_line][source_column][etage].taille = NONE;
	game->pieces[source_line][source_column][etage].joueur = NO_PLAYER;
	
	place_piece(game, piece_size, target_line, target_column);
	
	return OK;
}

board load_game(char * filename){
	board game = new_game();
	
	FILE *fichier = fopen(filename, "r");
	if(fichier == NULL)
		return game;
	
	// Lis le joueur dont c'est le tour.	
	fscanf(fichier, "%u\n", &game->joueur);
	fscanf(fichier, "\n");
	
	// Lis le plateau de jeu.
	for(int e = 0; e < NB_SIZE; e++){
		for(int l = 0; l < DIMENSIONS; l++){
			for(int c = 0; c < DIMENSIONS; c++){
				fscanf(fichier, "%u,%u ", &game->pieces[l][c][e].joueur, &game->pieces[l][c][e].taille);
			}
			fscanf(fichier, "\n");
		}
		fscanf(fichier, "\n");
	}
	
	// Lis la maison de pièce.
	for(int i = 0; i < NB_PLAYERS; i ++){
		for(int j = 0; j < NB_SIZE; j++){
			fscanf(fichier, "%d ", &game->maison[i][j]);
		}
		fscanf(fichier, "\n");
	}
	
	fscanf(fichier, "\n");
	fclose(fichier);
	
	return game;
}

void save_game(board game, char * filename){
	FILE *fichier = fopen(filename, "w");
	
	if(fichier == NULL){
		printf("Erreur pour la sauvegarde du fichier. L'ouverture à échoué.\n");
		return;
	}
	
	// Ecris le joueur dont c'est le tour de jouer.
	fprintf(fichier, "%d\n", game->joueur);
	fprintf(fichier, "\n");
	
	// Ecris le plateau de jeu.
	for(int e = 0; e < NB_SIZE; e++){
		for(int l = 0; l < DIMENSIONS; l++){
			for(int c = 0; c < DIMENSIONS; c++){
				fprintf(fichier, "%d,%d ", game->pieces[l][c][e].joueur, game->pieces[l][c][e].taille);
			}
			fprintf(fichier, "\n");
		}
		fprintf(fichier, "\n");
	}
	
	// Ecris la maison de pièces.
	for(int i = 0; i < NB_PLAYERS; i ++){
		for(int j = 0; j < NB_SIZE; j++){
			fprintf(fichier, "%d ", game->maison[i][j]);
		}
		fprintf(fichier, "\n");
	}
	
	fprintf(fichier, "\n");
	fclose(fichier);
}










