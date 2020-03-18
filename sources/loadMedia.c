#include "loadMedia.h"

SDL_Texture* loadTexture(char* filename)
{
    SDL_Texture* realTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(filename);

    if(!loadedSurface)
    {
        fprintf(stderr,"Surface IMG could not be loaded ! IMG Error %s ",SDL_GetError());
        exit(-1);
    }
    realTexture = SDL_CreateTextureFromSurface(gameAssets.renderer , loadedSurface);

    if(!realTexture)
    {
        fprintf(stderr,"Texture IMG could not be loaded ! SDL Error %s ",SDL_GetError());
        exit(-1);
    }

    SDL_FreeSurface(loadedSurface);
    return realTexture ;
}
SDL_bool loadAllMedia(void)
{
    int i = 0 , j = 0;

    SDL_bool success = SDL_TRUE;

    int wTexture, hTexture, minerWidthTexture , minerHeightTexture , clearBarW , clearBarH;

    mainTexture = loadTexture("./Images/texture.png");
    if(!mainTexture)
    {
        fprintf(stderr,"Image loading error ! SDL Error %s ",SDL_GetError());
        success = SDL_FALSE;
    }
    SDL_QueryTexture(mainTexture, NULL, NULL, &wTexture, &hTexture);

    minerTexture = loadTexture("./Images/miner.png");
    if(!minerTexture)
    {
        fprintf(stderr,"Image loading error ! SDL Error %s ",SDL_GetError());
        success = SDL_FALSE;
    }
    SDL_QueryTexture(minerTexture, NULL, NULL, &minerWidthTexture,&minerHeightTexture);

    clearBar = loadTexture("./Images/clear.png");
    if(!clearBar)
    {
        fprintf(stderr,"Image loading error ! SDL Error %s ",SDL_GetError());
        success = SDL_FALSE;
    }
    SDL_QueryTexture(clearBar, NULL, NULL, &clearBarW,&clearBarH);
    
    gameAssets.frameWidth = wTexture/TILE_TYPE_WIDTH_NUMBER;
    gameAssets.frameHeight = hTexture/TILE_TYPE_HEIGHT_NUMBER;


    for(i = 0 ; i < TILE_LEVEL_TYPE_NUMBER ; ++i)
    {
        for(j = 0 ; j < TILE_TYPE_NUMBER ; ++j)
        {
            if (j == TILE_TYPE_NUMBER - 1)
            {
                gameTexture[i][j].src.x = 0*gameAssets.frameWidth;
                gameTexture[i][j].src.y = 0*gameAssets.frameHeight;

                gameTexture[i][j].src.w = clearBarW;
                gameTexture[i][j].src.h = clearBarH;
            }
            else if(j == TILE_TYPE_NUMBER - 2)
            {
                gameAssets.frameWidth = minerWidthTexture/TILE_MINER_WIDTH_NUMBER;
                gameAssets.frameHeight = minerHeightTexture/TILE_MINER_HEIGHT_NUMBER;

                gameTexture[i][j].src.x = 0*gameAssets.frameWidth;
                gameTexture[i][j].src.y = 0*gameAssets.frameHeight;

                gameTexture[i][j].src.w = gameAssets.frameWidth;
                gameTexture[i][j].src.h = gameAssets.frameHeight;
            }
            else
            {    
                gameTexture[i][j].src.x = j*gameAssets.frameWidth;
                gameTexture[i][j].src.y = i*SPRITE_NUMBER*gameAssets.frameHeight;
            
                gameTexture[i][j].src.w = gameAssets.frameWidth;
                gameTexture[i][j].src.h = gameAssets.frameHeight;
                
                if(     (i == 0 ||   i ==   1) && j < 3)    gameTexture[i][j].animationIter = 1;
                else if((i == 0 ||   i ==   1) && j >= 3)   gameTexture[i][j].animationIter = 4;
                else if( i == 2 &&   j <    1)              gameTexture[i][j].animationIter = 1;
                else if( i == 2 &&   j >=   1)              gameTexture[i][j].animationIter = 4;
                else if( i == 3 &&   j <    2)              gameTexture[i][j].animationIter = 1;
                else if( i == 3 &&   j >=   2)              gameTexture[i][j].animationIter = 4;
                else if( i == 4 &&  (j ==   0 || j == 3))   gameTexture[i][j].animationIter = 1;
                else if( i == 4 && !(j ==   0 || j == 3))   gameTexture[i][j].animationIter = 4;
                else if( i == 5 &&  (j ==   0))             gameTexture[i][j].animationIter = 1;
                else if( i == 5 && !(j ==   0))             gameTexture[i][j].animationIter = 4;
            }
        }
    }

    return success;
}