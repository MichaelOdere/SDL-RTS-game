#include "house.hpp"

House::House(SDL_Setup* sdl_setup, std::string FilePath, int x, int y, int size_x, int size_y, int passed_team) : Building(sdl_setup, FilePath, x, y, size_x, size_y, passed_team)
{
    health = 200;
    max_health = 200;
    attack = 0.00;

    menuType = 2;
    /*
    if (team == 1) {
        humanMaxPop += 5;
    } else {
        orcMaxPop += 5;
    }
    */
}

House::~House()
{
}

void House::Update()
{
    Building::Update();
    /*
    if (health <= 0) {
        if (team == 1) {
            humanMaxPop -= 5;
        } else {
            orcMaxPop -= 5;
        }
    }
    */
}
