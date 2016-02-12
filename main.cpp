#include "main.hpp"
#include <math.h>

Main::Main() //Constructor
{

    quit = false; //boolean for game loop
    sdl_setup = new SDL_Setup(&quit);


    grass = new Sprite(sdl_setup->GetRenderer(), "images/grass.bmp", 0, 0, 1024, 768); //map

    MouseX = 0;
    MouseY = 0;

    unit = new Character(sdl_setup, &MouseX, &MouseY);

}

Main::~Main() //Destructor
{
    delete sdl_setup;
    delete grass;
    delete unit;
}


void Main::GameLoop()
{

    while (!quit && (sdl_setup->GetEv()->type != SDL_QUIT)) //the game loop
    {
        sdl_setup->Begin();
        SDL_GetMouseState(&MouseX, &MouseY);

        grass->Draw();
        unit->Draw();

        unit->Update();

        sdl_setup->End();

    }
}
