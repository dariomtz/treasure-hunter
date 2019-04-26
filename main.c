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

void initializeImageRect(struct SDL_Rect arrayRects[]){
    unsigned char xpos[118] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 16, 18, 20, 22, 0, 1, 2, 3, 4, 6, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 10, 12, 14, 16, 18, 20, 22, 0, 1, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0, 3, 6, 9, 12, 15, 17};
    unsigned char ypos[118] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8};
    unsigned char height[118] = {1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2};
    unsigned char width[177] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 3, 3, 2, 2};
    
    //fill all
    for (int i = 0; i < 118; i++) {
        arrayRects[i].x = xpos[i]*16;
        arrayRects[i].y = ypos[i]*16;
        arrayRects[i].h = height[i]*16;
        arrayRects[i].w = width[i]*16;
    }
    
}

int main(int argc, char* argv[]) {
    
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
    
    struct SDL_Rect images[118];
    initializeImageRect(images);
    
    char doors[] = {91, 92, 93, 94, 93, 92};
    
    struct SDL_Rect destination;

    for (int i = 0; i < 50; i++) {
        //clear the window
        SDL_RenderClear(rend);
        
        //draw top
        for (int j = 0; j<11; j++) {
            destination.x = j*100;
            destination.y = 0;
            destination.w = 100;
            destination.h = 100;
            SDL_RenderCopy(rend, tex, &images[6], &destination);
        }
        
        //draw floor
        for (int k=1; k<=3; k++) {
            for (int j = 0; j<11; j++) {
                destination.x = j*100;
                destination.y = 100*k;
                destination.w = 100;
                destination.h = 100;
                SDL_RenderCopy(rend, tex, &images[29], &destination);
            }
        }
        
        //draw walls
        for (int j = 0; j<4; j++) {
            destination.x = j*100;
            destination.y = 100;
            destination.w = 100;
            destination.h = 100;
            SDL_RenderCopy(rend, tex, &images[(j%2) ? 88 : 50], &destination);
        }
        
        //draw door
        destination.x = 4*100;
        destination.y = 100;
        destination.w = 100;
        destination.h = 100;
        SDL_RenderCopy(rend, tex, &images[doors[i%6]], &destination);
        
        //draw more walls
        for (int j = 5; j<10; j++) {
            destination.x = j*100;
            destination.y = 100;
            destination.w = 100;
            destination.h = 100;
            SDL_RenderCopy(rend, tex, &images[(j%2) ? 89 : 50], &destination);
        }
        
        //draw lower border
        for (int j = 0; j<11; j++) {
            destination.x = j*100;
            destination.y = 300;
            destination.w = 100;
            destination.h = 100;
            SDL_RenderCopy(rend, tex, &images[39], &destination);
        }
        
        //refill
        for (int k = 4; k<9; k++) {
            for (int j = 0; j<11; j++) {
                destination.x = j*100;
                destination.y = k*100;
                destination.w = 100;
                destination.h = 100;
                SDL_RenderCopy(rend, tex, &images[18], &destination);
            }
        }
        
        
        
        //Send the image drawn to the screen
        SDL_RenderPresent(rend);
        
        //wait
        SDL_Delay(500);
    }
    
    SDL_DestroyTexture(tex);
    
    SDL_DestroyRenderer(rend);
    
    SDL_DestroyWindow(win);
    
    SDL_Quit();
    return 0;
}
