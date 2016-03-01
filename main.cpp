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
    ai = new AI();
    gameMap = new Environment(sdl_setup, &MouseX, &MouseY, optionsMenu, ai);

    grass = new Sprite(sdl_setup->GetRenderer(), "images/grass.png", 0, 0, 1024, 1024, CollisionRectangle(0,0,0,0)); //map, one big grass tile


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
        grass->Draw();

        gameMap->DrawBack();

        gameMap->Update();

        sdl_setup->End();
    }
}
