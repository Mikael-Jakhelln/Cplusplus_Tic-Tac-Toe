#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
//global variables:
int n; //gameboard size
vector< vector<char> > gameboard; //2D array(vector) for gameboard

void boardreset()
{ //resets the gameboard
	gameboard.resize(n);
	for(int i=0; i<n; i++)
	{	
		gameboard[i].resize(n);
		for(int j=0; j<n; j++)
		{
			gameboard[i][j] = ' ';
		}
	}
}
void printboard()
{ //print out the current state of gameboard
	for(int j = 0; j<n; j++){cout << "___";} cout << endl;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout << '|'<< gameboard[i][j];
		}
		cout << '|'<< endl;
		for(int j = 0; j<n; j++){cout << "+-";} cout << "+" << endl;
	}
	for(int j = 0; j<n; j++){cout << "___";} cout << endl;
}

int intinput(){
	//gets an integer from the player, used to decide gameboard size
	int x;
	cin >> x;
	if(x<3)
	{
		cout<<"invalid boardsize! choose a valid boardsize, must be 3 or bigger" << endl;
		x = intinput();
	}
	return x;
}

int chooseposition(){
	int pos;
	cin >> pos;
	return pos;
}

void makemove(int player)
{ //get valid coordinates, and place X/O if the spot is empty
	if(player == 1)cout << "Player X, make a move!" << endl;
	if(player == 2)cout << "Player O, make a move!" << endl;
	int x, y;
	cout << "type in row:";
	x = chooseposition();
	cout << "type in column:";
	y = chooseposition();
	x--; y--; //because index starts at 0
	
	while(x > n-1 || y > n-1)
	{
		cout << "that position is outside the gameboard, choose another position" << endl;
		cout << "type in row:";
		x = chooseposition();
		cout << "type in column:";
		y = chooseposition();
		x--; y--; //because index starts at 0
	}
			
	while(gameboard[x][y] != ' ') //if the spot is filled, get another spot!
	{
		cout << "something is already placed in this spot, choose another spot" << endl;
		cout << "type in row:";
		x = chooseposition();
		cout << "type in column:";
		y = chooseposition();
		x--; y--; //because index starts at 0
	}
	if(gameboard[x][y] == ' ') //if the spot is free
	{
		if(player == 1){gameboard[x][y] = 'X';}
		if(player == 2){gameboard[x][y] = 'O';}
	}
}

int scorerow()
{ //returns 1 if player 1 won on any rows, 2 if player 2 won, and 3 if all rows are draw, else it returns 0
	int xinarow = 0;
	int oinarow = 0;
	int rowsdraw = 0;
	for(int x=0; x<n; x++)
	{
		for(int y=0; y<n; y++) 
		{
			if(gameboard[x][y] == 'X') //adds score for row
				xinarow++;
			else if(gameboard[x][y] == 'O')
				oinarow++;
		}
		if(xinarow == n || oinarow == n)//if score per row matches boardsize, somebody won, break loop
			break;
		if(xinarow != 0 && oinarow != 0)
			rowsdraw++; //this row is a draw
		xinarow = 0; //if nobody won this row, reset score
		oinarow = 0;
	}
	if(xinarow == n) //find out who won
		return 1;
	else if(oinarow == n)
		return 2;
	if(rowsdraw == n) //if all rows ended in a draw
		return 3;
	return 0; //nobody won, and its still possible to win in the rows
}
int scorecol()
{ //return 1 if player 1 won, 2 if player 2 won, 3 if its a draw in all columns and 0 if its nothing.
	int xinarow = 0;
	int oinarow = 0;
	int colsdraw = 0;
	for(int y=0; y<n; y++)
	{
		for(int x=0; x<n; x++) 
		{
			if(gameboard[x][y] == 'X') //adds score for column
				xinarow++;
			else if(gameboard[x][y] == 'O')
				oinarow++;
		}
		if(xinarow == n || oinarow == n) //if score per column matches boardsize, somebody won, break loop
			break;
		if(xinarow != 0 && oinarow != 0)
			colsdraw++; //this column is a draw
		xinarow = 0;//if nobody won this column, resets score
		oinarow = 0;
	}
	if(xinarow == n)	//find the winner
		return 1;
	else if(oinarow == n)
		return 2;
	if(colsdraw == n) //if all rows ended in a draw
		return 3;
	return 0;
}
int scorediagonal() //SOMETHING IS WRONG HERE, ON A DIAGONAL WIN ON A 4X4 BOARD from bottom left to top right
{	//returns 1 if player 1 won, 2 if player 2 won, 3 if its a draw in both diagonals and 0 if it nothing
	//check diagonal from top-left to bottom-right
	int xinarow, oinarow, diagdraw = 0; // score counters and counter for diagonal draws
	for(int i=0; i<n; i++)
	{
		if(gameboard[i][i] == 'X')
			xinarow++;
		else if(gameboard[i][i] == 'O')
			oinarow++;
	}
	if(xinarow == n) //if score per diagonal matches boardsize, somebody won
		return 1; //player X won
	else if(oinarow == n)
		return 2; //player O won
	if(xinarow != 0 && oinarow != 0)
		diagdraw++;
	//check diagonal from top-right to bottom-left
	xinarow=0; oinarow = 0; //resets score counters
	int j = n-1; //starts at the rightmost position
	for(int i=0; i<n; i++) //from top row to bottom row
	{
		if(gameboard[i][j] == 'X')
			xinarow++;
		else if(gameboard[i][j] == 'O')
			oinarow++;
		j--;
	}
	if(xinarow == n)	//if score per matches boardsize, somebody won
		return 1;
	else if(oinarow == n)
		return 2;
	if(xinarow != 0 && oinarow != 0)
		diagdraw++;
		
	if(diagdraw == 2) //if both diagonals is a draw, return 3
		return 3;

	return 0; //meh, nothing here.
}

int gameover()
{ 
	//returns 1 if player 1(X) won, 2 if player 2(O) won, 0 if nobody has won yet or 3 if the game ended in a draw.
	//check for winner in rows
	int rowwin = scorerow();
	if(rowwin != 0)
	{
		return rowwin;
	}
	//if nobody won in any rows, check columns
	int colwin = scorecol();
	if(colwin != 0)
	{
		return colwin;
	}
	//if no wins in columns either, check diagonals:
	int diagwin = scorediagonal();
	if(diagwin != 0)
	{
		return diagwin
	}
	//if still no win, then it might be a draw
	if(diagwin == 3 && rowwin == 3 && colwin == 3)
		return 3; //its a draw
	//if nobody won, and its not a draw, that means nobody has won yet
	return 0;
}

int game()
{//game runs in this method, and runs while gameover returns 0, also lets the player choose to play again
	while(gameover() == 0)
	{
		makemove(1); //player X makes a move
		printboard(); //prints the gameboard
		int go = gameover();
		if(go != 0) break; //if somebody won, or its a draw, break this while loop
		makemove(2); //player O makes a move
		printboard(); //prints board
	}
	int go = gameover(); //the result of the game
	if(go == 1){cout << "player X won" << endl;}//duh!
	if(go == 2){cout << "player O won" << endl;}//duh!
	if(go == 3){cout << "its a draw, good job" << endl;}//duh!

	//play another game?
	cout << "play another game? type y or Y for another game, anything else to exit" << endl;
	char again;
	cin >> again;
	if(again == 'y' || again == 'Y')//reset board, and start the game.
	{
		boardreset();
		printboard();
		game();
	}
}

main()
{
	printf("Welcome to INFINITE TIC-TAC-TOE\n");
	cout << "Choose size of gameboard, from 3 and up:" << endl;
	n = intinput(); //int n = size of gameboard, 3 for 3x3, 4 for 4x4, 8 for 8x8, 100 for 100x100
	cout << "Gameboard size set to: " << n << "X" << n << endl;
	cout << "to win you will have to get " << n << " in a row" << endl;
	boardreset();
	printboard();
	game();
	cout << "thanks for playing! have a nice day :D" << endl;
}