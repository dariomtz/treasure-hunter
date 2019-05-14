//
//  main.c
//  Hide and Sick
//
//  Created by DarÃƒÂ­o MartÃƒÂ­nez and Miguel GonzÃƒÂ¡lez on 4/2/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2_image/SDL_image.h>
#include "game_structs.h"
#include "game_functions.h"

int main(int argc, char* argv[]) {
	
	//initilization - do not delete
	//-----------------------------
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
		printf("Initalization not successful: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Window *win = SDL_CreateWindow("Hide and sick",
									   SDL_WINDOWPOS_CENTERED,
									   SDL_WINDOWPOS_CENTERED,
									   WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!win) {
		printf("Window creation not successful: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer * rend = SDL_CreateRenderer(win, -1, render_flags);
	
	if(!rend){
		printf("Renering not successful: %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	
	SDL_Surface* surface= IMG_Load("./resources/dungeon_sheet.png");
	if(!surface){
		printf("Image loading not successful: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if(!tex){
		printf("Image texture not successful: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	
	SDL_Surface* easterEgg= IMG_Load("./resources/easteregg.png");
	if(!surface){
		printf("Image loading 2 not successful: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	SDL_Texture* tex2 = SDL_CreateTextureFromSurface(rend, easterEgg);
	SDL_FreeSurface(easterEgg);
	if(!tex){
		printf("Image texture 2 not successful: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	//initilization - do not delete
	//-----------------------------
	
	SDL_Rect images[240];
	initializeImageRect(images);
	
	SDL_Rect shapes[240];
	initializeShapesRect(shapes,argv[0]);
	
	PLAYER player;
	initializePlayer(&player);
	
	BOX boxes[6];
	boxes[0] = newBox(11,21);
	boxes[1] = newBox(10,14);
	boxes[2] = newBox(5,3);
	boxes[3] = newBox(4,5);
	boxes[4] = newBox(-10,-10);
	boxes[5] = newBox(-10,-10);
	
	ANIMATION animations[20];
	initializeAnimations(animations, 20);
	
	SCREEN screen;

	int ticks_delay = 1000 / 60;
	unsigned char frames = 0;
	
	char close_requested = 0;
	SDL_Event event;
	
	//creation of Map1
	MAP maps[6];
	createMaps(maps, argv[0]);
	unsigned char currentMap = 0;
	unsigned int previousMap = 5;
	
	SDL_Rect dest;
	SDL_QueryTexture(tex2, NULL, NULL, &dest.w, &dest.h);
	
	while (!close_requested) {
		
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
					//close the game
				case SDL_QUIT:
					close_requested = 1;
					break;
					
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_W:
						case SDL_SCANCODE_UP:
							//player changes go up
							player.y_dir = -1;
							break;
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							//player changes go down
							player.y_dir = 1;
							break;
						case SDL_SCANCODE_A:
						case SDL_SCANCODE_LEFT:
							//player changes go left
							player.x_dir = -1;
							break;
						case SDL_SCANCODE_D:
						case SDL_SCANCODE_RIGHT:
							//player changes go right
							player.x_dir = 1;
							break;
						case SDL_SCANCODE_ESCAPE:
							close_requested = 1;
							break;
						case SDL_SCANCODE_SPACE:
							previousMap = currentMap;
							currentMap = playerInteraction(&player, &maps[currentMap], animations, currentMap);
							break;
						default:
							break;
					}
					break;
					
				case SDL_KEYUP:
					switch (event.key.keysym.scancode) {
						case SDL_SCANCODE_W:
						case SDL_SCANCODE_UP:
							//if the direction hasn't been changed to down (1), then stop moving upwards
							if (player.y_dir!=1)
								player.y_dir = 0;
							break;
						case SDL_SCANCODE_S:
						case SDL_SCANCODE_DOWN:
							//if the direction hasn't been changed to up (-1), then stop moving downwards
							if (player.y_dir!=-1)
								player.y_dir = 0;
							break;
						case SDL_SCANCODE_A:
						case SDL_SCANCODE_LEFT:
							//if the direction hasn't been changed to right (1), then stop moving left
							if (player.x_dir!=1)
								player.x_dir = 0;
							break;
						case SDL_SCANCODE_D:
						case SDL_SCANCODE_RIGHT:
							//if the direction hasn't been changed to left (-1), then stop moving right
							if (player.x_dir!=-1)
								player.x_dir = 0;
							break;
						default:
							break;
					}
					break;
			}
		}
		//clear the window
		SDL_RenderClear(rend);
		
		//matemachicken stuff
		frames++;
		player = updatePlayer2(player, maps[currentMap], shapes, rend);
		
		updateBox(&boxes[currentMap], &player, maps[currentMap], shapes);
		updateAnimations(animations, 20, &maps[currentMap]);
		updateScreen(&screen,player,maps[currentMap]);
		
		switch (currentMap) {
			case 0:
				if (maps[currentMap].walls[20][18] == 5 && maps[currentMap].walls[19][19] == 46) {
					addAnimation(19, 19, 46, animations);
				}
				
				if (maps[currentMap].walls[20][18] == 65 && maps[currentMap].walls[19][19] == 6) {
					addAnimation(19, 19, 6, animations);
				}
				
				if (boxes[currentMap].x / SCALE == 1 && boxes[currentMap].y /SCALE == 20 && maps[currentMap].walls[17][3] == 19) {
					addAnimation(2, 16, 8, animations);
					addAnimation(2, 17, 9, animations);
					addAnimation(3, 16, 18, animations);
					addAnimation(3, 17, 19, animations);
					addAnimation(4, 16, 28, animations);
					addAnimation(4, 17, 29, animations);
				}
				if((boxes[currentMap].x / SCALE != 1 || boxes[currentMap].y /SCALE != 20) && maps[currentMap].walls[17][3] == 139){
					addAnimation(2, 16, 128, animations);
					addAnimation(2, 17, 129, animations);
					addAnimation(3, 16, 138, animations);
					addAnimation(3, 17, 139, animations);
					addAnimation(4, 16, 148, animations);
					addAnimation(4, 17, 149, animations);
				}
				break;
			case 1:
				if (maps[currentMap].walls[2][1] == 5) {
					player.image = 197;
				}
				if (boxes[currentMap].x / SCALE == 2 && boxes[currentMap].y /SCALE == 8 && maps[currentMap].walls[12][2] == 87) {
					addAnimation(2, 12, 87, animations);
				}
				if (maps[currentMap].walls[12][2] == 127) {
					maps[currentMap].walls[12][3] = 196;
				}
				if (maps[currentMap].walls[12][3] == 196 && player.rocks[0] == 1) {
					maps[currentMap].walls[12][3] = EMPTY;
				}
				if (maps[currentMap].walls[8][7] == 35) {
					maps[currentMap].walls[8][6] = (maps[currentMap].walls[8][6] == EMPTY) ? 86: EMPTY;
					maps[currentMap].walls[14][9] = (maps[currentMap].walls[14][9] == EMPTY) ? 86: EMPTY;
					maps[currentMap].walls[10][6] = (maps[currentMap].walls[10][6] == EMPTY) ? 86: EMPTY;
					maps[currentMap].walls[10][10] = (maps[currentMap].walls[10][10] == EMPTY) ? 86: EMPTY;
				}
				if (maps[currentMap].walls[17][13] == 35) {
					maps[currentMap].walls[9][11] = (maps[currentMap].walls[9][11] == EMPTY) ? 106: EMPTY;
					maps[currentMap].walls[15][7] = (maps[currentMap].walls[15][7] == EMPTY) ? 106: EMPTY;
					maps[currentMap].walls[17][12] = (maps[currentMap].walls[17][12] == EMPTY) ? 106: EMPTY;
				}
				break;
			case 2:
				if (maps[currentMap].walls[11][19] == 5) {
					player.image = 217;
				}
				if (maps[currentMap].walls[15][16] == 35) {
					maps[currentMap].walls[8][15] = (maps[currentMap].walls[8][15] == EMPTY) ? 186: EMPTY;
					maps[currentMap].walls[11][10] = (maps[currentMap].walls[11][10] == EMPTY) ? 186: EMPTY;
					maps[currentMap].walls[10][5] = (maps[currentMap].walls[10][5] == EMPTY) ? 186: EMPTY;
					maps[currentMap].walls[15][17] = (maps[currentMap].walls[15][17] == EMPTY) ? 186: EMPTY;
				}
				if (maps[currentMap].walls[6][13] == 35) {
					maps[currentMap].walls[4][10] = (maps[currentMap].walls[4][10] == EMPTY) ? 176: EMPTY;
					maps[currentMap].walls[6][14] = (maps[currentMap].walls[6][14] == EMPTY) ? 176: EMPTY;
					maps[currentMap].walls[3][13] = (maps[currentMap].walls[3][13] == EMPTY) ? 176: EMPTY;
				}
				if (boxes[currentMap].x / SCALE == 1 && boxes[currentMap].y /SCALE == 7 && maps[currentMap].walls[10][1] == 10) {
					maps[currentMap].walls[10][0] = 21;
					maps[currentMap].walls[11][0] = 21;
					maps[currentMap].walls[10][1] = 219;
					maps[currentMap].walls[11][1] = 219;
					maps[currentMap].walls[10][2] = 219;
					maps[currentMap].walls[11][2] = 219;
					maps[currentMap].walls[10][3] = 0;
					maps[currentMap].walls[11][3] = 1;
				}
				if (maps[currentMap].walls[16][5] == 127) {
					maps[currentMap].walls[16][6] = 216;
				}
				if (maps[currentMap].walls[16][6] == 216 && player.rocks[2] == 1) {
					maps[currentMap].walls[16][6] = EMPTY;
				}
				break;
			case 3:
				if (boxes[currentMap].x / SCALE == 8 && boxes[currentMap].y /SCALE == 9 && maps[currentMap].walls[8][14] == 136) {
					maps[currentMap].walls[8][14] = EMPTY;
					maps[currentMap].walls[8][10] = EMPTY;
				}
				if ((boxes[currentMap].x / SCALE != 8 || boxes[currentMap].y /SCALE != 9)&& maps[currentMap].walls[8][14] == EMPTY) {
					maps[currentMap].walls[8][14] = 136;
					maps[currentMap].walls[8][10] = 136;
				}
				if (maps[currentMap].walls[4][16] == 35) {
					maps[currentMap].walls[4][17] = (maps[currentMap].walls[4][17] == EMPTY) ? 146: EMPTY;
					maps[currentMap].walls[6][6] = (maps[currentMap].walls[6][6] == EMPTY) ? 146: EMPTY;
				}
				if (boxes[currentMap].x / SCALE == 7 && boxes[currentMap].y /SCALE == 6 && maps[currentMap].walls[4][7] == EMPTY) {
					maps[currentMap].walls[4][7] = 87;
				}
				if (maps[currentMap].walls[4][7] == 127) {
					maps[currentMap].walls[4][8] = 206;
				}
				if (maps[currentMap].walls[4][8] == 206 && player.rocks[1] == 1) {
					maps[currentMap].walls[4][8] = EMPTY;
				}
				if (maps[currentMap].walls[13][2] == 5) {
					player.image = 207;
				}
				break;
			case 4:
				if (maps[currentMap].walls[2][6] == 5) {
					player.image = 237;
				}
				if (maps[currentMap].walls[2][7] == 127) {
					maps[currentMap].walls[2][8] = 236;
				}
				if (maps[currentMap].walls[2][8] == 236 && player.rocks[4] == 1) {
					maps[currentMap].walls[2][8] = EMPTY;
				}
				break;
			case 5:
				
				if (maps[currentMap].walls[2][1] == 5 && maps[currentMap].walls[1][2] == 46) {
					addAnimation(2, 1, 46, animations);
				}
				if (maps[currentMap].walls[2][1] == 65 && maps[currentMap].walls[1][2] == 6) {
					addAnimation(2, 1, 6, animations);
				}
				
				if (maps[currentMap].walls[2][4] == 5 && maps[currentMap].walls[1][5] == 46) {
					addAnimation(5, 1, 46, animations);
				}
				if (maps[currentMap].walls[2][4] == 65 && maps[currentMap].walls[1][5] == 6) {
					addAnimation(5, 1, 6, animations);
				}
				
				if (maps[currentMap].walls[2][6] == 5 && maps[currentMap].walls[1][7] == 46) {
					addAnimation(7, 1, 46, animations);
				}
				if (maps[currentMap].walls[2][6] == 65 && maps[currentMap].walls[1][7] == 6) {
					addAnimation(7, 1, 6, animations);
				}
				
				if (maps[currentMap].walls[2][8] == 5 && maps[currentMap].walls[1][9] == 46) {
					addAnimation(9, 1, 46, animations);
				}
				if (maps[currentMap].walls[2][8] == 65 && maps[currentMap].walls[1][9] == 6) {
					addAnimation(9, 1, 6, animations);
				}
				
				if (maps[currentMap].walls[2][10] == 5 && maps[currentMap].walls[1][11] == 46) {
					addAnimation(11, 1, 46, animations);
				}
				if (maps[currentMap].walls[2][10] == 65 && maps[currentMap].walls[1][11] == 6) {
					addAnimation(11, 1, 6, animations);
				}
				
				if (maps[currentMap].walls[2][12] == 5 && maps[currentMap].walls[1][13] == 46) {
					addAnimation(13, 1, 46, animations);
				}
				if (maps[currentMap].walls[2][12] == 65 && maps[currentMap].walls[1][13] == 6) {
					addAnimation(13, 1, 6, animations);
				}
				
				if (maps[currentMap].walls[2][14] == 5 && maps[currentMap].walls[1][15] == 46) {
					addAnimation(15, 1, 46, animations);
				}
				if (maps[currentMap].walls[2][14] == 65 && maps[currentMap].walls[1][15] == 6) {
					addAnimation(15, 1, 6, animations);
				}
				
				if (maps[currentMap].walls[2][16] == 5 && maps[currentMap].walls[1][17] == 46) {
					addAnimation(17, 1, 46, animations);
				}
				if (maps[currentMap].walls[2][16] == 65 && maps[currentMap].walls[1][17] == 6) {
					addAnimation(17, 1, 6, animations);
				}
				
				if (maps[currentMap].walls[2][18] == 5 && maps[currentMap].walls[1][19] == 46) {
					addAnimation(19, 1, 46, animations);
				}
				if (maps[currentMap].walls[2][18] == 65 && maps[currentMap].walls[1][19] == 6) {
					addAnimation(19, 1, 6, animations);
				}
				if (maps[currentMap].walls[14][3] == 5) {
					player.image = 227;
				}
				if (maps[currentMap].walls[7][20] == 127) {
					maps[currentMap].walls[7][21] = 226;
				}
				if (maps[currentMap].walls[7][21] == 226 && player.rocks[3] == 1) {
					maps[currentMap].walls[7][21] = EMPTY;
				}
				break;
			default:
				break;
		}
		
		
		
		//Draw stuff
		
		draw(maps[currentMap], images, rend, tex, player, boxes[currentMap], screen);
		drawInventory(player, images, rend, tex);
		if (currentMap == 4) {
			dest.y = SCALE * 4 - screen.y * SCALE - screen.y_module;
			dest.x = SCALE * 2 - screen.x * SCALE - screen.x_module;
			SDL_RenderCopy(rend, tex2, NULL, &dest);
		}
		
				
		//Send the image drawn to the screen
		SDL_RenderPresent(rend);
		
		if (frames == 60)
			frames = 0;
		
		//wait
		SDL_Delay(ticks_delay);
	}
	
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

