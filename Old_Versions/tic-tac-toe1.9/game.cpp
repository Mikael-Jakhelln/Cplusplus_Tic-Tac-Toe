#include "gameboard.cpp"
#include "score.cpp"
#include "bot.cpp"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
namespace game{

	class game{
		public:
		
		int intinput(){
			//gets an integer from the player
			int x;
			cin >> x;
			return x;
		}
		
		vector<int> getcoords(int size)
		{	//gets coordinates as input from player, within the boundaries of the parameter size
			vector<int> coords(2);
			cout << "choose row: ";
			coords[0] = intinput();
			cout << endl << "choose column: ";
			coords[1] = intinput();
			cout << endl;
			while(coords[0] > size || coords[1] > size)
			{	
				cout << "coordinates outside of gameboard! type in valid coords!" << endl;
				cout << "choose row: ";
				coords[0] = intinput();
				cout << endl << "choose column: ";
				coords[1] = intinput();
				cout << endl;
			}
			return coords;
		}
		
		game()
		{//game runs in here, runs while anyonewonyet returns 0, also lets the controlling entity choose to play again
		
			//first choose gameboard size
			cout << "choose gameboard size, from 3 and up:";
			int size=0;
			while(size < 3)
			{
				size = intinput();
			}
			
			gameboard::gameboard gameboard1 = gameboard::gameboard(size); //this is the gameboard, initialized to the chosen size.
			score::score score1 = score::score(); //check score with this with 
			//two bots so you can have bots with different skill level against eachother.
			bot::bot bot1 = bot::bot(); 
			bot1.difficulty = 1; //a bot player with difficulty 1
			bot::bot bot2 = bot::bot();
			bot2.difficulty = 1; //another bot with difficulty 1

			int humans = 0;
			
			cout << "Choose number of humans players:" << endl;
			humans = intinput();
			while(humans >2 || humans < 0)
			{
				cout << "invalid number of human players, choose again" << endl;
				humans = intinput();
			}
			cout << "Human players: " << humans << endl;
			//get random player to start
			int whostarts = rand() %(2+1);
			cout << "whostarts:" << whostarts << endl;
			if(humans == 1)
			{
				cout << "welcome puny human, are you ready to get served?" << endl;
				bot1.playernumber == whostarts;
				if(whostarts = 1)
				{
					//choose a either bot1 or bot2 to get this as its playernumber
					bot1.playernumber = 1;
					bot2.playernumber = 1;
				}
			}
			else if(humans == 0)
			{
				cout << "BOT BATTLE! Get ready to spectate the battle of the ages!" << endl;
				if(whostarts = 1)
				{
					bot1.playernumber = 1;
					bot2.playernumber = 2;
				}
				else
				{
					bot1.playernumber = 2;
					bot2.playernumber = 1;
				}
			}
			else if(humans == 2)
			{
				cout << "Sharpen your squishy brains humans, and commence battle!" << endl;
			}
			
			//game loop stuff starts here
			gameboard1.printboard();
			int gameover = 0;	//used to check the gamestate, at the start of the game, nobody has won yet.
			while(gameover == 0)
			{
				//player 1(X)'s turn 
				bool p1move = false;
				cout << "Player X, make a move!" << endl;
				while(p1move != true)
				{
					vector<int> coords(2); coords[0] = size+1; coords[1] = size+1; //something outside the gameboard, so it definately wont work
					if(bot1.playernumber == 1 || bot2.playernumber == 1)
					{
						if(bot1.playernumber == 1)
						{
							coords = bot1.getcoords(1, size); //gets some coords from the bot
							p1move = gameboard1.makemove(1, coords[0], coords[1]);
						}
						else if(bot2.playernumber == 1)
						{
							coords = bot2.getcoords(1, size); //gets some coords from the bot
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
					if(bot1.playernumber == 2 || bot2.playernumber == 2)
					{
						if(bot1.playernumber == 2)
						{
							coords = bot1.getcoords(2, size); //gets some coords from the bot
							p2move = gameboard1.makemove(2, coords[0], coords[1]);
						}
						else if(bot2.playernumber == 2)
						{
							coords = bot2.getcoords(2, size); //gets some coords from the bot
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
		}
	}; //end of classdefinition game
} //end of gamespace name