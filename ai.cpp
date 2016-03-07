#include "ai.hpp"
#include "house.hpp"

AI::AI()
{
    team = 2;
    villagerPop = 0;
    militiaPop = 0;
    championPop = 0;
    buildX = 700;
    buildY = 250;
    buildingHouse = false;
    buildingBarracks = false;
    notConstructing = false;
    houses = 0;
    barracks = 0;
    idle_x = 575;
    idle_y = 525;
    struct_x = 0;
    struct_y = 0;
}

AI::~AI()
{

}

void AI::updateCharacter(Character* character)
{
//gives orders to characters based on current game situation
    if (character->getType() == 1) //check if orc a VILLAGER
    {
        if (!character->isBuilding() && !character->isMining() && !character->isFollowing()) //IDLE VILLAGER
        {

            character->setFollowPoint(idle_x, idle_y);
            character->setNoTask();
        }

        if (environment->getOrcResources() >= 100 && environment->getOrcPop() + 2 >= environment->getOrcMaxPop() && !buildingHouse)
        {
            environment->createHouse(buildX, buildY);
            environment->setOrcResources(environment->getOrcResources() - 100);
            character->setFollowPoint(buildX, buildY); //move character to construction zone
            setBuildArea();
            buildingHouse = true;
        }

        if (environment->getOrcResources() >= 250 && barracks < 1 && !buildingBarracks)
        {
            environment->createBarracks(buildX, buildY);
            environment->setOrcResources(environment->getOrcResources() - 250);
            character->setFollowPoint(buildX, buildY); //move character to construction zone
            setBuildArea();
            buildingBarracks = true;
        }

        if (environment->getOrcResources() >= 1000 && !buildingBarracks && barracks < 5)
        {
            environment->createBarracks(buildX, buildY);
            environment->setOrcResources(environment->getOrcResources() - 250);
            character->setFollowPoint(buildX, buildY); //move character to construction zone
            setBuildArea();
            buildingBarracks = true;
        }

        if (notConstructing)
        {
            character->setFollowPoint(struct_x, struct_y);
            notConstructing = false;
        }
    }
    if (character->getType() == 2) //check if orc a MILITIA
    {
        character->setFollowPoint(100, 50); //attack human town center
    }
    if (character->getType() == 3) //check if orc a CHAMPION
    {
        character->setFollowPoint(100, 50); //attack human town center
    }
}

void AI::updateBuilding(Building* building)
{
//gives orders to buildings based on current game situation
    if (building->getType() == 1 && !building->Creating()) //if building is a town center
    {
        if(environment->getOrcResources() >= 50 && environment->getOrcPop() < environment->getOrcMaxPop()&& environment->getOrcPop() < 30 && villagerPop < (2*(militiaPop+championPop))+6)
        {
            environment->setOrcResources(environment->getOrcResources() - 50);
            building->startCreating(2);
        }
    }

    if (building->getType() == 2 && building->constructed) //if building is a barracks
    {
        if(environment->getOrcResources() >= 50 && militiaPop < 3 && environment->getOrcPop() < environment->getOrcMaxPop() && environment->getOrcPop() < 30 && !building->Creating())
        {
            environment->setOrcResources(environment->getOrcResources() - 50);
            building->startCreating(2);
        }
        if(environment->getOrcResources() >= 100 && environment->getOrcPop() < environment->getOrcMaxPop() && !building->Creating())
        {
            environment->setOrcResources(environment->getOrcResources() - 100);
            building->startCreating(4);
        }

    }
}

void AI::setEnvironment(Environment* passed_environment)
{
    environment = passed_environment;
}

void AI::setBuildArea() //changes build location after each construction, simple grid
{
    buildX += 100;
    if (buildX >= 1000)
    {
        buildX = 700;
        buildY += 150;
    }
}

void AI::goldMineDepleted(int gold_x, int gold_y) //called by gold mine when depleted, changes idle villager target to next gold mine
{
    if (gold_x == idle_x && gold_y == idle_y)
    {
        idle_y -= 50;
        if (idle_y == 375) //if reach gap between gold mines
        {
            idle_y = 225;
        }
        if (idle_y == 75) //if reached top of gold mines
        {
            idle_x =525;
            idle_y = 525;
        }
    }
}

void AI::buildingNotConstructing(int structure_x, int structure_y) //called if a building isn't being built (ie builder killed), thus needs replacement builder, currently doesn't do anything
{
    if (struct_y != structure_y && struct_x != structure_x) //prevents repeated calls
    {
        struct_x = structure_x;
        struct_y = structure_y;
        notConstructing = true;
    }
}
