/* 	Written by: Mikael Jakhelln, HIOA-studentnr: s169961
	Tic-Tac-Toe, n pieces on a row to win, with n sized gameboard.
*/
#include "gameboard.cpp"
#include "score.cpp"
#include "player.cpp"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>//for random

using namespace std;
namespace tictactoe{
	class game{
	
		private:
		int intinput(){
			//gets an integer from the player
			int x;
			cin >> x;
			return x;
		}
		void wait()	//used so the user can follow bot vs bot games
		{
			cout <<"USER! press any key to continue!"<<endl<<endl;
			cin.ignore(1);
		}
		
		public:
		game()
		{
			//game runs in here, runs while anyonewonyet returns 0, also lets the controlling entity choose to play again
			
			//first choose gameboard size
			cout << "choose gameboard size, from 3 and up:";
			int size=0;
			size = intinput();
			while(size < 3)
			{
				cout << "that is too small, choose another boardsize:" << endl;
				size = intinput();
			}
			
			//initialize gameboard, and make objects for players
			gameboard gameboard1 = gameboard(size); //this is the gameboard, initialized to the chosen size.
			score score1 = score(); //check score with this with 
			player player1;//two players, will be initialized once the almighty user has chosen number of human players
			player player2;

			int humans = 0;
			cout << "Choose number of humans players: ";
			humans = intinput();
			while(humans >2 || humans < 0)
			{
				cout << "invalid number of human players, choose again" << endl;
				humans = intinput();
			}
			cout << "Human players: " << humans << endl;
			//init players
			if(humans == 0)
			{
				player1 = bot(1);//init players as bots
				player2 = bot(2);
			}
			if(humans = 1)
			{
				player1 = human(1); //one human, one bot
				player2 = bot(2);
				//ask user for bot difficulty
				
			}
			if(humans = 2)
			{
				player1 = human(1);	//two bots, SHOWDOWN FTW!
				player2 = human(2);
			}
			//choose who to start
			srand(time(NULL));//seed random from system time
			int whostarts = (rand() %2)+1; //pick random number between 1 and 2
			cout << "DEBUG: whostarts:" << whostarts << endl;
			//prints out who starts
			int  x = player1.getplayernumber();
			char y = player1.getplayerpiece();
			cout << "player1: playernumber,playerpiece: " << x<< ",[" << y << "]"<<endl;
			x = player2.getplayernumber(); 
			y = player2.getplayerpiece();
			cout << "player: playernumber,playerpiece: " << x << ",["<< y << "]"<< endl;
			
			//the actual game loop stuff starts here, sorry
			gameboard1.printboard();
			int gameover = 0;	//used to check the gamestate, at the start of the game, nobody has won yet.
			while(gameover == 0)
			{
				//player 1(X)'s turn
				bool p1move = false;
				cout << "Player X, make a move!" << endl;
				while(p1move != true)
				{
					vector<int> coords(2); coords[0] = size+1; coords[1] = size+1; //temp vector for return values of player
					//initd to something outside the gameboard, so it definately wont work
					if(player1. getplayernumber() == 1 || player2. getplayernumber() == 1)
					{
						if(player1. getplayernumber() == 1)
						{
							coords = player1.getcoords(size, gameboard1.board); //gets some coords from the bot
							cout << "DEBUG: botplayer X coords: "<< coords[0] << "," << coords[1]<<endl;
							p1move = gameboard1.makemove(1, coords[0], coords[1]);
						}
						else if(player2. getplayernumber() == 1)
						{
							coords = player2.getcoords(size, gameboard1.board); //gets some coords from the bot
							p1move = gameboard1.makemove(1, coords[0], coords[1]);
						}
					}
					else	//human plays as player 1
					{
						coords = getcoords(size);
						p1move = gameboard1.makemove(1, coords[0], coords[1]);
						if(p1move == false) cout << "invalid coordinates, spot is already taken, choose another" << endl; //the bot doesnt need to see this
					}
				}
				//end of player1's turn
				gameboard1.printboard(); //prints the gameboard
				//check score
				gameover = score1.anybodywinyet(size, gameboard1.board);
				if(gameover != 0) break; //if somebody won, or its a draw, break this while loop
				
				//player 2(O)'s turn 
				bool p2move = false;
				cout << "Player O, make a move!" << endl;
				while(p2move != true)
				{
					vector<int> coords(2); coords[0] = size+1; coords[1] = size+1; //initialized to something outside the gameboard..	
					if(player1. getplayernumber() == 2 || player2. getplayernumber() == 2)
					{
						if(player1. getplayernumber() == 2)
						{
							coords = player1.getcoords(size, gameboard1.board); //gets some coords from the bot
							p2move = gameboard1.makemove(2, coords[0], coords[1]);
						}
						else if(player2. getplayernumber() == 2)
						{
							coords = player2.getcoords(size, gameboard1.board); //gets some coords from the bot
							p2move = gameboard1.makemove(2, coords[0], coords[1]);
						}
					}
					else	//human plays as player 2
					{
						coords = getcoords(size);
						p2move = gameboard1.makemove(2, coords[0], coords[1]);
						if(p2move == false) cout << "invalid coordinates, spot is already taken, choose another" << endl;
					}
					
				}
				//end of player2's turn
				
				gameboard1.printboard(); //prints the gameboard
				gameover = score1.anybodywinyet(size, gameboard1.board);
				if(gameover != 0) break; //if somebody won, or its a draw, break this while loop
			}
			gameover = score1.anybodywinyet(size, gameboard1.board); //the result of the game
			if(gameover == 1){cout << "player X won" << endl;}//duh!
			if(gameover == 2){cout << "player O won" << endl;}//duh!
			if(gameover == 3){cout << "its a draw, good job" << endl;}//duh!

			//play another game?
			cout << "play another game? type y or Y for another game, anything else to exit" << endl;
			char again;
			cin >> again;
			if(again == 'y' || again == 'Y')//reset board, and start the game.
			{
				game();
			}
			*/	
		}//end of function game
	}; //end of classdefinition game
} //end of namespace tictactoe