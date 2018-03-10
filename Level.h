/**file: Level.h */
#ifndef LEVEL_H
#define LEVEL_H

#include "Word.h"
typedef Word* wPtr;



/**Holds the current round's selected words,  */
class Level {
	public:
		/**
		@pre: setLevel must be >=3
		@post: Level will have an randomized array of jumbled words.
		*/
		Level(int inLen);

		
		void setLen();
		
		void setTotal();
		
		/**Retrieval for redun checking and saving */
		int getLen();
		
		int getTotal();
		
		/**Pulls word to be guessed. 
		@pre: checkTotal() has returned true
		(so this wont call a non-existant word).
		@post: A word will be pulled.
		@param: wordNum  the word to be retrieved. */
		Word getWord(int wordNum);
		
		/** Checks potential next word against
		the total amount of words.
		@pre: wordTotal is above zero, reflecting 
		that there are words in the wordArray.
		@post: Either a word pulling will be approved
		or denied.
		@param: wordNum  The nth word that will be checked
		against the total. 
		*/
		bool checkTotal(int wordNum);
		
		/** Pulls word from exterior source. Can fail if a capital letter is found
		@pre: Level has been initialized. inWord has no non letter characters.
		@post: Ideally, a new word is added to wordArr
		@param: inWord  The Word to be added.
		@return: True if successful, otherwise false. */
		bool addWord(Word inWord);
		
		/** Mixes the order of the words.
		@pre: the array of words has already been populated.
		@post: The order of words will be randomized, in comparison to the original order.
		@param: inArr  Our original order of words for the current level. */
		void scrambleOrder(wPtr inArr);
	
	private:
		
		//The current level. Will determine what words are summoned. 
		int len;
		//The list of words
		wPtr wordArr;
		//The number of words in the wordArr
		int wordTotal;
	
};
#endif