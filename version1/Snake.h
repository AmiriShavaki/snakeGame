#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "Pos.h"
#include <ctime> //time
#include <cstdlib> //srand and rand
#include <algorithm> //reverse

using namespace std;

class Snake {
	friend void operator+(Snake& snk, Pos newHead);

	private:
	vector <Pos> body;
int len;
Pos head;
char curDir;

public:
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

	//Random initialization of coordinates
	int y = rand() % n;
	int x = rand() % (m - 2); //x-coordinate of one end of the Snake's body (maybe tail, maybe head)

	body.clear();
	for (int i = 0; i < len; i++) {
		body.push_back(Pos(x + i, y));
}

if (rand() % 2) { //Head on the right
	head = Pos(x + len - 1, y);
	curDir = 'R';
} else { //Head on the left
	head = Pos(x, y);
	reverse(body.begin(), body.end());
	curDir = 'L';
}
}

void operator+(Snake& snk, Pos newHead) {
    snk.moveHead(newHead);
	snk.len++;
	
}

#endif 
