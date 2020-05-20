#ifndef BOARD_H
#define BOARD_H

#include "Snake.h"
#include "Pos.h"
#include <ctime> //time
#include <cstdlib> //srand and rand
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

map <char, char> opp;
map <char, string> dirName;
map <char, Pos> dirAdd;

class Board {
	friend ostream& operator<< (ostream& output, Board board);

	private:
	int h; //Height
	int w; //Width
	Snake snk;
	Pos foodCor; //Food coordinates

	public:
    bool checkWin() {
		return snk.getLen() >= (double(h * w)) / 2.0;
}


	bool move(char dir) {
		int newX = snk.getHead().getX() + dirAdd[dir].getX();
		int newY = snk.getHead().getY() + dirAdd[dir].getY();
		if (newX >= w || newX < 0 || newY >= h || newY < 0) { cout << "Game over! you crossed the border!";//We hit off-board
			return false;
} else if (snk.getCell(newX, newY) == '-') { cout << "Game over! you crossed the border!";//Snake's body
	return false;
} else if (Pos(newY, newX) == foodCor) {  //Food is there reversed!
	snk + Pos(newX, newY);
    	snk.setCurDir(dir);
        
        setFoodCor();
        
	return true;
} else { //Empty cell
	snk.cutTale();
    	snk.setCurDir(dir);
	snk.moveHead(Pos(newX, newY));
return true;
}
}
	const char getCurDir() const {
		return snk.getCurDir();
}
	Board(int n = 10) : snk(n, n) {
		h = n;
		w = n;
setFoodCor();

//Set mapping directions utilities
opp['R'] = 'L';
opp['L'] = 'R';
opp['U'] = 'D';
opp['D'] = 'U';
dirName['U'] = "UP";
dirName['D'] = "DOWN";
dirName['L'] = "LEFT";
dirName['R'] = "RIGHT";
dirAdd['U'] = Pos(0, -1);
dirAdd['D'] = Pos(0, 1);
dirAdd['R'] = Pos(1, 0);
dirAdd['L'] = Pos(-1, 0);
}
void setFoodCor() {
		//Food coordinations initialization
		int x = rand() % w;
		int y = rand() % h;
		while(snk.getCell(x, y) != '.') { //Finding a blank cell to place the food
			x = rand() % w;
		y = rand() % h;			
}
foodCor = Pos(y, x);
}
};

ostream& operator<< (ostream& output, Board board) {
	for (int i = 0; i < board.h; i++) {
		for (int j = 0; j < board.w; j++) {
			if (Pos(i, j) == board.foodCor) {
				cout << '*';
} else {
	cout << board.snk.getCell(j, i);
}
		}
		cout << endl;
	}
return output;
}

#endif 
