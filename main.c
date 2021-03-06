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
	boxes[0] = newBox(2,3);
	boxes[1] = newBox(9,15);
	boxes[2] = newBox(2,5);
	boxes[3] = newBox(5,3);
	boxes[4] = newBox(-10,-10);
	boxes[5] = newBox(-10,-10);
	
	ANIMATION animations[20];
	initializeAnimations(animations, 20);
	
	SCREEN screen;

	int ticks_delay = 1000 / 60;
	
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
		
		//operations
		player = updatePlayer(player, maps[currentMap], shapes, rend);
		updateBox(&boxes[currentMap], &player, maps[currentMap], shapes);
		updateAnimations(animations, 20, &maps[currentMap]);
		updateScreen(&screen,player,maps[currentMap]);
		
		switch (currentMap) {
			case 0:

                //open the path when the box is in the right place
                if (boxes[currentMap].x > 435 && boxes[currentMap].x < 460 &&
                    boxes[currentMap].y > 230 && boxes[currentMap].y < 240 &&
                    maps[currentMap].walls[1][6] == 1) {
                    maps[currentMap].walls[1][6] = 2;
                    maps[currentMap].walls[1][7] = 22;
                    maps[currentMap].walls[2][6] = EMPTY;
                    maps[currentMap].walls[2][7] = EMPTY;
                    maps[currentMap].walls[3][6] = EMPTY;
                    maps[currentMap].walls[3][7] = EMPTY;
                    maps[currentMap].walls[4][6] = 0;
                    maps[currentMap].walls[4][7] = 20;
                    boxes[currentMap].movable = 0;
                }
                
                //switch to clear the first path
                if (maps[currentMap].walls[1][10] == 35) {
                    maps[currentMap].walls[1][11] = (maps[currentMap].walls[1][11] == EMPTY) ? 86: EMPTY;
                    maps[currentMap].walls[3][14] = (maps[currentMap].walls[3][14] == EMPTY) ? 86: EMPTY;
                }
                
                //switch to open the door of lvl 4
				if (maps[currentMap].walls[21][5] == 5 && maps[currentMap].walls[20][6] == 46) {
					addAnimation(6, 20, 46, animations);
				}else if (maps[currentMap].walls[21][5] == 65 && maps[currentMap].walls[20][6] == 6) {
					addAnimation(6, 20, 6, animations);
				}
                
                //switch to open the door of lvl 5
                if (maps[currentMap].walls[21][19] == 5 && maps[currentMap].walls[20][20] == 9) {
                    addAnimation(20, 19, 8, animations);
                    addAnimation(20, 20, 9, animations);
                    addAnimation(21, 19, 18, animations);
                    addAnimation(21, 20, 19, animations);
                    addAnimation(22, 19, 28, animations);
                    addAnimation(22, 20, 29, animations);
                }else if (maps[currentMap].walls[21][19] == 65 && maps[currentMap].walls[20][20] == 129) {
                    addAnimation(20, 19, 128, animations);
                    addAnimation(20, 20, 129, animations);
                    addAnimation(21, 19, 138, animations);
                    addAnimation(21, 20, 139, animations);
                    addAnimation(22, 19, 148, animations);
                    addAnimation(22, 20, 149, animations);
                }
                
				break;
			case 1:
                //switch to change color back to blue
				if (maps[currentMap].walls[2][1] == 35) {
					player.image = 197;
				}
                
                //open the path when the box is in the right place
                if (boxes[currentMap].x > 235 && boxes[currentMap].x < 260 &&
                    boxes[currentMap].y > 930 && boxes[currentMap].y < 940 &&
                    maps[currentMap].walls[7][2] == 10) {
                    maps[currentMap].walls[7][2] = EMPTY;
                    maps[currentMap].walls[8][2] = EMPTY;
                    maps[currentMap].walls[7][3] = EMPTY;
                    maps[currentMap].walls[8][3] = EMPTY;
                    maps[currentMap].walls[7][1] = 21;
                    maps[currentMap].walls[8][1] = 22;
                    maps[currentMap].walls[7][4] = 1;
                    maps[currentMap].walls[8][4] = 2;
                    boxes[currentMap].movable = 0;
                }
                
                //switches to cleat the path
                if (maps[currentMap].walls[9][7] == 35) {
                    maps[currentMap].walls[9][6] = (maps[currentMap].walls[9][6] == EMPTY) ? 96: EMPTY;
                    maps[currentMap].walls[14][7] = (maps[currentMap].walls[14][7] == EMPTY) ? 96: EMPTY;
                    maps[currentMap].walls[12][10] = (maps[currentMap].walls[12][10] == EMPTY) ? 96: EMPTY;
                }
                
                if (maps[currentMap].walls[19][13] == 35) {
                    maps[currentMap].walls[11][5] = (maps[currentMap].walls[11][5] == EMPTY) ? 106: EMPTY;
                    maps[currentMap].walls[13][7] = (maps[currentMap].walls[13][7] == EMPTY) ? 106: EMPTY;
                    maps[currentMap].walls[12][13] = (maps[currentMap].walls[12][13] == EMPTY) ? 106: EMPTY;
                    maps[currentMap].walls[19][12] = (maps[currentMap].walls[19][12] == EMPTY) ? 106: EMPTY;
                }
                
                //drop the gem when opening
                if (maps[currentMap].walls[6][2] == 127) {
                    maps[currentMap].walls[6][3] = 196;
                }
                
                //take the gem
				if (maps[currentMap].walls[6][3] == 196 && player.rocks[0] == 1) {
					maps[currentMap].walls[6][3] = EMPTY;
				}
				break;
                
			case 2:
                //switch character color
                if (maps[currentMap].walls[5][16] == 35) {
                    player.image = 207;
                }
                
                //open and close the bloked part with the box
                if (boxes[currentMap].x > 1235 && boxes[currentMap].x < 1260 &&
                    boxes[currentMap].y > 530 && boxes[currentMap].y < 540 &&
                    maps[currentMap].walls[3][12] == 10) {
                    maps[currentMap].walls[3][12] = EMPTY;
                    maps[currentMap].walls[4][12] = EMPTY;
                    maps[currentMap].walls[3][13] = EMPTY;
                    maps[currentMap].walls[4][13] = EMPTY;
                    maps[currentMap].walls[3][11] = 21;
                    maps[currentMap].walls[4][11] = 22;
                    maps[currentMap].walls[3][14] = 1;
                    maps[currentMap].walls[4][14] = 2;
                    boxes[currentMap].movable = 0;
                }else if (!(boxes[currentMap].x > 1235 && boxes[currentMap].x < 1260 &&
                          boxes[currentMap].y > 530 && boxes[currentMap].y < 540) &&
                          maps[currentMap].walls[3][12] != 10){
                    maps[currentMap].walls[3][12] = 10;
                    maps[currentMap].walls[4][12] = 12;
                    maps[currentMap].walls[3][13] = 10;
                    maps[currentMap].walls[4][13] = 12;
                    maps[currentMap].walls[3][11] = 4;
                    maps[currentMap].walls[4][11] = 12;
                    maps[currentMap].walls[3][14] = 14;
                    maps[currentMap].walls[4][14] = 12;
                }
                
                //switch that clears the path
                if (maps[currentMap].walls[2][12] == 35) {
                    maps[currentMap].walls[2][13] = (maps[currentMap].walls[2][13] == EMPTY) ? 146: EMPTY;
                    maps[currentMap].walls[5][6] = (maps[currentMap].walls[5][6] == EMPTY) ? 146: EMPTY;
                    maps[currentMap].walls[6][6] = (maps[currentMap].walls[6][6] == EMPTY) ? 146: EMPTY;
                    maps[currentMap].walls[5][9] = (maps[currentMap].walls[5][9] == EMPTY) ? 146: EMPTY;
                    maps[currentMap].walls[6][9] = (maps[currentMap].walls[6][9] == EMPTY) ? 146: EMPTY;
                    maps[currentMap].walls[7][13] = (maps[currentMap].walls[7][13] == EMPTY) ? 146: EMPTY;
                    boxes[currentMap].movable = 1;
                }
                
                //open the path when the box is in the right place
                if (boxes[currentMap].x > 735 && boxes[currentMap].x < 760 &&
                    boxes[currentMap].y > 530 && boxes[currentMap].y < 540 &&
                    maps[currentMap].walls[3][7] == 10) {
                    maps[currentMap].walls[3][7] = EMPTY;
                    maps[currentMap].walls[4][7] = EMPTY;
                    maps[currentMap].walls[3][8] = EMPTY;
                    maps[currentMap].walls[4][8] = EMPTY;
                    maps[currentMap].walls[3][6] = 21;
                    maps[currentMap].walls[4][6] = 22;
                    maps[currentMap].walls[3][9] = 1;
                    maps[currentMap].walls[4][9] = 2;
                    boxes[currentMap].movable = 0;
                }
                
                //drop the gem while opening
                if (maps[currentMap].walls[2][7] == 127) {
                    maps[currentMap].walls[2][8] = 206;
                }
                
                //take the gem
                if (maps[currentMap].walls[2][8] == 206 && player.rocks[1] == 1) {
                    maps[currentMap].walls[2][8] = EMPTY;
                }
                break;
				
			case 3:
                //switch character color
                if (maps[currentMap].walls[11][19] == 35) {
                    player.image = 217;
                }
                
                //switch path openers
                if (maps[currentMap].walls[15][16] == 35) {
                    maps[currentMap].walls[7][15] = (maps[currentMap].walls[7][15] == EMPTY) ? 186: EMPTY;
                    maps[currentMap].walls[11][10] = (maps[currentMap].walls[11][10] == EMPTY) ? 186: EMPTY;
                    maps[currentMap].walls[10][6] = (maps[currentMap].walls[10][6] == EMPTY) ? 186: EMPTY;
                    maps[currentMap].walls[15][17] = (maps[currentMap].walls[15][17] == EMPTY) ? 186: EMPTY;
                }
                if (maps[currentMap].walls[6][13] == 35) {
                    maps[currentMap].walls[4][10] = (maps[currentMap].walls[4][10] == EMPTY) ? 176: EMPTY;
                    maps[currentMap].walls[6][14] = (maps[currentMap].walls[6][14] == EMPTY) ? 176: EMPTY;
                    maps[currentMap].walls[9][15] = (maps[currentMap].walls[9][15] == EMPTY) ? 176: EMPTY;
                    maps[currentMap].walls[9][5] = (maps[currentMap].walls[9][5] == EMPTY) ? 176: EMPTY;
                }
                
                //open path if the box is in the right place
                if (boxes[currentMap].x > 135 && boxes[currentMap].x < 160 &&
                    boxes[currentMap].y > 630 && boxes[currentMap].y < 640 &&
                    maps[currentMap].walls[10][1] == 10) {
                    maps[currentMap].walls[10][0] = 21;
                    maps[currentMap].walls[11][0] = 21;
                    maps[currentMap].walls[10][1] = 219;
                    maps[currentMap].walls[11][1] = 219;
                    maps[currentMap].walls[10][2] = 219;
                    maps[currentMap].walls[11][2] = 219;
                    maps[currentMap].walls[10][3] = 0;
                    maps[currentMap].walls[11][3] = 1;
                    boxes[currentMap].movable = 0;
                }
                
                //drop gem while opening chest
                if (maps[currentMap].walls[16][5] == 127) {
                    maps[currentMap].walls[16][6] = 216;
                }
                
                //grab gem
                if (maps[currentMap].walls[16][6] == 216 && player.rocks[2] == 1) {
                    maps[currentMap].walls[16][6] = EMPTY;
                }
                break;
			
			case 4:
                //switch character color
                if (maps[currentMap].walls[14][3] == 35) {
                    player.image = 227;
                }
                
                //switches that open and close doors
				if (maps[currentMap].walls[2][4] == 5 && maps[currentMap].walls[1][5] == 46) {
					addAnimation(5, 1, 46, animations);
				}else if (maps[currentMap].walls[2][4] == 65 && maps[currentMap].walls[1][5] == 6) {
					addAnimation(5, 1, 6, animations);
				}
				if (maps[currentMap].walls[2][6] == 5 && maps[currentMap].walls[1][7] == 46) {
					addAnimation(7, 1, 46, animations);
				}else if (maps[currentMap].walls[2][6] == 65 && maps[currentMap].walls[1][7] == 6) {
					addAnimation(7, 1, 6, animations);
				}
				if (maps[currentMap].walls[2][8] == 5 && maps[currentMap].walls[1][9] == 46) {
					addAnimation(9, 1, 46, animations);
				}else if (maps[currentMap].walls[2][8] == 65 && maps[currentMap].walls[1][9] == 6) {
					addAnimation(9, 1, 6, animations);
				}
				if (maps[currentMap].walls[2][10] == 5 && maps[currentMap].walls[1][11] == 46) {
					addAnimation(11, 1, 46, animations);
				}else if (maps[currentMap].walls[2][10] == 65 && maps[currentMap].walls[1][11] == 6) {
					addAnimation(11, 1, 6, animations);
				}
				if (maps[currentMap].walls[2][12] == 5 && maps[currentMap].walls[1][13] == 46) {
					addAnimation(13, 1, 46, animations);
				}else if (maps[currentMap].walls[2][12] == 65 && maps[currentMap].walls[1][13] == 6) {
					addAnimation(13, 1, 6, animations);
				}
				if (maps[currentMap].walls[2][14] == 5 && maps[currentMap].walls[1][15] == 46) {
					addAnimation(15, 1, 46, animations);
				}else if (maps[currentMap].walls[2][14] == 65 && maps[currentMap].walls[1][15] == 6) {
					addAnimation(15, 1, 6, animations);
				}
				if (maps[currentMap].walls[2][16] == 5 && maps[currentMap].walls[1][17] == 46) {
					addAnimation(17, 1, 46, animations);
				}else if (maps[currentMap].walls[2][16] == 65 && maps[currentMap].walls[1][17] == 6) {
					addAnimation(17, 1, 6, animations);
				}
				if (maps[currentMap].walls[2][18] == 5 && maps[currentMap].walls[1][19] == 46) {
					addAnimation(19, 1, 46, animations);
				}else if (maps[currentMap].walls[2][18] == 65 && maps[currentMap].walls[1][19] == 6) {
					addAnimation(19, 1, 6, animations);
				}
				
                //drop gem
				if (maps[currentMap].walls[7][20] == 127) {
					maps[currentMap].walls[7][21] = 226;
				}
                
                //grab gem
				if (maps[currentMap].walls[7][21] == 226 && player.rocks[3] == 1) {
					maps[currentMap].walls[7][21] = EMPTY;
				}
				break;

            case 5:
                //switch character color
                if (maps[currentMap].walls[2][6] == 5) {
                    player.image = 237;
                }
                
                //drop gem
                if (maps[currentMap].walls[2][7] == 127) {
                    maps[currentMap].walls[2][8] = 236;
                }
                
                //grab gem
                if (maps[currentMap].walls[2][8] == 236 && player.rocks[4] == 1) {
                    maps[currentMap].walls[2][8] = EMPTY;
                }
                break;
                
			default:
				break;
		}
		
		
		
		//Draw stuff
		draw(maps[currentMap], images, rend, tex, player, boxes[currentMap], screen);
		drawInventory(player, images, rend, tex);
		if (currentMap == 5) {
			dest.y = SCALE * 4 - screen.y * SCALE - screen.y_module;
			dest.x = SCALE * 2 - screen.x * SCALE - screen.x_module;
			SDL_RenderCopy(rend, tex2, NULL, &dest);
		}
				
		//Send the image drawn to the screen
		SDL_RenderPresent(rend);
		
		//wait
		SDL_Delay(ticks_delay);
	}
	
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

