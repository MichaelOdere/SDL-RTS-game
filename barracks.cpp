#include "barracks.h"
#include "champion.hpp"
#include "militia.hpp"
#include "orc_champion.hpp"
#include "orc_militia.hpp"


Barracks::Barracks(SDL_Setup* sdl_setup, std::string FilePath, int x, int y, int size_x, int size_y, int passed_team) : Building(sdl_setup, FilePath, x, y, size_x, size_y, passed_team)
{
    health = 500;
    max_health = 500;
    attack = 0.00;

    menuType = 5;
}

Barracks::~Barracks()
{
}

void Barracks::Update()
{
    Building::Update();

    if (timecheck + 15000 < SDL_GetTicks() && creating && (unit == 1 || unit == 2)) //if creating militia
    {
        environment->createMilitia(this, unit); //unit designates human or orc militia
        creating = false;
    }
    if (timecheck + 20000 < SDL_GetTicks() && creating && (unit == 3 || unit == 4)) //if creating champion
    {
        environment->createChampion(this, unit); //unit designates human or orc champion
        creating = false;
    }
}

void Barracks::startCreating(Environment* passed_environment, int unit_to_create)
{
    environment = passed_environment;
    creating = true;
    unit = unit_to_create;
    timecheck = SDL_GetTicks();
}
