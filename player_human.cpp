//#include "player.cpp"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;
namespace tictactoe{
	class human : public virtual player
	{
		private: 
		int intinput(){
			//gets an integer from the user
			int x;
			cin >> x;
			return x;
		}
		
		public:
		human(int pn) 
		: player(pn)
		{
			//nothing else to do here..
		}
		
		vector<int> getcoords(int size, vector< vector<char> >)
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
	}; //end of class player: human
}//end of namespace tictactoe

//testmain
//human works as it is supposed to.
/*
using namespace tictactoe;
int main()
{
	//initialiser en player av type human, init playervariabler, og test getcoords
	player * player1 = new human(1);
	
	cout << "Player 1: playernumber,playerpiece = " << player1->getplayernumber()<< "," << player1->getplayerpiece() << endl;
	int size = 3;
	vector< vector<char> > gb;
	vector<int> c = player1->getcoords(size, gb);
	cout << "Player 1. getcoords " << c[0] << "," << c[1] << endl;
	
}
*/