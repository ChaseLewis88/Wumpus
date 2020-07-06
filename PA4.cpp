#include "PA4.h"
// shows user all squares and what they contain in a text based interface
void GameWorld::display_entire_world()
{
	cout << "Entire World:\n";
	cout << "  _______ _______ _______ _______ _______ " << endl; // top of interface
	for (int i = 0; i < 5; i++)
	{
		cout << " |       |       |       |       |       |" << endl << " |   ";
		for (int j = 0; j < 5; j++)
		{
			cout << game_state[i][j] << "   |   "; // reads each letter from 2D array
		}
		cout << endl << " |_______|_______|_______|_______|_______|" << endl; // bottom of interface
	}
	score -= 5; // using this costs 5 points
}

// shows user only the squares around the user square
void GameWorld::display_visible_world()
{
	cout << "Nearby World:\n";
	cout << "  _______ _______ _______ _______ _______ " << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << " |       |       |       |       |       |" << endl << " |   ";
		for (int j = 0; j < 5; j++)
		{
			if ((user_y - i < 2 && user_y - i > -2) && (user_x - j < 2 && user_x - j > -2)) // checks if current square is within one square of user
			{
				cout << game_state[i][j] << "   |   "; // displays the square if it is in range
			}
			else
			{
				cout << " " << "   |   "; // displays an empty space if it should be hidden
			}
		}
		cout << endl << " |_______|_______|_______|_______|_______|" << endl;
	}
	score -= 2; // using this costs 2 points
}

// display only the user position, everything else hidden
void GameWorld::display_user_position()
{
	cout << "User view:\n";
	cout << "  _______ _______ _______ _______ _______ " << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << " |       |       |       |       |       |" << endl << " |   ";
		for (int j = 0; j < 5; j++)
		{
			if (game_state[i][j] == 'U') // displays U
			{
				cout << game_state[i][j] << "   |   ";
			}
			else
			{
				cout << " " << "   |   "; // everything else is displayed as empty space
			}
		}
		cout << endl << " |_______|_______|_______|_______|_______|" << endl;
	}
}

// lets user move up one space
void GameWorld::move_up()
{
	if (user_y == 0) // checks if user is already in the upmost row
	{
		cout << "You cannot move out of bounds. Please choose a different option\n";
		decrement_score(); // 5 is always added after every move, so 5 should be taken away since this not a real move
		return;
	}
	game_state[user_y][user_x] = ' '; // old user space becomes empty
	user_y -= 1; // user y coordinate decreases by 1, (moves upward)
	
	if (game_state[user_y][user_x] == ' ') // new coordinate becomes U if it is empty
		game_state[user_y][user_x] = 'U';
}

// lets user move down one space
void GameWorld::move_down()
{
	if (user_y == 4) // checks if user is already in bottom row
	{
		cout << "You cannot move out of bounds. Please choose a different option\n";
		decrement_score();
		return;
	}
	game_state[user_y][user_x] = ' ';
	user_y += 1;

	if (game_state[user_y][user_x] == ' ')
		game_state[user_y][user_x] = 'U';
}

// lets user move right one space
void GameWorld::move_right()
{
	if (user_x == 4) // checks if user is already in rightmost collumn
	{
		cout << "You cannot move out of bounds. Please choose a different option\n";
		decrement_score();
		return;
	}
	game_state[user_y][user_x] = ' ';
	user_x += 1;

	if (game_state[user_y][user_x] == ' ')
		game_state[user_y][user_x] = 'U';
}

// lets user move left one space
void GameWorld::move_left()
{
	if (user_x == 0) // checks if user is already in leftmost collumn
	{
		cout << "You cannot move out of bounds. Please choose a different option\n";
		decrement_score();
		return;
	}
	game_state[user_y][user_x] = ' ';
	user_x -= 1;

	if (game_state[user_y][user_x] == ' ')
		game_state[user_y][user_x] = 'U';
}

// checks if user has won. true if so else false
bool GameWorld::have_i_won()
{
	if (game_state[user_y][user_x] == 'G')
	{
		return true;
	}
	return false;
}

// checks if user is alive by seeing if position is shared by wampus or pit. true if alive else false
bool GameWorld::am_i_alive()
{
	if (game_state[user_y][user_x] == 'W') // share space with wampus
	{
		cout << "You were killed by the Wampus!\n";
		cout << "Score: " << score << endl;
		return false;
	}
	if (game_state[user_y][user_x] == 'P') // share space with pit
	{
		cout << "You fell into a pit!\n";
		cout << "Score: " << score << endl;
		return false;
	}
	score += 5;
	cout << "Score: " << score << endl;
	return true;
}

// calls position functions to make random world
void GameWorld::random_world()
{
	random_user_position();
	random_wampus_position();
	random_gold_position();
	random_pit_positions();
}

// places user in random position
void GameWorld::random_user_position()
{
	// random coordinates
	user_y = rand() % 5;
	user_x = rand() % 5;
	game_state[user_y][user_x] = 'U';
}

// places wampus in random position that is not already taken
void GameWorld::random_wampus_position()
{
	int y, x;
	do {
		y = rand() % 5;
		x = rand() % 5;
	} while (game_state[y][x] != ' '); // loop if space already taken
	game_state[y][x] = 'W';
}

// places gold in random position that is not already taken
void GameWorld::random_gold_position()
{
	int y, x;
	do {
		y = rand() % 5;
		x = rand() % 5;
	} while (game_state[y][x] != ' ');
	game_state[y][x] = 'G';
}

// places 5-10 pits in random positions that are not already taken
void GameWorld::random_pit_positions()
{
	int pit_count = rand() % 6 + 5; // random num of pits
	for (int i = 0; i < pit_count; i++) // loop pit number of times
	{
		int y, x;
		do {
			y = rand() % 5;
			x = rand() % 5;
		} while (game_state[y][x] != ' '); // loop if space already taken
		game_state[y][x] = 'P';
	}
}

// take away 5 points from user. a turn loop gives the user 5 points, so 5 need to be taken away if the user made an illegal/losing move
void GameWorld::decrement_score()
{
	score -= 5;
}

// grab final score for later printing to file
int GameWorld::get_score()
{
	return score;
}

// prints rules
void print_rules()
{
	cout << "You are in a cave attempting to find the gold. You must navigate the cave in order to find the gold. However, if you fall in a pit or run into the wampus then you will die.\n"
		<< "You start out being able to see your location and what is nearby, with all other spaces being hidden. In subsequent turns, you only know your own position.\n"
		<< "But, you can use certain cheats to see the world at a cost to your final score. With each move you make, your score goes up by 5.\n"
		<< "If you find the gold, your score is saved under your username. If you die or quit, your score is lost.\n"
		<< "Good luck!\n\n";
}

// displays menu and takes in user option
int menu_select()
{
	int option = 0;

	cout << "Please enter an option:\n\n"
		<< "1. Print Game Rules\n"
		<< "2. Play Game\n"
		<< "3. Exit\n";

	cin >> option;

	return option;
}

// actual game function. creates world, user plays world, determines outcome, prints score to file. returns integer.
// 0 for restarting with same user, 1 for restarting with new user, 2 for quitting
int play_game(char username[])
{
	GameWorld game_world; // creates world

	game_world.display_visible_world(); // show nearby world in the beginning at no point cost

	char option; // for user input

	while (game_world.am_i_alive() == true && game_world.have_i_won() == false) // loop continues if user has not won or lost yet
	{
		game_world.display_user_position(); // show user position at start of every turn
		// tells user their options
		cout << "Please choose an option:\n\n"
			<< "I. Move Up\n"
			<< "K. Move Down\n"
			<< "J. Move Left\n"
			<< "L. Move Right\n"
			<< "V. Display Adjacent Caves\n"
			<< "C. Cheat and Display All Caves\n"
			<< "R. Restart with Same Player\n"
			<< "N. Restart with New Player\n"
			<< "Q. Quit Game\n";

		cin >> option;
		system("cls");
		// call function based on user input. move, display world, quit, etc. not case sensitive
		switch (option)
		{
		case 'I':
		case 'i':
			game_world.move_up();
			break;
		case 'K':
		case 'k':
			game_world.move_down();
			break;
		case 'J':
		case 'j':
			game_world.move_left();
			break;
		case 'L':
		case 'l':
			game_world.move_right();
			break;
		case 'V':
		case 'v':
			game_world.display_visible_world();
			game_world.decrement_score(); // not a real turn, so 5 points are taken away
			break;
		case 'C':
		case 'c':
			game_world.display_entire_world();
			game_world.decrement_score(); // not a real turn, so 5 points are taken away
			break;
		case 'R':
		case 'r':
			cout << "You restarted as the same player.\n";
			return 0; // returns 0 so that loop outside this function can proceed without prompting for a username
			break;
		case 'N':
		case 'n':
			cout << "You restarted as a new player.\n";
			return 1; // returns 1 so that loop outside this function prompts for a username
			break;
		case 'Q':
		case 'q':
			cout << "You quit early.\n";
			return 2; // returns 2 so that loop outside this function ends and program returns to main menu
			break;
		default:
			cout << "That is not an option.\n";
			game_world.decrement_score(); // not a real turn, so 5 points are taken away
			break;
		}

	}

	// only print out the score if the user won
	if (game_world.have_i_won() == true)
	{
		ofstream outfile;
		outfile.open("GameScores.txt", ios_base::app); // for appending to file
		outfile << username << ": " << game_world.get_score() << endl; // writes username and score to file
		cout << "You found the gold!\n"; // tells user they won
		cout << "Your score has been recorded.\n";
	}

	game_world.display_entire_world(); // show user the whole world at the end
	
	system("pause"); // waits for user to finish looking at results before proceeding
	return 0; // automatically restarts a new game with same user
}

