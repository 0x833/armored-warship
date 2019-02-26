/**********************************************************************************\
	PROGRAMMER: Erick Meyer
	DATE CREATED: MARCH 10 2013
	LAST UPDATED: APRIL 1 2013
	ASSIGNMENT: Programming Assignment 6 -- BATTLESHIP
	DESCRIPTION: This project is the game of battleship and has the following 
				 options at the main start up; rules, play vs computer,
				 play vs. other player, and exit. The game is turn based and has 
				 5 ships of varying lengths. Each player will take turns 
				 guessing a coordinate and then the program will tell the player 
				 if the shot was a hit or miss. The game will continue until one 
				 of the players has sunk all of the opponents ships. 
\**********************************************************************************/

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define PLAYER1     1
#define PLAYER2     2
#define X_AXIS      10
#define Y_AXIS      10
#define PATROL_BOAT 'P'
#define DESTROYER   'D'
#define SUBMARINE   'S'
#define BATTLESHIP  'B'
#define CARRIER     'C'
#define HIT         '*'
#define MISS        'm'

typedef struct player
{
	int player_number;
	int moves;
	int hits;
	int misses;
	int total_ships_sunk;
	double h_m_ratio;
	int win_or_loss;

} Player_t;

typedef enum direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
} Direction;

FILE* open_outfile(void);
void write_move_outfile(FILE* outfile, int player, int count, char move[], int hit_or_miss);  
void create_game_board(char game_board[X_AXIS][Y_AXIS]);
void count_down(void);
void display_menu(int *menu_response);
void display_rules(void);
void display_exit_message(void);
void display_gameboard(int count, int player, char game_board[Y_AXIS][X_AXIS]);
void display_ship_sink(char game_board, int player);
void display_winner(int player);
void display_statistics(FILE* outfile, int player, int hits, int misses);
void pause_clear(void);
void place_ships(char game_board[Y_AXIS][X_AXIS], int player, int count);
void place_ships_random(char game_board[Y_AXIS][X_AXIS]);
void take_shot(char game_board_other_player[Y_AXIS][X_AXIS], int player, int count, int counter_of_hits_on_ships[5], FILE* outfile);
void line_sep(void);
void mirror_opponent_board(char game_board_computer[Y_AXIS][X_AXIS], char game_board_mirror[Y_AXIS][X_AXIS]);
int sum_numbers(int list[], int length);
int check_shot(int coordinates[2], char game_board[Y_AXIS][X_AXIS]);
int check_position(int coordinates[2], char game_board[X_AXIS][Y_AXIS]);
int check_orientation(int coordinates[2],int ship, int length, char orientation[30], char game_board[X_AXIS][Y_AXIS]);
int check_ship_sunk(int player, int hits_on_ships[5], int hits_on_ships2[5], int ships_sunk[5], int ships_sunk2[5]);
int change_to_upper(char string[]);
int change_color(void);
int number_ships_sunk(int hits_on_ship[5], int ships_sunk[5]);
int is_winner(int total_ships_sunk_of_player1, int total_ships_sunk_of_player2);
int who_goes_first(void);
int char_to_int(char axis);
int prompt_for_random(void);
int placement_okay(void);
int determine_player(int player);
#endif