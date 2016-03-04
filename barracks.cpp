#include "barracks.h"
#include "champion.hpp"
#include "militia.hpp"
#include "orc_champion.hpp"
#include "orc_militia.hpp"


Barracks::Barracks(SDL_Setup* sdl_setup, std::string FilePath, int x, int y, int size_x, int size_y, int passed_team, Environment* passed_environment) : Building(sdl_setup, FilePath, x, y, size_x, size_y, passed_team, passed_environment)
{
    health = 1;
    max_health = 10;
    attack = 0.00;

    menuType = 5;

    type = 2;

    constructed = false;
}

Barracks::~Barracks()
{
}

void Barracks::Update()
{
    Building::Update();

    if (timecheck + 15000 < SDL_GetTicks() && creating && (unit == 1 || unit == 2)) //if creating militia and been 15sec
    {
        environment->createMilitia(this, unit); //unit designates human or orc militia
        creating = false;
    }
    if (timecheck + 20000 < SDL_GetTicks() && creating && (unit == 3 || unit == 4)) //if creating champion and been 20sec
    {
        environment->createChampion(this, unit); //unit designates human or orc champion
        creating = false;
    }
}

void Barracks::startCreating(int unit_to_create)
{
    creating = true;
    unit = unit_to_create;
    timecheck = SDL_GetTicks(); //get time at call to create
}

void Barracks::constructing()
{
    Building::constructing();

    if (health >= max_health)
    {
        Structure->changeBarracksImage(); //reset image to created state, for some reason barracks.png doesn't work and is cropped weird
    }
}
