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
void display_menu(int *menu_response)
{
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(hStdout,  0x0006);
	line_sep();//printf("===============================================================================\n" );
	SetConsoleTextAttribute(hStdout,  0x0009);
	printf(" _____   _____   _____   _____   __     _____   ____   _   _   _____   ______\n");
	printf("|  _  | |  _  | |     | |     | |  |   |  ___| |    | | | | | |     | |  __  |\n");
	printf("| |_| | | |_| | |_   _| |_   _| |  |   |  |__  |  __| | |_| | |__ __| | |__| |\n");
	printf("|  _  | |  _  |   | |     | |   |  |   |   __| |___ | |  _  |  _| |_  |  ____|\n");
	printf("| |_| | | | | |   | |     | |   |  |_  |  |__  |    | | | | | |     | | |\n");
	printf("|_____| |_| |_|   |_|     |_|   |____| |_____| |____| |_| |_| |_____| |_|\n\n");
	line_sep();  //printf("===============================================================================\n\n");
	printf("                           ** Welcome to Battleship! **\n\n");
	printf("    1] Rules of Battleship\n    2] Play VS Computer\n    3] Play VS Friend\n    4] Exit\n\n");
	line_sep()   ;//printf("===============================================================================\n");
	printf("     What would you like to do? ");
	scanf(" %d", menu_response);
	printf("\n");
	if ((*menu_response > 4) || (*menu_response < 1))
	{
		system("cls");
		display_menu(menu_response);
	}


}
void display_exit_message(void)
{
	line_sep(); //printf("===============================================================================\n\n");
	printf("                           Thanks for playing! \n\n");
	line_sep(); //printf("===============================================================================\n\n");
}
void display_rules(void)
{
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	line_sep();
	printf("\nRules: Each player will place their ships on their own gameboard, any way they \n       choose");
	printf("so long as there is no over lapping of their own boats or a boat \n       placed out of");
	printf("bounds. Once each player has set their boats the first \n       player will be determined");
	printf("at random and the game will then commence.\n");
	SetConsoleTextAttribute(hStdout, 0x0003);
	printf("\nThe objective is to sink all of your opponents ships before they can sink YOURS!\n");
	SetConsoleTextAttribute(hStdout, 0x0007);
	printf("       Each player will then take turns calling out a position on the gameboard.");
	printf("       Every shot that is called out will be marked and announced as a 'hit' or\n       'miss'.");
	printf("Each time a ship is sunk, the player will announce which ship has\n       been sunk. Once");
	printf(" all of a players ships have been sunk the winner will be\n       announced.\n\n");
	line_sep();
}
void display_winner(int player)
{
	line_sep();
	printf("\n                                 PLAYER %d WINS!!!!!\n", player);
	line_sep();
}
void display_statistics(FILE* outfile, int player, int hits, int misses)
{
	double ratio = 0.0, total = 0.0;
	int total_shots = 0;
	total_shots = hits + misses;
	total = hits + misses;
	ratio = hits/ total;
	printf("\n   *** PLAYER %d ***\n", player);
	printf("  Hits: %d\n", hits);
	printf("  Misses: %d\n", misses);
	printf("  Shots taken: %d\n", total_shots);
	printf("  Hit/Miss ratio: %lf\n", ratio);
	fprintf(outfile, "   *** PLAYER %d ***\n", player);
	fprintf(outfile, "  Hits: %d\n", hits);
	fprintf(outfile,"  Misses: %d\n", misses);
	fprintf(outfile,"  Shots taken: %d\n", total_shots);
	fprintf(outfile,"  Hit/Miss ratio: %lf\n", ratio);
	

}
void pause_clear(void)
{
	system("pause");
	system("cls");
}
void create_game_board(char game_board[Y_AXIS][X_AXIS])
{
	int index = 0, index_2 = 0;
	for (index = 0; index < X_AXIS; index++)
	{
		for (index_2 = 0; index_2 < Y_AXIS; index_2++)
		{
			game_board[index][index_2] = '~';
		}
	}
}
void display_gameboard(int count, int player, char game_board[Y_AXIS][X_AXIS])
{
	int index = 0, index_2 = 0;
	HANDLE hStdout;

	if (count != 0)
	{
		printf(" ============= Player %d's turn! ==========[Shot %d]===\n\n", player, count);
	}
	else if (count == 0)
	{
		printf(" ====================== Player %d =====================\n\n", player);
	}
	
 
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
   
	printf("                   1 2 3 4 5 6 7 8 9 10\n");
	printf("                 +---------------------+\n");
	for (index = 0; index < X_AXIS; index++)
	{
		printf("               %c |", 'A' + index); 
		for (index_2 = 0; index_2 < Y_AXIS; index_2++)
		{
			SetConsoleTextAttribute(hStdout,  FOREGROUND_BLUE);
			if (game_board[index][index_2] < 90 && game_board[index][index_2] > 64)
			{
				SetConsoleTextAttribute(hStdout, 0x0007);
			}
			else if (game_board[index][index_2] == 42)
			{
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
			}
			else if(game_board[index][index_2] == 109)
			{
				SetConsoleTextAttribute(hStdout, 0x0003);
			}
			printf(" %c", game_board[index][index_2]); 
			SetConsoleTextAttribute(hStdout,  0x0007);
		}
		printf(" | \n");
	}
	printf("                 +---------------------+\n\n");
	printf(" ======================================================\n");

}
int prompt_for_random(void)
{
	char response = 0;
	int yes_no = -1;
	do
	{
		printf("Would you like randomly generated ships? [y/n] ");
		scanf(" %c", &response);
		response = toupper(response);
		switch(response)
		{
			case 'Y': yes_no = 1;
					  break;
			case 'N': yes_no = 0;
					  break;
			default:  yes_no = -1;
		}
	} while (yes_no == -1);
	return yes_no;
}
int placement_okay(void)
{
	char response = 0;
	int yes_no = -1;
	do
	{
		printf("Is this placement fine? [y/n] ");
		scanf(" %c", &response);
		response = toupper(response);
		switch(response)
		{
			case 'Y': yes_no = 1;
					  break;
			case 'N': yes_no = 0;
					  break;
			default:  yes_no = -1;
		}
	} while (yes_no == -1);
	return yes_no;
}
void mirror_opponent_board(char game_board_computer[Y_AXIS][X_AXIS], char game_board_mirror[Y_AXIS][X_AXIS])
{
	int index = 0, index2 = 0;
	for (index = 0; index < Y_AXIS; index++)
	{
		for (index2 = 0; index2 < X_AXIS; index2++)
		{
			if (game_board_computer[index][index2] > 'A' && game_board_computer[index][index2] < 'Z')
			{
				game_board_mirror[index][index2] = '~';
			}
			else if (game_board_computer[index][index2] == '*' || game_board_computer[index][index2] == 'm')
			{
				game_board_mirror[index][index2] = game_board_computer[index][index2];
			}
		}
	}
}
void place_ships(char game_board[Y_AXIS][X_AXIS], int player, int count)
{
	int index = 0, index2 = 0, number = 0, checked_orientation = 0, checked_position = 0, xy[3] = {0}, length = 0,
		ship_index = 0, ship_length[5] = {5, 4, 3, 3, 2};
	char position[50] = {0, 0, '0'}, orientation[50], 
		ships[5][50] = {"AIRCRAFT CARRIER[5]", "BATTLESHIP[4]", "DESTROYER[3]", "SUBMARINE[3]", "PATROL BOAT[2]"},
		ship_character;

	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	for (index = 0; index < 5 ; index++)
	{
		do 
		{
			if (checked_orientation == -1 || checked_position == -1)
			{
				SetConsoleTextAttribute(hStdout, FOREGROUND_RED);
				printf("\nPlay fair you cheater!\n");
				SetConsoleTextAttribute(hStdout, 0x0007);
				pause_clear();
				display_gameboard(count, player, game_board);
			}
			printf("\nStart %s at what position? ", ships[index]);
			scanf("%s", position);
			position[0] = toupper(position[0]);
			xy[0] = char_to_int(position[0]) - 1;
			xy[1] = position[1] - '0' - 1;
			for (index2 = 0; position[index2]; index2++);
			length = index2;
			xy[2] = position[2];
			
			if (((xy[2] > 0) || (xy[2] < 0)) || (length > 3))
			{
				if ((xy[2] - '0') == 0)
				{
					xy[1] = 9;
				}
				else
				{
					xy[1] = -1;
				}
				
			}
			checked_position = check_position(xy, game_board);
			printf("What orientation? [up, down, left, right] ");
			scanf("%s", orientation);
			length = change_to_upper(orientation);
			checked_orientation = check_orientation(xy, index, length, orientation, game_board); 

		} 
		while ((checked_orientation == -1) || (checked_position == -1));

		switch(index)
		{
			case 0: ship_character = CARRIER;
					break;
			case 1: ship_character = BATTLESHIP;
					break;
			case 2: ship_character = DESTROYER;
					break;
			case 3: ship_character = SUBMARINE;
					break;
			case 4: ship_character = PATROL_BOAT;
		}

		for (ship_index = 0; ship_index < ship_length[index]; ship_index++)
		{
			if (strcmp(orientation, "UP") == 0)
			{
				game_board[xy[0] - ship_index][xy[1]] = ship_character; 
			}
			else if (strcmp(orientation, "DOWN") == 0)
			{
				game_board[ship_index + xy[0]][xy[1]] = ship_character;
			}
			else if (strcmp(orientation, "LEFT") == 0)
			{
				game_board[xy[0]][xy[1] - ship_index ] = ship_character;
			}
			else if (strcmp(orientation, "RIGHT") == 0 )
			{
				game_board[xy[0]][ship_index + xy[1]] = ship_character;
			}
		}
		pause_clear();
		display_gameboard(count, player, game_board);
	}
	
}
void place_ships_random(char game_board[Y_AXIS][X_AXIS])
{
	int index = 0, index2 = 0, random_direction = 0, xy[2] = {0}, ship_length[5] = {5, 4, 3, 3, 2},
		checked_orientation = 0, checked_position;
	char ships_letters[5] = {CARRIER, BATTLESHIP, DESTROYER, SUBMARINE, PATROL_BOAT}, ship = ' ',
		orientation[10] = {0};

	for (index = 0; index < 5; index++)
	{
		do
		{
			random_direction = (rand() % 4);
			switch(random_direction)
			{
				case UP: xy[0] = (rand() % 10);
						 xy[1] = (rand() % 10);
						 checked_position = check_position(xy, game_board);
						 checked_orientation = check_orientation(xy, index, 3, "UP", game_board);
						 break;
				case DOWN: xy[0] = (rand() % 10);
						   xy[1] = (rand() % 10);
						   checked_position = check_position(xy, game_board);
						   checked_orientation = check_orientation(xy, index, 3, "DOWN", game_board);
						   break;
				case LEFT: xy[0] = (rand() % 10);
						   xy[1] = (rand() % 10);
						   checked_position = check_position(xy, game_board);
						   checked_orientation = check_orientation(xy, index, 3, "LEFT", game_board);
						   break;
				case RIGHT: xy[0] = (rand() % 10);
						    xy[1] = (rand() % 10);
						    checked_position = check_position(xy, game_board);
						    checked_orientation = check_orientation(xy, index, 3, "RIGHT", game_board);
						    break;
			}

		}
		while (checked_orientation == -1 || checked_position == -1);

		ship = ships_letters[index];

		for (index2 = 0; index2 < ship_length[index]; index2++)
		{
			switch(random_direction)
			{
				case UP: game_board[xy[0] - index2][xy[1]] = ship; 
						 break;
				case DOWN: game_board[index2 + xy[0]][xy[1]] = ship;
						 break;
				case LEFT: game_board[xy[0]][xy[1] - index2 ] = ship;
						 break;
				case RIGHT: game_board[xy[0]][index2 + xy[1]] = ship;
			}
		}
	}
	//display_gameboard(0, 0, game_board);
	//system("pause");
}
void take_shot(char game_board_other_player[Y_AXIS][X_AXIS], int player, int count, int counter_of_hits_on_ships[5], FILE* outfile)
{
	char coordinates[50] = {0,0,'0'}, coordinates_computer[4] = {0, 0, 0}, character, character_of_ship, 
		characters_of_ships[5] = {CARRIER, BATTLESHIP, DESTROYER, SUBMARINE, PATROL_BOAT};
	int  xy[3] = {0}, checked_shot = 0, index = 0, length = 0;

	if (player == 1)
	{
		do 
		{
			if (checked_shot == -2)
			{
				printf("Capitan we have already fired there!\n"); 
			}
			printf("Awaiting orders...\n");
			printf("Enter coordinates: ");
			scanf(" %s", coordinates);
			coordinates[0] = toupper(coordinates[0]);
			xy[0] = char_to_int(coordinates[0]) - 1;
			xy[1] = coordinates[1] - '0' - 1;
			for (index = 0; coordinates[index]; index++);
			length = index;
			xy[2] = coordinates[2];
			
			if (((xy[2] > 0) || (xy[2] < 0)) || (length > 3))
			{
				if ((xy[2] - '0') == 0)
				{
					xy[1] = 9;
				}
				else
				{
					xy[1] = -1;
				}
				
			}

			checked_shot = check_shot(xy, game_board_other_player);
		}
		while (checked_shot == -1 || checked_shot == -2);
		switch(checked_shot)
		{
			case 0: game_board_other_player[xy[0]][xy[1]] = MISS;
					printf("%s was a miss!\n", coordinates);
					write_move_outfile(outfile, player, count, coordinates, checked_shot);
					break;
			case 1: character_of_ship = game_board_other_player[xy[0]][xy[1]];
					game_board_other_player[xy[0]][xy[1]] = HIT;
					printf("%s was a hit!\n", coordinates);
					write_move_outfile(outfile, player, count, coordinates, checked_shot);
					break;
		}
		for (index = 0; index < 5 && checked_shot == 1; index++)
		{
			if (character_of_ship == characters_of_ships[index])
			{
				counter_of_hits_on_ships[index]++;
			}
		}

	}
	else if (player == 2)
	{
		do
		{
			xy[0] = rand() % 10;
			xy[1] = rand() % 10;
			checked_shot = check_shot(xy, game_board_other_player);
		}
		while (checked_shot == -1 || checked_shot == -2);
		character = (xy[0] + 'A');
		printf("Player 2 fires at %c%d!\n", character, xy[1] + 1 );
		Sleep(1000);
		coordinates_computer[0] = character;
		coordinates_computer[1] = xy[1] + 1 + '0';
		if (coordinates_computer[1] == ':')
		{
			coordinates_computer[1] = '1';
			coordinates_computer[2] = '0';
		}

		switch(checked_shot)
		{
			case 0: game_board_other_player[xy[0]][xy[1]] = MISS;
					printf("%s was a miss!\n", coordinates_computer);
					write_move_outfile(outfile, player, count, coordinates_computer, checked_shot);
					break;
			case 1: character_of_ship = game_board_other_player[xy[0]][xy[1]];
					game_board_other_player[xy[0]][xy[1]] = HIT;
					printf("%s was a hit!\n", coordinates_computer);
					write_move_outfile(outfile, player, count, coordinates_computer, checked_shot);
					break;
		}
		for (index = 0; index < 5 && checked_shot == 1; index++)
		{
			if (character_of_ship == characters_of_ships[index])
			{
				counter_of_hits_on_ships[index]++;
			}
		}
	}
}
int check_shot(int coordinates[2], char game_board[Y_AXIS][X_AXIS])
{
	if ((coordinates[0] >= 0) && (coordinates[0] < (Y_AXIS)))
	{
		if ((coordinates[1] >= 0) && (coordinates[1] < (X_AXIS)) && (game_board[coordinates[0]][coordinates[1]] == '~'))
		{
			return 0;
		}
		else if (game_board[coordinates[0]][coordinates[1]] != '~')
		{
			if ((game_board[coordinates[0]][coordinates[1]] == '*') || (game_board[coordinates[0]][coordinates[1]] == 'm'))
			{
				return -2;
			}
			else
				return 1;
		}
	}
	else
	{
		return -1;
	}

}
int check_position(int coordinates[2], char game_board[X_AXIS][Y_AXIS])
{
	if ((coordinates[0] >= 0) && (coordinates[0] < (Y_AXIS)))
	{
		if ((coordinates[1] >= 0) && (coordinates[1] < (X_AXIS)) && (game_board[coordinates[0]][coordinates[1]] == '~'))
		{
			return 1;
		}
		else
			return -1;
	}
	else
	{
		return -1;
	}
}
int number_ships_sunk(int hits_on_ship[5], int ships_sunk[5])
{
	int ships[5] = {5, 4, 3, 3, 2}, index = 0, ship = 0;

	for (index = 0; index < 5; index++)
	{
		if (hits_on_ship[index] == ships[index])
		{
			ship++;
			ships_sunk[index] = 1;
		}
	}
	return ship;
}
int check_orientation(int coordinates[2], int ship, int length, char orientation[30], char game_board[Y_AXIS][X_AXIS])
{
	char orientations[4][10] = {"UP", "DOWN", "LEFT", "RIGHT"};
	int ships[5] = {5, 4, 3, 3, 2};
	int index = 0, direction = 1, new_value_y = 0, new_value_x = 0, accumulator = 0;
	
	if (length < 6 && length > 1)
	{
	    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//For the UP orientation
		if (strcmp(orientation, orientations[0]) == 0)
		{
			new_value_y = coordinates[0] - ships[ship] + 1;
			for (index = new_value_y; (coordinates[0] >= index) && (new_value_y < 10) && (new_value_y >= 0); index++)
			{
				if (game_board[index][coordinates[1]] == '~')
				{
					accumulator += 1;
				}
				else
				{
					break;
				}
			}
			if (accumulator == ships[ship])
			{
				return 1;
			}
			else
				return -1;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//For the DOWN orientation
		else if (strcmp(orientation, orientations[1]) == 0)
		{
			new_value_y = coordinates[0] + ships[ship] - 1;
			
			for (index = coordinates[0]; (index <= new_value_y) && (new_value_y < 10) && (new_value_y >= 0); new_value_y--)
			{
				if (game_board[new_value_y][coordinates[1]] == '~')
				{
					accumulator += 1;
				}
				else
				{
					break;
				}
			}
			if (accumulator == ships[ship])
			{
				return 1;
			}
			else
				return -1;
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//For the LEFT orientation
		else if (strcmp(orientation, orientations[2]) == 0)
		{
			new_value_x = coordinates[1] - ships[ship] + 1;
			for (index = coordinates[1]; (index >= new_value_x) && (new_value_x < 10) && (new_value_x >= 0); index--)
			{
				if (game_board[coordinates[0]][index] == '~')
				{
					accumulator += 1;
				}
				else
				{
					break;
				}
			}
			if (accumulator == ships[ship])
			{
				return 1;
			}
			else
				return -1;
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//For the RIGHT orientation
		else if (strcmp(orientation, orientations[3]) == 0)
		{
			new_value_x = coordinates[1] + ships[ship] - 1;
			for (index = coordinates[1]; (index <= new_value_x) && (new_value_x < 10) && (new_value_x >= 0); index++)
			{
				if (game_board[coordinates[0]][index] == '~')
				{
					accumulator += 1;
				}
				else
				{
					break;
				}
			}
			if (accumulator == ships[ship])
			{
				return 1;
			}
			else
				return -1;
		}
		else
			return -1;
	}
	else
		return -1;
}
int change_to_upper(char string[])
{
	int index = 0, length = 0, direction = 0;
	

	for (index = 0; string[index]; index++);

	length = index;

	for (index = 0; index < length; index++)
	{
		string[index] = toupper(string[index]);
	}
	return length;
}
int is_winner(int total_ships_sunk_of_player1, int total_ships_sunk_of_player2)
{
	if (total_ships_sunk_of_player1 == 5)
	{
		return PLAYER1;
	}
	else if(total_ships_sunk_of_player1 == 5)
	{
		return PLAYER2;
	}
	else 
	{
		return -1;
	}
}
int char_to_int(char axis)
{
	int number = 0;
	switch(axis)
	{
		case 'A': number = 1;
			      break;
		case 'B': number = 2;
			      break;
		case 'C': number = 3;
			      break;
		case 'D': number = 4;
			      break;
		case 'E': number = 5;
			      break;
		case 'F': number = 6;
			      break;
		case 'G': number = 7;
			      break;
		case 'H': number = 8;
			      break;
		case 'I': number = 9;
			      break;
		case 'J': number = 10;
			      break;
	}
	return number;
}
void line_sep(void)
{
	HANDLE hStdout;
	int i = 0;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
	
	for (i = 2; i < 81; i++)
	{
		if (i % 2 == 0)
		{
			SetConsoleTextAttribute(hStdout,  0x0004);
		}
		else if (i % 2 == 1)
		{
			SetConsoleTextAttribute(hStdout,  0x0007);
		}
		printf("=");
	}
	printf("\n");
	SetConsoleTextAttribute(hStdout, 0x0007);
}
int sum_numbers(int list[], int length)
{
	int index = 0, sum = 0;
	for (index = 0; index < length; index++)
	{
		sum +=list[index];
	}
	return sum;
}
int who_goes_first(void)
{
	int player = 0;
	player = (rand() % 2) + 1;
	return player;
}
int determine_player(int player)
{
	if (player > 2)
	{
		player = 1;
		return player;
	}
	else
		return player;
}
int check_ship_sunk(int player, int hits_on_ships[5], int hits_on_ships2[5], int ships_sunk[5], int ships_sunk2[5])
{
	int total_sunk = 0, total_sunk2 = 0, winner = 0, index = 0;
	char ship_names[5][50] = {"CARRIER","BATTLESHIP", "DESTROYER", "SUBMARINE", "PATROL BOAT"}; 

	switch(player)
	{
		case 1: total_sunk = number_ships_sunk(hits_on_ships, ships_sunk);
				for (index = 0; index < 5; index++)
				{
					if (ships_sunk[index] == 1)
					{
						printf("Player 2's %s has been sunk!\n", ship_names[index]);
					}
				}
		case 2: total_sunk2 = number_ships_sunk(hits_on_ships2, ships_sunk2);
				for (index = 0; index < 5; index++)
				{
					if (ships_sunk2[index] == 1)
					{
						printf("Player 1's %s has been sunk!\n", ship_names[index]);
					}
				}
	}
	winner = is_winner(total_sunk, total_sunk2);
	return winner;

}
FILE* open_outfile(void)
{
	FILE* battleship_log = NULL;
	battleship_log = fopen("battleship.log", "w");
	return battleship_log;
}
void write_move_outfile(FILE* outfile, int player, int count, char move[], int hit_or_miss)
{
	char miss_or_hit[5] = {0}, hit[4] = {"HIT"}, miss[5] = {"MISS"};
	switch(hit_or_miss)
	{
		case 1: strcpy(miss_or_hit, hit);
				fprintf(outfile, "Player %d || Shot %d: %s || %s\n", player, count, move, miss_or_hit); 
				break;
		case 0: strcpy(miss_or_hit, miss);
				fprintf(outfile, "Player %d || Shot %d: %s || %s\n", player, count, move, miss_or_hit); 
				break;
	}
}
void count_down(void)
{
	int index = 0;
	for (index = 5; index > 0; index--)
	{
		system("cls");
		printf("Next player's turn in...%d", index);
		Sleep(500);
	}
	putchar('\n');
}

/*int change_color( void )
{
 
    HANDLE hStdout;
 
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout,  BACKGROUND_BLUE);
 
    return 0;
}*/