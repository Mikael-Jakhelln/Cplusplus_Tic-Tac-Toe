#the game consists of 5 classes
------------------------------
#####gameboard.cpp 
- contains the board, and sets pieces on the board
#####score.cpp 
- checks the gameboard for win or draw.
#####player.cpp(player_human.cpp and player_bot.cpp)
- what kind of player it is, gets coordinates to place on the board
#####game.cpp 
- brings everything together to play
#####play_tictactoe.cpp 
- runs the tic-tac-toe

______________________________
#Class descriptions
------------------------------
##gameboard
---------
this class contains the playingfield.
the actual board is a 2d char vector.
blank spots are marked with ' '
player 1 pieces are marked with 'X'
player 2 pieces are marked with 'O'
it has 4 functions:
gameboard(int s) - is the constructor, s is the size of the board
resetboard() - blanks out the board
printboard() - prints out the board, and all the pieces on it
makemove(int player, int x, int y) - puts a piece on the board and returns true, returns false if there is already a piece in that position
_______
##score
-------
score checks the board for a win or a draw.
all its funtions returns an int:
0 if nobody won yet
1 if X won
2 if O won
3 if it is a draw
its functions are:
scorerow(int n, vector<vector<int>> gb) - checks for win or draw in all the rows.
scorecol(int n, vector<vector<int>> gb) - checks for win or draw in all the columns.
scorediagonal(int n, vector<vector<int>> gb) - checks for win or draw in the diagonals.
anybodywinyet(int n, vector<vector<int>> gb) - runs all the other functions, to check for a winner, if there is no winner it checks if there is a draw in all the rows, columns and diagonals, then returns 0,1,2 or 3 accordingly.

__________
##player
----------
player is an abstract class, this is so the two players in game can be initialized to whatever kind of player they are supposed to be, human, bot, (network even).
the main funtion of player is to get some coordinates from it
int playernumber - is used to identify if it plays as X or O
getcoords(int player, int size) - returns some coords.
_____________
###player_human
-------------
getcoords returns coordinates from the user(s)
__________
###player_bot
----------
player_bot.getcoords(size, board)this is the computer AI, right now it just returns random coords, until something works.
#####int difficulty - defines the method to use to find coords
its functions are:
#####getcoords(int player, int size) - returns some coords.
	difficulty=1 returns some random coordinates within the gameboard.	
	difficulty=2 return the best possible coordinates to place a piece.
#####checkrow - should check if there is any threats in any of the rows, returns the row and the threat level, measures in pieces left for the other player to win on that row.
#####checkcol - same as checkrow, just for columns
#####checkdiagonal - same as the others, just for diagonals
#####decidemove - returns coordinates, based on the checks.
#####random move - returns some random coordinates.

_________
game
---------
brings all the classes together into tic-tac-toe.
its functions are:
intinput - gets userinput and returns an int.
intinput2 -(unfinished) better intinput with validation for ints(so close :()
getcoords - gets coordinates from user, first gets row, then column.
game() - this is the gameloop, and it goes like this:
1 - makes user choose gameboard size.
2 - makes the user choose number of human players
2.1 - chooses who goes first
3 - initializes players as bot or human, depending on the number 	of human players.
5 - starts the actual gameloop
5.1.1 - checks what player to get coords from.
5.1.2 - gets coordinates from said player
5.1.4 - tries to put a piece on the gameboard with aquired 		coordinates.
5.1.4.1 - if it fails, start again at 5.1
5.1.4.2 - if it succeeds, the piece is now placed on the board
5.2 - prints board
5.3 - checks the board for win/draw/continue
5.4 - if win/draw, break loop and go to 6, else continue
5.5 - gets move from the other player, then does the same as loop 5.1
5.6 - prints board
5.7 - checks score
5.8 - if win/draw, break loop and go to 6, else start from 5 again.
6 - somebody won or its a draw. check score
7 - print out the score
8 - lets player choose to play again, if 'y' start from 1 again.

______________
play_tictactoe
--------------
prints out welcome message
runs function game() from game.cpp
prints out goodbye message
