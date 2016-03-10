#include "barracks.h"
#include "champion.hpp"
#include "militia.hpp"
#include "orc_champion.hpp"
#include "orc_militia.hpp"


Barracks::Barracks(SDL_Setup* sdl_setup, SDL_Texture* passed_image, int x, int y, int size_x, int size_y, int passed_team, Environment* passed_environment) : Building(sdl_setup, passed_image, x, y, size_x, size_y, passed_team, passed_environment)
{
    health = 1;
    max_health = 750;

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

    if (health <= 0)
    {
        environment->barracksDestroyed();
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
        environment->changeImage(Structure, 2);
        if (team == 2)
        {
            environment->notBuildingBarracks(); //tell AI barracks construction complete
        }
    }
}
