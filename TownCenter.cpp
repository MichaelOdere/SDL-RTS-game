#include "TownCenter.h"


TownCenter::TownCenter(SDL_Setup* sdl_setup, std::string FilePath, int x, int y, int size_x, int size_y, int passed_team) : Building(sdl_setup, FilePath, x, y, size_x, size_y, passed_team)
{
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
