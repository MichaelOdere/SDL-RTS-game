#include "orc_villager.hpp"

OrcVillager::OrcVillager(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment) :
    Character( passed_SDL_Setup, passed_image, starting_x, starting_y, passed_MouseX, passed_MouseY, passed_environment)
{
    team = 2;
    health = 50;
    max_health = 50;
    attack = 0.005;
    defense = 0;

    menuType = 3;
    mining = false;
    building = false;
    hasTask = false;
    environment->addVillager();

    type = 1;

}

OrcVillager::~OrcVillager()
{
}

void OrcVillager::Update(){

    Character::Update();

    //MINING
    for (int i = 0; i < environment->getGoldMines().size(); i++) //check for collision with gold mines (mining)
    {
        if (unit->isColliding(environment->getGoldMines()[i]->GetGold()->GetCollisionRect()))
        {
            if (environment->getGoldMines()[i]->Mining()) //if resources successfully mined (ie gold mine isn't empty)
            {
                environment->AddResources(2); //add resources to orc stockpile (team 2)
                mining = true;
            } else {
                mining = false;
            }
            break;
        } else
        {
            mining = false;
        }
    }

    //CONSTRUCTING
    for (int i = 0; i < environment->getBuildings().size(); i++)
    {
        if (unit->isColliding(environment->getBuildings()[i]->GetBuilding()->GetCollisionRect()) && //if collides
            environment->getBuildings()[i]->getTeam() == team && //building on team
            environment->getBuildings()[i]->isAlive() && //building not destroyed
            !environment->getBuildings()[i]->isConstructed()) //not constructed
        {
            environment->getBuildings()[i]->constructing();
            building = true;
            distance = 0;   //stop unit when reached build site
            follow = false;
            follow_point_x = unit->GetX();
            follow_point_y = unit->GetY();
            break; //stop looking for other building to construct
        } else
        {
            building = false;
        }
    }

    if (health <= 0)
    {
        environment->removeVillager(); //tell AI villager killed
    }
}

void OrcVillager::setFollowPoint(int x, int y)
{
    Character::setFollowPoint(x, y);
    hasTask = true;
}
