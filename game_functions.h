//
//  game_functions.h
//  Hide and Sick
//
//  Created by Darío Martínez and Miguel González on 4/2/19.
//

#ifndef game_functions_h
#define game_functions_h

//Draw functions
void drawMap(MAP map, SDL_Rect images[], SDL_Renderer * rend, SDL_Texture * tex, SDL_Rect destination,PLAYER user){
    
    unsigned char x_initial, x_final, y_initial, y_final, x_module, y_module;
    x_module = 0;
    y_module = 0;
    if (user.x < WINDOW_WIDTH / 2) {
        x_initial = 0;
        x_final = WINDOW_WIDTH / SCALE;
    } else if(user.x > map.mapSize*SCALE-WINDOW_WIDTH/2){
        x_initial = map.mapSize-WINDOW_WIDTH/SCALE;
        x_final = map.mapSize;
    }else{
        x_initial = (user.x - WINDOW_WIDTH / 2) / SCALE;
        x_final = (user.x + WINDOW_WIDTH / 2) / SCALE+1;
        x_module = user.x%SCALE;
    }
    
    if (user.y < WINDOW_HEIGHT / 2) {
        y_initial = 0;
        y_final = WINDOW_HEIGHT / SCALE;
    } else if(user.y > map.mapSize*SCALE-WINDOW_HEIGHT/2){
        y_initial = map.mapSize-WINDOW_HEIGHT/SCALE;
        y_final = map.mapSize;
        
    }else{
        y_initial = (user.y - WINDOW_HEIGHT / 2) / SCALE;
        y_final = (user.y + WINDOW_HEIGHT / 2) / SCALE+1;
        y_module = user.y%SCALE;
    }
    
    //draw floor of map 1
    for (int j=y_initial; j<y_final; j++) {
        for (int k = x_initial; k<x_final; k++) {
            destination.x = (k-x_initial)*SCALE-x_module;
            destination.y = (j-y_initial)*SCALE-y_module;
			destination.w = SCALE;
			destination.h = SCALE;
            SDL_RenderCopy(rend, tex, &images[LIGHT], &destination);
        }
    }
    
    //draw whatever is not a floor of map 1
    for (int j=y_initial; j<y_final; j++) {
        for (int k = x_initial; k<x_final; k++)  {
            destination.x = (k-x_initial)*SCALE-x_module;
            destination.y = (j-y_initial)*SCALE-y_module;
            //if you are going to use the height and width of the image as a reference...
            //  it is necesary to divide it by 16 (which is the number of pixels of every unit in the image
            destination.w = images[map.walls[j][k]].w*SCALE/16;
            destination.h = images[map.walls[j][k]].h*SCALE/16;
            SDL_RenderCopy(rend, tex, &images[map.walls[j][k]], &destination);
        }
    }
}

void drawPlayer(PLAYER user,SDL_Rect images[], SDL_Renderer * rend,
                SDL_Texture * tex, SDL_Rect destination, MAP map) {
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

void drawBox(BOX box, SDL_Rect images[], SDL_Renderer * rend, SDL_Texture * tex,
             SDL_Rect destination, PLAYER user, int mapSize) {
    
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

//-------------------------------------------------------------------------------------------
//Math functions

unsigned char rectIsInsideRect(SDL_Rect rect1, SDL_Rect rect2) {
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

void playerInteraction(PLAYER player, MAP map, ANIMATION animations[]){
	unsigned char x = (player.x + player.w/2)/SCALE, y = (player.y + player.h/2)/SCALE;
	unsigned char image = map.walls[y][x];

	int i = 0;
	while (animations[i].active == 1) {
		i++;
	}

	switch (image) {
		case 47:
			animations[i].active = 1;
			animations[i].current = 0;
			animations[i].length = 4;
			animations[i].x = x;
			animations[i].y = y;
			for (int j = 0; j < 4; j++) {
				animations[i].images[j] = 47 + j*10;
			}
			animations[i].images[4] = '\0';
			//printf("%s", animations[i].images);
			break;
		case 5:
			animations[i].active = 1;
			animations[i].current = 0;
			animations[i].length = 7;
			animations[i].x = x;
			animations[i].y = y;
			for (int j = 0; j < 7; j++) {
				animations[i].images[j] = 5 + j*10;
			}
			animations[i].images[7] = '\0';
			//printf("%s", animations[i].images);
			break;
		case 65:
			animations[i].active = 1;
			animations[i].current = 0;
			animations[i].length = 7;
			animations[i].x = x;
			animations[i].y = y;
			for (int j = 0; j < 7; j++) {
				animations[i].images[j] = 65 - j*10;
			}
			animations[i].images[7] = '\0';
			//printf("%s", animations[i].images);
			break;

		default:
			printf("\nNo action to be done");
			break;
	}

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
    
    int xy[10][2] = {
        {x2,y1}, {x3,y1},
        {x1,y2}, {x2,y2}, {x3,y2}, {x4,y2},
        {x1,y3}, {x2,y3}, {x3,y3}, {x4,y3}
    };
	
    SDL_Rect rect[10];
    for (int i= 0;i<10;i++){
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
	
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
	SDL_RenderDrawRects(rend, rect, 10);
	
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 0);
    
    //change the position of the player based on direction.
    switch (user.x_dir){
        case 1:
            //check if by moving right it is now inside a place it shouldn't be before moving
            if (!isPointInsideRect(x3 + user.speed, y2, rect[4]) &&
                !isPointInsideRect(x3 + user.speed, y2, rect[5]) &&
                !isPointInsideRect(x3 + user.speed, y2, rect[8]) &&
                !isPointInsideRect(x3 + user.speed, y2, rect[9])){
                user.x += user.speed;
            }
            break;
        case -1:
            //check if by moving right it is now inside a place it shouldn't be before moving
            if (!isPointInsideRect(x2 - user.speed, y2, rect[2]) &&
                !isPointInsideRect(x2 - user.speed, y2, rect[3]) &&
                !isPointInsideRect(x2 - user.speed, y2, rect[6]) &&
                !isPointInsideRect(x2 - user.speed, y2, rect[7])
                ){
                user.x -= user.speed;
            }
            break;
    }
    
    switch (user.y_dir){
        case 1:
            //check if by moving down it is now inside a place it shouldn't be before moving
            if (!isLineInsideRect(y2 + user.speed, x2, x3, rect[2]) &&
                !isLineInsideRect(y2 + user.speed, x2, x3, rect[3]) &&
                !isLineInsideRect(y2 + user.speed, x2, x3, rect[4]) &&
                !isLineInsideRect(y2 + user.speed, x2, x3, rect[5]) &&
                !isLineInsideRect(y2 + user.speed, x2, x3, rect[6]) &&
                !isLineInsideRect(y2 + user.speed, x2, x3, rect[7]) &&
                !isLineInsideRect(y2 + user.speed, x2, x3, rect[8]) &&
                !isLineInsideRect(y2 + user.speed, x2, x3, rect[9])) {
                user.y += user.speed;
            }
            break;
        case -1:
            //check if by moving up it is now inside a place it shouldn't be before moving
            if (!isLineInsideRect(y2 - user.speed, x2, x3, rect[0]) &&
                !isLineInsideRect(y2 - user.speed, x2, x3, rect[1]) &&
                !isLineInsideRect(y2 - user.speed, x2, x3, rect[2]) &&
                !isLineInsideRect(y2 - user.speed, x2, x3, rect[3]) &&
                !isLineInsideRect(y2 - user.speed, x2, x3, rect[4]) &&
                !isLineInsideRect(y2 - user.speed, x2, x3, rect[5])) {
                user.y -= user.speed;
            }
            break;
    }
    return user;
}

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
    unsigned char move = 1;
    int x, y;
    contact = player_box_contact(player, box, shapes);
    if (contact) {
        if (box -> movable) {
            x = (box -> x+10 * player -> x_dir * player -> speed)/SCALE;
            y = (box -> y+10 * player -> y_dir * player -> speed)/SCALE;
            if(map.walls[y][x] != EMPTY){
                move = 0;
            }
        } else {
            move = 0;
        }
        
        if (move) {
            box -> x += 10 * player -> x_dir * player -> speed;
            box -> y += 10 * player -> y_dir * player -> speed;
            
        } else {
            player -> x -= player -> x_dir * player -> speed;
            player -> y -= player -> y_dir * player -> speed;
        }
    }
}

//-------------------------------------------------------------------------------------------
//Initialization functions

void initializePlayer(PLAYER * player) {
    player -> x = 3 * SCALE;
    player -> y = 3 * SCALE;
    player -> h = 1 * SCALE;
    player -> w = 1 * SCALE;
    player -> x_dir = 0;
    player -> y_dir = 0;
    player -> speed = 5;
    player -> image = 197;
}

BOX initialize_Box(BOX box){
    box.x = 6*SCALE;
    box.y = 4*SCALE;
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

MAP initialize_Map1(MAP map) {
    map.mapSize = 20;
    //assign values to the walls and not floor pieces
    for (int i = 0; i < map.mapSize; i++) {
        for (int j = 0; j < map.mapSize; j++) {
            switch (i) {
                case 0:
                    map.walls[i][j] = j==0 ? 50 : (j==map.mapSize-1) ? 70 : 60;
                    break;
                case 1:
                    switch (j) {
                        case 0:
                            map.walls[i][j] = 51;
                            break;
                        case 4:
                            map.walls[i][j] = 47;
                            break;
                            break;
                        default:
							map.walls[i][j] = (j == map.mapSize-1) ? 71: (j % 2) ? 17 : 54;
                            break;
                    }
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                    map.walls[i][j] = j==0 ? 52 : (j==map.mapSize-1) ? 72 : EMPTY;
                    break;
                case 6:
                    map.walls[i][j] = j==0 ? 53 : (j==map.mapSize-1) ? 73 : 63;
                    break;
                case 7:
                    map.walls[i][j] = DARK;
                    break;
                default:
                    map.walls[i][j] = EMPTY;
                    break;
            }
        }
    }
    map.walls[4][15] = 5;
    return map;
}

void initializeShapesRect(SDL_Rect arrayRects[], char dir[]){
	int count = 0;
	while (dir[count] != '\0') {
		count ++;
	}
	int i=count;
	while (dir[i] != '/' && dir[i] != '\\') {
		dir[i] = '\0';
		i--;
	}
	printf("%s\n", dir);
	
	char filePath[255];
	strcpy(filePath, dir);
	strcat(filePath, "resources/game_hitbox.csv");
	FILE * file = fopen(filePath, "r");
	char line[256];

	if(file != NULL){
		while (fgets(line, 256, file)){
			int piece[6];
			char num[5];
			i = 0;
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
			
			printf("%s", line);
		}
		
	}else{
		printf("ERROR: Unable to read CSV File \"resources/game_hitbox.csv\"");
	}
	fclose(file);
}

#endif /* game_functions_h */
