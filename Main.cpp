#include <windows.h>
#include <iostream>
#include <string>
#include <time.h> // MIGHT NEED
#include <conio.h>
#include "SerialPort.h"
#include <sstream>

using namespace std;

// GLOBAL VALUES
const int height = 25; 
const int width = 30;

// REWRITE HERE
char output[MAX_DATA_LENGTH];
char port[] = "\\\\.\\COM5"; // array of characters defined by a string which is just an array of characters
char incoming[MAX_DATA_LENGTH];


void draw(); // prototype

// INSERT GOTOXY
void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

int x, y;


int menu() {
	//int press;
	int menuFlag = 0;
	
	// INSERT ASCII TITLE OF GAME
		cout << "game title here\n";
		cout << "Press Spacebar to start game" << endl;
		cout << "Press x to exit";
do { // collect character inputs until one of them matches the program's accepted input
		char c = _getch();
		if ((c == 120) || (c == 88)) {
			menuFlag = 1;
			return menuFlag;
		}
		else if (c == 32) {
			
			menuFlag = 2;
			return menuFlag;
		}
	} while (menuFlag == 0);
}

void draw() {
	system("cls");
	for (int r = 0; r <= height; r++) { // rows 
		if ((r == 0) || (r == height)) {
			for (int i = 0; i <= width; i++) // print top row, iterate for width of section
				cout << char(219);	
		} 
		else {
			for (int c = 0; c <= width; c++) { // columns
				if ((c == 0) || (c == width)) 
					cout << char(219);
				else
					cout << " ";
			}
		}
		cout << endl; // end of row
		}
	x = width / 2;
	y = height - 2;
	gotoxy(x, y);
	cout << "#";

	}

void setup() {

}

struct FallingObject {

};

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main() {
	// arduino attempt
	SerialPort arduino(port);
	if (arduino.isConnected()) {
		cout << "Connection is Established...";
	}
	else {
		cout << "Arduino error";
	}

	//main idea: 
	//X open console X
	//print the menu
	//when play is pressed, send a signal to arduino to start recording gyroscope
	//read the input from the gyroscope continuously
	//call function that makes objects randomly fall from the sky
	//player avoid objects by moving gyroscope (set up keyboard for now)
	//when object collides with player, end the game or reduce score depending on score structure
	//for every object that passes, add one to the score, maybe increase intensity of falling objects depending on how this goes...
	//when game is over, end arduino input, show end screen that displays score and prompts user to insert name? prompt them to play again
	//displayMenu();
	// IMPLEMENTING PAUSE just have something pop up stating pause during loop when checking input (esc) and have nothing move while pause flag is up
	// while () run game
		int gameStart = menu();
		ShowConsoleCursor(false);
		//draw();
		if (gameStart == 1) {
			system("exit");
		}
		else if (gameStart == 2) {
			draw();
			// setup function
			// game time loop (while)
			//
			
			int gameStats[2] = { 3, 1 };
			char z;
			while (gameStats[0] > 0) { // MAIN GAMEPLAY LOOP
				//cout << incoming;
				arduino.readSerialPort(incoming, MAX_DATA_LENGTH);
				stringstream test(incoming);
				int place = 0;
				test >> place;
				
					if (place < 0) {
						if (x < width) {
							gotoxy(x, y);
							cout << " ";
							x = x + 1;
							gotoxy(x, y);
							cout << "#";
					}
				}
				
					else if (place > 0) {
						if (x > 0) {
							gotoxy(x, y);
							cout << " ";
							x = x - 1;
							gotoxy(x, y);
							cout << "#";
						}
					}

				else if (place == 0) {
					continue;
				}
				// CHECK IF ESC toggle is on (PAUSE / NO ACTION IF SO)
				// get arduino value at start of loop, then determine direction
			/*	if (_kbhit()) {
					z = _getch();
					if (z == 32) {
						cout << "test";
					}
					// move character around, replace kbhit with value given by arduino
				}*/
				Sleep(100);
			}
		}
		else {
			system("exit");
		}
		// TODO input validation - keep in one direction until direction is less than 0, or greater than 0
		// game setup function here. Initialize score, initialize falling objects, initialize character starting position, etc

		return 0;
	// draw input logic loop while gameover = false
		// array of coordinates for current position of all falling objects?
		// when time flag is % 2 = 0, even, every other move, move falling objects. every single move, move character in intended direction
		// create new object with random starting x coordinate, struct?
		//


}