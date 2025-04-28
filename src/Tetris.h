#pragma once

#include <SDL2/SDL.h>
#include <ctime>

#include "Pos.h"
#include "Board.h"
#include "HUD.h"

const int QSIZE = 5;
Uint32 COLORS[8];
const int SQUARESIZE = 30;
const pos SPAWNPOS = {5,21};

class Tetris{
public:
	Tetris();
	
	short pieceQ[QSIZE];
	int score;
	HUD hud;
	Board board;
	
	SDL_Window* windowptr;
	SDL_Surface* surfaceptr;
	Uint32 TIMEREVENT;
	SDL_TimerID timer;
	Uint8 timercount;
	
	short pop_queue(short n);
	void run();
	void loop();
	static Uint32 timerCallback(Uint32 interval, void* ptr);
	void drawBoard();
	void init();
};

Tetris::Tetris(){
	score = 0;
	hud.pieceQ = pieceQ;
	timercount = 0;
}

short Tetris::pop_queue(short next){
	short tmp = pieceQ[0];
	for(int i=0; i<QSIZE-1; i++){
		pieceQ[i] = pieceQ[i+1];
	}
	pieceQ[QSIZE-1] = next;
	return tmp;
}
