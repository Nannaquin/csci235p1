/**file: Player.h */
#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<string>
using namespace std;


/**Holds the current game stats. */
class Player {
	public:
	
		/**
		@pre: An old save game has been loaded.
		@post: Save data regarding player will be retrieved.
		@param: inStr  the current best solved word
				inWon  amount of levels won
				inScr  current score
				inLiv  Amount of remaining lives
				inLin  Amount of remaining life lines*/
		Player(string inStr, int inWon, int inScr, int inLiv, int inLin);
		
		/**New Game Constructor
		@pre: New Game is being started.
		@post: All member vars will be initialized.*/
		Player();
	
		
		//Save Loading Specific
		/**For the case of loading a save, or to update
		during gameplay. */
		void setCurrentBest(string inStr);
		/**For the case of loading a save. */
		void setLevelsWon(int & inVal);
		/**For the case of loading a save. */
		void setScore(int & inVal);
		/**For the case of loading a save. */
		void setLives(int & inVal);
		/**For the case of loading a save. */
		void setLifeLines(int & inVal);
		
		//For Saving the Game or Displaying
		/**For the case of saving */
		string getCurrentBest();
		int getLevelsWon();
		int getScore();
		int getLives();
		int getLifeLines();
		
		
		/**For the case of making a correct guess.
		@pre: A correct guess has been made.
		@post: The score will be incremented.*/
		void incrScore();
		
		/**For case of making an incorrect guess.
		@pre: An incorrect guess has been made.
		@post: Lives will be decremented. */
		void decrLives();
		
		/** Attempts to use a lifeline.
		@pre: Player has requested a lifeline be used.
		@post: if on last life, lifeline will be used (and decremented)
		@return: true if on last life or valid use, false if conditions
		not met. */
		bool useLifeLine();
		
		
	private:
	
	//Longest word solved?
	string currentBest;
	//Number of levels won
	int levelsWon;
	//Number of words solved.
	int score;
	
	//Current amount of lives. Less than or equal to 3
	int lives;
	//Current amount of lifelines.
	int lifelines;
	
	
	
	
};



#endif