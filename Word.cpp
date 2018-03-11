/**file: Word.cpp */
#include<iostream>
#include<string>
#include"Word.h"
using namespace std;

Word::Word(string inStr) { 
	orgWord = inStr;
	solveState = false;
	//scrambleWord();
	
	
}

void Word::scrambleWord() { }

string Word::getWord() { return orgWord; }

string Word::getMixWord() { return mixWord; }

bool Word::isSolved() { return solveState; }

bool Word::guess(string inStr) {
	if(inStr == orgWord) {
		solveState = true;
	}
	return solveState;
		
}
