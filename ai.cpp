#include "ai.hpp"
#include "house.hpp"

AI::AI()
{
    team = 2;
    villagerPop = 2;
    militiaPop = 2;
    championPop = 1;
    buildX = 700;
    buildY = 350;
    buildingHouse = false;
    buildingBarracks = false;
    houses = 0;
    barracks = 0;

}

AI::~AI()
{

}

void AI::updateCharacter(Character* character)
{
//to be implemented, will give orders to characters based on current game situation
    if (character->getType() == 1) //check if orc a villager
    {
        if (!character->isBuilding() && !character->isMining() && !character->isFollowing()) //IDLE VILLAGER
        {
            character->setFollowPoint(50,50);
        }

        if (environment->getOrcResources() >= 150 && environment->getOrcPop() + 5 >= environment->getOrcMaxPop())
        {
            environment->createHouse(buildX, buildY);
            environment->setOrcResources(environment->getOrcResources() - 150);
            character->setFollowPoint(buildX, buildY); //move character to construction zone
            setBuildArea();
        }

    }
}

void AI::updateBuilding(Building* building)
{
//to be implemented, will give orders to buildings based on current game situation
    if (building->getType() == 1 && !building->Creating()) //if building is a town center
    {
        if(environment->getOrcResources() >= 50 && environment->getOrcPop() < environment->getOrcMaxPop())
        {
            environment->setOrcResources(environment->getOrcResources() - 50);
            building->startCreating(2);
        }
    }
}

void AI::setEnvironment(Environment* passed_environment)
{
    environment = passed_environment;
}

void AI::setBuildArea()
{
    buildX += 100;
    if (buildX >= 1000)
    {
        buildX = 700;
        buildY += 100;
    }
}
