#ifndef _POS_H
#define _POS_H

class pos{
public:
	int x, y;
	pos operator+(const pos&);
	pos operator-(const pos&);
	pos operator*(const int&);
	pos operator=(const pos&);
	pos operator+=(const pos&);
	bool operator==(const pos&);
	bool operator!=(const pos&);
	bool operator<(const pos&);
	bool operator<=(const pos&);
	bool operator>(const pos&);
	bool operator>=(const pos&);
	pos(int a=0, int b=0) : x(a), y(b) {}
};

#endif