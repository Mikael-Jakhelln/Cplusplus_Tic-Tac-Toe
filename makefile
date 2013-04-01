
all:
	g++ -c play_tictactoe.cpp -o play_tictactoe.o
	@echo "g++ play_tictactoe.cpp -o play_tictactoe.o"
	@echo "run tictactoe with ./tictactoe.o"
	
clean:
	rm  play_tictactoe.o
	



