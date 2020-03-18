#include "common.h"
#include "init.h"
#include "input.h"
#include "draw.h"
#include "loadMedia.h"

void calculateBarProperty(void);
void frameIncrament(void);
void textureBar(void);
void fillObjectProperty(void);
void  setCamera( int* );

int cameraFlag = 0;

int main(void)
{
    setDefaultValue();

    if(!initSDL())
    {
        fprintf(stderr,"Initialization Error ! SDL_Error %s",SDL_GetError());
        exit(-1);
    }
    if(!loadAllMedia())
    {
        fprintf(stderr,"Loading Media Error ! SDL_Error %s",SDL_GetError());
        exit(-1);
    }

    mouse.newCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    SDL_SetCursor(mouse.newCursor);
    
    calculateBarProperty();
    SDL_SetRenderDrawColor(gameAssets.renderer, 0, 0, 0, 255);

    while (mainQuit)
    {
        frameIncrament();
        doInput();

        if( allocateFlag == 1)
            for(int i=0;i<dynamicCounter ;++i)
                blit(current_level_id,object[i].type,object[i].x + cameraMoveHorizonal ,object[i].y + cameraMoveVertical ,TILE_SIZE,TILE_SIZE);

        
        if( allocateFlag == 3)
            SDL_RenderClear(gameAssets.renderer);
        
        textureBar();
        SDL_RenderPresent(gameAssets.renderer);
    }
    
    quitSDL();
    return 0;
}
void frameIncrament(void)
{
    int i = 0 , j = 0;

    for(j = 0 ; j < TILE_LEVEL_TYPE_NUMBER ; ++j)
    {
        for(i = 0 ; i < TILE_TYPE_NUMBER - 2   ; ++i)
            ++gameTexture[j][i].animationTime;
        
        for(i = 0 ; i < TILE_TYPE_NUMBER - 2  ; ++i)
        {
            switch(gameTexture[j][i].animationIter)
            {
                case 1:
                if(FPS/gameTexture[j][i].animationTime == 4)
                {
                    gameTexture[j][i].animationTime = 0;
                }
                    break;
                case 4:
                if(FPS/gameTexture[j][i].animationTime == 4)
                {
                    gameTexture[j][i].src.y += gameAssets.frameHeight;

                    if(gameTexture[j][i].src.y >= (j+1)*SPRITE_NUMBER*gameAssets.frameHeight)
                        gameTexture[j][i].src.y = j*SPRITE_NUMBER*gameAssets.frameHeight;
                    
                    gameTexture[j][i].animationTime = 0;
                }
                    break;
            }
        }
    }
}
void calculateBarProperty(void)
{
    int tempBarX;

    int textureScreenWidth =  WINDOW_WIDTH/(TILE_TYPE_NUMBER-3);
    int textureScreenHeight =  WINDOW_HEIGHT/(TILE_TYPE_NUMBER-3);

    gameAssets.xBar = 0;
    gameAssets.yBar = WINDOW_HEIGHT - textureScreenHeight;
    gameAssets.wBar = textureScreenWidth;
    gameAssets.hBar = textureScreenHeight;


    tempBarX = gameAssets.xBar;
    for(int i=0 ; i<TILE_TYPE_NUMBER ; ++i)
    {
        if( (i!=diamondInc) && (i!=thing) && (i!=star) )
        {
            gameAssets.barTexture[i].x = tempBarX;
            gameAssets.barTexture[i].y = gameAssets.yBar;

            tempBarX+=textureScreenWidth;
        }
    }
}
void textureBar(void)
{
    int i = 0,counter = 0;
    for(i=0 ; i < TILE_TYPE_NUMBER  ;++i)
    {
        if((i!=diamondInc)&&(i!=thing)&&(i!=star))
        {
            blit(current_level_id,i,counter*gameAssets.wBar,gameAssets.yBar,gameAssets.wBar,gameAssets.hBar);
            counter += 1;
        }
    }
}