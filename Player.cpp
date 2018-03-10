/**file: Player.cpp */

#include<iostream>
#include<string>
#include"Player.h"
using namespace std;

/**
@pre: Game has been called.
@post: Player will either be a clean slate
or loaded from previous save file.
@param: load  If true, engage in loading procedure.
Otherwise, call setNew.*/
Player::Player(bool load) { }

/** Generic Constructor */
Player::Player() { }

/**Sets up member variables in event of new game.
@pre: A new game has been started. 
@post: All member variables will be set to beginning
values. */
void Player::setNew() { }

//Save Loading Specific
/**For the case of loading a save, or to update
during gameplay. */
void Player::setCurrentBest(string inStr) { }
/**For the case of loading a save. */
void Player::setLevelsWon(int inVal){ }
/**For the case of loading a save. */
void Player::setScore(int inVal){ }
/**For the case of loading a save. */
void Player::setLives(int inVal) { }
/**For the case of loading a save. */
void Player::setLifeLines(int inVal) { }

//For Saving the Game or Displaying
/**For the case of saving */
string Player::getCurrentBest() { }
int Player::getLevelsWon() { }
int Player::getScore() { }
int Player::getLives() { }
int Player::getLifeLines() { }


/**For the case of making a correct guess.
@pre: A correct guess has been made.
@post: The score will be incremented.*/
void Player::incrScore() { }

/**For case of making an incorrect guess.
@pre: An incorrect guess has been made.
@post: Lives will be decremented. */
void Player::decrLives() { }

/**For when a lifeline is used.
@pre: A request to expend a lifeline was successful		
@post: lifeLines will be decremented.*/
void Player::decrLifeLines() { }

/** Attempts to use a lifeline.
@pre: Player has requested a lifeline be used.
@post: if on last life, lifeline will be used (and decremented)
@return: true if on last life or valid use, false if conditions
not met. */
bool Player::useLifeLine() { }