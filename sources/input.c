#include "input.h"
#include "draw.h"
SDL_bool levelChoose(void);
void fillObjectProperty(void);
void makeNone(void);

void doInput(void)
{
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mainQuit = SDL_FALSE;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_C:
                        if(levelChoose())
                            ++current_level_id;
                        else
                            current_level_id = 0;
                        break;

                    default:
                        break;
                }
        } 

        mouse.x = event.button.x;
        mouse.y = event.button.y;

        if( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1) )   fillObjectProperty();
        if( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3) )   makeNone();
    }
}
SDL_bool levelChoose(void)
{
    if(current_level_id == TILE_LEVEL_TYPE_NUMBER - 1)
        return SDL_FALSE;
    else
        return SDL_TRUE;
}
void fillObjectProperty()
{
    int i,j;

    if((mouse.x > gameAssets.xBar) && (mouse.y > gameAssets.yBar ) )
    {
        allocateFlag = 0;

        for(i=0;i<TILE_TYPE_NUMBER;++i)
        {
            if( (i!=diamondInc) && (i!=thing) && (i!=star) )
            {
                if( ( mouse.x >= gameAssets.barTexture[i].x  ) && (mouse.y >= gameAssets.barTexture[i].y) )
                    currentTexture = i;
            }
        }
        if( currentTexture == clearButton )
        {
            free( object );
            object = NULL;
            dynamicCounter = 0;
            allocateFlag = 3;
        }
    }
    else if( currentTexture != -1 && currentTexture != clearButton )
    {
        allocateFlag = 1;
        ++dynamicCounter;

        if( !object )
        {
            object = (struct Object*)malloc(sizeof(struct Object)*1);

            for(i=1;i<=WINDOW_WIDTH/TILE_SIZE;++i)
            {
                if(i*TILE_SIZE>mouse.x)
                {
                    break;
                }
            }
            for(j=1;j<=WINDOW_HEIGHT/TILE_SIZE;++j)
            {
                if(j*TILE_SIZE>mouse.y)
                    break;
            }

            object->x = (i-1)*TILE_SIZE;
            object->y = (j-1)*TILE_SIZE;
            object->type = currentTexture;
        }
        else
        {
            object = (struct Object*)realloc(object,sizeof(struct Object)*(dynamicCounter));
            for(i=1;i<=WINDOW_WIDTH/TILE_SIZE;++i)
            {
                if(i*TILE_SIZE>mouse.x)
                    break;
            }
            for(j=1;j<=WINDOW_HEIGHT/TILE_SIZE;++j)
            {
                if(j*TILE_SIZE>mouse.y)
                    break;
            }
            object[dynamicCounter-1].x = (i-1)*TILE_SIZE;
            object[dynamicCounter-1].y = (j-1)*TILE_SIZE;
            object[dynamicCounter-1].type = currentTexture;
        }
    }
}
void makeNone(void)
{
    int i,j,t , newDynamicCounter = 0;
    struct Object* newObject = NULL;
    

    for(t=1;t<=WINDOW_WIDTH/TILE_SIZE;++t)
    {
        if(t*TILE_SIZE>mouse.x)
            break;
    }

    for(j=1;j<=WINDOW_HEIGHT/TILE_SIZE;++j)
    {
        if(j*TILE_SIZE>mouse.y)
            break;
    }

    for(i=0;i<dynamicCounter && allocateFlag ;++i)
    {
        if(object[i].x == (t-1)*TILE_SIZE && object[i].y == (j-1)*TILE_SIZE)
        {
            object[i].type = none;
            ++newDynamicCounter;
        }
    }           

    /* Allocating new object , copying all the way to the end of the existent array */
    newObject = (struct Object*) malloc( sizeof(struct Object)* (dynamicCounter - newDynamicCounter) );
    newDynamicCounter = 0;

    for( i = 0 ; i < dynamicCounter ; ++i )
        if( object[i].type != none )
        {
            newObject[newDynamicCounter] = object[i];
            ++newDynamicCounter;
        }
    
    free(object);
    object = NULL;

    object = newObject;
    dynamicCounter = newDynamicCounter;
    SDL_RenderClear(gameAssets.renderer);
}