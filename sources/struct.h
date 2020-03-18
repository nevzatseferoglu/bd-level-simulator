#ifndef STRUCT_H
#define STRUCT_H
#include "SDL2/SDL.h"

typedef enum {border , earth , empty , rock , diamond ,diamondInc, levelUp , water , thing , spider , monster , star , miner ,clearButton , none }textureType;
typedef enum {noClick , left , middle , right }mouseClickType;


struct Object{
    
    int x,y;
    int type;

};

struct mouseProperty{
    
    int x,y;
    SDL_Cursor* newCursor;

};

struct mainAssets{

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_bool key[MAX_KEYBOARD_KEY_NUMBER];
    int print;

    int xBar,yBar,wBar,hBar; /* Bar coordinates and width , height */
    SDL_Point barTexture[TILE_TYPE_NUMBER];
    int frameWidth;
    int frameHeight;

};

struct texturePropery{

    int id;
    int animationIter;
    int animationTime;
    SDL_Rect src;
    SDL_Rect dest;

};


#endif