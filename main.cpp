#include "main.hpp"
#include <math.h>

Main::Main() //Constructor
{

    quit = false; //boolean for game loop
    sdl_setup = new SDL_Setup(&quit);

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            grass[i][j] = new Sprite(sdl_setup->GetRenderer(), "images/grass.bmp", i*50, j*50, 50, 50); //map
        }
    }

    MouseX = 0;
    MouseY = 0;

    unit = new Character(sdl_setup, &MouseX, &MouseY);

}
Main::~Main() //Destructor
{
    delete sdl_setup;
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            delete grass[i][j];
        }
    }
    delete unit;
}


void Main::GameLoop()
{
    while (!quit && (sdl_setup->GetEv()->type != SDL_QUIT)) //the game loop
    {
        sdl_setup->Begin();
        SDL_GetMouseState(&MouseX, &MouseY);

        for (int i = 0; i < 21; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                grass[i][j]->Draw();
            }
        }


        unit->Draw();

        unit->Update();

        sdl_setup->End();

    }
}
