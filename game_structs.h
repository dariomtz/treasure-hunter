//
//  main.c
//  Hide and Sick
//
//  Created by DarÃ­o MartÃ­nez and Miguel GonzÃ¡lez on 4/2/19.
//

#ifndef game_structs_h
#define game_structs_h

#define SCALE 100
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

#define LIGHT 62
#define DARK 11
#define EMPTY 219

//player
typedef struct{
    int x;
    int y;
    unsigned char w;
    unsigned char h;
    unsigned char speed;
    char x_dir;
    char y_dir;
}PLAYER;

//maps
typedef struct{
    unsigned char floor[50][50];
    unsigned char walls[50][50];
    int mapSize;
} MAP;

//box
typedef struct{
	unsigned char movable: 1;
	int x;
	int y;
	unsigned char w;
	unsigned char h;
	unsigned char image;

}BOX;

typedef struct{
	BOX box;
	PLAYER user;
}BOX_PLAYER;

//All the levels
//menu

#endif /* game_structs_h */
