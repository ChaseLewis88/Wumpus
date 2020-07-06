/*
Name: Chase Lewis
Date: 2/26/20
Assignment: PA4
Section: 7
*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
using namespace std;

class GameWorld
{
private:
	char game_state[5][5]; // world grid
	int user_x; // for tracking user side to side
	int user_y; // for tracking user up and down
	int score = -3; // start at -3 because initial display neary world function plus 5 will set it to 0
public:
	GameWorld()
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				game_state[i][j] = ' '; // initial empty world is set to single spaces
			}
		}
		random_world(); // fills empty world
	}
	// functions for generating world
	void random_world(); // calls position functions to make random world
	void random_user_position(); // places user in random position
	void random_wampus_position(); // places wampus in random position that is not already taken
	void random_gold_position(); // places gold in random position that is not already taken
	void random_pit_positions(); // places 5-10 pits in random positions that are not already taken

	// functions for while game is playing
	void display_entire_world(); // shows user all squares and what they contain in a text based interface
	void display_visible_world(); // shows user only the squares around the user square
	void display_user_position(); // display only the user position, everything else hidden
	void move_up(); // lets user move up one space
	void move_down(); // lets user move down one space
	void move_right(); // lets user move right one space
	void move_left(); // lets user move left one space
	bool have_i_won(); // checks if user has won. true if so else false
	bool am_i_alive(); // checks if user is alive by seeing if position is shared by wampus or pit. true if alive else false
	void decrement_score(); // take away 5 points from user. a turn loop gives the user 5 points, so 5 need to be taken away if the user made an illegal/losing move
	int get_score(); // grab final score for later printing to file
};

// prints rules
void print_rules();

// displays menu and takes in user option
int menu_select();

// actual game function. creates world, user plays world, determines outcome, prints score to file. returns integer.
// 0 for restarting with same user, 1 for restarting with new user, 2 for quitting
int play_game(char username[]);