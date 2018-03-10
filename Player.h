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
		@pre: Game has been called.
		@post: Player will either be a clean slate
		or loaded from previous save file.
		@param: load  If true, engage in loading procedure.
		Otherwise, call setNew.*/
		Player(bool load);
		
		/**Generic Constructor */
		Player();
		
		/**Sets up member variables in event of new game.
		@pre: A new game has been started. 
		@post: All member variables will be set to beginning
		values. */
		void setNew();
		
		//==============
		// make set load?
		
		//Save Loading Specific
		/**For the case of loading a save, or to update
		during gameplay. */
		void setCurrentBest(string inStr);
		/**For the case of loading a save. */
		void setLevelsWon(int inVal);
		/**For the case of loading a save. */
		void setScore(int inVal);
		/**For the case of loading a save. */
		void setLives(int inVal);
		/**For the case of loading a save. */
		void setLifeLines(int inVal);
		
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
		
		/**For when a lifeline is used.
		@pre: A request to expend a lifeline was successful		
		@post: lifeLines will be decremented.*/
		void decrLifeLines();
		
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