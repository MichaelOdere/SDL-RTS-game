#include "TownCenter.h"
#include "villager.hpp"
#include "orc_villager.hpp"


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

    if (timecheck + 10000 < SDL_GetTicks() && creating)
    {
        environment->createVillager(this, unit); //unit designates human or orc villager
        creating = false;
    }
}

void TownCenter::startCreating(Environment* passed_environment, int unit_to_create)
{
    environment = passed_environment;
    creating = true;
    unit = unit_to_create;
    timecheck = SDL_GetTicks();
}
