#include "environment.hpp"

Environment::Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY)
{
    sdl_setup = passed_sdl_setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            grass[i][j] = new Sprite(sdl_setup->GetRenderer(), "images/grass.bmp", i*50, j*50, 50, 50); //map
        }
    }

    houses.push_back(new Building(sdl_setup, 200, 200));
    goldMines.push_back(new Gold(sdl_setup, 50, 50));
    goldMines.push_back(new Gold(sdl_setup, 600, 200));
    goldMines.push_back(new Gold(sdl_setup, 550, 500));
    goldMines.push_back(new Gold(sdl_setup, 720, 100));
}

Environment::~Environment()
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            delete grass[i][j];
        }
    }
    for (std::vector<Gold*>::iterator i = goldMines.begin(); i != goldMines.end(); ++i)
    {
        delete (*i);
    }
    for (std::vector<Building*>::iterator i = houses.begin(); i != houses.end(); ++i)
    {
        delete (*i);
    }
    goldMines.clear();
    houses.clear();
}

void Environment::DrawBack()
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            grass[i][j]->Draw();
        }
    }

    for (std::vector<Gold*>::iterator i = goldMines.begin(); i != goldMines.end(); ++i)
    {
        (*i)->DrawGold();
    }

    for (std::vector<Building*>::iterator i = houses.begin(); i != houses.end(); ++i)
    {
        (*i)->DrawBuilding();
    }
}

void Environment::Update()
{
    if (sdl_setup->GetEv()->type == SDL_MOUSEBUTTONDOWN)
    {
        if (sdl_setup->GetEv()->button.button == SDL_BUTTON_LEFT)
        {
            houses.push_back(new Building(sdl_setup, *MouseX, *MouseY));
        }
    }
}
