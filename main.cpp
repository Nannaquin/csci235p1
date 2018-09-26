/**file main.cpp*/
#include<iostream>
#include<fstream>
#include<string>
#include"Game.h"
using namespace std;

/**Checks to see if the file is actually loadable. */
bool checkFile(string filename);

/**Main Menu/Jumping Off Point */
int main() {
	cout << "\n\n\n\n\n" << endl;

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
		cin.ignore(100, '\n'); 

		switch(choice) {

			case 0: break;
					
			case 1: {
				string filename;
				cout << "Enter text file name to start a new game..." << endl;
				cout << "Otherwise, press enter to load a previously" << endl;
				cout << "saved game." << endl;
				
				//maybe error checking? Most anything can be a string inputwise
				getline(cin, filename);
				if(filename.empty()==false) {
					if(checkFile(filename) == true) {
						Game game(filename);
					}
				}
				else {
					Game();	
				}
			}
				break;

			default: { 

				break;
			} 

		} // choice switch	

	}// choice while

} // end of main


bool checkFile(string filename) {
	
	bool retState = false;
	ifstream checkThis(filename.c_str());
	if(checkThis.is_open()) { 
		retState = true;
		checkThis.close();
	}
	else { 
		cout << "[CANNOT FIND/OPEN FILE]" << endl;
	}
	
	return retState;
	
}