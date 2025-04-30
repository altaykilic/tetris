#ifndef _BOARD_H
#define _BOARD_H

#include "Piece.h"

//standard values according to tetris.fandom
const int SIZE_x = 10;
const int SIZE_y = 40;	//real grid size
const int SIZE_y2 = 20;	//visible grid size

class Board{
public:
	Board();
	
	Piece* activePiece;
	short grid[SIZE_x][SIZE_y];
	
	short& idx(pos p);
	void draw();
	int checkLines();
	void deleteLine(int l);
	
	bool putPiece(pos p = pos(-10,-10));
	bool deletePiece();
	bool movePiece(pos p = pos(0,-1));
	bool hardDrop();
	bool rotate(bool cw);
};

#endif