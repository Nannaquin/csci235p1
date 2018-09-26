/**file: Game.cpp */
#include<iostream>
#include<fstream> 
#include<string>
#include<vector>
#include<sstream>

#include"Game.h"
#include"Level.h"
#include"Player.h"
using namespace std;

/**We start here
@pre: A new game has been started.
@post: A game will be loaded and ready to play.
@param: filename: the name of the file be parsed.*/
Game::Game(string filename):athBest("NA"), athScore(0), inputFile(filename)
{
	
	cout << "\n\n////////////"
		 <<   "\nPLEASE WAIT" 
		 <<   "\n////////////" << endl;
		 

//	athBest = "NA";
//	athScore = 0;
	Player player;
	load(inputFile, true, player);
//	inputFile = filename;
	 
	//Creation
	parse(inputFile);
	
	currentLevel = 0;
	wordIndex = 0; // was an int declaration. Local var, etc

	
	cout << "\n\n=================\n\n" << endl;
	 
	bool exitState = false;
	
	while(exitState == false) {
		int choice = -1;
		
		printMenu(player);
		
		while(!(cin >> choice)) {
			cin.clear();
			cin.ignore();
			cout << "\nInvalid input. 0, 1, or 2, please: " << endl;
		}
		cout << "\n\n" << endl;
		
		switch(choice) {
			case 0: { // Quitting time, and saving I guess
				save(player, athScore, athBest, currentLevel, inputFile);
				exitState = true;
				break;
			}
			case 1: { //THE PLACE WHERE WE GUESS STUFF
			
				attemptOption(player, exitState);
				break;
			} // ================ end of guess scenario
			
			case 2: { //Trying to use a lifeline
				if(player.getLives() == 1) {
					if(player.useLifeLine() == true) {
						wordIndex++;
						//Searching for word that isnt solved
						while (lVec[currentLevel].pullSolveState(wordIndex) == true) {
							if(wordIndex >= lVec[currentLevel].getTotal()) { wordIndex = 0; }
							wordIndex++;
						}
					}
				}
				else cout << "[(!!!)Must be on LAST life to use!]" << endl;
				break;
			}
			
			default: {
				cout << "How wonderful! Another invalid entry." << endl;
				break;
			}
		}
		
		if(player.getLives() < 1) {
			cout << "\n\n\n\nGAME OVER\n\n\n\n" << endl;
			exitState = true;
			save(player, athScore, athBest, -1, inputFile);
		}
			
		
		
	}
}


/** We load here **/
Game::Game() 
{
	
	
	/* The only difference from the other constructor is these two lines below 
	instead of its first 8 lines starting at athBest. */
	Player player;
	bool exitState = load("NULL", false, player);
	
	cout << "\n\n=================\n\n" << endl;
	 
	
	
	while(exitState == false) {
		int choice = -1;
		
		printMenu(player);
		
		while(!(cin >> choice)) {
			cin.clear();
			cin.ignore();
			cout << "\nInvalid input. 0, 1, or 2, please: " << endl;
		}
		cout << "\n\n" << endl;
		
		switch(choice) {
			case 0: { // Quitting time, and saving I guess
				save(player, athScore, athBest, currentLevel, inputFile);
				exitState = true;
				break;
			}
			case 1: { //THE PLACE WHERE WE GUESS STUFF
				attemptOption(player, exitState);
				break;
			} // ================ end of guess scenario
			
			case 2: { //Tryng to use a lifeline
				if(player.getLives() == 1) {
					if(player.useLifeLine() == true) {
						wordIndex++;
						//Searching for word that isnt solved
						while (lVec[currentLevel].pullSolveState(wordIndex) == true) {
							if(wordIndex >= lVec[currentLevel].getTotal()) { wordIndex = 0; }
							wordIndex++;  
						}
					}
				}
				else cout << "Must be on last life to use" << endl;
				break;
			}
			
			default: {
				cout << "How wonderful! Another invalid entry." << endl;
				break;
			}
		}
		
		if(player.getLives() < 1) {
			cout << "\n\n\n\nGAME OVER\n\n\n\n" << endl;
			exitState = true;
			save(player, athScore, athBest, -1, inputFile);
		}
			
		
		
	}
	//No parse, or non of that stuff
	
}
	
/**Prints spaces between sides of screen
@pre: Game has loaded data
@post: Spaces will be printed to make the UI aesthetically pleasing.
@param:  maxSpaces  The maximum amount of dist between
the leftmost and rightmost output on this line
		 inVal  The integer value who's length will be
subtracted from maxSpaces */
void Game::spaces(int maxSpaces, int inVal)
{ 
	
	int shortVal = 0;
	
	if ((inVal >= 0)&&(inVal < 10)) shortVal = 1;
	else if ((inVal >= 10)&&(inVal < 100)) shortVal = 2;
	else if ((inVal >= 100)&&(inVal < 1000)) shortVal = 3;
	
	maxSpaces -= shortVal; 
	while(maxSpaces > 0) {
		cout << " ";
		maxSpaces--;
	}
}

/** Prints spaces between sides of screen.
@pre: Game has loaded data.
@post:  Spaces will be printed to make the UI aesthetically pleasing.
@param: maxSpaces  The maximum amount of dist between
the leftmost and rightmost output on this line
		inStr  A string whose number of characters we 
subtract to the number of spaces printed. */
void Game::spaces(int maxSpaces, string inStr) 
{ 
	
	maxSpaces -= inStr.length(); 
	while(maxSpaces > 0) {
		cout << " ";
		maxSpaces--;
	}
}
	
//


	

void Game::parse(string source) 
{
	

	string wordHolder; // holds a word to be assembled
	string lineHolder; // holds a line of characters to be disected. 
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

	makeLevels(wordCol);

	sortLevels();
	
	
} // end of parse;

/**Loads collected words into levels */
void Game::makeLevels(vector<string> & wordCol) 
{
	
	//Allocation of Words
	bool isFirstLevel = true;
	while(wordCol.size()!=0) {
		Level testLevel;

		
		//If first, get right to it. 
		if(isFirstLevel == true) {
			testLevel.setLen(wordCol[wordCol.size()-1].length());
			testLevel.addWord(wordCol[wordCol.size()-1]);
			lVec.push_back(testLevel);
			isFirstLevel = false;
			
		} // Otherwise, do a check before the fact
		else {
			bool isPreExist = false;
			for(int i = 0; i < lVec.size(); i++) { 
			
				
				if(wordCol[wordCol.size() - 1].length() == lVec[i].getLen()) {
					isPreExist = true;
					lVec[i].addWord(wordCol[wordCol.size() - 1]);

				}
			} 
			//If the level of this word's length doesnt exist, create that level
			if(isPreExist != true) {
				testLevel.setLen(wordCol[wordCol.size()-1].length());
				testLevel.addWord(wordCol[wordCol.size()-1]);
				lVec.push_back(testLevel);
			}
		}
		
		wordCol.pop_back();	
	}	// end of while wordcol's size isnt zero			
}
	
/** Sorts the generated levels by difficulty,
	and disqualifies levels that are too small
	or duplicates. */
void Game::sortLevels() 
{
		
	int i, j;
	Level temp;
	for( i = 0; i < lVec.size() - 1; i++) {
		for( j = 0; j < (lVec.size() - i - 1); j++ ) {

			if(lVec[j].getLen()>lVec[j+1].getLen()) 
			{
				temp=lVec[j];
				lVec[j]=lVec[j+1];
				lVec[j+1]=temp;
			}
		}
	}
	
	//Pruning levels with insufficient amt of words
	int index = 0;
	while(index<lVec.size()) {


		if(lVec[index].getTotal() < 3) { 
			for(int z = index + 1; z < lVec.size(); z++) { 
				lVec[z - 1] = lVec[z];
			}
			lVec.resize(lVec.size() - 1);
		}
		else index++;
	}
	
	//Culling Duplicate Levels
	index = 0;
	while(index<lVec.size()) {

		if(lVec[index].getLen() == lVec[index+1].getLen()) { 
			for(int z = index + 1; z < lVec.size(); z++) { 
				lVec[z - 1] = lVec[z];
			}
			lVec.resize(lVec.size() - 1);
		}
		else index++;
	}
	
	
}

/**Saves current game progress and stats
@pre: The player has opted to quit the game.
@post: Game details will be saved.
@param: p:  The Player object, with all of its stats to be saved.
		athScore: The persisting stat related to the particular input file.
		athBest:  Another persisting stat related to the particular input file.
		cLvl:  The index for what level we were last visiting.
		inFile: the particular input file the data is derived from. */
void Game::save(Player p, int athScore, string athBest, int cLvl, string inFile) 
{ 
	
	ofstream saveData ("savefile.txt", ios::trunc);
	
	saveData << "[FILESTATS]" << endl; // 0
	saveData << inFile << endl; // 1
	saveData << athScore << endl; //2
	saveData << athBest << endl;//3
	saveData << lVec.size() << endl;//4
	
	saveData << "[PLAYER]" << endl;//5
	saveData << p.getCurrentBest() << endl;//6
	saveData << p.getLevelsWon() << endl;//7
	saveData << p.getScore() << endl;//8
	saveData << p.getLives() << endl;//9
	saveData << p.getLifeLines() << endl;//10
	
	saveData << "[CURRENTSTATS]" << endl;//11
	saveData << cLvl << endl;//12
	saveData << wordIndex << endl;//13
	saveData << lVec.size() << endl;//14
	
	saveData << "[LEVELS]" << endl;//15
	
	for(int i = cLvl; i < lVec.size(); i++) { 
		
		saveData << lVec[i].saveOutput();
	
	}
	
	saveData << "~"; // end of file marker
	
	saveData.close();

}

/**Loads save data if available.
@pre: Either of Game's constructors have been called.
@post: The appropriate files to display stats or continue
	a saved game will be loaded.
@param: filename: The name of the file to be loaded, or "NULL" if continuing
	a previous save.
		newGame: Whether or not the Game load is being called from
	is a new one.
		player: The player object from the calling Game.
@return: if not illegal load, false. Otherwise, true. */
bool Game::load(string filename, bool newGame, Player& player) 
{ 
	ifstream pullSave ("savefile.txt");
	
	
	string lineHolder;
	string wordHolder; 
	int lineCount = -1; //Our index for processing a save file
	int lIndex = 0; // Level Index
	int inWord = 0; //For current word being taken in
	bool isNewFile = false; // what will tell us to skip the data collection
	bool isIllegal = false; // If someone tries to load after losing a game, prevents reloading last game.
	
	if(pullSave.is_open()) {
		while((pullSave.good())&&(lineCount != -4)) { // -4 is our exit value.
			getline(pullSave, lineHolder);
			if(lineCount >= -1) { lineCount++; }
			if((lineCount == 5)&&(newGame == true)) { lineCount = -4; } // If new game, dont collect rest of stuff	
			if(lineHolder=="~") lineCount = -4; //if at end, end
			
			//Initial data gathering;
			switch(lineCount) {
				
				case 1: {
					//if files are same
					if(lineHolder == filename) {
						inputFile = lineHolder;
					}
					else isNewFile = true;
					
					//If we are calling from second constructor, isnt a new file
					if(filename == "NULL") { isNewFile = false; }
					
					break;
				}
				case 2: { 
					if(isNewFile == false) { 
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						athScore = x;
					}
					break;
				}
				case 3: { 
					if(isNewFile == false) { 
						athBest = lineHolder;
						}
					break;
				}
				case 4: {
					if((isNewFile == true)||(newGame == false)) {
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						lVec.resize(x);
						}					
					break;	
				}
				default: { break; }

			}
			
			//if not new game, pull every level
			if(newGame != true) {
				
				
				//The fun stuff
				//(Pulling the words of each level, but not really)
				if(lineCount == -2) { lineCount = 16; }
				if(lineCount == -3) { lineCount = 20; }
				
				//Collecting preliminary info about each Level
				switch(lineCount) { 
					case 16: {
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						lVec[lIndex].setLen(x);
						break;
					}
					case 17: {
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						lVec[lIndex].setTotal(x);
						break;
					}
					case 18: {
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						lVec[lIndex].setCorrCount(x);
						break;
					}					
					case 19: {
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						lVec[lIndex].setWinState((bool)x);
						lineCount = -3;
						break;
						
					}
					default: break;
				} // End of Prelim Level Data Collecting Switch
				
				//End of Level Check
				if(lineHolder == "/") { 
					lineCount = -2;
					inWord = 0;
					lIndex++;
					}
					
				//Collecting every word's data for the current level.
				switch(lineCount) { 
					case 20: { 
						lVec[lIndex].loadWord(lineHolder, 1, inWord);
						break;
					}
					case 21: { 
						lVec[lIndex].loadWord(lineHolder, 2, inWord);
						break;
						}
					case 22: {
						lVec[lIndex].loadWord(lineHolder, 3, inWord);
						
						lineCount = -3;
						inWord++;
						break;
					}
					default:break;
				}

				
				
				// Lines 6 to 15
				switch(lineCount) {
					//Player Details
					case 6: { 
						player.setCurrentBest(lineHolder);
						break;
					}
					case 7: { 
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						player.setLevelsWon(x);
						break;
						}
					case 8: { 
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						player.setScore(x);
						break;
						}
					case 9: {
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						player.setLives(x);
						break;
						}
					case 10: {
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						player.setLifeLines(x);
						break;
						}			

					
					//Details to Build Level Vector, and start where left off
					case 12: { 
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						currentLevel = x;
						if (currentLevel == -1) { 
							cout << "ILLEGAL ACTION" << endl;
							isIllegal = true;
							lineCount = -4; 
						}
						lIndex = currentLevel;
						break;
						}
					case 13: {
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						wordIndex = x; 
						break;
						}
					case 14: {
						istringstream convert(lineHolder);
						int x; // holds converted string.
						convert >> x;
						lVec.resize(x);
						break;}
				
					case 15: {	
						
						lineCount = -2;
						break;
					}
					default: break;
				} // end of second switch
			} // end of ifnot new game
		} // end of while .good() 
		pullSave.close();
	} // end of if open 
	return isIllegal;
}

/** Outputs stuff onto the screen */
void Game::printMenu(Player & player) 
{
		cout << "All Time Scores";  // Start Line 1 
		spaces(20, ""); 
		cout <<"Current Info" << endl; // End Line 1
		
		cout << "High Score: " << athScore; // Start Line 2 
		spaces(23, athScore);
		cout << "Score: " << player.getScore() << endl; // End Line 2
		
		cout << "Best Word: " << athBest; //start line 3
		spaces(24, athBest);
		cout << "Best Word: " << player.getCurrentBest() << endl; // End line 3
		
		// Line 4
		spaces(36, 0); //Distance from 0 to Current Info is 35, but 36 to pad the -1 from single digit integer
		cout << "LIVES: " << player.getLives() << endl;
		
		//Line 5
		spaces(36, 0);
		cout << "LIFELINES: " << player.getLifeLines() << endl; // end l5

		cout << "Current Word: " << lVec[currentLevel].getWord(wordIndex, true) << endl;//L6
		
		cout << "0) Quit and Save " << endl; // L7
		cout << "1) Enter a guess " << endl; // L8
		cout << "2) Use a lifeline" << endl; // L9
		cout << "Choice: "; // L10
	
	
}

void Game::attemptOption(Player & player, bool & exitState) 
{
	string attempt;
	cout << "Go ahead: ";
	cin >> attempt;
	
	bool valid = lVec[currentLevel].processAttempt(wordIndex, attempt);
	if (valid == true) { //If guess was proper
		
		//Stat Best Word Update Operations
		if(lVec[currentLevel].getWord(wordIndex, false).length() > athBest.length()) {
			athBest = lVec[currentLevel].getWord(wordIndex, false);
		}
		if(lVec[currentLevel].getWord(wordIndex, false).length() > player.getCurrentBest().length()) {
			player.setCurrentBest(lVec[currentLevel].getWord(wordIndex, false));
		}
		
		// Increase both scores by one.
		player.incrScore();
		if(player.getScore() > athScore) { athScore = player.getScore(); }
		
		//Looking for new word
		while (lVec[currentLevel].pullSolveState(wordIndex) == true) {
			if(wordIndex >= lVec[currentLevel].getTotal()) { wordIndex = 0; }
			wordIndex++;
		}
		
		//Updating Progress and possibly acting on it
		lVec[currentLevel].incrCount();
		if(lVec[currentLevel].checkProg() == true) { 
			cout << "\n\n NEXT LEVEL\n\n" << endl;
			currentLevel++;
			wordIndex = 0;
			}
		
		if(currentLevel == lVec.size()) {
			cout << "\n\n\nYOU WIN!\n\n" << endl;
			exitState = true;
		}
		
		cout << "\n==============\n\n" << endl;

	} // ============= end of correct guess scenario
	else player.decrLives();
}