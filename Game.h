/**file: Game.h */

/*

Saving:
Save 
remaining lives, 
lifelines, 
level, 
finished words from current level, 
current word

classes

/** Holds iterative loop for levels and shit. Tests for game over, holds
input shit, quits, etc */
//Game



/** Holds plain word, jumbled form for that round. Had jumble
function. Has test guess function. */
//Word

/** Holds list of chosen words.  */
//Level

/** Searches a text file */
//Parse

/** Will hold stats (all time high, current progress),
lifelines, lives, etc */
//Player

/** Manages saved and loaded data. Really does the I/O business */ 
//SaveData

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
#include"Level.h"
#include"Player.h"

typedef Level* lPtr;
class Game {
	public:
		/**Starts new game.
		@pre: A file name has been entered.
		@post: A new game will be loaded.
		@param: filename  The name of the file to be parsed for words. */
		Game(string filename);
	
		/**Alternate constructor to load the previous game.
		@pre: No filename has been entered.
		@post: The previously saved game will be loaded.
		*/
		Game();
		
		/**Parses the data */
		void parse(string source);
		
		/**Loads save data if available. */
		bool load();

	
	private:
		
		
		lPtr levelArr;
		int numLevels;
		Player player;
};


#endif