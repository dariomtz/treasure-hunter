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
	//initilization - do not delete
	//-----------------------------
	
	SDL_Rect images[240];
	initializeImageRect(images);
	
	SDL_Rect shapes[240];
	initializeShapesRect(shapes,argv[0]);
	
	PLAYER player;
	initializePlayer(&player);
	
	BOX box;
	box = newBox(11,21);
	
	ANIMATION animations[20];
	initializeAnimations(animations, 20);
	
	SCREEN screen;

	int ticks_delay = 1000 / 60;
	unsigned char frames = 0;
	
	char close_requested = 0;
	SDL_Event event;
	
	//creation of Map1
	MAP maps[6];
	createMenu(maps, argv[0]);
	unsigned char currentMap = 0;
	unsigned int previousMap = 5;
	
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
							currentMap = playerInteraction(&player, maps[currentMap], animations, currentMap);
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
		
		updateBox(&box, &player, maps[0], shapes);
		updateAnimations(animations, 20, &maps[currentMap]);
		updateScreen(&screen,player,maps[0]);
		
		switch (currentMap) {
			case 0:
				if (maps[currentMap].walls[20][18] == 5 && maps[currentMap].walls[19][19] == 46) {
					addAnimation(19, 19, 46, animations);
				}
				
				if (maps[currentMap].walls[20][18] == 65 && maps[currentMap].walls[19][19] == 6) {
					addAnimation(19, 19, 6, animations);
				}
				
				if (box.x / SCALE == 1 && box.y /SCALE == 20 && maps[currentMap].walls[17][3] == 19) {
					addAnimation(2, 16, 8, animations);
					addAnimation(2, 17, 9, animations);
					addAnimation(3, 16, 18, animations);
					addAnimation(3, 17, 19, animations);
					addAnimation(4, 16, 28, animations);
					addAnimation(4, 17, 29, animations);
				}
				if((box.x / SCALE != 1 || box.y /SCALE != 20) && maps[currentMap].walls[17][3] == 139){
					addAnimation(2, 16, 128, animations);
					addAnimation(2, 17, 129, animations);
					addAnimation(3, 16, 138, animations);
					addAnimation(3, 17, 139, animations);
					addAnimation(4, 16, 148, animations);
					addAnimation(4, 17, 149, animations);
				}
				break;
				
			default:
				break;
			case 5:
				if (maps[currentMap].walls[2][1] == 5 && maps[currentMap].walls[1][2] == 46) {
					addAnimation(2, 1, 46, animations);
					
				}
				
				if (maps[currentMap].walls[2][1] == 65 && maps[currentMap].walls[1][2] == 6) {
					addAnimation(2, 1, 6, animations);
				}
		}
		
		
		
		//Draw stuff
		
		draw(maps[currentMap], images, rend, tex, player, box, screen);
				
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

