/* 	Written by: Mikael Jakhelln, HIOA-studentnr: s169961
	Tic-Tac-Toe, n pieces on a row to win, with n sized gameboard.
*/
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

namespace tictactoe
{
	class gameboard
	{
		public: //was originally one big file, rewrote to several classes for easier reading, hence everything is public :/
		bool isempty = false;
		int size; //gameboard size
		vector< vector<char> > board; //2D array(vector) for gameboard
		
		//constructor
		gameboard(int s)
		{
			size = s;
			resetboard();
		}
		
		void resetboard()
		{ //resets the gameboard
			board.resize(size);
			for(int i=0; i<size; i++)
			{	
				board[i].resize(size);
				for(int j=0; j<size; j++)
				{
					board[i][j] = ' ';
				}
			}
		}
		
		void printboard()
		{ //print out the current state of gameboard
			for(int j = 0; j<size; j++){cout << "___";} cout << endl;
			for(int i=0; i<size; i++)
			{
				for(int j=0; j<size; j++)
				{
					cout << '|'<< board[i][j];
				}
				cout << '|'<< endl;
				for(int j = 0; j<size; j++){cout << "+-";} cout << "+" << endl;
			}
			for(int j = 0; j<size; j++){cout << "___";} cout << endl;
		}
		
		bool isempty() //not used, should have implemented this here from the start :/
		{
			//checks wether the gameboard is empty or now
			for(int x=0; x<size; x++)
			{
				for(int y=0; y<size; y++)
				{
					if(board[x][y] != ' ') //if anything is on the board, return false
						return false;
				}
			}
			return true; //the board is empty
		}

		bool makemove(int player, int x, int y)
		{ 	//place players gamepiece on the board
			//parameters are player: 1/2, rownumber: x, columnnumber: y
			x--; y--; //because index starts at 0
			if(board[x][y] != ' ') //if the spot is filled, return false
			{
				return false;
			}
			if(board[x][y] == ' ') //if the spot is free, place gamepiece
			{
				if(player == 1){board[x][y] = 'X'; return true;}
				if(player == 2){board[x][y] = 'O'; return true;}
			}
			return false; //if u got here, something went terribly wrong! might aswell return false
		}
	};//end of classdefinition gameboard
}//end of namespace tictactoe

//testmain
/*
using namespace tictactoe;
int main()
{
	gameboard gameboard1 = gameboard(3);
	gameboard1.printboard();
	
	bool okmove = gameboard1.makemove(1,1,1);
	cout << "1,1,1: "<<okmove << endl;
	okmove = gameboard1.makemove(1,1,1);
	cout << "1,1,1: "<<okmove << endl;
	gameboard1.makemove(2,1,2);
	gameboard1.printboard();
	gameboard1.makemove(1,2,1);
	gameboard1.printboard();
	gameboard1.makemove(2,2,2);
	gameboard1.printboard();
	gameboard1.makemove(1,3,1);
	gameboard1.printboard();
	gameboard1.makemove(2,3,2);
	gameboard1.printboard();
	//everything works, onto next class
}
*/