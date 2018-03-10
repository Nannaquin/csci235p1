all: Word Level Player Game main link

Word: Word.cpp
	g++ -o Word.o -c Word.cpp
Level: Level.cpp
	g++ -o Level.o -c Level.cpp
Player: Player.cpp
	g++ -o Player.o -c Player.cpp
Game: Game.cpp
	g++ -o Game.o -c Game.cpp
main: main.cpp
	g++ -o main.o -c main.cpp
link: Word.o Level.o Player.o Game.o main.o
	g++ -o wordgame Word.o Level.o Player.o Game.o main.o
clean:
	rm link