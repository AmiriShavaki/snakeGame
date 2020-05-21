#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Pos {
	friend const bool operator==(Pos l, Pos r);

	private:
//0-based coordinates
	int x;
	int y;

	public:
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int x) {this -> x = x;}
	void setY(int y) {this -> y = y;}
	Pos(int x, int y);
	Pos(){}
};

const bool operator==(Pos l, Pos r) {
	return l.getY() == r.getY() && l.getX() == r.getX();
}

Pos::Pos(int x, int y) {
	setX(x);
	setY(y);
}

class Snake {
	friend void operator+(Snake& snk, Pos newHead);

	private:
	vector <Pos> body;
	int len;
	Pos head;
	char curDir;

	public:

	void load(ifstream& in) {
		in >> madeMoves >> len;
		body.clear();
		int x, y;
		for (int i = 0; i < len; i++) {
			in >> x >> y;
			body.push_back(Pos(x, y));
		}
		in >> x >> y;
		head.setX(x);
		head.setY(y);
		in >> curDir;		
	}

	void save(ofstream& out) { 
		out << madeMoves << endl << len << endl;
		for (int i = 0; i < len; i++) {
			out << body[i].getX() << endl << body[i].getY() << endl;
		}
		out << head.getX() << endl << head.getY() << endl << curDir << endl;
	}

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
		if (newX >= w || newX < 0 || newY >= h || newY < 0) { cout << "Game Over! You crossed the border!";//We hit off-board
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
						inFile.open("saved.txt", ios::in);
						board.load(inFile);
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
					cout << "The plate dimension is set to " << n << '*' << n << ".\n";
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
						outFile.open("saved.txt", ios::out);
						board.save(outFile);
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
