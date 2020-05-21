#ifndef BOARD_H
#define BOARD_H

#include "Snake.h"
#include "Pos.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

map <char, char> opp;
map <char, Pos> dirAdd;

class Board {
	friend ostream& operator<< (ostream& output, Board board);

	private:
	int h; //Height
	int w; //Width
	Snake snk;
	Pos foodCor; //Food coordinates
	vector <Pos> foodList;

	public:

	void load(ifstream& in) {
		int x, y; 
		in >> h >> w >> x >> y;
		foodCor.setX(x);foodCor.setY(y);
		int ln;
		in >> ln;
		foodList.clear();
		for (int i = 0; i < ln; i++) {
			in >> x >> y;
			foodList.push_back(Pos(x, y));
		}
		snk.load(in);		
	}

	void save(ofstream& out) {
		out << h << endl << w << endl << foodCor.getX() << endl << foodCor.getY() << endl << foodList.size() << endl;
		for (int i = 0; i < foodList.size(); i++) {
			out << foodList[i].getX() << endl << foodList[i].getY() << endl;
		}
		snk.save(out);
	}

	void initFoodList() {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (i % 2 == j % 2) {
					foodList.push_back(Pos(j, i));
				}
			}
		}
	}

    bool checkWin() {
		return snk.getLen() >= (double(h * w)) / 2.0 || foodList.size() == 0;
	}

	int getN() {
		return h;
	}

	/*template < typename T >
	static T getRemTime(T n) {
		if (n % 2) { //n is odd
			double doubleN = n; //type casting
			return Snake::calculateRemTime((doubleN) * (doubleN) / 2.0);
		} else { //n is even
			int intN = n; //type casting
			return Snake::calculateRemTime((intN) * (intN) / 2);
		}
	}*/

	bool move(char dir) {
		int newX = snk.getHead().getX() + dirAdd[dir].getX();
		int newY = snk.getHead().getY() + dirAdd[dir].getY();
		if (newX >= w || newX < 0 || newY >= h || newY < 0) { cout << "Game over! you crossed the border!";//We hit off-board
			return false;
		} else if (snk.getCell(newX, newY) == '-') { cout << "Game Over! You crossed your own body!";//Snake's body
			return false;
		} else if (Pos(newY, newX) == foodCor) {  //Food is there reversed!
			snk + Pos(newX, newY);
    		snk.setCurDir(dir);
			Snake::increaseRemTime();
        	setFoodCor();
			Snake::madeMoves++;
			return true;
		} else { //Empty cell
			snk.cutTale();
			snk.setCurDir(dir);
			snk.moveHead(Pos(newX, newY));
			Snake::madeMoves++;
			return true;
		}
	}	
	const char getCurDir() const {
		return snk.getCurDir();
	}
	Board(int n = 10) : snk(n, n) {
		h = n;
		w = n;
		initFoodList();
		setFoodCor();

		//Set mapping directions utilities
		opp['R'] = 'L';
		opp['L'] = 'R';
		opp['U'] = 'D';
		opp['D'] = 'U';
		dirAdd['U'] = Pos(0, -1);
		dirAdd['D'] = Pos(0, 1);
		dirAdd['R'] = Pos(1, 0);
		dirAdd['L'] = Pos(-1, 0);
	}
	
	void setFoodCor() {
		//Food coordinations initialization
		int x = foodList[0].getX();
		int y = foodList[0].getY();
		foodCor = Pos(y, x);
		foodList.erase(foodList.begin());
	}
};

ostream& operator<< (ostream& output, Board board) {
	for (int i = 0; i < board.h; i++) {
		for (int j = 0; j < board.w; j++) {
			if (Pos(i, j) == board.foodCor) {
				if (board.snk.getCell(j, i) == '-') {
					cout << " - ";
				} else {
					cout << " * ";
				}
			} else {
				cout << ' ' << board.snk.getCell(j, i) << ' ';
			}
		}
		cout << endl;
	}
return output;
}

#endif 
