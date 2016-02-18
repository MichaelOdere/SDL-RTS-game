#include "environment.hpp"

Environment::Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY)
{
    sdl_setup = passed_sdl_setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    
    showMenu = false;
    menuType = 1;

    resources = 100;

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            grass[i][j] = new Sprite(sdl_setup->GetRenderer(), "images/grass.bmp", i*50, j*50, 50, 50, CollisionRectangle(0,0,0,0)); //map
        }
    }

    buildings.push_back(new Building(sdl_setup, "images/house.png", 200, 200));
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
    for (std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
        delete (*i);
    }
    goldMines.clear();
    buildings.clear();
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

    for (std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
        (*i)->DrawBuilding();
    }
}

void Environment::AddResources()
{
    resources = resources + 0.005;
}

int Environment::getMenuType()
{
    return menuType;
}

bool Environment::shouldMenu()
{
    return showMenu;
}

void Environment::Update()
{
    if (sdl_setup->GetEv()->type == SDL_MOUSEBUTTONDOWN)
    {
        if (sdl_setup->GetEv()->button.button == SDL_BUTTON_LEFT)
        {
            for(int i = 0; i < buildings.size(); i++){
                if(*MouseX>buildings[i]->getStructureX() && *MouseX<(buildings[i]->getStructureX()+buildings[i]->getStructureW()) && *MouseY>buildings[i]->getStructureY() && *MouseY<(buildings[i]->getStructureY()+buildings[i]->getStructureH()))
                {
                    
                }
            }
            //buildings.push_back(new Building(sdl_setup, "images/house.png", *MouseX-50, *MouseY-50));
        }
    }
    
    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){
       // if(sdl_setup->GetEv()->button.button == SDLK_SPACE){
            if(showMenu){
                showMenu = false;
            }else{
                showMenu = true;
            }
        //}
    }
}
