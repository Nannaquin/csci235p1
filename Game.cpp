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
		 
		 
		 
	//	 parse(filename);
		 
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
	ifstream pullSrc("testfile1.txt");
	
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
						if(wordHolder.length() > topLen) {
							topLen = wordHolder.length();
						}
						if(wordHolder.length() > 2) {
							bool isPresent = false;
							
							//Preparing for check
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
	
	for (int i = 0; i < wordCol.size(); i++) {
		cout << wordCol[i] << endl;	
	}
} // end of parse;

bool Game::load() { }