#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "Pos.h"
#include <algorithm> //reverse
#include <iostream>

using namespace std;

class Snake {
	friend void operator+(Snake& snk, Pos newHead);

	private:
	vector <Pos> body;
	int len;
	Pos head;
	char curDir;

	public:

	static int madeMoves;
	template < typename T >
	static bool printRemTime(T initRemTime) {
		if (initRemTime - madeMoves > 0) {
			cout << "Your remaining lifetime is " << initRemTime - madeMoves << ".\n";
			return true;
		} else {
			cout << "Game Over! Your lifetime is expired!";
			return false;
		}
	}

	static void increaseRemTime() {
		madeMoves--;
	}

	const int getLen() const {return len;}
	Snake(int n, int m);
	const char getCell(int x, int y);
	const char getCurDir() const { return curDir; }
	void setCurDir(char dir) {curDir = dir;}
	void setHead(Pos newHead) { head = newHead; }
	Pos getHead() const {return head;}
	Pos getTail() const {return body[0];}
	void cutTale() {body.erase(body.begin());}
	void moveHead(Pos newPos) {
		head = newPos;
		body.push_back(newPos);
	}
};

int Snake::madeMoves = 0;

const char Snake::getCell(int x, int y) {
	//Star character will be check outside here
	if (head == Pos(x, y)) {
	return 'P';
}
for (int i = 0; i < len; i++) {
	if (body[i] == Pos(x, y)) {
		return '-';
}
}
return '.';
}

Snake::Snake(int n, int m) { //n and m are height and width of the board
	len = 3;

	//not random initialization of coordinates
	int y = 2;
	int x = m - 3; //x-coordinate of one end of the Snake's body (head)

	body.clear();
	for (int i = 0; i < len; i++) {
		body.push_back(Pos(x + i, y));
	}
	head = Pos(x + len - 1, y);
	curDir = 'R';
}

void operator+(Snake& snk, Pos newHead) {
    snk.moveHead(newHead);
	snk.len++;
	
}

#endif 
