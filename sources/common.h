#if !defined(COMMON_H)
#define COMMON_H

#include "stdio.h"
#include "stdlib.h"

/* Include SDL Library */

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "defs.h"
#include "struct.h"

SDL_Event event;

int dynamicCounter;
int currentTexture;
int allocateFlag;

struct Object* object;

textureType objectType;
mouseClickType click;

struct mouseProperty mouse;
struct mainAssets gameAssets;

SDL_Texture* mainTexture;
SDL_Texture* minerTexture;
SDL_Texture* clearBar;
SDL_Texture* saveBar;

struct texturePropery gameTexture[TILE_LEVEL_TYPE_NUMBER][TILE_TYPE_NUMBER];

SDL_bool mainQuit;

int current_level_id;

int cameraMoveHorizonal;
int cameraMoveVertical;

#endif