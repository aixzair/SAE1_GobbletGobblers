#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "affichage.h"
#include "jeu.h"
#include "extension.h"

#define NOM_TAILLE 20
#define SVG "svg.sav"

void vider_buffer(){
    int c = 0;
    while(c != '\n' && c != EOF){
        c = getchar();
    }
}

int demander_nombre(int min, int max){
	int nombre = min-1;
	int i = 1;
	
	do{
		if(i){
			printf("Entrez votre choix : ");
		} else {
			printf("Vous n'avez pas entré un nombre valide, réessayez : ");
		}
		
		scanf("%d", &nombre);
		vider_buffer();
		
		i = 0;
	}while(nombre < min || nombre > max);
	
	return nombre;
}

void placer_coordonnees(board jeu, int * ligne, int * colonne){
	int i = 0;
	do{
		if(i){
			printf("\nVous ne pouvez pas placer de pièce sur une grande pièce.\n");
		}
		
		printf("En quelle ligne voulez vous placer votre pièce ?\n");
		* ligne = demander_nombre(1, 3);
		
		printf("En quelle colonne voulez vous placer votre pièce ?\n");
		*  colonne = demander_nombre(1, 3);
		
		i = 1;
	}while(get_piece_size(jeu, (*ligne)-1, (*colonne)-1) == LARGE);
}

void placer_piece(board jeu, player joueur){
	int ligne = -1, colonne = -1;
	placer_coordonnees(jeu, &ligne, &colonne);
			
	printf("Sélectionnez la taille de votre pièce (1 pour petit, 2 pour moyen et 3 pour grand) :\n");
	int taille = demander_nombre(1, 3);
		
			
	int res = place_piece(jeu, taille, ligne - 1, colonne - 1);
	if(res == OK){
		printf("\nLa piece a été placée avec succès.\n");
		return;
	} else if(res == SOURCE){
		printf("\nVous n'avez pas assez de pièces de cette taille !\n");
	} else if(res == TARGET){
		if(get_place_holder(jeu, ligne - 1, colonne - 1) == joueur){
			printf("\nVous avez déjà une pièce ici !\n");
		} else {
			printf("\nIl y a déjà une pièce plus grande ici !\n");
		}
	} else{
		printf("\nIl n'y a pas de case à ces coordonnées !\n");
	}
	placer_piece(jeu, joueur);
}

void prendre_coordonnees(board jeu, int * ligne, int * colonne, player joueur){
	int i = 0;
	do{
		if(i){
			printf("Vous n'avez pas de pièce ici.\n");
		}
		
		printf("En quelle ligne voulez vous prendre votre pièce ?\n");
		* ligne = demander_nombre(1, 3);
		
		printf("En quelle colonne voulez vous prendre votre pièce ?\n");
		*  colonne = demander_nombre(1, 3);
		
		i = 1;
	}while(get_place_holder(jeu, (*ligne)-1, (*colonne)-1) != joueur);
}

int deplacer(player joueur, board jeu){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(get_place_holder(jeu, i, j) == joueur){
				return 1;
			}
		}
	}
	return 0;
}
 
void lire(char string[], int n){
	char *position_entree = NULL;
	
	if(fgets(string, n, stdin) != NULL){
		position_entree = strchr(string, '\n');
		if(position_entree != NULL){
			*position_entree = '\0';
		}
	}
}

void demander_prenom(char nom_joueur1[], char nom_joueur2[]){
	printf("Entrez le nom du premier joueur :\n");
	lire(nom_joueur1, NOM_TAILLE);
	
	printf("Entrez le nom du second joueur :\n");
	lire(nom_joueur2, NOM_TAILLE);
}

void deplacer_piece(board jeu, player joueur){
	int ligne_cible = 0, colonne_cible = 0;
	prendre_coordonnees(jeu, &ligne_cible, &colonne_cible, joueur);
			
	int ligne_but = 0, colonne_but = 0;
	placer_coordonnees(jeu, &ligne_but, &colonne_but);
			
	if(move_piece(jeu, ligne_cible - 1, colonne_cible - 1, ligne_but - 1, colonne_but - 1) == OK){
		printf("Pièce déplacée avec succès.\n");
		return;
	}
	else if(move_piece(jeu, ligne_cible - 1, colonne_cible - 1, ligne_but - 1, colonne_but - 1) == POSITION){
		printf("Il n'y a pas de case à ces coordonnées ! \n");
	}
	else if(move_piece(jeu, ligne_cible - 1, colonne_cible - 1, ligne_but - 1, colonne_but - 1) == SOURCE){
		printf("Vous n'avez pas de pion sur la case séléctionnée ! \n");
	}
	else if(move_piece(jeu, ligne_cible - 1, colonne_cible - 1, ligne_but - 1, colonne_but - 1) == TARGET){
		printf("La pièce que vous voulez déplacer est plus petite que la pièce qui se trouve à l'endroit séléctionné ! \n");
	}
	deplacer_piece(jeu, joueur);
}

void partie(int load){
	
	char nom_joueur1[NOM_TAILLE];
	char nom_joueur2[NOM_TAILLE];
	
	demander_prenom(nom_joueur1, nom_joueur2);
	
	board jeu = (load)? load_game(SVG): new_game();
	
	do{
		printf("\n---------------------------------------------------\n\n");
		player joueur = (next_player(jeu) == PLAYER_2)? PLAYER_1: PLAYER_2;
		
		printf("Au tour de %s, le joueur n°%d :\n\n"
		,(joueur == PLAYER_1)? nom_joueur1: nom_joueur2
		,joueur);
		
		afficher_jeu(jeu, joueur);
		afficher_pieces_joueur(jeu, joueur);
		
		
		int choix = 1;
		if(deplacer(joueur, jeu)){
			printf("\nSi vous voulez placer une pièce, entrez 1.\n");
			printf("Si vous voulez déplacer une pièce, entrez 2.\n");
			choix = demander_nombre(1, 2);
		}
		
		printf("\n");
		if(choix == 1){
			placer_piece(jeu, joueur);
		} else {
			deplacer_piece(jeu, joueur);
		}
		
		save_game(jeu, SVG);
	}while(get_winner(jeu) == NO_PLAYER);
	
	printf("\n------------------------------------------------\n");
	afficher_jeu(jeu, PLAYER_1);
	
	player gagnant = get_winner(jeu);
	
	printf("\nVainqueur : %s, le joueur n°%d !\n\n"
	,(gagnant == PLAYER_1)? nom_joueur1: nom_joueur2
	,((gagnant == PLAYER_2)+1));
	
	decompte_points(nom_joueur1, nom_joueur2, gagnant);
			
	destroy_game(jeu);
	remove(SVG);
	
	leaderboard();
}

void bot(){
	board jeu = new_game();
	
	do{
		printf("\n---------------------------------------------------\n\n");
		player joueur = (next_player(jeu) == PLAYER_2)? PLAYER_1: PLAYER_2;
		
		if(joueur == PLAYER_1){
		
			printf("Votre tour :\n\n");
			
			afficher_jeu(jeu, joueur);
			afficher_pieces_joueur(jeu, joueur);
			
			
			int choix = 1;
			if(deplacer(joueur, jeu)){
				printf("\nSi vous voulez placer une pièce, entrez 1.\n");
				printf("Si vous voulez déplacer une pièce, entrez 2.\n");
				choix = demander_nombre(1, 2);
			}
			
			printf("\n");
			if(choix == 1){
				placer_piece(jeu, joueur);
			} else {
				deplacer_piece(jeu, joueur);
			}
		}
		else{
			bot_facile(jeu, joueur);
			afficher_jeu(jeu, joueur);
			afficher_pieces_joueur(jeu, joueur);
		}
	}while(get_winner(jeu) == NO_PLAYER);
	
	printf("\n------------------------------------------------\n");
	afficher_jeu(jeu, PLAYER_1);
	
	if(get_winner(jeu) == PLAYER_1){
		printf("Vous avez gagné\n");
	}
	else{
		printf("Vous avez perdu, le bot a gagné\n");
	}
			
	destroy_game(jeu);
	remove(SVG);
}



void menu(){
	printf("Pour faire une partie joueur contre joueur, entrez 1\n");
	printf("Pour faire une partie joueur contre bot, entrez 2\n");
	printf("Pour afficher le tableau des scores, entrez 3\n");
	
	int max = 3;
	FILE *fichier = fopen(SVG, "r");
	if(fichier != NULL){
		printf("Pour recharger votre ancienne partie, entrez 4\n");
		fclose(fichier);
		max = 4;
	}
	
	int choix = demander_nombre(1, max);
	if(choix == 1)
		partie(0);
	if(choix == 2)
		bot();
	if(choix == 3)
		leaderboard();
	if(choix == 4)
		partie(1);
}



