//
//  main.c
//  Hide and Sick
//
//  Created by Darío Martínez and Miguel González on 4/2/19.
//
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
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
	initializeShapesRect(shapes);

	PLAYER player;
	player = Initialize_Player(player);

	BOX box;
	box = initialize_Box(box);

	BOX_PLAYER box_player;

	int ticks_delay = 1000 / 60;
	unsigned char frames = 0;
	unsigned char contact = 0;

	//char doors[] = {47, 57, 67, 77, 67, 52};

	SDL_Rect destination;

	char close_requested = 0;
	SDL_Event event;

	//creation of Map1
	MAP map1;
	map1 = initialize_Map1(map1);

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
					}
					break;
			}
		}

		//clear
		//clear the window
				SDL_RenderClear(rend);

		//matemachicken stuff
		frames++;
		contact = player_box_contact(player, box, shapes);
		box_player.box = box;

		//updates
		player = updatePlayer(player, map1, shapes);

		box_player.user = player;
		box_player = updateBox(box_player, map1, shapes);
		player = box_player.user;
		box = box_player.box;

		//Draw map
		drawMap(map1, images, rend, tex, destination, player);

		//draw player
		drawPlayer(player, images, rend, tex, destination, map1);

		//draw box
		drawBox (box, images, rend, tex, destination, player, map1.mapSize);

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
