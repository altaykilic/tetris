#include "Tetris.h"

void Tetris::run(){
	init();
	loop();
}

void Tetris::loop(){
	bool gameend = 0;
	SDL_Event eventobj;
	bool s_hold = 0;
	
	while(!gameend){
		static Uint64 fps_start = SDL_GetPerformanceCounter();
	
		drawBoard();
		SDL_UpdateWindowSurface(windowptr);
		
		if(board.activePiece == nullptr){
			int full_line, combo = 0;
			while((full_line = board.checkLines()) != -1){
				combo++;
				board.deleteLine(full_line);
				score += (1<<combo);
			}
			
			short newshape = pop_queue(rand()%7);
			board.activePiece = new Piece(newshape, 0, SPAWNPOS);
			board.putPiece();
			if(board.movePiece()){
				gameend = 1;
				break;
			}
		}
		
		while(SDL_PollEvent(&eventobj) && !gameend){
			switch(eventobj.type){
				case SDL_QUIT:
					SDL_Quit();
					gameend = 1;
				break;
				case SDL_KEYDOWN:
					// if(eventobj.key.repeat)
					// 	break;
					switch(eventobj.key.keysym.sym){
						case SDLK_a: board.movePiece({-1,0}); break;
						case SDLK_d: board.movePiece({1,0}); break;
						case SDLK_s: s_hold = 1; break;
						case SDLK_x: board.rotate(1); break;
						case SDLK_z: board.rotate(0); break;
						case SDLK_SPACE: board.hardDrop(); break;
					}
				break;
				case SDL_KEYUP:
					if(eventobj.key.keysym.sym == SDLK_s)
						s_hold = 0;
				break;
				default:
					if(eventobj.type == TIMEREVENT){
						timercount = (timercount + 1) % 8;
						if(s_hold){
							board.movePiece();
						}
						else if(timercount == 0){
							board.movePiece();
						}
					}
				break;
			}
		}
		static Uint64 fps_end = SDL_GetPerformanceCounter();
		float fps_elapsed = (fps_end - fps_start) / (float)SDL_GetPerformanceFrequency();
		// std::cout << "Current FPS: " << 1.0f / fps_elapsed << '\n'; /*
		SDL_Delay(int(16.666f - fps_elapsed * 1000.0f)); /**/
	}
	// std::cout << "game ended\n";
	SDL_RemoveTimer(timer);
	SDL_Quit();
}

void Tetris::init(){
	//library needs
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER);
	
	//create window
	windowptr = SDL_CreateWindow("Tetris made by Altay Kilic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	surfaceptr = SDL_GetWindowSurface(windowptr);
	SDL_RaiseWindow(windowptr);
	SDL_FillRect(surfaceptr, NULL, SDL_MapRGB(surfaceptr->format, 0xff, 0xff, 0xff));
	
	//start timer
	timer = SDL_AddTimer(125, timerCallback, this);
	TIMEREVENT = SDL_RegisterEvents(1);
	
	//set colors
	COLORS[0]=SDL_MapRGB(surfaceptr->format, 0x00, 0x00, 0x00);
	COLORS[1]=SDL_MapRGB(surfaceptr->format, 0x00, 0x00, 0xff);
	COLORS[2]=SDL_MapRGB(surfaceptr->format, 0x00, 0xff, 0x00);
	COLORS[3]=SDL_MapRGB(surfaceptr->format, 0x00, 0xff, 0xff);
	COLORS[4]=SDL_MapRGB(surfaceptr->format, 0xff, 0x00, 0x00);
	COLORS[5]=SDL_MapRGB(surfaceptr->format, 0xff, 0x00, 0xff);
	COLORS[6]=SDL_MapRGB(surfaceptr->format, 0xff, 0xff, 0x00);
	COLORS[7]=SDL_MapRGB(surfaceptr->format, 0xff, 0x7f, 0x00); //orange, instead of white
	
	
	srand(time(NULL));
	for(int i=0; i<QSIZE; i++){
		pieceQ[i] = rand()%7;
	}
	
	// //DEBUGB
	// // board.activePiece = new Piece(2, 0, {2,10});
	// // board.putPiece();
	// for(int i=0; i<QSIZE; i++){
	// 	pieceQ[i] = i;
	// }
	// //DEBUGE
}

void Tetris::drawBoard(){
	SDL_Rect rect;
	rect.h = SQUARESIZE;
	rect.w = SQUARESIZE;
	
	for(int i=0; i<SIZE_x; i++) for(int j=0; j<SIZE_y2; j++){
		rect.x = i*SQUARESIZE+30;
		rect.y = j*SQUARESIZE+30;
		SDL_FillRect(surfaceptr, &rect, COLORS[board.grid[i][SIZE_y2-j-1]]);
	}
}

// Note: This function runs on a seperate thread.
Uint32 Tetris::timerCallback(Uint32 interval, void* ptr){
	Tetris* tmp = (Tetris*)ptr;
	// //DEBUG
	// std::cout << "timer " << int(tmp->timercount) << '\n';
	
	SDL_Event event;
	event.type = tmp->TIMEREVENT;
	SDL_PushEvent(&event);
	
	return interval;
}
