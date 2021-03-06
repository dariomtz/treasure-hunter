//
//  main.c
//  Hide and Sick
//
//  Created by DarÃƒÂ­o MartÃƒÂ­nez and Miguel GonzÃƒÂ¡lez on 4/2/19.
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
    unsigned char image;
    unsigned char rocks[5];
}PLAYER;

//maps
typedef struct{
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

//animation
typedef struct{
    unsigned char current;
    unsigned char active;
    unsigned char length;
    char dir;
    unsigned char skip;
    unsigned char x;
    unsigned char y;
    unsigned char images[15];
} ANIMATION;

typedef struct{
	unsigned char x;
	unsigned char y;
	unsigned char x2;
	unsigned char y2;
	unsigned char x_module;
	unsigned char y_module;
}SCREEN;

//All the levels
//menu

#endif /* game_structs_h */
