/**file: Word.h */
#ifndef WORD_H
#define WORD_H

#include<string>
using namespace std;

/**Its what we guessing. */
class Word {
	public:
		/**Summons a word from the list, calls the scramble function. */
		Word(string inStr);
	
		/**Creates the jumbled form of the word.
		@pre: a word has been pulled.
		@post: mixword will be filled with a mixed copy of orgWord.*/
		void scrambleWord();
		
		
		/** Procures the unscrambled word.
		@pre: The Word exists.
		@post: The word, in string form, will be supplied, or ERR if error( word not present).
		@return: Will return orgWord's string if it exists, otherwise "ERR" */
		string getWord();
		
		/**Procures the scrambled word.
		@pre: The scrambled word has been created. */
		string getMixWord();
		
	
		/**Determines if the word is valid for selection.
		@pre: Word is part of a level's array.
		@post: Whether the word has been solved or not will be returned
		@return: True if already solved, false if otherwise. */
		bool isSolved();
		
		
		/**Checks the guess against the orgWord and sets solveState correspondingly
		@pre: The word exists and the player has attempted to solve it. 
		@post: If the guess is correct, solveState is true; If not, remains false.
		@param: inStr  The incoming guess from the player.
		@return: If guess is correct, return true. Otherwise, return false.*/
		bool guess();
	
	
	private:
	
		//Original word.
		string orgWord;
		//Mixed up word.
		string mixWord;
		//If word has been solved or not.
		bool solveState;
	
};
#endif