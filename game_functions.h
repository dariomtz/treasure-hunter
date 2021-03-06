//
//  game_functions.h
//  Hide and Sick
//
//  Created by DarÃ­o MartÃ­nez and Miguel GonzÃ¡lez on 4/2/19.
//

#ifndef game_functions_h
#define game_functions_h

//Draw functions
void drawBox(BOX box, SDL_Rect images[], SDL_Renderer * rend, SDL_Texture * tex, PLAYER user, int mapSize) {
	SDL_Rect destination;
	if (user.x < WINDOW_WIDTH / 2)
		destination.x = box.x;
	else if (user.x > mapSize * SCALE - WINDOW_WIDTH / 2)
		destination.x = box.x - mapSize * SCALE + WINDOW_WIDTH;
	else
		destination.x = box.x - (user.x - WINDOW_WIDTH / 2);
	if (user.y < WINDOW_HEIGHT / 2)
		destination.y = box.y;
	else if (user.y > mapSize * SCALE - WINDOW_HEIGHT / 2)
		destination.y = box.y - mapSize * SCALE + WINDOW_HEIGHT;
	else
		destination.y = box.y - (user.y - WINDOW_HEIGHT / 2);
	destination.h = box.h;
	destination.w = box.w;
	
	SDL_RenderCopy(rend, tex, &images[box.image], &destination);
}

void drawPlayer(PLAYER user,SDL_Rect images[], SDL_Renderer * rend, SDL_Texture * tex, MAP map) {
	SDL_Rect destination;
	if (user.x < WINDOW_WIDTH / 2)
		destination.x = user.x;
	else if (user.x > map.mapSize * SCALE - WINDOW_WIDTH / 2)
		destination.x = user.x - map.mapSize * SCALE + WINDOW_WIDTH ;
	else
		destination.x = WINDOW_WIDTH / 2;
	if (user.y < WINDOW_HEIGHT / 2)
		destination.y = user.y;
	else if (user.y > map.mapSize * SCALE - WINDOW_HEIGHT / 2)
		destination.y = user.y - map.mapSize * SCALE + WINDOW_HEIGHT ;
	else
		destination.y = WINDOW_HEIGHT / 2;
	destination.h = user.h;
	destination.w = user.w;
	SDL_RenderCopy(rend, tex, &images[user.image], &destination);
}

void draw(MAP map, SDL_Rect images[], SDL_Renderer * rend, SDL_Texture * tex, PLAYER user, BOX box, SCREEN screen){
	SDL_Rect destination;
	for (int j=screen.y-1; j<screen.y2; j++) {
		for (int k = screen.x; k<screen.x2; k++) {
			destination.x = (k-screen.x)*SCALE-screen.x_module;
			destination.y = (j-screen.y)*SCALE-screen.y_module;
			destination.w = SCALE;
			destination.h = SCALE;
			SDL_RenderCopy(rend, tex, &images[LIGHT], &destination);
		}
	}
	
	unsigned char drawPriority[9][11];
	for (int j = screen.y; j < screen.y2; j++) {
		for (int k = screen.x; k < screen.x2; k++) {
			drawPriority[j-screen.y][k - screen.x] = 0;
			if (j == user.y / SCALE || j == box.y / SCALE) {
				drawPriority[j-screen.y][k - screen.x] = 1;
			}
			switch (map.walls[j][k]) {
				case 24:
				case 157:
				case 158:
				case 159:
				case 167:
				case 168:
				case 169:
				case 177:
				case 178:
				case 179:
				case 187:
				case 188:
				case 189:
				case 102:
				case 105:
				case 112:
				case 115:
				case 122:
				case 125:
				case 132:
				case 135:
				case 142:
				case 145:
				case 152:
				case 155:
				case 162:
				case 165:
				case 172:
				case 175:
				case 182:
				case 185:
				case 192:
				case 195:
				case 202:
				case 205:
				case 212:
				case 215:
				case 222:
				case 225:
				case 232:
				case 235:
					drawPriority[j-screen.y][k - screen.x] = 1;
					break;
				case 23:
				case 30:
				case 40:
				case 53:
				case 63:
				case 73:
				case 64:
				case 74:
				case 75:
				case 52:
				case 80:
				case 90:
				case 100:
				case 103:
				case 110:
				case 113:
				case 120:
				case 123:
				case 130:
				case 133:
				case 140:
				case 143:
				case 150:
				case 153:
				case 160:
				case 163:
				case 170:
				case 173:
				case 180:
				case 183:
				case 190:
				case 193:
				case 200:
				case 203:
				case 210:
				case 213:
				case 220:
				case 223:
				case 230:
				case 233:
					drawPriority[j-screen.y][k - screen.x] = 0;
					break;
				default:
					break;
			}
		}
	}
	
	for (int j = screen.y; j < screen.y2; j++) {
		for (int k = screen.x; k < screen.x2; k++) {
			if (drawPriority[j-screen.y][k - screen.x] == 1) {
				destination.x = (k - screen.x) * SCALE - screen.x_module;
				destination.y = (j - screen.y) * SCALE - screen.y_module;
				destination.w = SCALE;
				destination.h = SCALE;
				
				SDL_RenderCopy(rend, tex, &images[map.walls[j][k]], &destination);
			}
		}
	}
	
	
	if (user.y < box.y) {
		drawPlayer(user, images, rend, tex, map);
		drawBox(box, images, rend, tex, user,map.mapSize);
	}
	else {
		drawBox(box, images, rend, tex, user,map.mapSize);
		drawPlayer(user, images, rend, tex, map);
	}
	
	for (int j = screen.y; j < screen.y2; j++) {
		for (int k = screen.x; k < screen.x2; k++) {
			if (drawPriority[j-screen.y][k - screen.x] == 0) {
				destination.x = (k - screen.x) * SCALE - screen.x_module;
				destination.y = (j - screen.y) * SCALE - screen.y_module;
				destination.w = SCALE;
				destination.h = SCALE;
				
				SDL_RenderCopy(rend, tex, &images[map.walls[j][k]], &destination);
			}
		}
	}
}

void drawInventory(PLAYER player, SDL_Rect images[], SDL_Renderer * rend, SDL_Texture * tex){
	SDL_Rect dest;
	for (int i = 0; i < 5; i++) {
		if (player.rocks[i]) {
			dest.x = i * SCALE;
			dest.y = 0;
			dest.h = SCALE;
			dest.w = SCALE;
			SDL_RenderCopy(rend, tex, &images[(19 + i) * 10 + 6], &dest);
		}
	}
}

//-------------------------------------------------------------------------------------------
//Math functions

unsigned char rectIsInsideRect(SDL_Rect rect1, SDL_Rect rect2) {
    unsigned char contact = 0;
    if (rect1.x <= rect2.x) {
        if (rect1.x + rect1.w >= rect2.x)
            contact++;
    } else if (rect2.x + rect2.w >= rect1.x)
            contact++;

    if (rect1.y <= rect2.y) {
        if (rect1.y + rect1.h >= rect2.y)
            contact++;
    } else if (rect2.y + rect2.h >= rect1.y)
            contact++;

    return (contact == 2);
}

unsigned char pointIsInsideRect(SDL_Point point, SDL_Rect rect){
	return (rect.x <= point.x && point.x <= (rect.x + rect.w) && rect.y <= point.y && point.y <= (rect.y + rect.h));
}

unsigned char isPointInsideRect(int x, int y, SDL_Rect rect){
	return (rect.x <= x && x <= (rect.x + rect.w) && rect.y <= y && y <= (rect.y + rect.h));
}

unsigned char isLineInsideRect(int y, int x1, int x2, SDL_Rect rect){
	char heightOfLineIsInRect = (rect.y <= y && y <= rect.y + rect.h);
	char lineIsCrossingLeftSide = (x1 <= rect.x && rect.x <= x2);
	char lineIsCrossingRightSide = (x1 <= rect.x + rect.w && rect.x + rect.w <= x2);
	return (heightOfLineIsInRect && (lineIsCrossingLeftSide || lineIsCrossingRightSide));
}

//-------------------------------------------------------------------------------------------
//update functions

void addAnimation(int x, int y, int numOfBeginning, ANIMATION animations[]){
	int i = 0;
	while (animations[i].active) {
		i++;
	}
	animations[i].active = 1;
	animations[i].current = 0;
	animations[i].x = x;
	animations[i].y = y;
	animations[i].skip = 1;
	animations[i].dir = 1;
	switch (numOfBeginning) {
		case 47:
			animations[i].length = 4;
			break;
		case 5:
			animations[i].length = 7;
			break;
		case 65:
			animations[i].length = 7;
			animations[i].dir = -1;
			break;
		case 46:
			animations[i].length = 5;
			animations[i].dir = -1;
			break;
		case 6:
			animations[i].length = 5;
			break;
		case 8:
			animations[i].length = 5;
			animations[i].skip = 3;
			break;
		case 9:
			animations[i].length = 5;
			animations[i].skip = 3;
			break;
		case 18:
			animations[i].length = 5;
			animations[i].skip = 3;
			break;
		case 19:
			animations[i].length = 5;
			animations[i].skip = 3;
			break;
		case 28:
			animations[i].length = 5;
			animations[i].skip = 3;
			break;
		case 29:
			animations[i].length = 5;
			animations[i].skip = 3;
			break;
		case 128:
			animations[i].length = 5;
			animations[i].dir = -1;
			animations[i].skip = 3;
			break;
		case 129:
			animations[i].length = 5;
			animations[i].dir = -1;
			animations[i].skip = 3;
			break;
		case 138:
			animations[i].length = 5;
			animations[i].dir = -1;
			animations[i].skip = 3;
			break;
		case 139:
			animations[i].length = 5;
			animations[i].dir = -1;
			animations[i].skip = 3;
			break;
		case 148:
			animations[i].length = 5;
			animations[i].dir = -1;
			animations[i].skip = 3;
			break;
		case 149:
			animations[i].length = 5;
			animations[i].dir = -1;
			animations[i].skip = 3;
			break;
		case 87:
			animations[i].length = 6;
			break;
		default:
			animations[i].active = 0;
			animations[i].x = 0;
			animations[i].y = 0;
			animations[i].length = 0;
			animations[i].dir = 0;
			break;
			
	}
	for (int j = 0; j < animations[i].length; j++) {
		animations[i].images[j] = numOfBeginning + j * 10 * animations[i].dir * animations[i].skip;
	}
	
}

unsigned char playerInteraction(PLAYER * player, MAP * map, ANIMATION animations[], unsigned char currentMap){
	unsigned char initialMap = currentMap;
	unsigned char x = (player -> x + player -> w/2)/SCALE, y = (player -> y + player -> h/2)/SCALE;
	unsigned char image = map -> walls[y][x];
	unsigned char playerDestinationX = x, playerDestinationY = y;
	switch (image) {
		case 196:
		case 206:
		case 216:
		case 226:
		case 236:
			if (player -> image - 1 == image) {
				player -> rocks[image / 10 - 19] = 1;
			}
			break;
		case 147:
			map -> walls[y][x] = EMPTY;
			break;
		case 46:
		case 8:
		case 9:
		case 18:
		case 19:
		case 28:
		case 29:
		case 128:
		case 129:
		case 138:
		case 148:
		case 149:
			break;
		case 6:
			switch (initialMap) {
				case 0:
					if (x == 6 && y == 20) {
						currentMap = 4;
						playerDestinationY = 1;
						playerDestinationX = 2;
					}
					break;
				case 4:
					if (y == 1){
						if (x == 2) {
							currentMap = 0;
							playerDestinationY = 20;
							playerDestinationX = 6;
						}else if (x == 9){
							playerDestinationY = 6;
							playerDestinationX = 18;
						}else if (x == 17){
							playerDestinationY = 13;
							playerDestinationX = 1;
						}else{
							playerDestinationY = 19;
							playerDestinationX = 18;
						}
						
					}else if ((y == 6 && x == 22) || (y == 13 && x == 5) || (y == 19 && x == 22)) {
						playerDestinationY = 1;
						playerDestinationX = 22;
					}
					break;
					
				default:
					break;
			}
			break;
		case 139:
			if (initialMap == 0){
				if (x == 21 && y == 20) {
					currentMap = 5;
					playerDestinationY = 1;
					playerDestinationX = 2;
				}
			}else if(initialMap == 5){
				if (x == 2 && y == 1) {
					currentMap = 0;
					playerDestinationY = 20;
					playerDestinationX = 21;
				}
			}
			break;
		case 77:
			switch (initialMap) {
				case 0:
					if (x == 16 && y == 1) {
						currentMap = 1;
                        playerDestinationX = 2;
                        playerDestinationY = 1;
					}else if (x == 2 && y == 14) {
						currentMap = 3;
						playerDestinationY = 1;
					}else if (x == 21 && y == 8) {
						currentMap = 2;
						playerDestinationY = 1;
						playerDestinationX = 2;
					}
					break;
				case 1:
					if (x == 2 && y == 1) {
						currentMap = 0;
                        playerDestinationX = 16;
                        playerDestinationY = 1;
					}
					break;
				case 2:
					if (x == 2 && y == 1) {
						currentMap = 0;
						playerDestinationY = 8 ;
						playerDestinationX = 21;
					}
                    break;
                case 3:
                    if (x == 2 && y == 1) {
                        currentMap = 0;
                        playerDestinationY = 14;
                    }
					break;
				default:
					break;
			}
		case 87:
            if(initialMap != 1){
             addAnimation(x, y, image, animations);
            }
			
		default:
			addAnimation(x, y, image, animations);
			break;
	}
	if(initialMap != currentMap || x != playerDestinationX || y != playerDestinationY){
		player -> x = playerDestinationX * SCALE + SCALE / 8;
		player -> y = playerDestinationY * SCALE;
	}
	return currentMap;

}

void updateAnimations(ANIMATION animations[], int num, MAP * map){
	for (int i = 0; i < num; i++) {
		if (animations[i].active){
			animations[i].current++;
			map -> walls[animations[i].y][animations[i].x] = animations[i].images[animations[i].current];
			if (animations[i].current == animations[i].length-1) {
				animations[i].active = 0;
			}
		}
	}
}

PLAYER updatePlayer(PLAYER user, MAP map, SDL_Rect shapes[], SDL_Renderer * rend) {
    int x1, x2, x3, x4, y1, y2, y3;
    x1 = user.x - user.w;
    x2 = user.x;
    x3 = user.x + user.w;
    x4 = user.x + user.w * 2;
    
    y1 = user.y;
    y2 = user.y + user.h;
    y3 = user.y + user.h * 2;
    
    int xy[12][2] = {
        {x1,y1}, {x2,y1}, {x3,y1}, {x4,y1},
        {x1,y2}, {x2,y2}, {x3,y2}, {x4,y2},
        {x1,y3}, {x2,y3}, {x3,y3}, {x4,y3}
    };
    
    SDL_Rect rect[12];
    for (int i= 0;i<12;i++){
        int x = xy[i][0], y = xy[i][1];
        int numOfPiece = map.walls[y/SCALE][x/SCALE];
        
        if (shapes[numOfPiece].w==0) {
            rect[i].x = 0;
            rect[i].y = 0;
            rect[i].w = 0;
            rect[i].h = 0;
        }else{
            rect[i].x = shapes[numOfPiece].x;
            rect[i].y = shapes[numOfPiece].y;
            rect[i].w = shapes[numOfPiece].w;
            rect[i].h = shapes[numOfPiece].h;
            rect[i].x += x/SCALE * SCALE;
            rect[i].y += y/SCALE * SCALE;
        }
    }
    
    SDL_Rect playerHitBox;
    playerHitBox.x = user.x;
    playerHitBox.y = user.y + 7 * SCALE/8;
    playerHitBox.w = user.w;
    playerHitBox.h = SCALE / 8;
    
    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
    SDL_RenderDrawRects(rend, rect, 10);
    
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 0);
    
    //change the position of the player based on direction.
    switch (user.x_dir){
        case 1:
            //check if by moving right it is now inside a place it shouldn't be before moving
            playerHitBox.x += user.speed;
            if (rectIsInsideRect(playerHitBox, rect[2]) ||
                rectIsInsideRect(playerHitBox, rect[3]) ||
                rectIsInsideRect(playerHitBox, rect[6]) ||
                rectIsInsideRect(playerHitBox, rect[7]) ||
                rectIsInsideRect(playerHitBox, rect[10]) ||
                rectIsInsideRect(playerHitBox, rect[11])) {
                playerHitBox.x -= user.speed;
            }
            break;
        case -1:
            //check if by moving right it is now inside a place it shouldn't be before moving
            playerHitBox.x -= user.speed;
            if (rectIsInsideRect(playerHitBox, rect[0]) ||
                rectIsInsideRect(playerHitBox, rect[1]) ||
                rectIsInsideRect(playerHitBox, rect[4]) ||
                rectIsInsideRect(playerHitBox, rect[5]) ||
                rectIsInsideRect(playerHitBox, rect[8]) ||
                rectIsInsideRect(playerHitBox, rect[9])) {
                playerHitBox.x += user.speed;
            }
            break;
    }
    
    switch (user.y_dir){
        case 1:
            //check if by moving down it is now inside a place it shouldn't be before moving
            playerHitBox.y += user.speed;
            if (rectIsInsideRect(playerHitBox, rect[4]) ||
                rectIsInsideRect(playerHitBox, rect[5]) ||
                rectIsInsideRect(playerHitBox, rect[6]) ||
                rectIsInsideRect(playerHitBox, rect[7]) ||
                rectIsInsideRect(playerHitBox, rect[8]) ||
                rectIsInsideRect(playerHitBox, rect[9]) ||
                rectIsInsideRect(playerHitBox, rect[10]) ||
                rectIsInsideRect(playerHitBox, rect[11])) {
                playerHitBox.y -= user.speed;
            }
            break;
        case -1:
            //check if by moving up it is now inside a place it shouldn't be before moving
            playerHitBox.y -= user.speed;
            if (rectIsInsideRect(playerHitBox, rect[0]) ||
                rectIsInsideRect(playerHitBox, rect[1]) ||
                rectIsInsideRect(playerHitBox, rect[2]) ||
                rectIsInsideRect(playerHitBox, rect[3]) ||
                rectIsInsideRect(playerHitBox, rect[4]) ||
                rectIsInsideRect(playerHitBox, rect[5]) ||
                rectIsInsideRect(playerHitBox, rect[6]) ||
                rectIsInsideRect(playerHitBox, rect[7])) {
                playerHitBox.y += user.speed;
            }
            break;
    }
    user.x = playerHitBox.x;
    user.y = playerHitBox.y - 7 * SCALE / 8;
    return user;}

unsigned char player_box_contact(PLAYER * player, BOX * box, SDL_Rect shapes[]) {
	SDL_Rect box_rect, player_rect;
	unsigned char contact = 0;
	box_rect = shapes[box -> image];
	box_rect.x += box -> x;
	box_rect.y += box -> y;
	player_rect.x = player -> x - player -> x_dir * player -> speed;
	player_rect.y = player -> y + player -> h * 15 / 16;
	player_rect.w = player -> w;
	player_rect.h = player -> h / 16;
	
	if(rectIsInsideRect(player_rect, box_rect)){
		contact ++;
	}
	player_rect.x = player -> x;
	player_rect.y = player -> y + (player -> h * 15 / 16) - player -> y_dir * player -> speed;
	
	if(rectIsInsideRect(player_rect, box_rect)){
		contact ++;
	}
	
	return contact;
}

void updateBox(BOX * box, PLAYER * player, MAP map, SDL_Rect shapes[]){
    unsigned char contact = 0;
    unsigned char move_x = 1, move_y = 1;
    contact = player_box_contact(player, box, shapes);
    if (contact) {
        if (box -> movable) {
            int x[2] = {(box -> x + shapes[box -> image].x), (box -> x + shapes[box -> image].x + shapes[box -> image].w)};
            int y[2] = {(box -> y + shapes[box -> image].y), (box -> y + shapes[box -> image].y + shapes[box -> image].h)};
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    int present_x = x[i]/SCALE;
                    int present_y = y[i]/SCALE;
                    int future_x = (x[j] + player -> x_dir * player -> speed) / SCALE;
                    int future_y = (y[j] + player -> y_dir * player -> speed) / SCALE;
                    if(map.walls[present_y][future_x] != EMPTY &&
                       map.walls[present_y][future_x] != 178 &&
                       map.walls[present_y][future_x] != 188 &&
                       map.walls[present_y][future_x] != 179 &&
                       map.walls[present_y][future_x] != 189){
                        move_x = 0;
                    }
                    if(map.walls[future_y][present_x] != EMPTY &&
                       map.walls[future_y][present_x] != 178 &&
                       map.walls[future_y][present_x] != 188 &&
                       map.walls[future_y][present_x] != 179 &&
                       map.walls[future_y][present_x] != 189){
                        move_y = 0;
                    }
                }
            }
            
        } else {
            move_x = 0;
            move_y = 0;
        }
        
        
        
        if (move_x) {
            box -> x += player -> x_dir * player -> speed;
        } else {
            player -> x -= player -> x_dir * player -> speed;
        }
        
        if (move_y) {
            box -> y += player -> y_dir * player -> speed;
        } else {
            player -> y -= player -> y_dir * player -> speed;
        }
        
    }
}

void updateScreen(SCREEN *screen, PLAYER user, MAP map){
	screen->x_module = 0;
	screen->y_module = 0;
	if (user.x < WINDOW_WIDTH / 2) {
	        screen->x = 0;
	        screen->x2 = WINDOW_WIDTH / SCALE;
	    } else if(user.x > map.mapSize*SCALE-WINDOW_WIDTH/2){
	    	screen->x = map.mapSize-WINDOW_WIDTH/SCALE;
	    	screen->x2 = map.mapSize;
	    }else{
	    	screen->x = (user.x - WINDOW_WIDTH / 2) / SCALE;
	    	screen->x2 = (user.x + WINDOW_WIDTH / 2) / SCALE+1;
	    	screen->x_module = user.x%SCALE;
	    }

	    if (user.y < WINDOW_HEIGHT / 2) {
	    	screen->y = 0;
	        screen->y2 = WINDOW_HEIGHT / SCALE;
	    } else if(user.y > map.mapSize*SCALE-WINDOW_HEIGHT/2){
	    	screen->y = map.mapSize-WINDOW_HEIGHT/SCALE;
	        screen->y2 = map.mapSize;

	    }else{
	    	screen->y = (user.y - WINDOW_HEIGHT / 2) / SCALE;
	        screen->y2 = (user.y + WINDOW_HEIGHT / 2) / SCALE+1;
	        screen->y_module = user.y%SCALE;
	    }
}


//-------------------------------------------------------------------------------------------
//Initialization functions

void initializePlayer(PLAYER * player) {
    player -> x = 2 * SCALE;
    player -> y = 1 * SCALE;
    player -> h = 1 * SCALE;
    player -> w = 3 * SCALE / 4;
    player -> x_dir = 0;
    player -> y_dir = 0;
    player -> speed = 5;
    player -> image = 197;
	for (int i = 0; i < 5; i++) {
		player -> rocks[i] =0;
	}
	
}

BOX newBox(int x, int y){
	BOX box;
    box.x = x*SCALE;
    box.y = y*SCALE;
    box.w = SCALE;
    box.h = SCALE;
    box.image = 147;
    box.movable = 1;
    return box;
}

void initializeImageRect(SDL_Rect arrayRects[]){
    for (int i = 0; i < 240; i++) {
        arrayRects[i].x = (i/10)*16;
        arrayRects[i].y = (i%10)*16;
        arrayRects[i].h = 16;
        arrayRects[i].w = 16;
    }
	
	for (int i=197; i<240; i+=10) {
		arrayRects[i].x +=2;
		arrayRects[i].w -=4;
	}
}

void initializeAnimations(ANIMATION animations[], int num){
	for (int i = 0; i < num; i++) {
		animations[i].active = 0;
		animations[i].current = 0;
		animations[i].length = 0;
		animations[i].x = 0;
		animations[i].y = 0;
		animations[i].images[0] = '\0';
	}
}

void createMaps(MAP maps[], char dir[]){
    int count = 0;
    while (dir[count] != '\0') {
        count ++;
    }
    while (dir[count] != '/' && dir[count] != '\\') {
        dir[count] = '\0';
        count--;
    }

	char filePath[255];
	strcpy(filePath, dir);
	strcat(filePath, "resources/levels.csv");
	FILE * file = fopen(filePath, "r");
	char line[256];

	if(file != NULL){
		int row = 0;
		int map = -1;
		while (fgets(line, 256, file)){
			if (line[0] == '-' || map == -1){
				row = 0;
				map++;
				maps[map].mapSize = 24;
			}
			
			int columns[maps[map].mapSize];
			char num[6];
			int index = 0;
			int numIndex = 0;
			int destination = 0;
            
			while(line[index] != '\n' && line[index] != '-' && destination < 24){
				if (line[index] == ',' ) {
					numIndex = 0;
                    columns[destination] = atoi(num);
                    destination++;
				}else{
					num[numIndex] = line[index];
					num[numIndex+1] = '\0';
                    numIndex++;
				}
				index++;
			}
            columns[destination] = atoi(num);
			if (line[index] != '-') {
				for (int l = 0; l < maps[map].mapSize; l++) {
					maps[map].walls[row][l] = columns[l];
				}
				row++;
			}
		}
	}else{
		printf("ERROR: Unable to read CSV File \"resources/levels.csv\"");
	}
	fclose(file);
}

void initializeShapesRect(SDL_Rect arrayRects[], char dir[]){
    int count = 0;
    while (dir[count] != '\0') {
        count ++;
    }
    while (dir[count] != '/' && dir[count] != '\\') {
        dir[count] = '\0';
        count--;
    }
    
	char filePath[255];
	strcpy(filePath, dir);
	strcat(filePath, "resources/game_hitbox.csv");
	FILE * file = fopen(filePath, "r");
	char line[256];
	if(file != NULL){

		while (fgets(line, 256, file)){
			int piece[6];
			char num[5];
			int i = 0;
			int j = 0;
			int k = 0;
			while(line[i] != '\n'){

				if (line[i] == ',' ) {
					j = - 1;
				}else{
					if ((j==0 && i != 0) || line[i+1] == '\n') {
						piece[k] = atoi(num);
						k++;
					}
					num[j] = line[i];
					num[j+1] = '\0';
				}
				j++;
				i++;
			}
			arrayRects[piece[0]].x = (int) (piece[1] / (float) 16 * SCALE);
			arrayRects[piece[0]].y = (int) (piece[2] / (float) 16 * SCALE);
			arrayRects[piece[0]].w = (int) (piece[3] / (float) 16 * SCALE);
			arrayRects[piece[0]].h = (int) (piece[4] / (float) 16 * SCALE);
		}
	}else{
		printf("ERROR: Unable to read CSV File \"resources/game_hitbox.csv\"");

	}
	fclose(file);
}

#endif /* game_functions_h */
