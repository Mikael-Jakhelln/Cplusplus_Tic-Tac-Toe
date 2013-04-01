/* 	Written by: Mikael Jakhelln, HIOA-studentnr: s169961
	Tic-Tac-Toe, n pieces on a row to win, with n sized gameboard.
*/
#include "gameboard.cpp"
#include "score.cpp"
#include "player.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cstdlib>	//is this the same as stdlib?
#include <ctime>//for random and wait

using namespace std;
namespace tictactoe{
	class game{
	
		private:
		bool willwait;	//used to check if it should wait for user keypress, when playing bot vs bot
		
		/* // old intinput
		int intinput() //gets an int from the user
		{
			int x;
			cin >> x;
			return x;
		}
		*/
		
		int intinput()
		{
			//better inputmethod, almost done
			int returnint = 0;
			int intmax =  2147483647;
			
			bool isint = false;
			char input[10];	//get input into array
			cin >> input;
			int inputcount = 0;
			for(int i = 0; i<10; i++) //loop trough array
			{
				
				if(!isdigit(input[i]))//char isnt a digit
				{
					break;	//if a character in input isnt a digit
				}
				else	//char is a digit
				{	
					isint = true;
				}
				inputcount++;
			}
			
			
			while(isint != true) //input isn't an int, ask user to type it in again
			{
				cout << "thats not a number, try again:";
				cin >> input;
				for(int i = 0; i<10; i++)
				{
					if(!isdigit(input[i]))//char isnt a digit
					{	
						break;	//if a character in input isnt a digit
					}
					else	//char is a digit
					{	
						isint = true;
					}
					inputcount++;
				}
			}
			if(isint == false)	//if it still isnt an int, just exit
			{
				cout << "YOU BROKE SOMETHING! terminating program" << endl;
				exit(EXIT_FAILURE);
			}
			returnint = atoi(input);
			while(returnint > intmax || returnint < 0)
			{
				cout <<"that number is way to big! try again:";
				returnint = intinput();
			}
			while(returnint > intmax || returnint < 0)
			{
				cout <<"the number is too small! try again:";
				returnint = intinput();
			}
			return returnint;
		}
		
		void wait()	//waiting for 1 second, so the user can follow bot vs bot games
		{
			if(willwait = true) //waits only if willwait is true
			{
				cout <<"waiting so the USER! can see whats happening!"<<endl<<endl;
				clock_t temp;
				temp = clock () + 1 * CLOCKS_PER_SEC ;
				while (clock() < temp) {}
			}
		}
		
		public:
		game()
		{	
			wait();
		
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
			gameboard board = gameboard(size); //this is the gameboard, initialized to the chosen size.
			score score1 = score(); //check score with this with 
			player * player1;//two players, will be initialized once the almighty user has chosen number of human players
			player * player2;
			
			//choose who to start
			srand(time(NULL));//seed random from system time
			int whostarts = (rand() %2)+1; //pick random number between 1 and 2
			cout << "DEBUG: whostarts:" << whostarts << endl;
			
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
			
			if(humans == 0) //two bots, MACHINE SHOWDOWN FTW!
			{
				willwait = true;	//wait between turns
				if(whostarts == 1)	//player 1 starts
				{
					player1 = new bot(1, false); //bot(players piece = X, ishuman = false)
					player2 = new bot(2, false); //bot(players piece = O, ishuman = false)
				}
				else
				{
					player1 = new bot(2, false); //bot(players piece = X, ishuman = false)
					player2 = new bot(1, false); //bot(players piece = O, ishuman = false)
				}
				//ask user for bot difficulty
				cout << "set difficulty for bot " << player1->getplayerpiece() << ":";
				bool p1diff = player1->setdifficulty(intinput());
				cout << "set difficulty for bot " << player2->getplayerpiece() << ":";
				bool p2diff = player2->setdifficulty(intinput());
			}
			else if(humans == 1)
			{
				willwait = false;	//dont wait between turns
				if(whostarts == 1)//human starts as player X
				{
					player1 = new human(1, true); //human(players piece = X, ishuman = true)
					player2 = new bot(2, false); //bot(players piece = O, ishuman = false)
				}
				else //human is player O
				{
					player1 = new human(2, true); //human(players piece = X, ishuman = true)
					player2 = new bot(1, false); //bot(players piece = O, ishuman = false)
				}
				//ask user for bot difficulty
				
			}
			else if(humans == 2)
			{
				willwait = false;	//dont wait for humans
				if(whostarts == 1)
				{
					player1 = new human(1, true); //two Humans
					player2 = new human(2, true); //human(players piece = X, ishuman = true)
				}
				else
				{
					player1 = new human(2, true); //two Humans
					player2 = new human(1, true); //human(players piece = X, ishuman = true)
				}
			}
			else	//somehow humans are fucked up
			{
				cout << "OMG OMG OMG, somehow you managed to break something" << endl;
				exit(EXIT_FAILURE);	//exits program
			}
			
			//prints out who starts
			int  x = player1->getplayernumber();
			char y = player1->getplayerpiece();
			int z = player1->getdifficulty();
			cout << "player1: playernumber,playerpiece,difficulty: " << x<< ",[" << y << "],"<< z <<endl;
			x = player2->getplayernumber(); 
			y = player2->getplayerpiece();
			z = player2->getdifficulty();
			cout << "player2: playernumber,playerpiece,difficulty: " << x << ",["<< y << "]," << z << endl;
			
			wait();
			
			//the actual game loop stuff starts here, sorry
			board.printboard();
			int gameover = 0;	//used to check the gamestate, at the start of the game, nobody has won yet.
			while(gameover == 0)
			{
				//the starting player's turn
				bool Xmove = false;
				cout << "player X, make a move!" << endl;
				while(Xmove != true)
				{
					vector<int> coords(2); coords[0] = size+1; coords[1] = size+1; //temp vector for return values of player
					//initd to something outside the gameboard, so it definately wont work
					if(player1->getplayernumber() == 1)
					{
						coords = player1->getcoords(size, board.board); //gets some coords from the bot
						cout << "DEBUG: game(): player1.getcoords are: "<< coords[0] << "," << coords[1]<<endl;
						Xmove = board.makemove(player1->getplayerpiece(), coords[0], coords[1]);
						
						if(player1->ishuman())
						{
							if(Xmove == false) cout << "invalid coordinates, spot is already taken, choose another" << endl;
						}
					}
					else //player2.playernumber == 2
					{
						coords = player2->getcoords(size, board.board); //gets some coords from the bot
						cout << "DEBUG: game(): player2.getcoords are: "<< coords[0] << "," << coords[1]<<endl;
						Xmove = board.makemove(player2->getplayerpiece(), coords[0], coords[1]);
						
						if(player2->ishuman())
						{
							if(Xmove == false) cout << "invalid coordinates, spot is already taken, choose another" << endl;
						}
					}
					if(Xmove == false) cout << "invalid coordinates, spot is already taken, choose another" << endl; //the bot doesnt need to see this
				}
				//end of playerX's turn
				
				wait();	//might wait here
				board.printboard(); //prints the gameboard
				//check score
				gameover = score1.anybodywinyet(size, board.board);
				if(gameover != 0) break; //if somebody won, or its a draw, break this while loop
				
				//player(O)'s turn 
				bool Omove = false;
				while(Omove != true)
				{
					vector<int> coords(2); coords[0] = size+1; coords[1] = size+1; //initialized to something outside the gameboard..	
					if(player1->getplayernumber() == 2)
					{
						coords = player1->getcoords(size, board.board); //gets some coords from the bot
						cout << "DEBUG: game(): player1.getcoords are: "<< coords[0] << "," << coords[1]<<endl;
						Xmove = board.makemove(player1->getplayerpiece(), coords[0], coords[1]);
						
						if(player1->ishuman())
						{
							if(Xmove == false) cout << "invalid coordinates, spot is already taken, choose another" << endl;
						}
					}
					else //player2.playernumber == 2
					{
						coords = player2->getcoords(size, board.board); //gets some coords from the bot
						cout << "DEBUG: game(): player1.getcoords are: "<< coords[0] << "," << coords[1]<<endl;
						Xmove = board.makemove(player2->getplayerpiece(), coords[0], coords[1]);
						
						if(player2->ishuman())
						{
							if(Xmove == false) cout << "invalid coordinates, spot is already taken, choose another" << endl;
						}
					}
				}
				//end of playerO's turn
				wait(); //might wait here
					
				board.printboard(); //prints the gameboard
				gameover = score1.anybodywinyet(size, board.board);
				if(gameover != 0) break; //if somebody won, or its a draw, break this while loop
			}
			gameover = score1.anybodywinyet(size, board.board); //the result of the game
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
		//debugline end ftw! */
		}//end of function game
	}; //end of classdefinition game
} //end of namespace tictactoe