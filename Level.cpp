/**file: Level.cpp */
#include<iostream>
#include"Level.h"
#include"Word.h"
using namespace std;

Level::Level(int inLen){ }

Level::Level() { }

		
void Level::setLen(int inVal){ len = inVal; }

void Level::setTotal(){ }

/**Retrieval for redun checking and saving */
int Level::getLen() { return len; }

int Level::getTotal(){ return wVec.size(); }

/**Pulls word to be guessed. 
@pre: checkTotal() has returned true
(so this wont call a non-existant word).
@post: A word will be pulled.
@param: wordNum  the word to be retrieved.
isScram  if true, return scrambled string. */
string Level::getWord(int wordNum, bool isScram){
	
	string retStr;
	
	if (isScram == true){ retStr = wVec[wordNum].getMixWord(); }
	else retStr = wVec[wordNum].getWord(); 
	
	return retStr;
	
}

/** Checks potential next word against
the total amount of words.
@pre: wordTotal is above zero, reflecting 
that there are words in the wordArray.
@post: Either a word pulling will be approved
or denied.
@param: wordNum  The nth word that will be checked
against the total. 
*/
bool Level::checkTotal(int wordNum) { 
/** Might just get wVec's size instead, now that its a vector */
}

/** Pulls word from exterior source. Can fail if a capital letter is found
@pre: Level has been initialized. inWord has no non letter characters.
@post: Ideally, a new word is added to wordArr
@param: inStr  The Word to be added.
@return: True if successful, otherwise false. */
//bool Level::addWord(Word inWord) { }
bool Level::addWord(string inStr) { 
	Word temp(inStr); 
	wVec.push_back(temp);
	total++;
	
	return true; 
	}

/** Mixes the order of the words.
@pre: the array of words has already been populated.
@post: The order of words will be randomized, in comparison to the original order.*/
void Level::scrambleOrder() { }