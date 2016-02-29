#include "barracks.h"


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
}


