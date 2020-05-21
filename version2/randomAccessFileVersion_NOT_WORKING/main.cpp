#include "Board.h"
#include <iostream>
#include <fstream>

int main() {
	Board board;

	bool gameIsOver = false;
	bool loadGame = false;
	while (!gameIsOver) {
		char opt; //input operation
		cin >> opt;

		switch (opt) {

			case '1': {
				int n;
				cin >> n;
				switch (n) {
					case 1: {
						cout << "A new plate is created for you :)\n";
					} break;
					
					case 2: {
						ifstream inFile;
						inFile.open("saved", ios::in | ios::binary);
						inFile.read(reinterpret_cast<char *>(&board), sizeof(board)); 
						inFile.close();
						loadGame = true;
						cout << "A new plate is created for you :)\n";
					} break;

					default: {
						cout << "Unable to do your instruction.\n";
					} break;
				}
			} break;

			case '2': { //plate size
				int n;
				cin >> n;
				if (n >= 5 && !loadGame) {
					board = Board(n);
					cout << "The plate dimension is set " << n << '*' << n << ".\n";
				} else {
					cout << "Unable to do your instruction.\n";
				}
			} break;

			case '3': {
				cout << board;
			} break;

			case '4': {
				char dir;
				cin >> dir;
				if (!board.move(dir)) {
					gameIsOver = true;
				} else {
					cout << board;
					if (board.getN() % 2) { //n is odd
						double doubleN = board.getN(); //type casting
						gameIsOver = !Snake::printRemTime((doubleN) * (doubleN) / 2.0);
					} else { //n is even
						int intN = board.getN(); //type casting
						gameIsOver = !Snake::printRemTime((intN) * (intN) / 2);
					}
				}
				/*
				if (board.getCurDir() == opp[dir]) {
					cout << "The movement to " << dirName[dir] << " is not possible!\n";
				} else { //not opposite direction
					if (!board.move(dir)) {
						gameIsOver = true;
					} else {
						cout << board;
					}
				}*/
			} break;

			case '5': {
				int n;
				cin >> n;
				switch (n) {
					case 1: {
						ofstream outFile;
						outFile.open("saved", ios::binary);
						outFile.write(reinterpret_cast<const char *>(&board), sizeof(board)); 
						outFile.close();
						cout << "Your game is saved for future. Goodbye!\n";
						gameIsOver = true;
					} break;
					case 2: {
						cout << "Goodbye!\n";
						gameIsOver = true;
					} break;
					default: {
						cout << "Unable to do your instruction.\n";
					} break;
				}
			} break;

			default: {
				cout << "Unable to do your instruction.\n";
			} break;

		}

		if (board.checkWin()) {
			cout << "Congratulation! You are always a winner!\n";
			gameIsOver = true;
		}

	}
}
