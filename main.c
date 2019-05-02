//
//  main.c
//  Hide and Sick
//
//  Created by Darío Martínez and Miguel González on 4/2/19.
//
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2_image/SDL_image.h>

typedef struct{
	unsigned char floor[50][50];
	unsigned char walls[50][50];
	int mapSize;
} MAP;

struct PLAYER {
	int x;
	int y;
	unsigned char w;
	unsigned char h;
	unsigned char speed;
	char x_dir;
	char y_dir;
};

void initializeImageRect(SDL_Rect arrayRects[]){
	unsigned char xpos[119] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 22, 0, 1, 2, 3, 4, 6, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 10, 12, 14, 16, 18, 20, 22, 0, 1, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0, 3, 6, 9, 12, 15, 17, 19};
	unsigned char ypos[119] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8};
	unsigned char height[119] = {1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1};
	unsigned char width[119] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 2, 2, 1};
	
	for (int i = 0; i < 119; i++) {
		arrayRects[i].x = xpos[i]*16;
		arrayRects[i].y = ypos[i]*16;
		arrayRects[i].h = height[i]*16;
		arrayRects[i].w = width[i]*16;
	}
}

struct PLAYER InitializePlayer(struct PLAYER user, unsigned char scale) {
	user.x = 3 * scale;
	user.y = 3 * scale;
	user.h = 1;
	user.w = 1;
	user.x_dir = 0;
	user.y_dir = 0;
	user.speed = 3;
	return user;
}

unsigned char box_contact(struct SDL_Rect rect1, struct SDL_Rect rect2) {
	unsigned char contact = 0;
	if (rect1.x <= rect2.x) {
		if (rect1.x + rect1.w > rect2.x)
			contact++;
	} else {
		if (rect2.x + rect2.w > rect1.x)
			contact++;
	}
	if (rect1.y <= rect2.y) {
		if (rect1.y + rect1.h > rect2.y)
			contact++;
	} else {
		if (rect2.y + rect2.h > rect1.y)
			contact++;
	}
	return (contact == 2);
}
struct PLAYER ChangePlayer(struct PLAYER user, char time, MAP map,
		short int windowWidth, short int windowHeight, unsigned char Scale) {

	unsigned char x_move = 1, y_move = 1;

	//detect if the position is outside the windows
	if (user.x <= 0)
		user.x = 0;
	else if (user.w + user.x >= windowWidth)
		user.x = windowWidth - user.w;
	if (user.y <= 0)
		user.y = 0;
	else if (user.h + user.y >= windowHeight)
		user.y = windowHeight - user.h;

	struct SDL_Rect Rectx, Recty, RectWall;

	Rectx.x = (user.x + user.x_dir * user.speed) + 16;
	Rectx.y = user.y + Scale / 2;
	Rectx.h = Scale / 2;
	Rectx.w = 1 * Scale - 32;

	Recty.x = user.x + 16;
	Recty.y = (user.y + user.y_dir * user.speed) + Scale / 2;
	Recty.h = Scale / 2;
	Recty.w = 1 * Scale - 32;

	//detect contact with walls
	for (int x = 0; x < map.mapSize; x++) {
		for (int y = 0; y < map.mapSize; y++) {
			if (map.walls[y][x] != 118) {

				RectWall.x = x * Scale;
				RectWall.y = y * Scale;
				RectWall.w = Scale;
				RectWall.h = Scale;

				if (box_contact(RectWall, Rectx))
					x_move = 0;

				if (box_contact(Recty, RectWall))
					y_move = 0;
			}
		}
	}

	//move the position of the player
	if (x_move)
		user.x += user.x_dir * user.speed;
	if (y_move)
		user.y += user.y_dir * user.speed;

	return user;
}




void drawMap(MAP map, SDL_Rect images[], unsigned char scale, SDL_Renderer * rend, SDL_Texture * tex, SDL_Rect destination){
	
	//draw floor of map 1
	for (int j=0; j<map.mapSize; j++) {
		for (int k = 0; k<map.mapSize; k++) {
			destination.x = k*scale;
			destination.y = j*scale;
			destination.w = images[map.floor[j][k]].w*scale/16;
			destination.h = images[map.floor[j][k]].h*scale/16;
			SDL_RenderCopy(rend, tex, &images[map.floor[j][k]], &destination);
		}
	}
	
	//draw whatever is not a floor of map 1
	for (int j=0; j<map.mapSize; j++) {
		for (int k = 0; k<map.mapSize; k++) {
			destination.x = k*scale;
			destination.y = j*scale;
			//if you are going to use the height and width of the image as a reference...
			//  it is necesary to divide it by 16 (which is the number of pixels of every unit in the image
			destination.w = images[map.walls[j][k]].w*scale/16;
			destination.h = images[map.walls[j][k]].h*scale/16;
			SDL_RenderCopy(rend, tex, &images[map.walls[j][k]], &destination);
		}
	}
}

MAP initialize_Map1(MAP map) {
	enum {
		LIGHT = 29, DARK = 18, EMPTY = 118
	};
	map.mapSize = 10;
	
	//assign values to the floor pieces of the floor pieces
	for (int i = 0; i < map.mapSize; i++) {
		for (int j = 0; j < map.mapSize; j++) {
			switch (i) {
				case 0:
					map.floor[i][j] = EMPTY;
					break;
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
					map.floor[i][j] = LIGHT;
					break;
				default:
					map.floor[i][j] = DARK;
					break;
			}
		}
	}
	
	//assign values to the walls and not floor pieces
	for (int i = 0; i < map.mapSize; i++) {
		for (int j = 0; j < map.mapSize; j++) {
			switch (i) {
				case 0:
					map.walls[i][j] = 6;
					break;
				case 1:
					map.walls[i][j] = (j == 4) ? EMPTY : ((j % 2) ? 88 : 50);
					break;
				case 2:
				case 3:
				case 4:
				case 5:
					map.walls[i][j] = EMPTY;
					break;
				case 6:
					map.walls[i][j] = 39;
					break;
				default:
					map.walls[i][j] = EMPTY;
					break;
			}
		}
	}
	map.walls[4][4] = 50;
	return map;
	
}


int main(int argc, char* argv[]) {
	unsigned char scale = 100;
	short int windowWidth = scale*10;
	short int windowHeight = scale*8;
	
	//initilization - do not delete
	//-----------------------------
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
		printf("Initalization not successful: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Window *win = SDL_CreateWindow("HELLO WORLD",
									   SDL_WINDOWPOS_CENTERED,
									   SDL_WINDOWPOS_CENTERED,
									   1000, 800, 0);
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
	
	enum {LIGHT = 29, DARK = 18, EMPTY = 118};
	
	struct SDL_Rect images[119];
	initializeImageRect(images);
	
	struct PLAYER player;
	player = InitializePlayer(player, scale);
	
	int ticks_delay = 1000 / 60;
	unsigned char frames = 0;
	
	char doors[] = {91, 92, 93, 94, 93, 92};
	
	struct SDL_Rect destination;
	
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
		
		//matemachicken stuff
		frames++;
		player = ChangePlayer(player, frames, map1, windowWidth, windowHeight, scale);
		
		//clear the window
		SDL_RenderClear(rend);
		
		drawMap(map1, images, scale, rend, tex, destination);
		
		//draw door
		destination.x = 4*100;
		destination.y = 100;
		destination.w = 100;
		destination.h = 100;
		SDL_RenderCopy(rend, tex, &images[doors[0]], &destination);
		
		//draw player
		destination.x = player.x;
		destination.y = player.y;
		destination.h = player.h * scale;
		destination.w = player.w * scale;
		SDL_RenderCopy(rend, tex, &images[108], &destination);
		
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
