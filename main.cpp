#include "Board.h"
#include <ctime> //time
#include <cstdlib> //srand and rand
#include <iostream>

int main() {
srand(time(NULL));
	Board board; //default w = h = 10 plate size

bool gameIsOver = false;
while (!gameIsOver) {
	char opt; //input operation
	cin >> opt;

	switch (opt) {
	case '1': { //plate size
		int n;
		cin >> n;
		board = Board(n);
		cout << "The plate dimension is set " << n << '*' << n << ".\n";
} break;
	case '2': {
		cout << board;
} break;
	case '3': {
		char dir;
		cin >> dir;
		if (board.getCurDir() == opp[dir]) {
			cout << "The movement to " << dirName[dir] << " is not possible!\n";
}else { //not opposite direction
	if (!board.move(dir)) {
		gameIsOver = true;
}
}

} break;
default: {
	cout << "Please enter 1, 2 or 3\n";
} break;
}
if (board.checkWin()) {
cout << "Congratulation! you have won!\n";
gameIsOver = true;
}

}
}
