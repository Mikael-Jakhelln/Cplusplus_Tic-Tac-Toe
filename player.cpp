/* 	Written by: Mikael Jakhelln, HIOA-studentnr: s169961
	Tic-Tac-Toe, n pieces on a row to win, with n sized gameboard.
*/
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
namespace tictactoe{
	class player
	{
		private:
		int playernumber; //playernumber, used to find who goes first in a turn.
		char playerpiece; //this players piece, player1.playerpiece = 'X', player2.playerpiece='O'.
		int difficulty;
		bool human;
		
		//abstract class player, can be both human and bot, maybe even a networked human?
		public:
		player() //used so im able to create object post initialization
		{
			//do nothing
		}
		
		player(int pn, bool humanornot) //constructor, used to initialize playernumber and playerpiece, and also if this player is human
		{
			difficulty = 1;
			playernumber = pn;
			human = humanornot;
			if(playernumber == 1)
			{
				playerpiece = 'X';
			}
			else if(playernumber == 2)
			{
				playerpiece = 'O';
			}
			else
			{
				playerpiece = ' '; // this is not supposed to happen, so init to blank.
				cout<< "DEBUG: playernumber isnt 0 or 2" << endl;
			}
		}
		
		bool ishuman() //used to see if this player is a human, wish i knew how to isinstanceof(human) :/
		{
			return human;
		}
		
		bool setdifficulty(int diff) //set difficulty for this player
		{
			return false;
		}
		int getdifficulty() //returns difficulty
		{
			return difficulty;
		}
		
		int getplayernumber()	//returns playernumber
		{
			return playernumber;
		}
		char getplayerpiece()	//returns playernumber
		{
			return playerpiece;
		}
		
		virtual/*makes player an abstract class*/ vector<int> getcoords(int, vector< vector<char> >)//this is overridden by children classes. returns  two coordinates
		{
			vector<int> c(2);
			c[0] = -1;
			c[1] = -1;
			return c;
		}
	};//end of "abstract" class player
}//end of namespace tictactoe
#include "player_human.cpp"
#include "player_bot.cpp"
//end of player.cpp

//testplayer, not really used for anything
namespace tictactoe{
	class test : public virtual player
	{
		public:
		test(int pn, bool humanornot) 
		: player(pn, humanornot)
		{
			//nothing else to do here..
		}
		
		vector<int> getcoords(int size, vector< vector<char> >)
		{	//gets coordinates as input from player, within the boundaries of the parameter size
			vector<int> coords(2);
			coords[0] = 2;
			coords[1] =1;
			return coords;
		}
	}; //end of class player: test
}//end of namespace tictactoe

//player test, works as it is supposed to 
//make a non abstract test player
/*
using namespace std;
using namespace tictactoe;
int main()
{
	//initialize the two parameters needed, and something to keep the return values in
	int size = 3;
	vector< vector<char> > gb;
	vector<int> c(2);
	
	//test player
	player * player0;
	player0 = new test(1, false);
	cout << "test Player 0: playernumber,playerpiece = " << player0->getplayernumber()<< "," << player0->getplayerpiece() << endl;
	c = player0->getcoords(size, gb);
	cout << "test Player 0. getcoords " << c[0] << "," << c[1] << endl;
	
	//human player
	player * player1 = new human(1, true);
	cout << "human Player 1: playernumber,playerpiece = " << player1->getplayernumber()<< "," << player1->getplayerpiece() << endl;
	c = player1->getcoords(size, gb);
	cout << "human Player 1. getcoords " << c[0] << "," << c[1] << endl;
	
	//bot player
	player * player2 = new bot(1, true);
	player2->setdifficulty(1);
	cout << "bot Player 2: playernumber,playerpiece = " << player2->getplayernumber()<< "," << player2->getplayerpiece() << endl;
	c = player2->getcoords(size, gb);
	cout << "bot Player 2. getcoords " << c[0] << "," << c[1] << endl;
}
//end of test */