#include "villager.hpp"

Villager::Villager(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment) :
    Character( passed_SDL_Setup, passed_image, starting_x, starting_y, passed_MouseX, passed_MouseY, passed_environment)
{
    team = 1;
    health = 50;
    max_health = 50;
    attack = 0.005;
    defense = 0;

    menuType = 3;

}

Villager::~Villager()
{
}

void Villager::Update()
{
    Character::Update();

    //MINING
    for (int i = 0; i < environment->getGoldMines().size(); i++) //check for collision with gold mines (mining)
    {
        if (unit->isColliding(environment->getGoldMines()[i]->GetGold()->GetCollisionRect()))
        {
            if (environment->getGoldMines()[i]->Mining()) //if resources successfully mined (ie gold mine isn't empty)
            {
                environment->AddResources(1);
            }
            break; //prevents villager from mining more than one gold mine
        }
    }

    //CONSTRUCTING
    for (int i = 0; i < environment->getBuildings().size(); i++)
    {
        if (unit->isColliding(environment->getBuildings()[i]->GetBuilding()->GetCollisionRect()) &&
            environment->getBuildings()[i]->getTeam() == team &&
            environment->getBuildings()[i]->isAlive() &&
            !environment->getBuildings()[i]->isConstructed()) //not constructed
        {
            environment->getBuildings()[i]->constructing();
        }
    }
}
