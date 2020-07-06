#include "PA4.h"

int main(void)
{
	// makes random values actually random
	srand(time(NULL));

	// intro
	cout << "Welcome to Hunt the Wumpus!\n\n";

	// initializations for exiting program and taking user input
	int keep_playing = 1, option = 0;
	char username[30];
	int play;

	// starts as true so that first loop starts
	while (keep_playing == 1)
	{
		// input validation on menu selection
		do {
			option = menu_select();
			if (option > 3 || option < 1)
			{
				cout << "That is not an option. You must choose option 1, 2 or 3.\n\n";
			}
		} while (option > 3 || option < 1);

		// cleaning screen
		system("cls");

		// depending on input, either prints rules, plays game, or exits
		switch (option)
		{
		case 1:
			// prints rules, then return to menu
			print_rules();
			break;
		case 2:
			play = 1; // in the first loop, play is 1 so that user must enter username
			while (play == 0 || play == 1) // loop continues unless play_game function returns 2, meaning the user quit
			{
				if (play == 1) // if first loop or if user chose to restart as new user, this loop executes
				{
					cout << "Please enter your username: ";
					cin >> username;
				}
				// plays game, then returns to menu afterwards
				play = play_game(username); // user choice to restart as same player, restart as new player, or quit is stored in play
				system("cls");
			}
			break;
		case 3:
			// loop condition no longer satisfied, so program ends
			cout << "Thanks for playing!";
			keep_playing = 0;
			break;
		}
	}
	return 0;
}