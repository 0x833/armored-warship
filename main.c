/**********************************************************************************\
	PROGRAMMER: Erick Meyer
	DATE CREATED: MARCH 10 2013
	LAST UPDATED: APRIL 1 2013
	ASSIGNMENT: Programming Assignment 6 -- BATTLESHIP
	DESCRIPTION: This project is the game of battleship and has the following 
				 options at the main start up; rules, play vs computer,
				 play vs. other player, and exit. The game is turn based and has 
				 5 ships of varying lengths. Each player will guess a coordinate 
				 and then the program will tell the player if the shot was a hit or 
				 miss. The game will continue until one of the players has sunk
				 all of the opponents ships. 
\**********************************************************************************/

#include "battleship.h"


int main(void)
{
	int menu_response = 0, *ptr_menu_response = NULL,  win = 0, index = 0, index2 = 0, player = 0, 
		players[2] = {PLAYER1, PLAYER2}, count = 0, shot_count = 0, hits_on_ships[5] = {0}, hits_on_ships2[5] = {0},
		ships_sunk[5] = {0}, ships_sunk2[5] = {0}, winner = 0, yes_no = 0, ok_placement = 0;
	char game_board_player[X_AXIS][Y_AXIS] = {0}, game_board_player2[X_AXIS][Y_AXIS] = {0}, game_board_player2_mirror[Y_AXIS][X_AXIS] = {0},
		game_board_player_mirror[Y_AXIS][X_AXIS] = {0};
	Player_t player1 = {0};
	Player_t player2 = {0};
	FILE* battleship_log = NULL;
	
	srand(time(NULL));
    ptr_menu_response = &menu_response;
	battleship_log = open_outfile();
	player1.player_number = PLAYER1;
	player2.player_number = PLAYER2;
	display_menu(ptr_menu_response);
	switch(menu_response)
	{
		case 1: pause_clear();
				display_rules();
				pause_clear();
				main();
				break;
		case 2: pause_clear();
				create_game_board(game_board_player); // Users gameboard.
				create_game_board(game_board_player2); //computer gameboard.
				create_game_board(game_board_player2_mirror);
				display_gameboard(count, player1.player_number, game_board_player); //displays the gameboard for the user and not the computer.
				yes_no = prompt_for_random();
				switch(yes_no)
				{
					case 1: do // cycles through the random placement of ships until user accepts.
							{
								if (ok_placement == 0)
								{
									create_game_board(game_board_player);
								}
								place_ships_random(game_board_player);
								pause_clear();
								display_gameboard(count, player1.player_number, game_board_player);
								ok_placement = placement_okay();
							} while (ok_placement == 0);
							break;
					case 0: place_ships(game_board_player, player1.player_number, count); //This is a manual placement of the ships ment for the user.
							break;
				}
				place_ships_random(game_board_player2);
				player = who_goes_first(); // Determines the player who goes first, the user or the computer.
				printf("Player %d goes first! \n", player);
				pause_clear();
				do // Simulates the game of between Player and computer. 
				{
					count++; //Increases the count after every 2 shots. 
					do 
					{
						shot_count++;// Increases every shot taken to figure out to use as a restriction on how often it is executed. 
						switch (player)
						{
							case PLAYER1: mirror_opponent_board(game_board_player2, game_board_player2_mirror);
										  display_gameboard(count, player1.player_number, game_board_player2_mirror);
										  take_shot(game_board_player2, PLAYER1, count, hits_on_ships, battleship_log);
										  winner = check_ship_sunk(PLAYER1, hits_on_ships, hits_on_ships2, ships_sunk, ships_sunk2);
										  mirror_opponent_board(game_board_player2, game_board_player2_mirror);
										  Sleep(1250);
										  system("cls");
										  display_gameboard(count, PLAYER1, game_board_player2_mirror);  
										  break;
							case PLAYER2: display_gameboard(count, player2.player_number, game_board_player);
										  take_shot(game_board_player, PLAYER2, count, hits_on_ships2, battleship_log);
										  winner = check_ship_sunk(PLAYER2, hits_on_ships, hits_on_ships2, ships_sunk, ships_sunk2);
										  Sleep(1250);
										  system("cls");
										  display_gameboard(count, PLAYER2, game_board_player);
										  break;
						}
						player++;
						player = determine_player(player);
						player1.hits = sum_numbers(hits_on_ships, 5);
						player2.hits = sum_numbers(hits_on_ships2, 5);
						pause_clear();
					} while (shot_count < 2 && (player1.hits != 17 && player2.hits != 17));
					shot_count = 0;
				}
				while(player1.hits != 17 && player2.hits != 17);
				if (player1.hits == 17)
				{
					player = PLAYER1;
				}
				else if (player2.hits == 17)
				{
					player = PLAYER2;
				}
				display_winner(player);
				if (shot_count == 1)
				{
					switch(player)
					{
						case PLAYER1: count++;
								      break;
						case PLAYER2: count++;
					}
				}
				player1.misses = count - player1.hits;
				player2.misses = count - player2.hits;
				display_statistics(battleship_log, player1.player_number, player1.hits, player1.misses);
				display_statistics(battleship_log, player2.player_number, player2.hits, player2.misses);
				break;
		case 3: pause_clear();
				create_game_board(game_board_player); // Users gameboard.
				create_game_board(game_board_player_mirror);
				create_game_board(game_board_player2); //computer gameboard.
				create_game_board(game_board_player2_mirror);
				display_gameboard(count, player1.player_number, game_board_player); //displays the gameboard for the user and not the computer.
				yes_no = prompt_for_random();
				switch(yes_no)
				{
					case 1: do// cycles through the random placement of ships until user accepts.
							{
								if (ok_placement == 0)
								{
									create_game_board(game_board_player);
								}
								place_ships_random(game_board_player);
								pause_clear();
								display_gameboard(count, player1.player_number, game_board_player);
								ok_placement = placement_okay();
							} while (ok_placement == 0);
							break;
					case 0: place_ships(game_board_player, player1.player_number, count); //This is a manual placement of the ships ment for the user.
							break;
				}
				count_down();
				display_gameboard(count, player2.player_number, game_board_player2); //displays the gameboard for the user and not the computer.
				yes_no = prompt_for_random();
				switch(yes_no)
				{
					case 1: do// cycles through the random placement of ships until user accepts.
							{
								if (ok_placement == 0)
								{
									create_game_board(game_board_player2);
								}
								place_ships_random(game_board_player2);
								pause_clear();
								display_gameboard(count, player2.player_number, game_board_player2);
								ok_placement = placement_okay();
							} while (ok_placement == 0);
							break;
					case 0: place_ships(game_board_player2, player2.player_number, count); //This is a manual placement of the ships ment for the user.
							break;
				}
				player = who_goes_first(); // Determines the player who goes first, the user or the computer.
				printf("Player %d goes first! \n", player);
				count_down();
				pause_clear();
				do // Simulates the game of between Player and computer. 
				{
					count++; //Increases the count after every 2 shots. 
					do 
					{
						shot_count++;// Increases every shot taken to figure out to use as a restriction on how often it is executed. 
						switch (player)
						{
							case PLAYER1: mirror_opponent_board(game_board_player2, game_board_player2_mirror);
										  display_gameboard(count, player1.player_number, game_board_player2_mirror);
										  take_shot(game_board_player2, PLAYER1, count, hits_on_ships, battleship_log);
										  winner = check_ship_sunk(PLAYER1, hits_on_ships, hits_on_ships2, ships_sunk, ships_sunk2);
										  mirror_opponent_board(game_board_player2, game_board_player2_mirror);
										  Sleep(1250);
										  system("cls");
										  display_gameboard(count, PLAYER1, game_board_player2_mirror);  
										  break;
							case PLAYER2: mirror_opponent_board(game_board_player, game_board_player_mirror);
										  display_gameboard(count, player2.player_number, game_board_player_mirror);
										  take_shot(game_board_player, PLAYER1, count, hits_on_ships2, battleship_log);
										  winner = check_ship_sunk(PLAYER1, hits_on_ships, hits_on_ships2, ships_sunk, ships_sunk2);
										  mirror_opponent_board(game_board_player, game_board_player_mirror);
										  Sleep(1250);
										  system("cls");
										  display_gameboard(count, PLAYER1, game_board_player_mirror);  
										  break;
						}
						player++;
						player = determine_player(player);
						player1.hits = sum_numbers(hits_on_ships, 5);
						player2.hits = sum_numbers(hits_on_ships2, 5);
						count_down();
						pause_clear();
					} while (shot_count < 2 && (player1.hits != 17 && player2.hits != 17));
					shot_count = 0;
				}
				while(player1.hits != 17 && player2.hits != 17);
				if (player1.hits == 17)
				{
					player = PLAYER1;
				}
				else if (player2.hits == 17)
				{
					player = PLAYER2;
				}
				display_winner(player);
				if (shot_count == 1)
				{
					switch(player)
					{
						case PLAYER1: count++;
								      break;
						case PLAYER2: count++;
					}
				}
				player1.misses = count - player1.hits;
				player2.misses = count - player2.hits;
				display_statistics(battleship_log, player1.player_number, player1.hits, player1.misses);
				display_statistics(battleship_log, player2.player_number, player2.hits, player2.misses);
				break;
		case 4: system("cls");
				display_exit_message();
				exit(1);
	}
	fclose(battleship_log);
}