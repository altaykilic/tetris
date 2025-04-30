#include "Shape.h"

Shape::Shape(pos p1, pos p2, pos p3, pos p4, short c){
	blocks[0] = p1;
	blocks[1] = p2;
	blocks[2] = p3;
	blocks[3] = p4;
	colorid = c;
}