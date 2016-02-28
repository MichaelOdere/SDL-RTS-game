#include "TownCenter.h"


TownCenter::TownCenter(SDL_Setup* sdl_setup, std::string FilePath, int x, int y) : Building(sdl_setup, FilePath, x, y)
{
    team = 1;
    health = 1000;
    max_health = 1000;
    attack = 0.00;
    
    menuType = 4;
}
TownCenter::~TownCenter()
{
}

void TownCenter::Update()
{
    Building::Update();
}
