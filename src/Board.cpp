#include "Board.h"

bool Board::putPiece(pos p){
	if(p == pos(-10,-10))
		p = activePiece->coords;
	for(int i=0; i<4; i++){
		if(!(p+activePiece->shape->blocks[i]<pos(SIZE_x,SIZE_y) && p+activePiece->shape->blocks[i]>=pos(0,0))){
			// std::cout << "\tputPiece() error\n\tposition out of board";
			return 1;
		}
		if(idx(p + activePiece->shape->blocks[i]) != 0){
			// std::cout << "\tputPiece() error\n\tposition is occupied\n";
			return 1;
		}
	}
	for(int i=0; i<4; i++){
		idx(p + activePiece->shape->blocks[i]) = activePiece->shape->colorid;
	}
	activePiece->coords = p;
	return 0;
}

bool Board::deletePiece(){
	if(activePiece == nullptr){
		// std::cout << "\tdelete() error\n\tactivePiece == nullptr\n";
		return 1;
	}
	for(int i=0; i<4; i++){
		if(idx(activePiece->coords + activePiece->shape->blocks[i]) != activePiece->shape->colorid){
			// std::cout << "\tdelete() error\n\tpiece is not there\n";
			return 1;
		}
		idx(activePiece->coords + activePiece->shape->blocks[i]) = 0;
	}
	return 0;
}

bool Board::movePiece(pos p){
	if(deletePiece()){
		// std::cout << "\tmovePiece() error\n\tcouldn't delete\n\n";
		return 1;
	}
	if(putPiece(activePiece->coords + p)){
		putPiece();
		if(p == pos(0,-1)){
			activePiece = nullptr;
		}
		return 1;
	}
	return 0;
}

bool Board::hardDrop(){
	if(activePiece == nullptr)
		return 1;
	while(!movePiece());
	return 0;
}

bool Board::rotate(bool cw){
	if(deletePiece()){
		// std::cout << "\trotate()\n\tcouldn't delete\n\n";
		return 1;
	}
	
	activePiece->rotation = (activePiece->rotation + cw*2-1 + 4) % 4;
	activePiece->shape = activePiece->getShape();
	
	if(putPiece()){
		activePiece->rotation = (activePiece->rotation - cw*2+1 + 4) % 4;
		activePiece->shape = activePiece->getShape();
		putPiece();
		return 1;
	}
	
	return 0;
}

int Board::checkLines(){
	for(int j=0; j<SIZE_y; j++){
		for(int i=0; i<SIZE_x; i++){
			if(grid[i][j] == 0){
				goto skip;
			}
		}
		return j;
		skip:;
	}
	return -1;
}

void Board::deleteLine(int l){
	for(int j=l; j<SIZE_y-1; j++){
		for(int i=0; i<SIZE_x; i++){
			grid[i][j] = grid[i][j+1];
		}
	}
}
