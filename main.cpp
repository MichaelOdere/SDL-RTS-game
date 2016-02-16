#include "main.hpp"
#include <math.h>

Main::Main() //Constructor
{

    quit = false; //boolean for game loop
    sdl_setup = new SDL_Setup(&quit);

    MouseX = 0;
    MouseY = 0;

    gameMap = new Environment(sdl_setup, &MouseX, &MouseY);

    unit = new Character(sdl_setup, &MouseX, &MouseY);

}
Main::~Main() //Destructor
{
    delete sdl_setup;

    delete unit;

    delete gameMap;
}


void Main::GameLoop()
{
    while (!quit && (sdl_setup->GetEv()->type != SDL_QUIT)) //the game loop
    {
        sdl_setup->Begin();
        SDL_GetMouseState(&MouseX, &MouseY);

        gameMap->DrawBack();
        unit->Draw();

        unit->Update();
        gameMap->Update();

        sdl_setup->End();
    }
}
