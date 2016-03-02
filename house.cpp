#include "house.hpp"

House::House(SDL_Setup* sdl_setup, std::string FilePath, int x, int y, int size_x, int size_y, int passed_team) : Building(sdl_setup, FilePath, x, y, size_x, size_y, passed_team)
{
    health = 1;
    max_health = 200;
    attack = 0.00;

    menuType = 2;

    constructed = false;
}

House::~House()
{
}

void House::Update()
{
    Building::Update();
}

void House::constructing()
{
    Building::constructing();

    if (health >= max_health)
    {
        Structure->changeImage("images/house.png");
    }
}
