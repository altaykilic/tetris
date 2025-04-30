#ifndef _TETRIS_H
#define _TETRIS_H

#include <SDL2/SDL.h>
#include <ctime>

#include "Pos.h"
#include "Board.h"
#include "HUD.h"

class Tetris{
public:
	
	static const int QSIZE = 7;
	static Uint32 COLORS[8];
	static const int SQUARESIZE = 30;
	static const int CONTOURSIZE = 1;
	static const int BOARDOFFSET_X = 30;
	static const int BOARDOFFSET_Y = 30;
	static const pos SPAWNPOS;
	
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

#endif