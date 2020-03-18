#include "draw.h"
void blit(int levelId,int textureId,int x , int y, int w ,int h)
{
    gameTexture[levelId][textureId].dest.x = x;
    gameTexture[levelId][textureId].dest.y = y;
    gameTexture[levelId][textureId].dest.w = w;
    gameTexture[levelId][textureId].dest.h = h;
    

    if(textureId == miner)            SDL_RenderCopy(gameAssets.renderer,minerTexture,&(gameTexture[levelId][textureId].src),&(gameTexture[levelId][textureId].dest));
    else if(textureId == clearButton) SDL_RenderCopy(gameAssets.renderer,clearBar,&(gameTexture[levelId][textureId].src),&(gameTexture[levelId][textureId].dest));
    else                              SDL_RenderCopy(gameAssets.renderer,mainTexture,&(gameTexture[levelId][textureId].src),&(gameTexture[levelId][textureId].dest));

}