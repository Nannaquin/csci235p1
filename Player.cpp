/**file: Player.cpp */

#include<iostream>
#include<string>
#include"Player.h"
using namespace std;

/** Intended for loading a save, but is not in use.
@pre: An old save game has been loaded.
@post: Save data regarding player will be retrieved.
@param: inStr  the current best solved word
		inWon  amount of levels won
		inScr  current score
		inLiv  Amount of remaining lives
		inLin  Amount of remaining life lines*/
Player::Player(string inStr, int inWon, int inScr, int inLiv, int inLin)
:currentBest(inStr), levelsWon(inWon), score(inScr), lives(inLiv), lifelines(inLin) { }

/** New Game Constructor
@pre: New Game is being started.
@post: All member vars will be initialized.*/
Player::Player():currentBest(""), levelsWon(0), score(0), lives(3), lifelines(5) { }

	
//Save Loading Specific
/**For the case of loading a save, or to update
during gameplay. */
void Player::setCurrentBest(string inStr) { currentBest = inStr; }
/**For the case of loading a save. */
void Player::setLevelsWon(int & inVal){ levelsWon = inVal; }
/**For the case of loading a save. */
void Player::setScore(int & inVal){ score = inVal; }
/**For the case of loading a save. */
void Player::setLives(int & inVal) { lives = inVal; }
/**For the case of loading a save. */
void Player::setLifeLines(int & inVal) { lifelines = inVal; }

//For Saving the Game or Displaying
string Player::getCurrentBest() { return currentBest; }
int Player::getLevelsWon() { return levelsWon; }
int Player::getScore() { return score; }
int Player::getLives() { return lives; }
int Player::getLifeLines() { return lifelines; }


/**For the case of making a correct guess.
@pre: A correct guess has been made.
@post: The score will be incremented.*/
void Player::incrScore() { score++; }

/**For case of making an incorrect guess.
@pre: An incorrect guess has been made.
@post: Lives will be decremented. */
void Player::decrLives() { lives--; }

/** Attempts to use a lifeline.
@pre: Player has requested a lifeline be used.
@post: if on last life, lifeline will be used (and decremented)
@return: true if on last life or valid use, false if conditions
not met. */
bool Player::useLifeLine() 
{
	bool retVal = false;
	if(lifelines > 0) { 
		retVal = true;
		lifelines--;
		}
	
	return retVal; 
}