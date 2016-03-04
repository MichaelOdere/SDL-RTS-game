#include "orc_champion.hpp"

OrcChampion::OrcChampion(SDL_Setup* passed_SDL_Setup, std::string FilePath, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment) :
Character( passed_SDL_Setup, FilePath, starting_x, starting_y, passed_MouseX, passed_MouseY, passed_environment)
{
    team = 2;
    health = 100;
    max_health = 100;
    attack = 0.02;
    defense = 0.005;
    environment->addChampion();

    type = 3;
}

OrcChampion::~OrcChampion()
{
}

void OrcChampion::Update(){

    Character::Update();

    if (health <= 0)
    {
        environment->removeChampion();
    }

}
