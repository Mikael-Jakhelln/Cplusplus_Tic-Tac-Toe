
all: classes	
	g++ blackjack.cpp class*.o -o blackjack

classes:
	g++ -c class*.cpp

game: gambler
	g++ -c class_game.cpp -o class_game.o

gambler: 
	g++ -c class_gambler.cpp -o class_gambler.o
