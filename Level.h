/**file: Level.h */
#ifndef LEVEL_H
#define LEVEL_H

#include<vector>
#include<sstream>
#include "Word.h"

//typedef Word* wPtr;



/**Holds the current round's selected words,  */
class Level {
	
	private:
		
		//The current level. Will determine what words are summoned. 
		int len;
		//The collection of words.
		vector<Word> wVec;	
		//How many correct guesses. If 3, next level.
		int corrCount;
		// if the level is beat or not. For saving purposes.
		bool winState;
		
	public:
		/** Constructor that sets the difficulty/level.
		@pre: setLevel must be >= 3
		@post: Level will have an randomized array of jumbled words. */
		Level(int inLen);
		
	/** Needed for loading previous save. */	
		Level();
		

		/**For loading save files. */
		void setLen(int inVal);
		void setTotal(int & inVal);
		void setWinState(bool inVal);
		void setCorrCount(int & inVal);
		
		/**Retrieval for redundancy checking and saving */
		int getLen();
		int getTotal();
		bool getWinState();
		
		/** Outputs a particular Level's details plus the
		details of its Words, for saving purposes.
		@pre: The player has chosen to leave the game
			willingly.
		@post: All of the Level's details and the details
			of its Words will be output via a single 
			string.
		@return: A single string, containing all the info
			listed above.*/ 
		string saveOutput();
		
		/**Pulls word to be guessed. 
		@pre: checkTotal() has returned true
		(so this wont call a non-existant word).
		@post: A word will be pulled.
		@param: wordNum  the word to be retrieved.
				isScram  if true, return scrambled string. */
		string getWord(int wordNum, bool isScram);
		
		/**A mere vehicle for a word's solvestate
		@pre: An attempt to find an unsolved word is being made.
		@post: The targeted word's solve state will be retrieved.
		@param: wordNum  the index for the targeted word.
		@return: True if solved, otherwise false */
		bool pullSolveState(int & wordNum);
		
		/** Returns result of guess.
		@pre: A guess has been made.
		@post: Result of guess will be determined
		@param: wordNum  The index of the targeted word 
				attempt  The string of the guess.
		@return:  True if success, otherwise false*/
		bool processAttempt(int wordNum, string attempt);
		

		/** Pulls word from exterior source. Can fail if a capital letter is found
		@pre: Level has been initialized. inWord has no non letter characters.
		@post: Ideally, a new word is added to wordArr
		@param: inWord  The Word to be added.
		@return: True if successful, otherwise false. */
		bool addWord(string inWord);
		
		/** Pulls data to form a word in save loading.
		@pre: A previous save is being loaded. 
		@post: A given part of a word will be passed.
		@param: inStr  Either string component of the word,
			also the boolean value assoc with the word. 
				inVal  1 for unscram word, 2 for scram'd word,
			3 for boolean value as string.
				wordVal  The index of word we are targeting*/
		void loadWord(string inStr, int inVal, int wordVal);
		
		/**Increases correct count
		@pre: A correct guess has been made.
		@post: corrCount will be incremented.*/
		void incrCount();
		
		/**Checks to see if its time to move on.
		@pre: A correct guess has been made.
		@post: If true returned, next Level will be played.
		@return: If currCount >= 3, return true. Otherwise false. */
		bool checkProg();
	
		
		/** Mixes the order of the words. 
		@pre: the array of words has already been populated.
		@post: The order of words will be randomized, in comparison to the original order. */
		void scrambleOrder();

};
#endif