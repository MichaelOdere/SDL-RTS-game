#include "main.hpp"
#include <math.h>

Main::Main() //Constructor
{
    SDL_Init(SDL_INIT_EVERYTHING); //Initialize everything in SDL
    quit = false; //boolean for game loop
    sdl_setup = new SDL_Setup(&quit);

    MouseX = 0;
    MouseY = 0;

    optionsMenu = new SubMenu(sdl_setup, &MouseX, &MouseY,0);
    gameMap = new Environment(sdl_setup, &MouseX, &MouseY, optionsMenu);
}

Main::~Main() //Destructor
{
    //avoids memory leaks
    delete sdl_setup;
    delete gameMap;
    delete optionsMenu;

    SDL_Quit();
}

void Main::GameLoop()
{
    while (!quit && (sdl_setup->GetEv()->type != SDL_QUIT)) //the game loop
    {
        sdl_setup->Begin();
        SDL_GetMouseState(&MouseX, &MouseY); //sets x and y of mouse location for each loop

        gameMap->DrawBack();

        gameMap->Update();

        sdl_setup->End();
    }
}
