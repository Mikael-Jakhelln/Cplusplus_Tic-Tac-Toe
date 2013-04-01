//#include "player.cpp" //used for test in this file
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
namespace tictactoe{
	class bot: public virtual player
	{
		private: 
		int difficulty;	//to set bot difficulty
		char opponentpiece;	//the opponents piece.
		
		public:
		bot(int pn) 
		: player(pn)
		{
			difficulty = 0; //default difficulty is set to easy
			if(getplayerpiece() == 'X')
				opponentpiece = 'O';
			if(getplayerpiece() == 'O')
				opponentpiece = 'X';
			srand(time(NULL));	//seed random, so it doesnt give the same values every time
		}
		
		void setdifficulty(int diff) //set difficulty for this bot
		{
			difficulty = diff;
		}
		int getdifficulty() //returns difficulty
		{	return difficulty; }
		
		
		vector<int> getcoords(int size, vector< vector<char> > board)
		{
			//this should analyse the gameboard, then make the best possible move :P, should also not make a move that doesnt work
			if(difficulty == 0) //if EZ-mode: just return some random coords untill something hits. (mostly for debug)
			{
				return randommove(size);
			}
			else if(difficulty == 1)
			{
				return bettermove(size, board);
			}
			else if(difficulty < 0 || difficulty > 1 ) //difficulties above 2 are not implemented yet. insert even better algorithm here..
			{
				cout << "DEBUG: bot difficulty level " << difficulty << " is not implemented! do randommove.";
				return randommove(size);
			}
		}
		
		vector<int> randommove(int size)
		{
			vector<int> c(2); 
				c[0]=rand()%(size+1);
				c[1]=rand()%(size+1);
				while(c[0] > size || c[1] > size || c[0] == 0 || c[1] == 0)
				{	
					c[0]=rand()%(size+1);
					c[1]=rand()%(size+1);
				}
				//DEBUG
				cout << "DEBUG: bot.randommove = " << c[0] << "," << c[1] << endl;
				return c;
		}

		vector<int> bettermove(int size, vector< vector<char> > board)
		{	
			//first check for empty gameboard
			if(checkempty(size, board)) 
				return randommove(size);
			//use checkrow, checkcol and checkdiag to find the best possible move, its also possible to have moar difficulties by cloning this with less checks
			vector<int> a = checkrow(size, board);
			if(a[0] == -1 && a[1] == -1 && a[2] == size && a[3] == -1)
			{
				cout << "DEBUG: player._bot.checrow couldnt find a move, maybe all rows are a draw" << endl;
			}
			vector<int> c(2); //returnvector
			c[0]=a[0];	//sets row
			c[1]=a[1];	//sets column
			cout << "DEBUG: player_bot.bettermove = " << c[0] << "," << c[1] << endl;
			return c;
		}
		bool checkempty(int size, vector< vector<char> > board)
		{
			//checks wether the gameboard is empty or not, returns true if it's empty
			for(int x=0; x<size; x++)
			{
				for(int y=0; y<size; y++)
				{
					if(board[x][y] != ' ') return false; //if anything is on the board, it's not empty
				}
			}
			return true; //the board is empty
		}
		
		vector<int> checkrow(int n, vector< vector<char> > gb)
		{ 
			// check the rows and return a vector of ints.
			// the two first two ints [0] and [1] are the proposed coordinates, [0] is the row and [1] is the column
			// the third [2] is moves left to win/lose
			// the fourth [3] int is treated as a boolean, 0 means moves left to loss, 1 means moves left to win
			vector<int> returnvalues(4); // vector contains returnvalues are initialized to values that will not cause problems in the loop below.
			returnvalues[0] = -1;//row outside the gameboard
			returnvalues[1] = -1;//column outside the gameboard
			returnvalues[2] = n;//moves left to win
			returnvalues[3] = -1;//win/lose, init to something wrong, should be changed to 0 or 1 in the loop anyways
			int movestowin = n; //to win on a 3x3 board, you need 3 pieces in a row, same number for a loss
			int movestoloss = n; //moves left to win/lose starts at the needed number of pieces in a row aka gamebord size.
			int row = 0; //used to count 
			for(int x=0; x<n; x++) //loops trough all rows
			{
				movestowin = n; //reset movesleft counters for each row
				movestoloss = n;
				for(int y=0; y<n; y++) //loops trough all values in that row
				{
					if(gb[x][y] == getplayerpiece()) //counts moves left untill win for that row
						movestowin--;
					else if(gb[x][y] == opponentpiece) //counts moves left untill loss for that row
						movestoloss--;
					
				}//now we know how many moves the bot and the opponent have left to win the game.
				cout << "DEBUG: bot.bettermove: row,movestowin,movestolose = "<< x << "," << movestowin << "," << movestoloss << endl;
				bool rowisdraw = false; //find out if the row is a draw.
				if(movestowin < n && movestoloss < n) //if both players have set some pieces in this row, the row is a draw
					rowisdraw=true;
				if(!rowisdraw)//if the row isnt a draw, chekc who is close to win, the bot or the opponent
				{
					//now we know if we are closer to a win or a loss on that row
					if(movestowin < returnvalues[2]) //closer to win than last closest to win/lose
					{
						returnvalues[0] = x;
						returnvalues[2] = movestowin;
						returnvalues[3] = 1;
					}
					else if(movestoloss < returnvalues[2]) //closer to lose than last closest to win/lose
					{
						returnvalues[0] = x;  //sets returnrow to this row
						returnvalues[2] = movestoloss; //sets returnmoves left untill win/lose
						returnvalues[3] = 0;	//returnvalues [2] is how many moves left till bot loses
					}
				}
			}
			//now we need to find what column to place our piece in
			row = returnvalues[0];
			for(int i=0; i<n; i++ )	//find the first open spot, and choose that
			{
				if(gb[row][i] == ' ')
					returnvalues[1] = i;
			}
			cout << "DEBUG: bot.bettermove: returnvalues = " << returnvalues[0] << "," << returnvalues[1] << "," << returnvalues[2] << "," << returnvalues[3] << endl;
			return returnvalues;
		}//end of function checkrow
		/*
		int checkcol(int n, vector< vector<char> > gb)
		{ //return 1 if player 1 won, 2 if player 2 won, 3 if its a draw in all columns and 0 if its nothing.
			int xinarow = 0;
			int oinarow = 0;
			int colsdraw = 0;
			for(int y=0; y<n; y++)
			{
				xinarow = 0;//resets score counter for each column
				oinarow = 0;
				for(int x=0; x<n; x++) 
				{
					if(gb[x][y] == 'X') //adds score for column
						xinarow++;
					else if(gb[x][y] == 'O')
						oinarow++;
				}
				if(xinarow == n) return 1;//if score per row matches boardsize, somebody won, return winner
				if(oinarow == n) return 2;
				if(xinarow > 0 && oinarow > 0)
					colsdraw++; //this column is a draw
				
			}
			if(xinarow == n)	//find the winner
				return 1;
			else if(oinarow == n)
				return 2;
			if(colsdraw == n) //if all rows ended in a draw
				return 3;
			return 0;
		}
		*/
		/*		
		int checkdiagonal(int n, vector< vector<char> > gb)
		{	//returns 1 if player 1 won, 2 if player 2 won, 3 if its a draw in both diagonals and 0 if it nothing
			//check diagonal from top-left to bottom-right
			int xinarow =0, oinarow=0, diagdraw = 0; // score counters and counter for diagonal draws
			for(int i=0; i<n; i++)
			{
				if(gb[i][i] == 'X')
					xinarow++;
				else if(gb[i][i] == 'O')
					oinarow++;
			}
			if(xinarow == n) //if score per diagonal matches boardsize, somebody won
			{
				cout << "DEBUG, X won on diagonal topleft-bottomright "<< endl;
				return 1; //player X won 
			}
			else if(oinarow == n)
			{
				cout << "DEBUG, O won on diagonal topleft-bottomright "<< endl;
				return 2; //player O won
			}
			if(xinarow > 0 && oinarow > 0)
			{
				cout << "DEBUG, Its a draw on diagonal topleft-bottomright "<< endl;
				diagdraw++;
			}
			//check diagonal from bottom-left to top-right
			xinarow=0; oinarow = 0; //resets score counters
			int j = n-1; //starts at the rightmost position
			for(int i=0; i<n; i++) //from top row to bottom row
			{
				if(gb[i][j] == 'X')
					xinarow++;
				else if(gb[i][j] == 'O')
					oinarow++;
				j--;
			}
			if(xinarow == n)	//if score per matches boardsize, somebody won
			{
				cout << "DEBUG, X won on diagonal bottomleft-topright "<< endl;
				return 1;
			}
			else if(oinarow == n)
			{
				cout << "DEBUG, O won on diagonal bottomleft-topright "<< endl;
				return 2;
			}
			if(xinarow > 0 && oinarow > 0)
			{
				cout << "DEBUG, Its a draw on diagonal bottomleft-topright "<< endl;
				diagdraw++;
			}
				
			if(diagdraw == 2) //if both diagonals is a draw, return 3
			{
				cout << "DEBUG, its a draw on both diagonals "<< endl;
				return 3;
			}

			return 0; //meh, nothing here.
		}
		*/

		
	}; //end of classdefinition bot
}//end of namespace tictactoe

//testmain
// moar testing needed!
/*
using namespace tictactoe;
int main()
{
	//initialiser en player av type human, init playervariabler, og test getcoords
	player * player1 = new bot(1);
	
	cout << "Player 1: playernumber,playerpiece = " << player1->getplayernumber()<< "," << player1->getplayerpiece() << endl;
	int size = 3;
	vector< vector<char> > gb;
	vector<int> c = player1->getcoords(size, gb);
	cout << "Player 1. getcoords " << c[0] << "," << c[1] << endl;
	
}
*/