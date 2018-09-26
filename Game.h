/**file: Game.h */

/*

Progression
-----------
Each successive win levelwise will incriment a counter.
	Must plan for some textfiles not having enough words of similar length to constitute a level.


*/
#ifndef GAME_H
#define GAME_H

#include<iostream>
#include<string>
#include<vector>
#include"Level.h"
#include"Player.h"

//typedef Level* lPtr;
class Game {
	
	private:
		
		
		int currentLevel; // held for saving and loading purposes.
		int wordIndex; // where we are operating in a given level.
		vector<Level> lVec; //Where the levels are held. 
		
		string inputFile; // holder for save/load shenanigans
		string athBest; // all time longest word/highest  difficulty
		int athScore; // all time high score for current input file
		
	public:
		/**Starts new game. Entirety of the game occurs within this.
		@pre: A file name has been entered.
		@post: A new game will be loaded.
		@param: filename  The name of the file to be parsed for words. */
		Game(string filename);
	
		/**Alternate constructor to load the previous game. Similarly
		contains the entire game loop.
		@pre: No filename has been entered.
		@post: The previously saved game will be loaded.
		*/
		Game();
		
		/**Prints spaces between sides of screen
		@pre: Game has loaded data
		@post: spaces will be printed
		@param:  maxSpaces  The maximum amount of dist between
		the leftmost and rightmost output on this line
				 inVal  The integer value who's length will be
		subtracted from maxSpaces */
		void spaces(int maxSpaces, int inVal);
		
		/**Prints spaces between sides of screen 
		@pre: Game has loaded data
		@post: spaces will be printed
		@param:  maxSpaces  The maximum amount of dist between
		the leftmost and rightmost output on this line
				 inStr  The string who's length will be
		subtracted from maxSpaces */
		void spaces(int maxSpaces, string inStr); 
		
		/**Parses the data
		@pre: A filename has been specified at main menu (a new game)
		@post: words will be collected if their length is at least 3 characters
		@param: source  Where the words will be sourced from. */
		void parse(string source);
		
		/**Loads collected words into levels 
		@pre: Words have been collected in parse() function
		@post: words will be in levels based on their character less
		@param: wordCol  The collection of words from parse()*/
		void makeLevels(vector<string> & wordCol);
		
		/** Sorts the generated levels by difficulty
		@pre: levels have been made in makeLevels()
		@post: levels will be sorted by difficulty (character length) */
		void sortLevels();
		
		/**Saves current game progress and stats
			@pre: The player has opted to quit the game.
			@post: Game details will be saved.
			@param: p:  The Player object, with all of its stats to be saved.
					athScore: The persisting stat related to the particular input file.
					athBest:  Another persisting stat related to the particular input file.
					cLvl:  The index for what level we were last visiting.
					inFile: the particular input file the data is derived from. */
		void save(Player p, int athScore, string athBest, int cLvl, string inFile);
		
		/**Loads save data if available.
		@pre: Either of Game's constructors have been called.
		@post: The appropriate files to display stats or continue
			a saved game will be loaded.
		@param: filename  The name of the file to be loaded, or "NULL" if continuing
			a previous save.
				newGame  Whether or not the Game load is being called from
			is a new one.
				player  The player object from the calling Game.
		@return: if not illegal load, false. Otherwise, true. */
		bool load(string filename, bool newGame, Player& player);
		
		/** Outputs stuff onto the screen */
		void printMenu(Player & player);
		
		/** Operates the guess process */
		void attemptOption(Player & player, bool & exitState);
		

};


#endif