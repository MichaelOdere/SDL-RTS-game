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

Environment::Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY, SubMenu* passed_menu, AI* passed_ai)
{
    sdl_setup = passed_sdl_setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    optionsMenu = passed_menu;
    ai = passed_ai;


    goldText = new TextMessage(sdl_setup->GetRenderer(), std::to_string((int)resources), 20, 0);
    timeText = new TextMessage(sdl_setup->GetRenderer(), std::to_string(SDL_GetTicks()/1000), 720, 0);
    insufficientFunds = new TextMessage(sdl_setup->GetRenderer(), "You don't have " + std::to_string(optionsMenu->getOpCost()) + " gold!", 350, 300);
    noHousing = new TextMessage(sdl_setup->GetRenderer(), "You don't have enough houses for a new character", 350, 300);

    showMenu = false;//start with menu not displayed
    optionsMenu->UpdateType(1);// 1 is main menu
    broke = false;
    overpopulated = false;

    resources = 300;
    orcResources = 300;

    team = 1;

    humanPop = 5;
    orcPop = 5;
    humanMaxPop = 10;
    orcMaxPop = 10;

    //Humans
    selectedCharacter = new Villager(sdl_setup, "images/villager.png", 300, 200, MouseX, MouseY, this); //game begins with villager selected to avoid error of deselecting an unselected character below
    selectedCharacter->unSelect();
    characters.push_back(selectedCharacter);
    characters.push_back(new Villager(sdl_setup, "images/villager.png", 200, 200, MouseX, MouseY, this));
    characters.push_back(new Villager(sdl_setup, "images/villager.png", 250, 200, MouseX, MouseY, this));

    //Orcs
    characters.push_back(new OrcVillager(sdl_setup, "images/orcVillager.png", 650, 200, MouseX, MouseY, this));
    characters.push_back(new OrcVillager(sdl_setup, "images/orcVillager.png", 700, 200, MouseX, MouseY, this));
    characters.push_back(new OrcVillager(sdl_setup, "images/orcVillager.png", 750, 200, MouseX, MouseY, this));



    selectedBuilding = new TownCenter(sdl_setup, "images/towncenter.png", 100, 50, 140, 120, 1, this);
    selectedBuilding->unSelect();
    buildings.push_back(selectedBuilding);
    buildings.push_back(new TownCenter(sdl_setup, "images/towncenter.png", 800, 50, 140, 120, 2, this));


    selectedGold = new Gold(sdl_setup, 500, 500, this);
    selectedGold->unSelect();
    goldMines.push_back(selectedGold);
    goldMines.push_back(new Gold(sdl_setup, 550, 500, this));
    goldMines.push_back(new Gold(sdl_setup, 500, 450, this));
    goldMines.push_back(new Gold(sdl_setup, 550, 450, this));
    goldMines.push_back(new Gold(sdl_setup, 500, 400, this));
    goldMines.push_back(new Gold(sdl_setup, 550, 400, this));
    goldMines.push_back(new Gold(sdl_setup, 500, 200, this));
    goldMines.push_back(new Gold(sdl_setup, 550, 200, this));
    goldMines.push_back(new Gold(sdl_setup, 500, 150, this));
    goldMines.push_back(new Gold(sdl_setup, 550, 150, this));
    goldMines.push_back(new Gold(sdl_setup, 500, 100, this));
    goldMines.push_back(new Gold(sdl_setup, 550, 100, this));
}

Environment::~Environment()
{
    delete optionsMenu;

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
        if ((*i)->Alive())
        {
            (*i)->DrawGold();
        }
    }

    for (std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
        if ((*i)->Alive())
        {
            (*i)->DrawBuilding();
        }
    }

    for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i)
    {
        if ((*i)->Alive())
        {
            (*i)->Draw();
        }
    }
}

void Environment::AddResources(int i)
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
    timeText->Draw(timeHandler((int)(SDL_GetTicks()/1000)));

    if(broke){
        if(SDL_GetTicks() < brokeTime+5000){
            insufficientFunds->Draw("You don't have " + std::to_string(optionsMenu->getOpCost()) + " gold!");
        }else{
            broke = false;
        }
    }

    if(overpopulated){
        if(SDL_GetTicks() < brokeTime+5000){
            noHousing->Draw("You don't have enough houses for a new character");
        }else{
            overpopulated = false;
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

    if(selectedBuilding->menuType == 4 && selectedBuilding->Alive()){ //town center selected
        if(optionsMenu->buttonPressed){
            if (selectedBuilding->getTeam() == 1) { //check if human towncenter
                if(optionsMenu->getWhatToMake() == 3){ //if villager selected
                    //make villager next to towncenter
                    if(resources>=optionsMenu->getOpCost() && humanPop < humanMaxPop && selectedBuilding->creating == false){ //if enough resources and population room
                        resources = resources - optionsMenu->getOpCost(); //remove resources
                        selectedBuilding->startCreating(1); //initiate creation of unit (10 sec, multiple units may be queued)
                    }else if(resources<optionsMenu->getOpCost()){
                        alertInsufficientFunds();
                    }else if(humanPop >= humanMaxPop){
                        alertNoHousing();
                    }
                    optionsMenu->buttonPressed = false;
                }
            } else { //orc towncenter
                if(optionsMenu->getWhatToMake() == 4){ //if orc villager selected
                    //make orc villager next to towncenter
                    if(orcResources>=optionsMenu->getOpCost()  && orcPop < orcMaxPop && selectedBuilding->creating == false){
                        orcResources = orcResources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(2);
                    }else if(resources<optionsMenu->getOpCost()){
                        alertInsufficientFunds();
                    }else if(humanPop >= humanMaxPop){
                        alertNoHousing();
                    }
                    optionsMenu->buttonPressed = false;
                }
            }
        }
    }

    if(selectedBuilding->menuType == 5 && selectedBuilding->Alive() && selectedBuilding->isConstructed()){ //barracks selected
        if(optionsMenu->buttonPressed){
            if (selectedBuilding->getTeam() == 1) { //check if human barracks
                if(optionsMenu->getWhatToMake() == 5){
                    //make militia next to barracks
                    if(resources>=optionsMenu->getOpCost() && humanPop < humanMaxPop && selectedBuilding->creating == false){
                        resources = resources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(1);
                    }else if(resources<optionsMenu->getOpCost()){
                        alertInsufficientFunds();
                    }else if(humanPop>=humanMaxPop){
                        alertNoHousing();
                    }
                    optionsMenu->buttonPressed = false;
                }else if(optionsMenu->getWhatToMake() == 7){
                    //make champion next to barracks
                    if(resources>=optionsMenu->getOpCost() && humanPop < humanMaxPop && selectedBuilding->creating == false){
                        resources = resources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(3);
                    }else if(resources<optionsMenu->getOpCost()){
                        alertInsufficientFunds();
                    }else if(humanPop>=humanMaxPop){
                        alertNoHousing();
                    }
                    optionsMenu->buttonPressed = false;
                }
            } else { //orc barracks
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
        if ((*i)->Alive())
        {
            (*i)->Update();
            if ((*i)->getTeam() == 2) { //pass each orc unit to AI to determine its next action
                ai->updateCharacter((*i));
            }
        }
    }

    for (std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
        if ((*i)->Alive())
        {
            (*i)->Update();
            if ((*i)->getTeam() == 2) { //pass each orc building to AI to determine its next action
                ai->updateBuilding((*i));
            }
        }
    }

    for (std::vector<Gold*>::iterator i = goldMines.begin(); i != goldMines.end(); ++i)
    {
        if ((*i)->Alive())
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
                if(*MouseX >= ((*i)->getCharacterX()-15) && *MouseX <= ((*i)->getCharacterX()+(*i)->getCharacterW()-15) && *MouseY >= ((*i)->getCharacterY()-20) && *MouseY <= ((*i)->getCharacterY()+(*i)->getCharacterH()-20) && (*i)->Alive())
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

            if(optionsMenu->getWhatToMake() == 1 && !buildingConstructionCollision(*MouseX-50, *MouseY-50)){
                if (selectedCharacter->getTeam() == 1) {//check villager team
                    if(resources >= optionsMenu->getOpCost()){
                        buildings.push_back(new House(sdl_setup, "images/collision_rectangle.png", *MouseX-50, *MouseY-50, 50, 50, 1, this)); //initially display construction zone
                        resources = resources - optionsMenu->getOpCost();
                    }else{
                        alertInsufficientFunds();
                    }
                } else {
                    if(orcResources >= optionsMenu->getOpCost()){
                        buildings.push_back(new House(sdl_setup, "images/collision_rectangle.png", *MouseX-50, *MouseY-50, 50, 50, 2, this));
                        orcResources = orcResources - optionsMenu->getOpCost();
                    }else{
                        alertInsufficientFunds();
                    }
                }
                selectedCharacter->setFollowPoint(*MouseX, *MouseY); //move villager to construction zone

            }else if(optionsMenu->getWhatToMake() == 2 && !buildingConstructionCollision(*MouseX-50, *MouseY-50)){
                if (selectedCharacter->getTeam() == 1) {//check villager team
                    if(resources >= optionsMenu->getOpCost()){
                        buildings.push_back(new Barracks(sdl_setup, "images/collision_rectangle.png", *MouseX-50, *MouseY-50, 75, 75, 1, this));
                        resources = resources - optionsMenu->getOpCost();
                    }
                } else {
                    if(orcResources >= optionsMenu->getOpCost()){
                        buildings.push_back(new Barracks(sdl_setup, "images/collision_rectangle.png", *MouseX-50, *MouseY-50, 75, 75, 2, this));
                        orcResources = orcResources - optionsMenu->getOpCost();
                    }
                }
                selectedCharacter->setFollowPoint(*MouseX, *MouseY); //move character to construction zone
            }
        }
    }
}
    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){
       if(sdl_setup->GetEv()->key.keysym.sym == SDLK_SPACE){
            if(showMenu){
                showMenu = false;
            }else{
                showMenu = true;
            }
       }
    }
}

Character* Environment::Combat(Sprite* attacker, int attacker_team) //returns Character attacked by input, if no collision, return NULL
{
    for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i)
    {
        if (attacker->isColliding((*i)->GetCharacter()->GetCollisionRect()) && (*i)->Alive() && (*i)->getTeam() != attacker_team) //check for collision with character, excluding allies and dead characters
        {
            return (*i);
        }
    }
    return NULL;
}

Building* Environment::CombatBuilding(Sprite* attacker, int attacker_team) //returns Character attacked by input, if no collision, return NULL
{
    for (std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
        if (attacker->isColliding((*i)->GetBuilding()->GetCollisionRect()) && (*i)->Alive() && (*i)->getTeam() != attacker_team) //check for collision with character, excluding allies and dead characters
        {
            return (*i);
        }
    }
    return NULL;
}

Character* Environment::FindTarget(int x, int y) //used for following, currently not called because of bug which entails from it
{
    for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i) //character selection takes priority over buildings and gold mines
        {
            if(x >= ((*i)->getCharacterX()-15) && x <= ((*i)->getCharacterX()+(*i)->getCharacterW()-15) && y >= ((*i)->getCharacterY()-20) && y <= ((*i)->getCharacterY()+(*i)->getCharacterH()-20))
            {
                return (*i);
            }
        }
    return NULL;
}

void Environment::decreasePop(int team)
{
    if (team == 1) {
        humanMaxPop -= 5;
    } else {
        orcMaxPop -= 5;
    }
}

void Environment::increasePop(int team)
{
    if (team == 1) {
        humanMaxPop += 5;
    } else {
        orcMaxPop += 5;
    }
}

bool Environment::buildingConstructionCollision(int x, int y)
{
    for (int j = 0; j < buildings.size(); j++) //check for collision
    {
        if (buildings[j]->Alive())
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
        if (goldMines[j]->Alive())
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
}

void Environment::alertNoHousing(){
    overpopulated = true;
    brokeTime = SDL_GetTicks();
}

void Environment::createVillager(Building* passed_building, int unit) //creates new unit next to passed building
{
    if (unit == 1) // if human villager
    {
        characters.push_back(new Villager(sdl_setup, "images/Villager.png",passed_building->getStructureX() + passed_building->getStructureW(), passed_building->getStructureY() + passed_building->getStructureH()+20, MouseX, MouseY, this));
        humanPop++;
    } else
    {
        characters.push_back(new OrcVillager(sdl_setup, "images/orcVillager.png",passed_building->getStructureX() + passed_building->getStructureW(), passed_building->getStructureY() + passed_building->getStructureH()+20, MouseX, MouseY, this));
        orcPop++;
    }
}

void Environment::createMilitia(Building* passed_building, int unit)
{
    if (unit == 1) //if human militia
    {
        characters.push_back(new Militia(sdl_setup, "images/Militia.png",passed_building->getStructureX() + passed_building->getStructureW(), passed_building->getStructureY() + passed_building->getStructureH()+20, MouseX, MouseY, this));
        humanPop++;
    } else
    {
        characters.push_back(new OrcMilitia(sdl_setup, "images/orcMilitia.png",passed_building->getStructureX() + passed_building->getStructureW(), passed_building->getStructureY() + passed_building->getStructureH()+20, MouseX, MouseY, this));
        orcPop++;
    }
}

void Environment::createChampion(Building* passed_building, int unit)
{
    if (unit == 3) //if human champion
    {
        characters.push_back(new Champion(sdl_setup, "images/Champion.png",passed_building->getStructureX() + passed_building->getStructureW(), passed_building->getStructureY() + passed_building->getStructureH()+20, MouseX, MouseY, this));
        humanPop++;
    } else
    {
        characters.push_back(new OrcChampion(sdl_setup, "images/orcChampion.png",passed_building->getStructureX() + passed_building->getStructureW(), passed_building->getStructureY() + passed_building->getStructureH()+20, MouseX, MouseY, this));
        orcPop++;
    }
}


void Environment::createHouse(int x, int y)
{
    buildings.push_back(new House(sdl_setup, "images/collision_rectangle.png", x, y, 50, 50, 2, this)); //initially display construction zone
}

void Environment::createBarracks(int x, int y)
{
    buildings.push_back(new Barracks(sdl_setup, "images/collision_rectangle.png", x, y, 75, 75, 2, this)); //initially display construction zone
}

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

std::string Environment::timeHandler(int time){

    int mins = floor((int)(time/60));
    int secs = time-mins*60;
    return "Time: "+ std::to_string(mins) +":" +std::to_string(secs);


}
