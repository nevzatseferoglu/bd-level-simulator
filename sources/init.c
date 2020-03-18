#include "init.h"

SDL_bool initSDL(void)
{
    SDL_bool success = SDL_TRUE;

    Uint32 initFlags = SDL_INIT_EVERYTHING;
    Uint32 windowFlags = SDL_WINDOW_OPENGL;
    SDL_Point windowPos = {SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED};
    
    int rendererIndex = -1 ; /* the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags */
    SDL_RendererFlags rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    int imgFlags = IMG_INIT_PNG;

    if(SDL_Init(initFlags) < 0)
    {
        fprintf(stderr,"SDL Initialization Error! SDL_Eror %s",SDL_GetError());
        success = SDL_FALSE;
    }
    else
    {
        gameAssets.window = SDL_CreateWindow("Level Builder",
                    windowPos.x,
                    windowPos.y,
                    WINDOW_WIDTH,
                    WINDOW_HEIGHT,
                    windowFlags);
        
        if(gameAssets.window == NULL)
        {
            fprintf(stderr,"Window could not be initialized ! SDL_Error %s",SDL_GetError());
            success = SDL_FALSE;
        }
        else
        {
            gameAssets.renderer = SDL_CreateRenderer(gameAssets.window,
                        rendererIndex,
                        rendererFlags);
            
            if(gameAssets.renderer == NULL)
            {
                fprintf(stderr,"Renderer could not be initialized ! SDL_Error %s",SDL_GetError());
                success = SDL_FALSE;
            }
        }
    }
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        fprintf(stderr,"IMG_Init could not be initialized ! IMG Error : %s",SDL_GetError());
        success = SDL_FALSE;
    }
    return success;
}
void quitSDL(void)
{
    free(object);
    object = NULL;
    
    SDL_FreeCursor(mouse.newCursor);
    SDL_DestroyRenderer(gameAssets.renderer);
    SDL_DestroyWindow(gameAssets.window);
    SDL_Quit();
}
void setDefaultValue(void)
{
    memset(&gameAssets,0,sizeof(gameAssets));
    memset(&gameTexture,0,sizeof(gameTexture));
    memset(&mouse,0,sizeof(mouse));
    memset(&object,0,sizeof(object));
    
    mainTexture = NULL;
    minerTexture = NULL;
    clearBar = NULL;
    saveBar = NULL;
    
    current_level_id = 0;
    dynamicCounter = 0;
    currentTexture = -1;
    allocateFlag = 0;

    mainQuit = SDL_TRUE;

    cameraMoveHorizonal = 0;
    cameraMoveVertical = 0;
}