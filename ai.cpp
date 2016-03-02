#include "ai.hpp"

AI::AI()
{
    team = 2;
}

AI::~AI()
{

}

void AI::updateCharacter(Character* character)
{
//to be implemented, will give orders to characters based on current game situation
    if (character->getType() == 1) //check if orc a villager
    {
        if (!character->isBuilding() && !character->isMining() && !character->isFollowing())
        {
            //character->setFollowPoint(50,50);
        }
    }
}

void AI::updateBuilding(Building* building)
{
//to be implemented, will give orders to buildings based on current game situation
}


