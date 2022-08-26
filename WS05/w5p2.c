#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_PATH 70
#define MIN_PATH 10
#define MULTIPLIER 5

// create structure array required for game
struct playerInfo
{
	int num_lives;
	char p_symbol;
	int num_treasure_found;
	int move_history[MAX_PATH];
};

struct gameInfo
{
	int max_moves;
	int path_length;
	int bomb_pos[MAX_PATH];
	int treasure_pos[MAX_PATH];
};


int main(void)
{
	const int min_lives = 1, max_lives = 10;

	int moves_per_turn, i, n, bomb_row, treasure_row, player_move, adj_move;
	char stop;

	int example[15] = { 1,0,0,1,1,1,0,0,1,1,1,0,0,1,1 };

	// initializes the structure for the game
	struct playerInfo player = { 0, '\0', 0, {0} };
	struct gameInfo game = { 0, 0, {0}, {0} };

	printf("================================\n");
	printf("         Treasure Hunt!         \n");
	printf("================================\n\n");

	printf("PLAYER Configuration\n");
	printf("--------------------\n");

	printf("Enter a single character to represent the player: ");
	scanf(" %c", &player.p_symbol);

	do // sets number of lives and keeps within range
	{
		printf("Set the number of lives: ");
		scanf("%d", &player.num_lives);

		if ((player.num_lives < min_lives) || (player.num_lives > max_lives))
		{
			printf("     Must be between %d and %d!\n", min_lives, max_lives);
		}
	} while ((player.num_lives < min_lives) || (player.num_lives > max_lives));

	printf("Player configuration set-up is complete\n\n");

	printf("GAME Configuration\n");
	printf("------------------\n");

	do // sets length of game and keeps within range
	{
		printf("Set the path length (a multiple of %d between %d-%d): ", MULTIPLIER, MIN_PATH, MAX_PATH);
		scanf("%d", &game.path_length);

		// path must be divisible by MULTIPLIER and in range
		if ((game.path_length % MULTIPLIER != 0) || (game.path_length < MIN_PATH) || (game.path_length > MAX_PATH))
		{
			printf("     Must be a multiple of %d and between %d-%d!!!\n", MULTIPLIER, MIN_PATH, MAX_PATH);
		}
	} while ((game.path_length % MULTIPLIER != 0) || (game.path_length < MIN_PATH) || (game.path_length > MAX_PATH));

	do // sets max moves per turn
	{
		printf("Set the limit for number of moves allowed: ");
		scanf("%d", &game.max_moves);

		// sets the max allowed moves to per turn <= 75% of game path length.
		moves_per_turn = 0.75 * game.path_length;

		if ((game.max_moves < player.num_lives) || (game.max_moves > moves_per_turn))
		{
			printf("    Value must be between %d and %d\n", player.num_lives, moves_per_turn);
		}
	} while ((game.max_moves < player.num_lives) || (game.max_moves > moves_per_turn));

	printf("\nBOMB Placement\n");
	printf("--------------\n");
	printf("Enter the bomb positions in sets of %d where a value\n", MULTIPLIER);
	printf("of 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n");
	printf("(Example:");

	//prints number of examples based on MULTIPLIER
	for (i = 0; i < MULTIPLIER; i++)
	{
		printf(" %d", example[i]);
	}
	printf(") NOTE: there are %d to set!\n", game.path_length);

	treasure_row = 0;

	// used to keep track of iterations. 
	bomb_row = 0;
	i = 0;
	n = 0;

	do // records bomb position of player 
	{
		// print statement had to be split else 
		// bomb_row += MULTIPLIER would perform before bomb_row + 1
		// i.e "Positions [ 6-5]:" would display instead of "Position [ 1-5]:"
		printf("   Positions [%2d-", bomb_row + 1);
		printf("%2d]: ", bomb_row += MULTIPLIER);
		i += 1;
		do
		{
			// scans all user input and adds to array until a new line is detected
			scanf("%d%c", &game.bomb_pos[n], &stop);
			n++;
		} while (stop != '\n');
	} while (i < (game.path_length / MULTIPLIER));

	printf("BOMB placement set\n\n");
	printf("TREASURE Placement\n");
	printf("------------------\n");
	printf("Enter the treasure placements in sets of 5 where a value\n");
	printf("of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n");
	printf("(Example:");

	for (i = 0; i < MULTIPLIER; i++)
	{
		printf(" %d", example[i]);
	}
	printf(") NOTE: there are %d to set!\n", game.path_length);
	treasure_row = 0;

	// resets counter for treasure loop
	i = 0;
	n = 0;

	do // records treasure position of player 
	{
		printf("   Positions [%2d-", treasure_row + 1);
		printf("%2d]: ", treasure_row += MULTIPLIER);
		i += 1;
		do
		{
			scanf("%d%c", &game.treasure_pos[n], &stop);
			n++;
		} while (stop != '\n');
	} while (i < (game.path_length / MULTIPLIER));

	printf("TREASURE placement set\n\n");
	printf("GAME configuration set-up is complete...\n\n");
	printf("------------------------------------\n");
	printf("TREASURE HUNT Configuration Settings\n");
	printf("------------------------------------\n");
	printf("Player:\n");
	printf("   Symbol     : %c\n", player.p_symbol);
	printf("   Lives      : %d\n", player.num_lives);
	printf("   Treasure   : [ready for gameplay]\n");
	printf("   History    : [ready for gameplay]\n\n");
	printf("Game:\n");
	printf("   Path Length: %d\n", game.path_length);
	printf("   Bombs      : ");

	for (i = 0; i < game.path_length; i++)
	{
		printf("%d", game.bomb_pos[i]);
	}
	printf("\n");
	printf("   Treasure   : ");

	for (i = 0; i < game.path_length; i++)
	{
		printf("%d", game.treasure_pos[i]);
	}
	printf("\n\n");
	printf("====================================\n");
	printf("~ Get ready to play TREASURE HUNT! ~\n");
	printf("====================================\n");
	printf("\n");
	printf("  "); //spacing

	for (i = 0; i < game.path_length; i++) //display gameboard and player settings
	{
		printf("-");
	}
	printf("\n");
	printf("  ");

	for (i = 1; i <= game.path_length; i++)
	{
		if (i % 10 == 0) //only prints the major ruler
		{
			printf("%d", i/10); 
		}
		else
		{
			printf("|");
		}
	}
	printf("\n");
	printf("  ");
	for (i = 1; i < game.path_length + 1; i++)
	{
		printf("%d", i % 10); // only prints last digit (minor ruler)
	}
	printf("\n");
	printf("+---------------------------------------------------+\n");
	printf("  Lives:  %d  | Treasures:  %d  |  Moves Remaining: %2d\n",
		player.num_lives, player.num_treasure_found, game.max_moves);
	printf("+---------------------------------------------------+\n");
		
	do // actual start of game
	{
		printf("Next Move [1-%d]: ", game.path_length);
		scanf("%d", &player_move);

		while ((player_move < 1) || (player_move > game.path_length))
		{
			printf("  Out of Range!!!\n");
			printf("Next Move [1-%d]: ", game.path_length);
			scanf("%d", &player_move);
		}
		printf("\n");
		adj_move = (player_move - 1); //adjusted to match index array numbering

		// check if player has been to location previously 
		if (player.move_history[adj_move] == 1) 
		{
			printf("===============> Dope! You've been here before!\n\n");
		}
		else
		{
			//sets the element of the move to 1 to indicate player has been there.
			player.move_history[adj_move] = 1;
			game.max_moves -= 1;

			//set conditions for each scenario based on the input move
			if ((game.bomb_pos[adj_move] == 1) && (game.treasure_pos[adj_move] == 1))
			{
				printf("===============> [&] !!! BOOOOOM !!! [&]\n");
				printf("===============> [&] $$$ Life Insurance Payout!!! [&]\n\n");
				player.num_lives -= 1;
				player.num_treasure_found += 1;
			}
			else if ((game.bomb_pos[adj_move] == 1) && 
				(game.treasure_pos[adj_move] == 0))
			{
				printf("===============> [!] !!! BOOOOOM !!! [!]\n\n");
				player.num_lives -= 1;
			}
			else if ((game.bomb_pos[adj_move] == 0) && 
				(game.treasure_pos[adj_move] == 1))
			{
				printf("===============> [$] $$$ Found Treasure! $$$ [$]\n\n");
				player.num_treasure_found += 1;
			}
			else if ((game.bomb_pos[adj_move] == 0) && 
				(game.treasure_pos[adj_move] == 0))
			{
				printf("===============> [.] ...Nothing found here... [.]\n\n");
			}
		}
		if (player.num_lives == 0)
		{
			printf("No more LIVES remaining!\n\n");
		}
		if (game.max_moves == 0)
		{
			printf("No more MOVES remaining!\n\n");
		}

		// formatting and printing player symbol
		printf("  "); 
		for (i = 0; i < adj_move; i++)
		{
			printf(" ");
		}
		printf("%c", player.p_symbol);

		// matrix required us to print the empty spaces after player symbol
		for (i = 1; i < game.path_length - adj_move; i++)
		{
			printf(" ");
		}
		printf("\n");
		printf("  ");

		for (i = 0; i < game.path_length; i++) // iterates every position in the game
		{
			// show symbol at index based on element at index
			if (player.move_history[i] == 0)
			{
				printf("-");
			}
			else if (player.move_history[i] == 1)
			{
				if ((game.bomb_pos[i] == 1) && (game.treasure_pos[i] == 1))
				{
					printf("&");
				}
				else if ((game.bomb_pos[i] == 1) && (game.treasure_pos[i] == 0))
				{
					printf("!");
				}
				else if ((game.bomb_pos[i] == 0) && (game.treasure_pos[i] == 1))
				{
					printf("$");
				}
				else
				{
					printf(".");
				}
			}
		}
		printf("\n");
		printf("  ");
		for (i = 1; i <= game.path_length; i++)
		{
			if (i % 10 == 0) //only prints leading digit (major ruler)
			{
				printf("%d", i / 10);
			}
			else
			{
				printf("|");
			}
		}
		printf("\n");
		printf("  ");

		for (i = 1; i < game.path_length + 1; i++)
		{
			if (i % 10 == 0)
			{
				printf("0");
			}
			else
			{
				printf("%d", i % 10); // prints only last digit (minor ruler)
			}
		}
		printf("\n");
		printf("+---------------------------------------------------+\n");
		printf("  Lives:  %d  | Treasures:  %d  |  Moves Remaining: %2d\n",
			player.num_lives, player.num_treasure_found, game.max_moves);
		printf("+---------------------------------------------------+\n");

	} while ((player.num_lives > 0) && (game.max_moves > 0));
	
	printf("\n##################");
	printf("\n#   Game over!   #");
	printf("\n##################\n");
	printf("\nYou should play again and try to beat your score!");

	return 0;
}