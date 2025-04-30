#ifndef _PIECE_H
#define _PIECE_H

#include "Pos.h"
#include "Shape.h"

class Piece{
public:
	Piece(short s, short r, pos p);
	
	short shapeid;
	short rotation;
	Shape const* shape;
	
	pos coords;
	
	Shape const* getShape();
};

#endif