#include "main.hpp"
#include <math.h>

Main::Main() //Constructor
{

    quit = false; //boolean for game loop
    sdl_setup = new SDL_Setup(&quit);

    MouseX = 0;
    MouseY = 0;

    gameMap = new Environment(sdl_setup, &MouseX, &MouseY);

    unit = new Character(sdl_setup, "images/villager.png", &MouseX, &MouseY, gameMap);

}
Main::~Main() //Destructor
{
    //avoids memory leaks
    delete sdl_setup;
    delete unit;
    delete gameMap;
}


void Main::GameLoop()
{
    while (!quit && (sdl_setup->GetEv()->type != SDL_QUIT)) //the game loop
    {
        sdl_setup->Begin();
        SDL_GetMouseState(&MouseX, &MouseY); //sets x and y of mouse location for each loop

        gameMap->DrawBack();
        unit->Draw(); //unit drawn after map so that unit is not behind map
        //in future, only map will be drawn and updated, with unit drawn in environment class
        unit->Update();
        gameMap->Update();

        sdl_setup->End();
    }
}
