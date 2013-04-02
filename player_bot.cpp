/* 	Written by: Mikael Jakhelln, HIOA-studentnr: s169961
	Tic-Tac-Toe, n pieces on a row to win, with n sized gameboard.
*/
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
		static const int defaultdifficulty = 1;	//default difficulty to initialize to
		static const int numberofdifficulties = 2; //the number if implemented difficulties, 1 is the easiest, 2 is harder, and so on.
		char opponentpiece;	//the opponents piece.
		
		public:
		vector<int> defaultreturn;//this vector will contan the default return values of all checkmethods
		
		bot(int pn, bool humanornot) 
		: player(pn, humanornot)
		{
			//initialize defaultreturn vector
			defaultreturn.resize(4);
			defaultreturn[0] = -1;
			defaultreturn[1] = -1;
			defaultreturn[2] = 0;
			defaultreturn[3] = 0;
		
			difficulty = defaultdifficulty; //default difficulty is set to easy
			if(getplayerpiece() == 'X')
				opponentpiece = 'O';
			if(getplayerpiece() == 'O')
				opponentpiece = 'X';
			srand(time(NULL));	//seed random, so it doesnt give the same values every time
		}
		
		bool setdifficulty(int diff) //set difficulty for this bot
		{	
			
			difficulty = 2; return true; //difficulty doesn't get set properly 
			cout << "DEBUG: difficulty set to" << diff << endl;
			if(diff > numberofdifficulties || diff <= defaultdifficulty)
			{
				difficulty = defaultdifficulty;
				return false;
			}
			difficulty = diff;
			return true;
		}
		int getdifficulty() //returns difficulty
		{
			return difficulty; 
		}
		
		
		vector<int> getcoords(int size, vector< vector<char> > board)
		{
			return bettermove(size, board);
			//this should analyse the gameboard, then make the best possible move :P, should also not make a move that doesnt work
			if(difficulty == 1) //if EZ-mode: just return some random coords untill something hits. (mostly for debug)
			{
				return randommove(size);
			}
			else if(difficulty == 2)
			{
				return bettermove(size, board);
			}
			/*//to add more difficulties to a bot, make lines like this
			else if(difficulty == 3)
			{
				return evenbettermove(size, board); 
			}
			*/
			else //difficulties above 2 are not implemented yet. insert even better algorithm here..
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
		{	/*REMOVE THIS WHEN CHECKS WORK*/return randommove(size);
			//first check for empty gameboard
			if(checkempty(size, board) == false) 
				return randommove(size);
			//use checkrow, checkcol and checkdiag to find the best possible move, its also possible to have moar difficulties by cloning this with less checks
			vector<int> bestreturn = defaultreturn;
			vector< vector<int> > allchecks(3);	//for iterating through them in a for
			vector<int> bestrow = checkallrows(size, board); allchecks[0] = bestrow;
			/*
			vector<int> bestcolumn = checkallcolumns(size, board); allchecks[1] = bestrow;
			vector<int> bestdiagonal = checkalldiagonals(size, board); allchecks[2] = bestrow;
			
			for(int i=0;i<3;i++)//loop through all the best moves for rows, columns and diagonals
			{
				vector<int> thismove = allchecks[i];	//temp move is the first move in allchecks
				if(thismove[2] > bestmove[2])			//if thismove is better, (this player has more pieces in sequence)
					bestmove = thismove;				//thismove is now the best, loop through the rest, and you have the best possible move
			}
			*/
			/*DEBUG test*/bestreturn = bestrow;
			if(bestreturn[2] > defaultreturn[2])
			{
				vector<int>c(2);
				c[0] = bestreturn[0];
				c[1] = bestreturn[1];
				return c;
			}
			return randommove(size);//just in case it cant find any good moves
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
		
		vector<int> checkrow(int n, vector< vector<char> > gb, int row) //check single row
		{	//returnvector has 4 values [0]=row, [1]=column, [2]=number of pieces, [3]=advantage/disadvantage 
			vector<int> out(4); out[0]=-1; out[1]=-1; out[2]=0; out[3]=0;
			int o=0;	//count number of O and X
			int x=0;
			for(int i=0; i<n; i++)	//loop trough row and count
			{
				char c = gb[row][i];  //get current piece
				if(c == 'O')	//check what piece it is
					o++;		//increase counter
				else if(c == 'X')
					x++;
			}
			if(o=x)	//same count, this if might be reduntant, since we return 
			{
				return out; //return no advantage
			}
			else if(x>o) //advantage X
			{
				if(getplayerpiece() == 'X')
				{
					out[3]=1;//bot has advantage
					out[2]=x; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row
					{
						if(gb[row][j] == ' ')
							out[0] = j;
					}
				}
				else
				{
					out[3]=-1;//bot has disadvantage 
					out[2]=o; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row, to sabotage row with
					{
						if(gb[row][j] == ' ')
							out[0] = j;
					}
				}
			}
			else if(x<o)
			{
				if(getplayerpiece() == 'X')
				{
					out[3]=-1;//bot has disadvantage 
					out[2]=o; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row, to sabotage row with
					{
						if(gb[row][j] == ' ')
							out[0] = j;
					}
				}
				else
				{
					out[3]=1;//bot has disadvantage 
					out[2]=x; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row
					{
						if(gb[row][j] == ' ')
							out[0] = j;
					}
				}
			}
			return out;
		}
		vector<int> checkallrows(int n, vector< vector<char> > gb)//check all rows with checkrow
		{
			vector<int> bestrow(4); bestrow[0]=-1; bestrow[1]=-1; bestrow[2]=0; bestrow[3]=0;
			for(int i=0;i<n;i++)
			{
				vector<int> thisrow = checkrow(n, gb, i);
				if(thisrow[2] > bestrow[2])
				{
					bestrow[0] = thisrow[0];
					bestrow[1] = thisrow[1];
					bestrow[2] = thisrow[2];
					bestrow[3] = thisrow[3];
				}
			}
			return bestrow;
		}
		//end of check rows
/*		//check columns
		vector<int> checkcolumn(int n, vector< vector<char> > gb, int row) //check single row
		{	//returnvector has 4 values [0]=row, [1]=column, [2]=number of pieces, [3]=advantage/disadvantage 
			vector<int> out(4); out[0]=-1; out[1]=-1; out[2]=0; out[3]=0;
		
			o=0;	//count number of O and X
			x=0;
			for(int i=0; i<n, i++)	//loop trough row and count
			{
				char c = gb[row][i];  //get current piece
				if(c == 'O')	//check what piece it is
					o++;		//increase counter
				else if(c == 'X')
					x++;
			}
			if(o=x)	//same count, this if might be reduntant, since we return 
			{
				return out; //return no advantage
			}
			else if(x>o) //advantage X
			{
				if(playerpiece == 'X')
				{
					out[3]=1;//bot has advantage
					out[2]=x; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row
					{
						if(gb[row][i] == ' ')
							out[0] = i;
					}
				}
				else
				{
					out[3]=-1;//bot has disadvantage 
					out[2]=o; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row, to sabotage row with
					{
						if(gb[row][i] == ' ')
							out[0] = i;
					}
				}
			}
			else if(x<o)
			{
				if(playerpiece == 'X')
				{
					out[3]=-1;//bot has disadvantage 
					out[2]=o; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row, to sabotage row with
					{
						if(gb[row][i] == ' ')
							out[0] = i;
					}
				}
				else
				{
					out[3]=1;//bot has disadvantage 
					out[2]=x; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row
					{
						if(gb[row][i] == ' ')
							out[0] = i;
					}
				}
			}
			return out;
		}
		vector<int> checkallcolumns(int n, vector< vector<char> > gb)//check all rows with checkrow
		{
			vector<int> bestrow(4); bestrow[0]=-1; bestrow[1]=-1; bestrow[2]=0; bestrow[3]=0;
			for(int i=0;i<n;i++)
			{
				vector<int> thisrow = checkrow(n, gb, i);
				if(thisrow[2] > bestrow[2])
				{
					bestrow[0] = thisrow[0];
					bestrow[1] = thisrow[1];
					bestrow[2] = thisrow[2];
					bestrow[3] = thisrow[3];
				}
			}
			return bestrow;
		}
		//end of check columns
		//check diagonals
		vector<int> checkdiagonal(int n, vector< vector<char> > gb, int row) //check single row
		{	//returnvector has 4 values [0]=row, [1]=column, [2]=number of pieces, [3]=advantage/disadvantage 
			vector<int> out(4); out[0]=-1; out[1]=-1; out[2]=0; out[3]=0;
		
			o=0;	//count number of O and X
			x=0;
			for(int i=0; i<n, i++)	//loop trough row and count
			{
				char c = gb[row][i];  //get current piece
				if(c == 'O')	//check what piece it is
					o++;		//increase counter
				else if(c == 'X')
					x++;
			}
			if(o=x)	//same count, this if might be reduntant, since we return 
			{
				return out; //return no advantage
			}
			else if(x>o) //advantage X
			{
				if(playerpiece == 'X')
				{
					out[3]=1;//bot has advantage
					out[2]=x; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row
					{
						if(gb[row][i] == ' ')
							out[0] = i;
					}
				}
				else
				{
					out[3]=-1;//bot has disadvantage 
					out[2]=o; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row, to sabotage row with
					{
						if(gb[row][i] == ' ')
							out[0] = i;
					}
				}
			}
			else if(x<o)
			{
				if(playerpiece == 'X')
				{
					out[3]=-1;//bot has disadvantage 
					out[2]=o; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row, to sabotage row with
					{
						if(gb[row][i] == ' ')
							out[0] = i;
					}
				}
				else
				{
					out[3]=1;//bot has disadvantage 
					out[2]=x; //number of pieces on this row
					out[1]=row; //on this row
					for(int j=0;j<n;j++)//now find a free spot on this row
					{
						if(gb[row][i] == ' ')
							out[0] = i;
					}
				}
			}
			return out;
		}
		vector<int> checkalldiagonals(int n, vector< vector<char> > gb)//check all rows with checkrow
		{
			vector<int> bestrow(4); bestrow[0]=-1; bestrow[1]=-1; bestrow[2]=0; bestrow[3]=0;
			for(int i=0;i<n;i++)
			{
				vector<int> thisrow = checkrow(n, gb, i);
				if(thisrow[2] > bestrow[2])
				{
					bestrow[0] = thisrow[0];
					bestrow[1] = thisrow[1];
					bestrow[2] = thisrow[2];
					bestrow[3] = thisrow[3];
				}
			}
			return bestrow;
		}
		//end of check diagonals
		//*/
	}; //end of classdefinition bot
}//end of namespace tictactoe