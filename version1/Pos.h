#ifndef POS_H
#define POS_H

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

#endif
