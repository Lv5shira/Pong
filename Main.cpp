//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "GameManager.h"

//Event handler
SDL_Event e;


int main(int argc, char* args[])
{
    GameManager* game = GameManager::Instance();
    if (!game->init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        while (!game->quit)
        {
            game->Render();
        }
    }
    game->close();
    return 0;
}