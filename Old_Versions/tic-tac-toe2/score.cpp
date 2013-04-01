//#include "gameboard.cpp" //for testmain only
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
//using namespace gameboard; //for testmain only
//this namespace is for checking score on a gb.
namespace score{

	class score{
		public:
		int scorerow(int n, vector< vector<char> > gb)
		{ //returns 1 if player 1 won on any rows, 2 if player 2 won, and 3 if all rows are draw, else it returns 0
			int xinarow = 0;
			int oinarow = 0;
			int rowsdraw = 0;
			for(int x=0; x<n; x++)
			{
				xinarow = 0; //reset score counter for each row
				oinarow = 0;
				for(int y=0; y<n; y++) 
				{
					if(gb[x][y] == 'X') //adds score for row
						xinarow++;
					else if(gb[x][y] == 'O')
						oinarow++;
				}
				if(xinarow == n) return 1;//if score per row matches boardsize, somebody won, return winner
				if(oinarow == n) return 2;
				if(xinarow > 0 && oinarow > 0)
					rowsdraw++; //this row is a draw

			}
			if(xinarow == n) //find out who won
				return 1;
			else if(oinarow == n)
				return 2;
			if(rowsdraw == n) //if all rows ended in a draw
				return 3;
			return 0; //nobody won, and its still possible to win in the rows
		}
		int scorecol(int n, vector< vector<char> > gb)
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
		int scorediagonal(int n, vector< vector<char> > gb)
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
				//cout << "DEBUG, X won on diagonal topleft-bottomright "<< endl;
				return 1; //player X won 
			}
			else if(oinarow == n)
			{
				//cout << "DEBUG, O won on diagonal topleft-bottomright "<< endl;
				return 2; //player O won
			}
			if(xinarow > 0 && oinarow > 0)
			{
				//cout << "DEBUG, Its a draw on diagonal topleft-bottomright "<< endl;
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
				//cout << "DEBUG, X won on diagonal bottomleft-topright "<< endl;
				return 1;
			}
			else if(oinarow == n)
			{
				//cout << "DEBUG, O won on diagonal bottomleft-topright "<< endl;
				return 2;
			}
			if(xinarow > 0 && oinarow > 0)
			{
				//cout << "DEBUG, Its a draw on diagonal bottomleft-topright "<< endl;
				diagdraw++;
			}
				
			if(diagdraw == 2) //if both diagonals is a draw, return 3
			{
				//cout << "DEBUG, its a draw on both diagonals "<< endl;
				return 3;
			}

			return 0; //meh, nothing here.
		}

		int anybodywinyet(int n, vector< vector<char> > gb)
		{
			//returns 1 if player 1(X) won, 2 if player 2(O) won, 0 if nobody has won yet or 3 if the game ended in a draw.
			//check for winner in rows
			int rowwin = scorerow(n, gb);
			if(rowwin != 0)
			{
				/*
				if(rowwin == 1)
					cout << "DEBUG: player X won on a row" << endl;
				if(rowwin == 2)
					cout << "DEBUG: player O won on a row" << endl;
				if(rowwin == 3)
					cout << "DEBUG: its a draw on all of the rows" << endl;
				*/
				if(rowwin == 1 || rowwin == 2)
					return rowwin;
			}
			//if nobody won in any rows, check columns
			int colwin = scorecol(n, gb);
			if(colwin != 0)
			{
				/*
				if(colwin == 1)
					cout << "DEBUG: player X won on a column" << endl;
				if(colwin == 2)
					cout << "DEBUG: player O won on a column" << endl;
				if(colwin == 3)
					cout << "DEBUG: its a draw on all of the columns" << endl;
				*/
				if(colwin == 1 || colwin == 2)
					return colwin;
			}
			//if no wins in columns either, check diagonals:
			int diagwin = scorediagonal(n, gb);
			if(diagwin != 0)
			{
				/*
				if(diagwin == 1)
					cout << "DEBUG: player X won on a diagonal" << endl;
				if(diagwin == 2)
					cout << "DEBUG: player O won on a diagonal" << endl;
				if(diagwin == 3)
					cout << "DEBUG: its a draw on all of the diagonals" << endl;
				*/
				if(diagwin == 1 || diagwin == 2)
					return diagwin; //somebody won the diagonal, return the winner
			}
			//if still no win, then it might be a draw
			if(diagwin == 3 && rowwin == 3 && colwin == 3)
				return 3; //its a draw
			//if nobody won, and its not a draw, that means nobody has won yet
			return 0;
		}
	}; //end of classdefinition score
}//end of namespace

//testmain
/*
int main()
{
	gameboard::gameboard gameboard1 = gameboard::gameboard(3);
	gameboard1.makemove(1,1,1);
	gameboard1.makemove(2,1,2);
	gameboard1.makemove(1,2,1);
	gameboard1.makemove(2,2,2);
	gameboard1.makemove(1,3,1);
	gameboard1.printboard();
	score::score score1 = score::score();
	vector< vector<char> > board = gameboard1.board;
	int i = score1.scorerow(3, board);
	cout << "SCOREROW: " << i << endl;
	int j = score1.scorecol(3, board);
	cout << "SCORECOLUMN: " << j << endl;
	int k = score1.scorediagonal(3, board);
	cout << "SCOREDIAGONAL: " << k << endl;
	//everything works, onto the next
}
*/