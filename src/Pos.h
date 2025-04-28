#pragma once

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

pos pos::operator+(const pos& p){
	return {x+p.x,y+p.y};
}

pos pos::operator-(const pos& p){
	return {x-p.x,y-p.y};
}

pos pos::operator*(const int& i){
	return {x*i, y*i};
}

pos pos::operator=(const pos& p){
	x=p.x;
	y=p.y;
	return *this;
}

pos pos::operator+=(const pos& p){
	(*this)=(*this)+p;
	return *this;
}

bool pos::operator==(const pos& p){
	return (x==p.x && y==p.y);
}

bool pos::operator!=(const pos& p){
	return !(x==p.x && y==p.y);
}

bool pos::operator<(const pos& p){
	return (x<p.x && y<p.y);
}

bool pos::operator<=(const pos& p){
	return (x<=p.x && y<=p.y);
}

bool pos::operator>(const pos& p){
	return (x>p.x && y>p.y);
}

bool pos::operator>=(const pos& p){
	return (x>=p.y && y>=p.y);
}
