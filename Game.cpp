/**file: Game.cpp */
#include<iostream>
#include<fstream> 
#include<string>
#include<vector>

#include"Game.h"
#include"Level.h"
#include"Player.h"
using namespace std;

/**We start here*/
Game::Game(string filename) {
	
	cout << "\n\n///////////////////////////////"
		 << "\nPLEASE WAIT" << endl;
		 
		 
		 
		 parse(filename);
		 
	//	 Player player;
		 
}


/** We load here **/
Game::Game() {

	//No parse, or non of that stuff
	
	}
	

void Game::parse(string source) {
	// check for redundant levels.
	//must verify enough words to form a full level
	
	string str;
	string wordHolder;
	string lineHolder;
	int topLen = 0;
	vector<string> wordCol; // word collector
	ifstream pullSrc(source.c_str());
	
	if(pullSrc.is_open()) {
		bool isNewLine = false;
		while(pullSrc.good()) {
			getline(pullSrc, lineHolder);
			isNewLine = true;

			bool skipChar = false; // to avoid inclusion of special characters into a new word
			
//===Line Assembly
			for(int i = 0; i <= lineHolder.length() - 1; i++) {
				
				//Punctuation Check
				if (!(((lineHolder[i] >= 'a')&&(lineHolder[i] <= 'z'))
				||((lineHolder[i] >= 'A')&&(lineHolder[i] <= 'Z')))
				||((wordHolder.empty()==false)&&(isNewLine==true))) {
					skipChar = true;
					if((wordHolder.empty()==false)&&(isNewLine==true)) skipChar = false;
					
					//Excluding words that start with capital letters
					if(((wordHolder[0] >= 'a')&&(wordHolder[0] <= 'z'))
					||((wordHolder[0] >= 'A')&&(wordHolder[0] <= 'Z'))) {
						//Checks for highest length of words recieved
						if(wordHolder.length() > topLen) {
							topLen = wordHolder.length();
						}
						if(wordHolder.length() > 2) {
							bool isPresent = false;
							
							//Adjusting all proper words to be lowercase
							if(!((wordHolder[0] >= 'a')&&(wordHolder[0] <= 'z'))) {
								unsigned char part = wordHolder[0];
								part = (unsigned char) ((int) part + 32);
								if(part > 'z') { part += 26; }
								wordHolder[0] = part;
							}
						
							//checking for duplicates
							for(int z = 0; z < wordCol.size(); z++) {
								if(wordHolder == wordCol[z]) { isPresent = true; }
							}
							//final stage
							if(isPresent != true) {
								wordCol.push_back(wordHolder); //WORD IS ADDED 
							}
					}
						wordHolder = "";
					}
				}// end of "end of word/punc checker"
				
				//Assembling the word
				if(skipChar == false) { 
					wordHolder += lineHolder[i];
				}
				skipChar = false;
				isNewLine = false;
				
			}// end of line parsing for loop
		} // end of while .good() 
		pullSrc.close();
	} // end of if is_open()
	
/*	for (int i = 0; i < wordCol.size(); i++) {
		cout << wordCol[i] << endl;	
	} */
	makeLevels(wordCol);
/*	//Allocation of Words
	bool isFirstLevel = true;
	while(wordCol.size()!=0) {
		Level testLevel;
		bool addSuccess = false;
		
		//If first, get right to it. 
		if(isFirstLevel == true) {
		testLevel.setLen(wordCol[wordCol.size()-1]);
		addSuccess = testLevel.addWord(wordCol[wordCol.size()-1]);
		lVec.push_back(testLevel);
		isFirstLevel = false;
		numLevels++;
		
		} // Otherwise, do a check before the fact
		else {
			bool isPreExist = false;
			for(int i = 0; i < wordCol.size(); i++) { 
				if(wordCol[wordCol.size() - 1].length() == lVec[i].getLen()) {
					lVec[i].addWord(wordCol[wordCol.size() - 1]);
					isPreExist = true;
				}
			} 
			//If the level of this word's length doesnt exist, create that level
			if(isPreExist != true) {
				testLevel.setLen(wordCol[wordCol.size()-1]);
				addSuccess = testLevel.addWord(wordCol[wordCol.size()-1]);
				lVec.push_back(testLevel);
			}
		}
		
		wordCol.pop_back();
		
		if(addSuccess == false) { cerr << "\nError in insertion\n" << endl; } 
		
	} */ // End of Word Alloc while loop
	
	
} // end of parse;

/**Loads collected words into levels */
void Game::makeLevels(vector<string> wordCol) {
	
	//Allocation of Words
	bool isFirstLevel = true;
	while(wordCol.size()!=0) {
		 cout << "lVec's size = " << lVec.size() << endl;
		Level testLevel;
		bool addSuccess = false;
		
		//If first, get right to it. 
		if(isFirstLevel == true) {
			testLevel.setLen(wordCol[wordCol.size()-1].length());
//			cout << wordCol[wordCol.size()-1] << " the first" << endl; // debug
			addSuccess = testLevel.addWord(wordCol[wordCol.size()-1]);
			lVec.push_back(testLevel);
			isFirstLevel = false;
			numLevels++;
			
		} // Otherwise, do a check before the fact
		else {
			bool isPreExist = false;
			for(int i = 0; i < lVec.size(); i++) { 
			
				
		//		cout << "curr Word's length = " << wordCol[wordCol.size() - 1].length() <<
		//		"; lVec["<<i<<"]'s len = " << lVec[i].getLen() << endl;
				if(wordCol[wordCol.size() - 1].length() == lVec[i].getLen()) {
					isPreExist = true;
					cout << "////"<< wordCol[wordCol.size()-1] << " preExist" << endl; // debug
					addSuccess = lVec[i].addWord(wordCol[wordCol.size() - 1]);

				}
			} 
			//If the level of this word's length doesnt exist, create that level
			if(isPreExist != true) {
				testLevel.setLen(wordCol[wordCol.size()-1].length());
				cout <<"////"<< wordCol[wordCol.size()-1] << " not preExist" << endl; // debug
				addSuccess = testLevel.addWord(wordCol[wordCol.size()-1]);
				lVec.push_back(testLevel);
			}
		}
		
		wordCol.pop_back();
		cout << "wordCol.size() = " << wordCol.size() << endl;
		if(addSuccess == false) { cerr << "\nError in insertion\n" << endl; }
		
		
	}
	cout << "\nout of part 1" << endl;
	//here we test
	for(int i = 0; i < lVec.size(); i++) {
		cout << "For " << i << " level, len = " << lVec[i].getLen() << ", total = " << lVec[i].getTotal() << endl;
		for(int j = 0; j < lVec[i].getTotal(); j++) {
			
			cout << lVec[i].getWord(j, false) << endl;
		}
		
	}
		
		
		
}
	
/** Sorts the generated levels by difficulty*/
void Game::sortLevels() { }

bool Game::load() { }