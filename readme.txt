03/13/18
CSCI23500 
Project 1

Initial Details
===============
	While coded in Notepad++ on Windows, the actual program was compiled in Ubuntu with g++. 
If compiled on Windows, any graphical display errors have not been accounted for. 


Oversights/Things Taken For Granted
===================================
* Have not expected to parse files with words larger than 20 characters, let alone 25.


Some Bugs
========
1)If one attempts to load the savefile.txt as the sourcefile in a new game, a crash will occur.
2)Trying to load a blank file (literally no contents, whitespace/newlines or otherwise) will cause a crash.
**Bugs 1 and 2 have been fixed via a checking function in main.cpp.


Compiling the Program
==================
Given the makefile is in the same folder as the other files (main.cpp, Word.cpp/.h, Level.cpp/h, Game.cpp/h),
and your linux command line is targeting said folder, type make to assemble the program. Will need g++ installed.


Running the Program
===================
Simply type and enter "./wordgame"


Playing the Game
=================

	In Menu
	-------
	*Enter 1 to Start a game. 
		*If you want to start a new game, enter the filename of the file you would like to load words from (including the file extension).
		*If you want to continue a previous save, granted there is one, press enter without entering anything. 
			*[ILLEGAL ACTION] will be displayed in the event that one is attempting to load a game after losing from a loaded file.
	*Enter 0 to end the program.

	In Game
	-------
	*Enter 0 to quit. The data for the game will be saved so that it may be continued if one chooses to at a later time.
	*Enter 1 to be permitted to enter a guess. If wrong, -1 life.
	*Enter 2 to use lifeline if on last life. Using a lifeline will switch a word for an unsolved word in the same level.



Class Design
============
I determined only three classes were really required for this program. One class to manage the interactions between the player and the game (like UI display,
and input), that also had a collection of objects that represented each level of difficulty in ascending order. Within each of these objects was a vector of
objects that each contained the clue, the correct answer, and if the particular object was to be used or not.

class Word

	Literally only needed the unscrambled word, the scrambled word, and a bool variable for whether or not it was solved. Besides its functions, it was only
necessary to make this as simple as possible.

class Level

	Held the vector of words, how many hits it took (correct answers on current level), if it was beaten or not, and most importantly the length
of every Word it held (essentially the difficulty), by which it would be sorted.

class Game
	
	Home of the big main operations. Has index for current level and word, the vector of Levels, the given source file, and the two all time
 high stats for the given source file. Since Game contains the levels for the current match (as well as runs the match from within its constructors),
 it also holds the functions to parse the input data, organize the words pulled from it into levels, and interact with/create savefile data. 	


UI Design
=========
	Small and simple, but enough to look back on what has been done. Sloppy in the sense that the whole UI is reprinted,
but at the same time I was unsure how to clear the screen for linux or how to manage that between two operating systems, so
I chose to remain as neutral about that as possible.

Best stats (High Scores for the file) on the upper left, and the player's current stats on the right.	


Regarding the Game constructor
==============================
	In all honesty, the two constructors could have been the same one, with a simple if/else statement determining the first set of actions to take.
Regarding this, for both constructors, literally everything from the printed border / declaration of exitState downward are the same. The only difference is
how certain variables are assigned (parse()/things to zero with load() in a minor sense, or load() for everything important).


Exit State Details
==================
Only two possible conditions.
	1) Voluntary quit via entering 0. This saves the current game's data.
	2) Running out of lives, setting the exitState to false, saving the game with save()'s cLvl as -1, and ending the game.
		*This usage of save() prevents a player from reloading their previous save in the event that they lost after
		saving then loading said savefile.


Save File Details
=================
	Essentail details for the resuming of a previously saved games are saved. Tags explaining what relevance the preceding details hold
are denoted on lines within square brackets, for the sake of viewability. In terms of code, it can be easily determined by looking at the
save file:


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

Beyond line 15 is where levels and their words begin getting printed. From within Level's saveOutput()...

	ostringstream output;
	
	output << len; //16
	output << "\n";
	output << wVec.size(); //17
	output << "\n";
	output << corrCount; //18
	output << "\n";
	output << winState; //19
	output << "\n"; 
	
	for(int i = 0; i < wVec.size(); i++) { 
				
		output << wVec[i].savePrint();
	
	}
	output << "/\n";  
	string truOut = output.str();
	return truOut;


	Essential details for the level are saved first, then we proceed to a loop recording the three member variables of each Word object, 
using Word's saveOutput()...

	ostringstream output;
	output << orgWord; //20
	output << "\n";
	output << mixWord; //21
	output << "\n";
	output << solveState; //22
	output << "\n";
	
	string truOut = output.str();
	return truOut;


	You may have noticed at this point that both previous member functions have utilized stringstreams for output. This was done because I had initially had problems
adding "\n" to the strings and lines get skipped in the savefile.txt once viewing the textfile in a plaintext editor. The entire time I was viewing the file
in Windows, not realizing that the compiler (in Ubuntu) was likely using its version of a newline character or code. This may very well mean that using
stringstreams were totally unnecessary. Unfortunately, time is has been at a premium.

**EDIT: stringstreams were used because despite the g++ on my Ubuntu installation being "up to date", and covering C++ 11, it was not recognizing two important
string functions included in 11, toString() and stoi(). Using stringstreams was the only way I was able to get this going.


Loading Details
===============

	This one is a doozy, and once I had designed and implemented the thing, I felt as if I was writing code in assembly, utilizing goto statements
(while not actually utilizing goto statements). Despite some bug fixing (see: great typos like == where a single = should have resided) and the time spent
doing that, and the system actually functions great. 

	(*)Here, when saying new file, we are referring to a different input file than the one found within the save file.
	
	The first switch statement for lineCount covers only lines 1 to 4. In the first case, it determines if the game is using a new file or not. If so,
load() will only load lines two and three (as it doesnt need to know line 4, which is the size of the Level vector in Game). If its not a newgame, or it is 
a new file, it will load lines two through four (this is overwritten in the case of a new game with a new file by the parse() function).

	Relying on the numbering order listed above, pulling the first 15 lines (15 - 3 descriptive [] tag lines) was the easiest part of this. Once at line 15 (in the switch statement checking the lineCount, that manages lines 6 to 15, conveniently placed at
the end of the while loop), the lineCount is set to a set to a special value (-2) that will trap lineCount in loops that will continue until it reaches '/',
which is used here to denote the end of the current level. With this, lineCount is set back to (-2) to repeat this process with any other levels until the
function reaches '~', with which it will then set the lineCount to a value that is one of the two conditions that would cause the file reading to end.



