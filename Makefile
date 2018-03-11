all: Word Level Player Game main link

Word: Word.cpp
	g++ -o Word.o -c Word.cpp -g
Level: Level.cpp
	g++ -o Level.o -c Level.cpp -g
Player: Player.cpp
	g++ -o Player.o -c Player.cpp -g
Game: Game.cpp
	g++ -o Game.o -c Game.cpp -g
main: main.cpp
	g++ -o main.o -c main.cpp -g 
link: Word.o Level.o Player.o Game.o main.o
	g++ -o wordgame Word.o Level.o Player.o Game.o main.o -g 
clean:
	rm link
