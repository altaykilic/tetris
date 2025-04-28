#pragma once

#include "Pos.h"
#include "Shape.h"

class Piece{
public:
	Piece(short s, short r, pos p);
	
	short shapeid;
	short rotation;
	Shape* shape;
	
	pos coords;
	
	Shape* getShape();
};

Piece::Piece(short s = 0, short r = 0, pos p = {-10,-10}){
	shapeid = s;
	rotation = r;
	coords = p;
	shape = getShape();
}

Shape* Piece::getShape(){
	return &(TETROMINOES[shapeid][rotation]);
}
