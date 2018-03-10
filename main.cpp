/**file main.cpp*/
#include<iostream>
#include<string>

#include"Game.h"
//#include"Level.h"
//#include"Word.h"
//#include"Player.h"
using namespace std;


/**Preload: Checks if there is a save file. */



int main() {

	int choice = -1;
	
	while(choice!=0) {

		cout << "Welcome to Word Jumble Thing" << endl;
		cout << "----------------------------" << endl;
		cout << "1) Play Game!" << endl;
		cout << "0) Exit Program" << endl;
		cout << "Enter: ";

		while(!(cin >> choice)) {
			cin.clear();
			cin.ignore();
			cout << "\nInvalid input. 1 or 0, please." << endl;
		}

		switch(choice) {

			case 0: break;
					
			case 1: {
				string filename;
				cout << "Enter text file name to start a new game..." << endl;
				cout << "Otherwise, press enter to load a previously" << endl;
				cout << "saved game." << endl;
				
				//maybe error checking? Most anything can be a string inputwise
				cin >> filename;
				if(filename.empty()==false) {
					Game game(filename);
				}
				else {
					//Game();	
				}
			}
				break;

			default: { 

				break;
			} 

		} // choice switch	

	}// choice while

} // end of main


