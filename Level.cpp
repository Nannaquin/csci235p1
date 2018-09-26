/**file: Level.cpp */
#include<iostream>
#include<sstream> 
#include<string> 
#include"Level.h"
#include"Word.h"
using namespace std;

/** Constructor that sets the difficulty/level. */
Level::Level(int inLen):len(inLen), corrCount(0), winState(false)
{
	
}


/** Needed for loading previous save. */
Level::Level():corrCount(0), winState(false)
{

}

		
void Level::setLen(int inVal) { len = inVal; }

void Level::setTotal(int & inVal) { wVec.resize(inVal); };

void Level::setWinState(bool inVal) { winState = inVal; }

void Level::setCorrCount(int & inVal) { corrCount = inVal; }

/**Retrieval for redundancy checking and saving */
int Level::getLen() { return len; }

int Level::getTotal(){ return wVec.size(); }

bool Level::getWinState() { return winState; }

/** Outputs a particular Level's details plus the
details of its Words, for saving purposes. */ 
string Level::saveOutput() 
{ 
	ostringstream output;
	
	output << len;
	output << "\n";
	output << wVec.size();
	output << "\n";
	output << corrCount;
	output << "\n";
	output << winState;
	output << "\n"; 


	/*Collecting the details of every word in
		this particular level. */
	for(int i = 0; i < wVec.size(); i++) { 
		output << wVec[i].savePrint();
	}
	
	output << "/\n";  
	string truOut = output.str();
	return truOut;


}
/** Pulls word to be guessed.*/
string Level::getWord(int wordNum, bool isScram)
{
	
	string retStr;
	
	if (isScram == true){ retStr = wVec[wordNum].getMixWord(); }
	else retStr = wVec[wordNum].getWord(); 
	
	return retStr;
	
}

/** A mere vehicle for a word's solvestate. */
bool Level::pullSolveState(int & wordNum) { return wVec[wordNum].isSolved(); }

/** Returns result of guess.*/
bool Level::processAttempt(int wordNum, string attempt) { return wVec[wordNum].guess(attempt); }


/** Pulls word from exterior source.*/
bool Level::addWord(string inStr) 
{ 
	Word temp(inStr); 
	wVec.push_back(temp);
	
	return true; 
}

/** Pulls data to form a word. 
@pre: A previous save is being loaded. 
@post: A given part of a word will be passed.
@param: inStr  Either string component of the word,
	also the boolean value assoc with the word. 
		inVal  1 for unscram word, 2 for scram'd word,
	3 for boolean value as string. 
		wordVal  Which word we are targeting */
void Level::loadWord(string inStr, int inVal, int wordVal) 
{ 

	switch(inVal) { 
	
		case 1: {
			wVec[wordVal].setOrgWord(inStr);
			break;
			}
		case 2: {
			wVec[wordVal].setMixWord(inStr);
			break;
		}
		case 3: { 
			istringstream convert(inStr);
			int x; // holds converted string.
			convert >> x;
			wVec[wordVal].setSolveState((bool) x); 
			break;
		}
		default: break;
				
	}

}

	
/**Increases correct count
@pre: A correct guess has been made
@post: corrCount will be incremented */
void Level::incrCount() { corrCount++; }

/**Checks to see if its time to move on.
@pre: A correct guess has been made.
@post: If true returned, next Level will be played.
@return: If currCount >= 3, return true. Otherwise false. */
bool Level::checkProg() 
{

	if(corrCount >= 3) winState = true;
	return winState;
	
	}


/** Mixes the order of the words.
@pre: the array of words has already been populated.
@post: The order of words will be randomized, in comparison to the original order.*/
void Level::scrambleOrder() { }