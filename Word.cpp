/**file: Word.cpp */
#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<sstream>
#include"Word.h"
using namespace std;

/**Summons a word from the list, calls the scramble function.
@pre: A file has been parsed.
@post: A Word object will be properly initialized.
@*/
Word::Word(string inStr) 
{ 
	orgWord = inStr;
	solveState = false;
	scrambleWord();	
}

/**For loading previous save file. */
Word::Word() { }

/**Creates the jumbled form of the word.
@pre: a word has been pulled.
@post: mixword will be filled with a mixed copy of orgWord.*/
void Word::scrambleWord() 
{ 
    srand(time(0));
	bool isEven = false;

	
	if(orgWord.length()%2==0) { isEven = true;}
	
	int z;
	z = 1+rand()%10;
	
	string outWord;
	if ((z > 5)||(orgWord.length() == 3)) {
		if(isEven == true) {
			//if even, go along swapping out every pair of letters
			int i = 0;
			while(i < orgWord.length()) {
				
				outWord += orgWord[i+1];
				outWord += orgWord[i];			
				
				i += 2;
			}	
		}
		else { 
			//if odd, do above but at the end, swap 1st and last char;
			int i = 0;
			while(i < orgWord.length()) {
				
				if(i == orgWord.length() - 1) {

					outWord += outWord[0];
					outWord[0] = orgWord[orgWord.length() - 1];
				}		
				else {
					outWord += orgWord[i+1];
					outWord += orgWord[i];
				}
				i += 2;
			}
		}
	}
	else if (z < 6) {
		if(isEven == true) {
			//Same as even above, but invert word first.
			int i = 0;
			int j = orgWord.length() - 1;
			
			outWord.resize(orgWord.length());
			while (i < orgWord.length()/2) { 
				outWord[i] = orgWord[j];
				outWord[j] = orgWord[i];
				i++;
				j--;
			}
		}
		else { 			
			//shift of 3 characters at a time
			int i = 0;
			outWord = orgWord;
			while(i < orgWord.length()-2) {
				
				char temp;
				temp = outWord[i];
				outWord[i] = outWord[i+1];
				outWord[i+1] = outWord[i+2];
				outWord[i+2] = temp;
				i++;
			}
		}
	}
	mixWord = outWord;
}

/**All three for loading save purposes */
void Word::setOrgWord(string inStr) { orgWord = inStr; }
void Word::setMixWord(string inStr) { mixWord = inStr; }
void Word::setSolveState(bool inVal) { solveState = inVal; }

/** Procures the unscrambled word. */
string Word::getWord() { return orgWord; }

/**Procures the scrambled word.
@pre: The scrambled word has been created. */
string Word::getMixWord() { return mixWord; }

/**Determines if the word is valid for selection. */
bool Word::isSolved() { return solveState; }

/**Loads data from word to be sent for saving. */
string Word::savePrint() 
{ 

	ostringstream output;
	output << orgWord;
	output << "\n";
	output << mixWord;
	output << "\n";
	output << solveState;
	output << "\n";
	
	string truOut = output.str();
	return truOut;
	}
/**Checks the guess against the orgWord and sets solveState accordingly. */
bool Word::guess(string inStr) 
{
	if(inStr == orgWord) {
		solveState = true;
	}
	return solveState;
		
}
