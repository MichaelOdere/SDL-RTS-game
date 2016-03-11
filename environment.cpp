#include "environment.hpp"
#include "villager.hpp"
#include "militia.hpp"
#include "champion.hpp"
#include "orc_villager.hpp"
#include "orc_militia.hpp"
#include "orc_champion.hpp"
#include "TownCenter.h"
#include "barracks.h"
#include "house.hpp"
#include "text.hpp"
#include <math.h>       /* floor */

Environment::Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY, SubMenu* passed_menu, AI* passed_ai, Main* passed_main)
{
    sdl_setup = passed_sdl_setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    optionsMenu = passed_menu;
    ai = passed_ai;
    main = passed_main;
    startTime = SDL_GetTicks()/1000; //ensures game time corresponds to when spacebar hit on splash screen and game begins

    collisionImage20 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangleGREEN.png");
    collisionImage19= IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle19.png");
    collisionImage18 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle18.png");
    collisionImage17 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle17.png");
    collisionImage16 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle16.png");
    collisionImage15 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle15.png");
    collisionImage14= IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle14.png");
    collisionImage13 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle13.png");
    collisionImage12 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle12.png");
    collisionImage11 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle11.png");
    collisionImage10 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle10.png");
    collisionImage9= IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle9.png");
    collisionImage8 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle8.png");
    collisionImage7 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle7.png");
    collisionImage6 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle6.png");
    collisionImage5 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle5.png");
    collisionImage4 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle4.png");
    collisionImage3 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle3.png");
    collisionImage2 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle2.png");
    collisionImage1 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle1.png");
    villagerImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/villager.png");
    militiaImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/militia.png");
    championImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/champion.png");
    orcVillagerImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/orcVillager.png");
    orcMilitiaImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/orcMilitia.png");
    orcChampionImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/orcChampion.png");
    houseImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/house.png");
    barracksImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/barracks.png");
    barracksImage1 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/barracks1.png");
    townCenterImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/towncenter.png");
    goldImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/gold.png");
    constructionImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/collision_rectangle.png");

    goldText = new TextMessage(sdl_setup->GetRenderer(), std::to_string((int)resources), 8, 0);
    timeText = new TextMessage(sdl_setup->GetRenderer(), std::to_string((SDL_GetTicks()/1000) - startTime), 880, 0);
    populationText = new TextMessage(sdl_setup->GetRenderer(), "Population: " + std::to_string(humanPop)+"/"+std::to_string(humanMaxPop), 150, 0);
    insufficientFunds = new TextMessage(sdl_setup->GetRenderer(), "You don't have " + std::to_string(optionsMenu->getOpCost()) + " gold!", 350, 300);
    noHousing = new TextMessage(sdl_setup->GetRenderer(), "Need more houses", 350, 300);
    busyBuilding = new TextMessage(sdl_setup->GetRenderer(), "This building is already creating", 350, 300);

    showMenu = true;//start with menu displayed
    optionsMenu->UpdateType(1);// 1 is main menu
    broke = false;
    overpopulated = false;

    //starting resources
    resources = 100;
    orcResources = 100;

    team = 1; //player team

    //initial pop
    humanPop = 3;
    orcPop = 3;

    //initial max pop
    humanMaxPop = 10;
    orcMaxPop = 10;

    maxMaxPop = 25; //neither team may have more than 25 units

    //Humans
    selectedCharacter = new Villager(sdl_setup, villagerImage, 300, 200, MouseX, MouseY, this); //need to select initial character to avoid error of deselecting an unselected character below
    selectedCharacter->unSelect();
    characters.push_back(selectedCharacter);
    characters.push_back(new Villager(sdl_setup, villagerImage, 200, 200, MouseX, MouseY, this));
    characters.push_back(new Villager(sdl_setup, villagerImage, 250, 200, MouseX, MouseY, this));

    //Orcs
    characters.push_back(new OrcVillager(sdl_setup, orcVillagerImage, 650, 200, MouseX, MouseY, this));
    characters.push_back(new OrcVillager(sdl_setup, orcVillagerImage, 700, 200, MouseX, MouseY, this));
    characters.push_back(new OrcVillager(sdl_setup, orcVillagerImage, 750, 200, MouseX, MouseY, this));

    //Town Center placement on map
    selectedBuilding = new TownCenter(sdl_setup, townCenterImage, 100, 50, 140, 120, 1, this);
    selectedBuilding->unSelect();
    buildings.push_back(selectedBuilding);
    buildings.push_back(new TownCenter(sdl_setup, townCenterImage, 800, 50, 140, 120, 2, this));

    //Gold placement on map
    selectedGold = new Gold(sdl_setup, goldImage, 475, 550, this);
    selectedGold->unSelect();
    goldMines.push_back(selectedGold);
    goldMines.push_back(new Gold(sdl_setup, goldImage, 550, 550, this));
    goldMines.push_back(new Gold(sdl_setup, goldImage, 475, 475, this));
    goldMines.push_back(new Gold(sdl_setup, goldImage, 550, 475, this));
    goldMines.push_back(new Gold(sdl_setup, goldImage, 475, 400, this));
    goldMines.push_back(new Gold(sdl_setup, goldImage, 550, 400, this));
    goldMines.push_back(new Gold(sdl_setup, goldImage, 475, 175, this));
    goldMines.push_back(new Gold(sdl_setup, goldImage, 550, 175, this));
    goldMines.push_back(new Gold(sdl_setup, goldImage, 475, 100, this));
    goldMines.push_back(new Gold(sdl_setup, goldImage, 550, 100, this));
    goldMines.push_back(new Gold(sdl_setup, goldImage, 475, 25, this));
    goldMines.push_back(new Gold(sdl_setup, goldImage, 550, 25, this));
}

Environment::~Environment()
{

    for (std::vector<Gold*>::iterator i = goldMines.begin(); i != goldMines.end(); ++i)
    {
        delete (*i);
    }
    for (std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
        delete (*i);
    }
    for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i)
    {
        delete (*i);
    }

    goldMines.clear();
    buildings.clear();
    characters.clear();
}

void Environment::DrawBack()
{
    for (std::vector<Gold*>::iterator i = goldMines.begin(); i != goldMines.end(); ++i)
    {
        if ((*i)->isAlive())
        {
            (*i)->DrawGold();
        }
    }
    for (std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
        if ((*i)->isAlive())
        {
            (*i)->DrawBuilding();
        }
    }
    for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i)
    {
        if ((*i)->isAlive())
        {
            (*i)->Draw();
        }
    }
}

void Environment::AddResources(int i) //called with a successful mine
{
    if (i == 1)
    {
    resources = resources + 0.0025;
    } else
    {
    orcResources = orcResources + 0.0025;
    }
}

void Environment::Update()
{


    goldText->Draw("Gold: " + std::to_string((int)resources));
    populationText->Draw("Population: " + std::to_string(humanPop)+"/"+std::to_string(humanMaxPop));
    timeText->Draw(timeHandler((int)((SDL_GetTicks()/1000))-startTime));

    if(broke){
        if(SDL_GetTicks() < brokeTime+2000){
            insufficientFunds->Draw("You don't have " + std::to_string(brokeCost) + " gold!");
        }else{
            broke = false;
        }
    }

    if(overpopulated){
        if(SDL_GetTicks() < brokeTime+2000){
            noHousing->Draw("You need more houses!");
        }else{
            overpopulated = false;
        }
    }
    
    if(alreadyCreating){
        if(SDL_GetTicks() < brokeTime+2000){
            busyBuilding->Draw("This building is already creating!");
        }else{
            alreadyCreating = false;
        }
    }

    if(showMenu){
        if(selectedBuilding->selected){
            optionsMenu->UpdateType(selectedBuilding->getMenuType());
        }else if(selectedCharacter->selected){
            optionsMenu->UpdateType(selectedCharacter->getMenuType());
        }else{
            optionsMenu->UpdateType(1);
        }
        optionsMenu->Draw();
        optionsMenu->Update();
    }

    if(selectedBuilding->menuType == 4 && selectedBuilding->isAlive()){ //town center selected
        if(optionsMenu->buttonPressed){
            if (selectedBuilding->getTeam() == 1) { //check if human towncenter
                if(optionsMenu->getWhatToMake() == 3){ //if villager selected
                    //make villager next to towncenter
                    if(resources>=optionsMenu->getOpCost() && humanPop < humanMaxPop && humanPop < maxMaxPop  && selectedBuilding->creating == false){ //if enough resources and population room

                        resources = resources - optionsMenu->getOpCost(); //remove resources
                        selectedBuilding->startCreating(1); //initiate creation of unit (10 sec)
                    }else if(resources<optionsMenu->getOpCost()){
                        alertInsufficientFunds();
                    }else if(humanPop >= humanMaxPop){
                        alertNoHousing();
                    }else if(selectedBuilding->creating){
                        alertCreating();
                    }
                    optionsMenu->buttonPressed = false;
                }
            } else if (team == 2) { //orc towncenter
                if(optionsMenu->getWhatToMake() == 4){ //if orc villager selected
                    //make orc villager next to towncenter
                    if(orcResources>=optionsMenu->getOpCost()  && orcPop < orcMaxPop && selectedBuilding->creating == false){
                        orcResources = orcResources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(2);
                    }else if(resources<optionsMenu->getOpCost()){
                        alertInsufficientFunds();
                    }else if(humanPop >= humanMaxPop){
                        alertNoHousing();
                    }else if(selectedBuilding->creating){
                        alertCreating();
                    }
                    optionsMenu->buttonPressed = false;
                }
            }
        }
    }

    if(selectedBuilding->menuType == 5 && selectedBuilding->isAlive() && selectedBuilding->isConstructed()){ //barracks selected
        if(optionsMenu->buttonPressed){
            if (selectedBuilding->getTeam() == 1) { //check if human barracks
                if(optionsMenu->getWhatToMake() == 5){
                    //make militia next to barracks
                    if(resources>=optionsMenu->getOpCost() && humanPop < humanMaxPop && humanPop < maxMaxPop && selectedBuilding->creating == false){

                        resources = resources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(1);
                    }else if(resources < optionsMenu->getOpCost()){
                        alertInsufficientFunds();
                    }else if(humanPop >= humanMaxPop){
                        alertNoHousing();
                    }else if(selectedBuilding->creating){
                        alertCreating();
                    }
                    optionsMenu->buttonPressed = false;
                }else if(optionsMenu->getWhatToMake() == 7){
                    //make champion next to barracks
                    if(resources >= optionsMenu->getOpCost() && humanPop < humanMaxPop && selectedBuilding->creating == false){
                        resources = resources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(3);
                    }else if(resources < optionsMenu->getOpCost()){
                        alertInsufficientFunds();
                    }else if(humanPop >= humanMaxPop){
                        alertNoHousing();
                    }else if(selectedBuilding->creating){
                        alertCreating();
                    }
                    optionsMenu->buttonPressed = false;
                }
            } else if (team == 2) { //orc barracks
                if(optionsMenu->getWhatToMake() == 6){
                    //make orc militia next to barracks

                    if(orcResources>=optionsMenu->getOpCost() && orcPop < orcMaxPop && selectedBuilding->creating == false){
                        orcResources = orcResources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(2);
                    }else{
                        alertInsufficientFunds();
                    }
                    optionsMenu->buttonPressed = false;
                }else if(optionsMenu->getWhatToMake() == 8){
                    //make champion next to barracks
                    if(orcResources>=optionsMenu->getOpCost()  && orcPop < orcMaxPop && selectedBuilding->creating == false){
                        orcResources = orcResources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(4);
                    }else{
                        alertInsufficientFunds();
                    }
                    optionsMenu->buttonPressed = false;
                }
            }
        }
    }

    for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i)
    {
        if ((*i)->isAlive())
        {
            (*i)->Update();
            if ((*i)->getTeam() == 2) { //pass each orc unit to AI to determine its next action
                ai->updateCharacter((*i));
            }
        }
    }

    for (std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
        if ((*i)->isAlive())
        {
            (*i)->Update();
            if ((*i)->getTeam() == 2) { //pass each orc building to AI to determine its next action
                ai->updateBuilding((*i));
            }
        }
    }

    for (std::vector<Gold*>::iterator i = goldMines.begin(); i != goldMines.end(); ++i)
    {
        if ((*i)->isAlive())
        {
            (*i)->Update();
        }
    }

    if (sdl_setup->GetEv()->type == SDL_MOUSEBUTTONDOWN)
    {
        if (sdl_setup->GetEv()->button.button == SDL_BUTTON_LEFT)
        {

            if(showMenu == false || *MouseY <= optionsMenu->getY()){
            for(std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i){
                if(*MouseX >= ((*i)->getStructureX()) && *MouseX <= ((*i)->getStructureX()+(*i)->getStructureW()) && *MouseY >= ((*i)->getStructureY()) && *MouseY <= ((*i)->getStructureY()+(*i)->getStructureH()))
                {
                    selectedBuilding->unSelect(); //unselect previously selected
                    (*i)->setSelected();
                    selectedBuilding = (*i); //reassign selected building for future deselection

                    break; //end loop once building found
                }
                selectedBuilding->unSelect(); //no building found, unselect previous building
            }

            for(std::vector<Gold*>::iterator i = goldMines.begin(); i != goldMines.end(); ++i){
                if(*MouseX >= ((*i)->getGoldX()) && *MouseX <= ((*i)->getGoldX()+(*i)->getGoldW()) && *MouseY >= ((*i)->getGoldY()) && *MouseY <= ((*i)->getGoldY()+(*i)->getGoldH()))
                {
                    selectedGold->unSelect(); //unselect previously selected
                    (*i)->setSelected();
                    selectedGold = (*i); //reassign selected gold mine for future deselection
                    break; //end loop once gold found
                }
                selectedGold->unSelect(); //no gold found, unselect previous gold
            }

            for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i) //character selection takes priority over buildings and gold mines
            {
                if(*MouseX >= ((*i)->getCharacterX()-15) && *MouseX <= ((*i)->getCharacterX()+(*i)->getCharacterW()-15) && *MouseY >= ((*i)->getCharacterY()-20) && *MouseY <= ((*i)->getCharacterY()+(*i)->getCharacterH()-20) && (*i)->isAlive())
                {
                    selectedCharacter->unSelect(); //unselect previously selected
                    selectedBuilding->unSelect();
                    selectedGold->unSelect();
                    (*i)->setSelected();
                    selectedCharacter = (*i); //reassign selected character for future deselection

                    break; //prevent selection of multiple characters in same area
                }
                selectedCharacter->unSelect(); //unselect previously selected
            }

            if(optionsMenu->getWhatToMake() == 1 && !buildingConstructionCollision(*MouseX-50, *MouseY-50) && *MouseX < 550){ //check if valid build zone (no collisions and not in enemy territory)
                if (selectedCharacter->getTeam() == 1) {//check villager team
                    if(resources >= optionsMenu->getOpCost()){
                        buildings.push_back(new House(sdl_setup, constructionImage, *MouseX-50, *MouseY-50, 50, 50, 1, this)); //initially display construction zone
                        resources = resources - optionsMenu->getOpCost();
                    }else{
                        alertInsufficientFunds();
                    }
                } else {
                    if(orcResources >= optionsMenu->getOpCost()){
                        buildings.push_back(new House(sdl_setup, constructionImage, *MouseX-50, *MouseY-50, 50, 50, 2, this));
                        orcResources = orcResources - optionsMenu->getOpCost();
                    }else{
                        alertInsufficientFunds();
                    }
                }
                selectedCharacter->setFollowPoint(*MouseX, *MouseY); //move villager to construction zone

            }else if(optionsMenu->getWhatToMake() == 2 && !buildingConstructionCollision(*MouseX-50, *MouseY-50) && *MouseX < 550){
                if (selectedCharacter->getTeam() == 1) {//check villager team
                    if(resources >= optionsMenu->getOpCost()){
                        buildings.push_back(new Barracks(sdl_setup, constructionImage, *MouseX-50, *MouseY-50, 75, 75, 1, this));
                        resources = resources - optionsMenu->getOpCost();
                    }
                    else{
                        alertInsufficientFunds();
                    }
                } else {
                    if(orcResources >= optionsMenu->getOpCost()){
                        buildings.push_back(new Barracks(sdl_setup, constructionImage, *MouseX-50, *MouseY-50, 75, 75, 2, this));
                        orcResources = orcResources - optionsMenu->getOpCost();
                    }
                    else{
                        alertInsufficientFunds();
                    }
                }
                selectedCharacter->setFollowPoint(*MouseX, *MouseY); //move character to construction zone
            }
        }
    }
}
    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){ //toggle showing of menu
       if(sdl_setup->GetEv()->key.keysym.sym == SDLK_SPACE){
            if(showMenu){
                showMenu = false;
            }else{
                showMenu = true;
            }
       }
    }
    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){
       if(sdl_setup->GetEv()->key.keysym.sym == SDLK_F8){
            endGame(2);
       }
    }
    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){
       if(sdl_setup->GetEv()->key.keysym.sym == SDLK_INSERT){
            resources += 100;
       }
    }
}

Character* Environment::Combat(Sprite* attacker, int attacker_team) //returns Character attacked by input, if no collision, return NULL
{
    for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i)
    {
        if (attacker->isColliding((*i)->GetCharacter()->GetCollisionRect()) && (*i)->isAlive() && (*i)->getTeam() != attacker_team) //check for collision with character, excluding allies and dead characters
        {
            return (*i);
        }
    }
    return NULL;
}

Building* Environment::CombatBuilding(Sprite* attacker, int attacker_team) //returns Building attacked by input, if no collision, return NULL
{
    for (std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
        if (attacker->isColliding((*i)->GetBuilding()->GetCollisionRect()) && (*i)->isAlive() && (*i)->getTeam() != attacker_team) //check for collision with Building, excluding team buildings and destroyed buildings
        {
            return (*i);
        }
    }
    return NULL;
}

Character* Environment::FindTarget(int x, int y) //used for following, searches for Character in click location
{
    for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i)
        {
            if(x >= ((*i)->getCharacterX()-15) && x <= ((*i)->getCharacterX()+(*i)->getCharacterW()-15) && y >= ((*i)->getCharacterY()-20) && y <= ((*i)->getCharacterY()+(*i)->getCharacterH()-20))
            {
                return (*i);
            }
        }
    return NULL;
}

void Environment::decreasePop(int team) //called when house destroyed
{
    if (team == 1) {
        humanMaxPop -= 5;
    } else {
        orcMaxPop -= 5;
    }
}

void Environment::increasePop(int team) //called when house created
{
    if (team == 1) {
        humanMaxPop += 5;
    } else {
        orcMaxPop += 5;
    }
}

bool Environment::buildingConstructionCollision(int x, int y) //Cannot build on other buildings or gold mines
{
    for (int j = 0; j < buildings.size(); j++) //check for collision
    {
        if (buildings[j]->isAlive())
        {
            collision_rect = buildings[j]->GetBuilding()->GetCollisionRect();

            if (collision_rect.GetRectangle().x + collision_rect.GetRectangle().w > x &&
            collision_rect.GetRectangle().y + collision_rect.GetRectangle().h > y &&
            collision_rect.GetRectangle().x < x+50 &&
            collision_rect.GetRectangle().y < y+50)
            {
                return true;
            }
        }
    }
    for (int j = 0; j < goldMines.size(); j++) //check for collision
    {
        if (goldMines[j]->isAlive())
        {
            collision_rect = goldMines[j]->GetGold()->GetCollisionRect();

            if (collision_rect.GetRectangle().x + collision_rect.GetRectangle().w > x &&
            collision_rect.GetRectangle().y + collision_rect.GetRectangle().h > y &&
            collision_rect.GetRectangle().x < x+50 &&
            collision_rect.GetRectangle().y < y+50)
            {
                return true;
            }
        }
    }
    return false;
}

void Environment::alertInsufficientFunds(){
    broke = true;
    brokeTime = SDL_GetTicks();
    brokeCost =optionsMenu->getOpCost();
}

void Environment::alertNoHousing(){
    overpopulated = true;
    brokeTime = SDL_GetTicks();
}

void Environment::alertCreating(){
    alreadyCreating = true;
    brokeTime = SDL_GetTicks();
}

void Environment::createVillager(Building* passed_building, int unit) //creates new unit next to passed building
{
    if (unit == 1) // if human villager
    {
        characters.push_back(new Villager(sdl_setup, villagerImage,passed_building->getStructureX() + passed_building->getStructureW(), passed_building->getStructureY() + passed_building->getStructureH()+20, MouseX, MouseY, this));
        humanPop++;
    } else
    {
        characters.push_back(new OrcVillager(sdl_setup, orcVillagerImage,passed_building->getStructureX() + passed_building->getStructureW(), passed_building->getStructureY() + passed_building->getStructureH()+20, MouseX, MouseY, this));
        orcPop++;
    }
}

void Environment::createMilitia(Building* passed_building, int unit)
{
    if (unit == 1) //if human militia
    {
        characters.push_back(new Militia(sdl_setup, militiaImage,passed_building->getStructureX() + passed_building->getStructureW(), passed_building->getStructureY() + passed_building->getStructureH()+20, MouseX, MouseY, this));
        humanPop++;
    } else
    {
        characters.push_back(new OrcMilitia(sdl_setup, orcMilitiaImage,passed_building->getStructureX() + passed_building->getStructureW()-30, passed_building->getStructureY() + passed_building->getStructureH()+30, MouseX, MouseY, this));
        orcPop++;
    }
}

void Environment::createChampion(Building* passed_building, int unit)
{
    if (unit == 3) //if human champion
    {
        characters.push_back(new Champion(sdl_setup, championImage,passed_building->getStructureX() + passed_building->getStructureW(), passed_building->getStructureY() + passed_building->getStructureH()+20, MouseX, MouseY, this));
        humanPop++;
    } else
    {
        characters.push_back(new OrcChampion(sdl_setup, orcChampionImage,passed_building->getStructureX() + passed_building->getStructureW(), passed_building->getStructureY() + passed_building->getStructureH()+20, MouseX, MouseY, this));
        orcPop++;
    }
}

void Environment::createHouse(int x, int y)
{
    buildings.push_back(new House(sdl_setup, constructionImage, x, y, 50, 50, 2, this)); //initially display construction zone
}

void Environment::createBarracks(int x, int y)
{
    buildings.push_back(new Barracks(sdl_setup, constructionImage, x, y, 75, 75, 2, this)); //initially display construction zone
}

//Methods to pass information to AI
void Environment::notBuildingHouse() { ai->notBuildingHouse(); }
void Environment::notBuildingBarracks() { ai->notBuildingBarracks(); }
void Environment::barracksDestroyed() { ai->barracksDestroyed(); }
void Environment::addVillager() { ai->addVillager(); }
void Environment::addMilitia() { ai->addMilitia(); }
void Environment::addChampion() { ai->addChampion(); }
void Environment::removeVillager() { ai->removeVillager(); }
void Environment::removeMilitia() { ai->removeMilitia(); }
void Environment::removeChampion() { ai->removeChampion(); }
void Environment::goldMineDepleted(int gold_x, int gold_y) { ai->goldMineDepleted(gold_x, gold_y); }
void Environment::buildingNotConstructing(int structure_x, int structure_y) { ai->buildingNotConstructing(structure_x, structure_y); }
void Environment::inEnemyTerritory(Character* enemy) { ai->addEnemy(enemy); }

void Environment::removeCharacter(int team) //handles population
{
    if (team == 1)
    {
        humanPop--;
    } else
    {
        orcPop--;
    }
}

std::string Environment::timeHandler(int time){

    int mins = floor((int)(time/60));
    int secs = time-mins*60;
    return "Time: "+ std::to_string(mins) +":" +std::to_string(secs);
}

void Environment::displayHealthBar(Sprite* item, float health_percent)
{
        //display health bar corresponding to health percentage
    if (health_percent < 0.05)
    {
        item->DisplayRectangle(collisionImage1);
    }
    else if (health_percent < 0.10)
    {
        item->DisplayRectangle(collisionImage2);
    }
    else if (health_percent < 0.15)
    {
        item->DisplayRectangle(collisionImage3);
    }
    else if (health_percent < 0.20 )
    {
        item->DisplayRectangle(collisionImage4);
    }
    else if (health_percent < 0.25 )
    {
        item->DisplayRectangle(collisionImage5);
    }
    else if (health_percent < 0.30)
    {
        item->DisplayRectangle(collisionImage6);
    }
    else if (health_percent < 0.35 )
    {
        item->DisplayRectangle(collisionImage7);
    }
    else if (health_percent < 0.40 )
    {
        item->DisplayRectangle(collisionImage8);
    }
    else if (health_percent < 0.45 )
    {
        item->DisplayRectangle(collisionImage9);
    }
    else if (health_percent < 0.50)
    {
        item->DisplayRectangle(collisionImage10);
    }
    else if (health_percent < 0.55 )
    {
        item->DisplayRectangle(collisionImage11);
    }
    else if (health_percent < 0.60 )
    {
        item->DisplayRectangle(collisionImage12);
    }
    else if (health_percent < 0.65 )
    {
        item->DisplayRectangle(collisionImage13);
    }
    else if (health_percent < 0.70)
    {
        item->DisplayRectangle(collisionImage14);
    }
    else if (health_percent < 0.75 )
    {
        item->DisplayRectangle(collisionImage15);
    }
    else if (health_percent < 0.80 )
    {
        item->DisplayRectangle(collisionImage16);
    }
    else if (health_percent < 0.85 )
    {
        item->DisplayRectangle(collisionImage17);
    }
    else if (health_percent < 0.90)
    {
        item->DisplayRectangle(collisionImage18);
    }
    else if (health_percent < 0.95 )
    {
        item->DisplayRectangle(collisionImage19);
    }
    else
    {
        item->DisplayRectangle(collisionImage20);
    }
}

void Environment::changeImage(Sprite* building, int type)
{
    if (type == 1) //house
    {
        building->changeImage(houseImage); //reset image to created state
    } else //barracks
    {
        building->changeImage(barracksImage1); //reset image to created state
    }
}

void Environment::setCollisionImage(Sprite* building)
{
    building->setCollisionImage(collisionImage20);
}

void Environment::endGame(int loser) //tells Main game is over and declares winner
{
    main->endGame(loser);
}
