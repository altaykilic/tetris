#include "Piece.h"

Piece::Piece(short s = 0, short r = 0, pos p = {-10,-10}){
	shapeid = s;
	rotation = r;
	coords = p;
	shape = getShape();
}

Shape const* Piece::getShape(){
	return &(TETROMINOES[shapeid][rotation]);
}
