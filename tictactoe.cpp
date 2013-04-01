/* 	Written by: Mikael Jakhelln, HIOA-studentnr: s169961
	Tic-Tac-Toe, n pieces on a row to win, with n sized gameboard.
*/
#include "game.cpp"
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace tictactoe;
int main()
{
	printf("-------------------------------\n");
	printf("Welcome to INFINITE TIC-TAC-TOE\n");
	printf("-------------------------------\n");
	game();	//GAME-ON!!
	cout << "thanks for playing! have a nice day :D" << endl;
	return 0;
}