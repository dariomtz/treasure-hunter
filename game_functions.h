//
//  main.c
//  Hide and Sick
//
//  Created by Darío Martínez and Miguel González on 4/2/19.
//

#ifndef game_functions_h
#define game_functions_h

//inizialization functions
//----------------------------------------------------

void initializeImageRect(SDL_Rect arrayRects[]){
    for (int i = 0; i < 240; i++) {
        arrayRects[i].x = (i/10)*16;
        arrayRects[i].y = (i%10)*16;
        arrayRects[i].h = 16;
        arrayRects[i].w = 16;
    }
}

void initializeShapesRect(SDL_Rect arrayRects[]){
    for (int i = 0; i < 240; i++) {
        //x
        switch (i) {
            case 147:
                arrayRects[i].x =(int) ((3/(float)16)*SCALE);
                break;
            case 24:
            case 31:
            case 34:
            case 40:
            case 81:
            case 83:
            case 86:
            case 96:
            case 106:
            case 136:
            case 146:
            case 176:
            case 186:
                arrayRects[i].x = SCALE/4;
                break;
            case 56:
            case 66:
            case 76:
            case 101:
            case 102:
            case 116:
            case 121:
            case 122:
            case 126:
            case 141:
            case 142:
            case 156:
            case 161:
            case 162:
            case 166:
            case 181:
            case 182:
            case 201:
            case 202:
            case 221:
            case 222:
                arrayRects[i].x = (int) ((6/(float)16)*SCALE);
                break;
            case 33:
            case 42:
            case 71:
            case 72:
            case 73:
            case 82:
            case 124:
            case 125:
            case 144:
            case 145:
            case 164:
            case 165:
            case 184:
            case 185:
            case 204:
            case 205:
            case 224:
            case 225:
                arrayRects[i].x = (int) ((7/(float)16)*SCALE);
                break;
            case 104:
            case 105:
                arrayRects[i].x = SCALE/2;
                break;
            default:
                arrayRects[i].x = 0;
                break;
        }
        //y
        switch (i) {
            case 24:
                arrayRects[i].y = SCALE/4;
                break;
            case 147:
                arrayRects[i].y = (int) ((6/(float)16)*SCALE);
                break;
            case 5:
            case 15:
            case 25:
            case 35:
            case 45:
            case 55:
            case 56:
            case 65:
            case 66:
            case 76:
            case 86:
            case 96:
            case 106:
            case 116:
            case 126:
            case 136:
            case 146:
            case 156:
            case 166:
            case 176:
            case 186:
                arrayRects[i].y = (int) ((7/(float)16)*SCALE);
                break;
            case 87:
            case 97:
            case 107:
            case 117:
            case 127:
            case 137:
                arrayRects[i].y = SCALE/2;
                break;
            case 104:
            case 114:
            case 124:
            case 134:
            case 144:
            case 154:
            case 164:
            case 174:
            case 184:
            case 194:
            case 204:
            case 214:
            case 224:
            case 234:
                arrayRects[i].y = (int) ((11/(float)16)*SCALE);
                break;
                
            default:
                arrayRects[i].y = 0;
                break;
        }
        
        //w
        switch (i) {
            case 56:
            case 66:
            case 76:
            case 116:
            case 126:
            case 156:
            case 166:
                arrayRects[i].w = 25;
                break;
            case 24:
            case 86:
            case 96:
            case 104:
            case 105:
            case 106:
            case 114:
            case 115:
            case 124:
            case 125:
            case 134:
            case 135:
            case 136:
            case 144:
            case 145:
            case 146:
            case 154:
            case 155:
            case 164:
            case 165:
            case 174:
            case 175:
            case 176:
            case 184:
            case 185:
            case 186:
            case 194:
            case 195:
            case 204:
            case 205:
            case 214:
            case 215:
            case 224:
            case 225:
            case 234:
            case 235:
                arrayRects[i].w = 50;
                break;
            case 32:
            case 33:
            case 42:
            case 43:
            case 51:
            case 52:
            case 53:
            case 64:
            case 71:
            case 72:
            case 73:
            case 74:
            case 82:
            case 92:
                arrayRects[i].w = 56;
                break;
            case 101:
            case 102:
            case 111:
            case 112:
            case 121:
            case 122:
            case 131:
            case 132:
            case 141:
            case 142:
            case 147:
            case 151:
            case 152:
            case 161:
            case 162:
            case 171:
            case 172:
            case 181:
            case 182:
            case 191:
            case 192:
            case 201:
            case 202:
            case 211:
            case 212:
            case 221:
            case 222:
            case 231:
            case 232:
                arrayRects[i].w = 62;
                break;
            case 30:
            case 31:
            case 34:
            case 40:
            case 41:
            case 44:
            case 81:
            case 83:
            case 91:
            case 93:
                arrayRects[i].w = 75;
                break;
            case 5:
            case 15:
            case 25:
            case 35:
            case 45:
            case 55:
            case 65:
            case 87:
            case 97:
            case 107:
            case 117:
            case 127:
            case 137:
                arrayRects[i].w = 87;
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 26:
            case 27:
            case 28:
            case 29:
            case 36:
            case 37:
            case 38:
            case 39:
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
            case 54:
            case 57:
            case 58:
            case 59:
            case 60:
            case 61:
            case 67:
            case 68:
            case 69:
            case 70:
            case 77:
            case 78:
            case 79:
            case 84:
            case 85:
            case 88:
            case 89:
            case 94:
            case 95:
            case 98:
            case 99:
            case 108:
            case 109:
            case 118:
            case 119:
            case 128:
            case 129:
            case 138:
            case 139:
            case 148:
            case 149:
                arrayRects[i].w = 100;
                break;

            default:
                arrayRects[i].w = 0;
                break;
        }
        
        //h
        switch (i) {
            case 56:
            case 66:
            case 76:
            case 116:
            case 126:
            case 156:
            case 166:
                arrayRects[i].h = 25;
                break;
            case 104:
            case 114:
            case 124:
            case 134:
            case 144:
            case 154:
            case 164:
            case 174:
            case 184:
            case 194:
            case 204:
            case 214:
            case 224:
            case 234:
                arrayRects[i].h = 31;
                break;
            case 24:
            case 86:
            case 96:
            case 106:
            case 136:
            case 146:
            case 176:
            case 186:
            case 5:
            case 15:
            case 25:
            case 35:
            case 45:
            case 55:
            case 65:
            case 87:
            case 97:
            case 107:
            case 117:
            case 127:
            case 137:
                arrayRects[i].h = 50;
                break;
            case 102:
            case 112:
            case 122:
            case 132:
            case 142:
            case 152:
            case 162:
            case 172:
            case 182:
            case 192:
            case 202:
            case 212:
            case 222:
            case 232:
                arrayRects[i].h = 56;
                break;
            case 147:
                arrayRects[i].h = 62;
                break;
            case 105:
            case 115:
            case 125:
            case 135:
            case 145:
            case 155:
            case 165:
            case 175:
            case 185:
            case 195:
            case 205:
            case 215:
            case 225:
            case 235:
                arrayRects[i].h = 68;
                    break;

            default:
                arrayRects[i].h = 100;
                break;
        }
    }
}

PLAYER InitializePlayer(PLAYER player) {
    player.x = 3 * SCALE;
    player.y = 3 * SCALE;
    player.h = 1 * SCALE;
    player.w = 1 * SCALE;
    player.x_dir = 0;
    player.y_dir = 0;
    player.speed = 5;
    return player;
}

MAP initialize_Map1(MAP map) {
    map.mapSize = 10;
    //assign values to the floor pieces of the floor pieces
    for (int i = 0; i < map.mapSize; i++) {
        for (int j = 0; j < map.mapSize; j++) {
            switch (i) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    map.floor[i][j] = LIGHT;
                    break;
                default:
                    map.floor[i][j] = EMPTY;
                    break;
            }
        }
    }
    
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
                            map.walls[i][j] = EMPTY;
                            break;
                        case 9:
                            map.walls[i][j] = 71;
                            break;
                        default:
                            map.walls[i][j] = (j % 2) ? 17 : 54;
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
    //map.walls[4][4] = 69;
    return map;
}

//Game functions
//----------------------------------------------------

void drawMap(MAP map, SDL_Rect images[], SDL_Renderer * rend, SDL_Texture * tex, SDL_Rect destination){
    
    //draw floor of map 1
    for (int j=0; j<map.mapSize; j++) {
        for (int k = 0; k<map.mapSize; k++) {
            destination.x = k*SCALE;
            destination.y = j*SCALE;
            destination.w = images[map.floor[j][k]].w*SCALE/16;
            destination.h = images[map.floor[j][k]].h*SCALE/16;
            SDL_RenderCopy(rend, tex, &images[map.floor[j][k]], &destination);
        }
    }
    
    //draw whatever is not a floor of map 1
    for (int j=0; j<map.mapSize; j++) {
        for (int k = 0; k<map.mapSize; k++) {
            destination.x = k*SCALE;
            destination.y = j*SCALE;
            //if you are going to use the height and width of the image as a reference...
            //  it is necesary to divide it by 16 (which is the number of pixels of every unit in the image
            destination.w = images[map.walls[j][k]].w*SCALE/16;
            destination.h = images[map.walls[j][k]].h*SCALE/16;
            SDL_RenderCopy(rend, tex, &images[map.walls[j][k]], &destination);
        }
    }
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

char isPointInsideRect(int x, int y, SDL_Rect rect){
    return (rect.x <= x && x <= (rect.x + rect.w) && rect.y <= y && y <= (rect.y + rect.h));
}

int isLineInsideRect(int y, int x1, int x2, SDL_Rect rect){
    char heightOfLineIsInRect = (rect.y <= y && y <= rect.y + rect.h);
    char lineIsCrossingLeftSide = (x1 <= rect.x && rect.x <= x2);
    char lineIsCrossingRightSide = (x1 <= rect.x + rect.w && rect.x + rect.w <= x2);
    return (heightOfLineIsInRect && (lineIsCrossingLeftSide || lineIsCrossingRightSide));
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
    
//    SDL_SetRenderDrawColor(rend, 255, 0, 0, 255);
//    SDL_RenderDrawRects(rend, rect, 10);
//    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    
    //change the position of the player based on direction.
    switch (user.x_dir){
        case 1:
            //check if by moving right it is now inside a place it shouldn't be
            //If it is, place it where it can go.
            if (!isPointInsideRect(x3 + user.speed, y2, rect[4]) &&
                !isPointInsideRect(x3 + user.speed, y2, rect[5]) &&
                !isPointInsideRect(x3 + user.speed, y2, rect[8]) &&
                !isPointInsideRect(x3 + user.speed, y2, rect[9])){
                user.x += user.speed;
            }
            break;
        case -1:
            //check if by moving right it is now inside a place it shouldn't be
            //If it is, place it where it can go.
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
            //check if by moving down it is now inside a place it shouldn't be
            //If it is, place it where it can go.
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
            //check if by moving up it is now inside a place it shouldn't be
            //If it is, place it where it can go.
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
    
    if (user.y_dir || user.x_dir) {
//        printf("\n-------------------\
//               \nIzquierda: (%d, %d) \
//               \nDerecha: (%d, %d)", user.x, user.y+user.h, user.x+user.w, user.y+user.h  );
    }
    
    
    
    //detect if the position is outside the windows
    if (user.x <= 0)
        user.x = 0;
    else if (user.x + user.w >= WINDOW_WIDTH)
        user.x = WINDOW_WIDTH - user.w;
    if (user.y <= 0)
        user.y = 0;
    else if (user.y + user.h >= WINDOW_HEIGHT)
        user.y = WINDOW_HEIGHT - user.h;
    return user;
}





#endif /* game_functions_h */
