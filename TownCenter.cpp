#include "TownCenter.h"
#include "villager.hpp"
#include "orc_villager.hpp"


TownCenter::TownCenter(SDL_Setup* sdl_setup, SDL_Texture* passed_image, int x, int y, int size_x, int size_y, int passed_team, Environment* passed_environment) : Building(sdl_setup, passed_image, x, y, size_x, size_y, passed_team, passed_environment)
{
    health = 2000;
    max_health = 2000;

    menuType = 4;

    type = 1;

    constructed = true;
}
TownCenter::~TownCenter()
{
}

void TownCenter::Update()
{
    Building::Update();

    if (timecheck + 10000 < SDL_GetTicks() && creating) //if creating unit and been 10sec
    {
        environment->createVillager(this, unit); //unit designates human or orc villager
        creating = false;
    }

    if (health <= 0)
    {
        environment->endGame(team);
    }
}

void TownCenter::startCreating(int unit_to_create)
{
    creating = true;
    unit = unit_to_create;
    timecheck = SDL_GetTicks(); //get time at call to create
}
