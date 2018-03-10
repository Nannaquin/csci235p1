/**file: Level.cpp */
#include<iostream>
#include"Level.h"
#include"Word.h"
using namespace std;

Level::Level(int inLen){ }

		
void Level::setLen(){ }

void Level::setTotal(){ }

/**Retrieval for redun checking and saving */
int Level::getLen() { }

int Level::getTotal(){ }

/**Pulls word to be guessed. 
@pre: checkTotal() has returned true
(so this wont call a non-existant word).
@post: A word will be pulled.
@param: wordNum  the word to be retrieved. */
Word Level::getWord(int wordNum){ }

/** Checks potential next word against
the total amount of words.
@pre: wordTotal is above zero, reflecting 
that there are words in the wordArray.
@post: Either a word pulling will be approved
or denied.
@param: wordNum  The nth word that will be checked
against the total. 
*/
bool Level::checkTotal(int wordNum) { }

/** Pulls word from exterior source. Can fail if a capital letter is found
@pre: Level has been initialized. inWord has no non letter characters.
@post: Ideally, a new word is added to wordArr
@param: inWord  The Word to be added.
@return: True if successful, otherwise false. */
bool Level::addWord(Word inWord) { }

/** Mixes the order of the words.
@pre: the array of words has already been populated.
@post: The order of words will be randomized, in comparison to the original order.
@param: inArr  Our original order of words for the current level. */
void Level::scrambleOrder(wPtr inArr) { }