#include "house.hpp"

House::House(SDL_Setup* sdl_setup, SDL_Texture* passed_image, int x, int y, int size_x, int size_y, int passed_team, Environment* passed_environment) : Building(sdl_setup, passed_image, x, y, size_x, size_y, passed_team, passed_environment)
{
    health = 1;
    max_health = 200;

    menuType = 2;

    constructed = false;
}

House::~House()
{
}

void House::Update()
{
    Building::Update();

    if (health <= 0)
    {
        environment->decreasePop(team); //house destroyed, decrease max pop
    }
    if (health <= 0 && !constructed)
    {
        environment->notBuildingHouse(); //tell AI house construction halted
    }
}

void House::constructing()
{
    Building::constructing();

    if (health >= max_health)
    {
        environment->changeImage(Structure, 1); //change image to constructed state
        environment->increasePop(team); //house created, increase max pop
        if (team == 2)
        {
            environment->notBuildingHouse(); //tell AI house construction completed
        }
    }
}
