#include "ai.hpp"
#include "house.hpp"

AI::AI()
{
    team = 2;
    villagerPop = 0;
    militiaPop = 0;
    championPop = 0;
    buildX = 700;
    buildY = 200;
    buildingHouse = false;
    buildingBarracks = false;
    notConstructing1 = false;
    notConstructing2 = false;
    barracksConstructionInitiated = false;
    houses = 0;
    barracks = 0;
    idle_x = 580;
    idle_y = 580;
    struct_x = 0;
    struct_y = 0;
    militiaCreations = 0;
    villagerDefender = NULL;
}

AI::~AI()
{
    enemies.clear();
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

        if (environment->getOrcResources() >= 100 && environment->getOrcPop() + 2 >= environment->getOrcMaxPop() && !buildingHouse && barracksConstructionInitiated)
        {
            environment->createHouse(buildX, buildY);
            environment->setOrcResources(environment->getOrcResources() - 100);
            character->setFollowPoint(buildX, buildY); //move character to construction zone
            setBuildArea();
            buildingHouse = true;
        }

        if (environment->getOrcResources() >= 250 && barracks < 1)
        {
            environment->createBarracks(buildX, buildY);
            environment->setOrcResources(environment->getOrcResources() - 250);
            character->setFollowPoint(buildX, buildY); //move character to construction zone
            setBuildArea();
            buildingBarracks = true;
            barracksConstructionInitiated = true;
        }

        if (barracks == 0 && barracksConstructionInitiated && !character->isFollowing() && buildingBarracks) //send all villagers to build first barracks
        {
            character->setFollowPoint(buildX-120, buildY);
        }

        if (barracks == 1 && environment->getOrcPop() < 10 && militiaPop == 0)
        {
            character->setFollowPoint(idle_x, idle_y);
        }

        if (environment->getOrcResources() >= 1000 && !buildingBarracks && barracks < 5)
        {
            environment->createBarracks(buildX, buildY);
            environment->setOrcResources(environment->getOrcResources() - 250);
            character->setFollowPoint(buildX, buildY); //move character to construction zone
            setBuildArea();
            buildingBarracks = true;
        }

        if (notConstructing1 || notConstructing2) //if two villagers haven't been sent to idle construction site
        {
            character->setFollowPoint(struct_x, struct_y);
            if (!notConstructing1)
            {
                notConstructing2 = false;
                struct_x = 0;
                struct_y = 0;
            }
            notConstructing1 = false;
        }
    }
    if (character->getType() == 2) //check if orc a MILITIA
    {
        if (character->getEnemy() != NULL)
        {
            if (character->getEnemy()->isAlive())
            {
                character->setFollowPoint(enemy_target->GetCharacter()->GetX(), enemy_target->GetCharacter()->GetY());
            }
        }
        if (!character->isAttacking() && !enemies.empty())
        {
            enemy_target = enemies.back();
            enemies.pop_back();
            if (enemy_target->isAlive())
            {
                character->setFollowPoint(enemy_target->GetCharacter()->GetX(), enemy_target->GetCharacter()->GetY());
                enemy_target->Target(character);
                character->setEnemy(enemy_target);
            }
        }
        else
        {
            character->setFollowPoint(100, 50); //attack human town center
        }
        if (villagerDefender == NULL || !villagerDefender->isAlive()) //send one militia to guard villagers
        {
            villagerDefender = character;
            character->setFollowPoint(idle_x, idle_y);
        }
    }
    if (character->getType() == 3) //check if orc a CHAMPION
    {
        if (character->getEnemy() != NULL)
        {
            if (character->getEnemy()->isAlive())
            {
                character->setFollowPoint(enemy_target->GetCharacter()->GetX(), enemy_target->GetCharacter()->GetY());
            }
        }
        if (!character->isAttacking() && !enemies.empty())
        {
            enemy_target = enemies.back();
            enemies.pop_back();
            if (enemy_target->isAlive())
            {
                character->setFollowPoint(enemy_target->GetCharacter()->GetX(), enemy_target->GetCharacter()->GetY());
                enemy_target->Target(character);
                character->setEnemy(enemy_target);
            }
        }
        else
        {
            character->setFollowPoint(100, 50); //attack human town center
        }
    }
}

void AI::updateBuilding(Building* building)
{
//gives orders to buildings based on current game situation
    if (building->getType() == 1 && !building->Creating()) //if building is a town center
    {
        if(environment->getOrcResources() >= 50 && environment->getOrcPop() < environment->getOrcMaxPop()&& environment->getOrcPop() && (environment->getOrcPop() < 7 || barracksConstructionInitiated) )
        {
            environment->setOrcResources(environment->getOrcResources() - 50);
            building->startCreating(2);
        }
    }

    if (building->getType() == 2 && building->constructed) //if building is a barracks
    {
        if(environment->getOrcResources() >= 50 && (militiaCreations < 3 || environment->getOrcResources() <= 75) && environment->getOrcResources() <= 300 && environment->getOrcPop() < environment->getOrcMaxPop()
           && environment->getOrcPop() < 25 && !building->Creating())
        {
            environment->setOrcResources(environment->getOrcResources() - 50);
            building->startCreating(2);
            militiaCreations++;
        }
        if(environment->getOrcResources() >= 150 && environment->getOrcPop() < environment->getOrcMaxPop() && !building->Creating())
        {
            environment->setOrcResources(environment->getOrcResources() - 150);
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
    buildX += 120;
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
        idle_y -= 75;
        if (idle_x == 580 && idle_y == 355) //if reach gap between gold mines
        {
            idle_x = 505;
            idle_y = 580;
        }
        if (idle_x == 505 && idle_y == 355) //if reached gap between gold mines a second time
        {
            idle_x == 580;
            idle_y = 205;
        }
    }
}

void AI::buildingNotConstructing(int structure_x, int structure_y) //called if a building isn't being built (ie builder killed), thus needs replacement builder, currently doesn't do anything
{
    if (struct_y != structure_y && struct_x != structure_x) //prevents repeated calls
    {
        struct_x = structure_x;
        struct_y = structure_y;
        notConstructing1 = true;
        notConstructing2 = true;
    }
}
