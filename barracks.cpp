#include "barracks.h"


Barracks::Barracks(SDL_Setup* sdl_setup, std::string FilePath, int x, int y) : Building(sdl_setup, FilePath, x, y)
{
    team = 1;
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


