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

Environment::Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY, SubMenu* passed_menu, AI* passed_ai)
{
    sdl_setup = passed_sdl_setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    optionsMenu = passed_menu;
    ai = passed_ai;


    txt = new TextMessage(sdl_setup->GetRenderer(), "hi, I'm here", 500, 300);

    showMenu = false;//start with menu not displayed
    optionsMenu->UpdateType(1);// 1 is main menu

    resources = 1000;
    orcResources = 1000;

    team = 1;

    humanPop = 5;
    orcPop = 5;
    humanMaxPop = 10;
    orcMaxPop = 10;

    //Humans
    selectedCharacter = new Militia(sdl_setup, "images/militia.png", 300, 150, MouseX, MouseY, this); //game begins with villager selected to avoid error of deselecting an unselected character below
    selectedCharacter->unSelect();
    characters.push_back(selectedCharacter);
    characters.push_back(new Villager(sdl_setup, "images/villager.png", 200, 150, MouseX, MouseY, this));
    characters.push_back(new Villager(sdl_setup, "images/villager.png", 250, 150, MouseX, MouseY, this));
    characters.push_back(new Militia(sdl_setup, "images/militia.png", 350, 150, MouseX, MouseY, this));
    characters.push_back(new Champion(sdl_setup, "images/Champion.png", 400, 150, MouseX, MouseY, this));

    //Orcs
    characters.push_back(new OrcChampion(sdl_setup, "images/orcChampion.png", 600, 150, MouseX, MouseY, this)); // "this" is instance of current class
    characters.push_back(new OrcVillager(sdl_setup, "images/orcVillager.png", 500, 150, MouseX, MouseY, this));
    characters.push_back(new OrcVillager(sdl_setup, "images/orcVillager.png", 550, 150, MouseX, MouseY, this));
    characters.push_back(new OrcMilitia(sdl_setup, "images/orcMilitia.png", 650, 150, MouseX, MouseY, this));
    characters.push_back(new OrcMilitia(sdl_setup, "images/orcMilitia.png", 700, 150, MouseX, MouseY, this));


    selectedBuilding = new TownCenter(sdl_setup, "images/towncenter.png", 100, 200, 140, 120, 1, this);
    selectedBuilding->unSelect();
    buildings.push_back(selectedBuilding);
    //buildings.push_back(new House(sdl_setup, "images/house.png", 900, 200, 50, 50, 2));
    //buildings.push_back(new House(sdl_setup, "images/house.png", 300, 200, 50, 50, 1));
    buildings.push_back(new TownCenter(sdl_setup, "images/towncenter.png", 700, 200, 140, 120, 2, this));
    //buildings.push_back(new Barracks(sdl_setup, "images/barracks.png", 300, 300, 75, 75, 1));
    //buildings.push_back(new Barracks(sdl_setup, "images/barracks.png", 700, 350, 75, 75, 2));


    selectedGold = new Gold(sdl_setup, 50, 50);
    selectedGold->unSelect();
    goldMines.push_back(selectedGold);
    goldMines.push_back(new Gold(sdl_setup, 150, 50));
    goldMines.push_back(new Gold(sdl_setup, 600, 200));
    goldMines.push_back(new Gold(sdl_setup, 550, 500));
    goldMines.push_back(new Gold(sdl_setup, 720, 100));
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
    resources = resources + 0.005;
    } else
    {
    orcResources = orcResources + 0.005;
    }
}

void Environment::Update()
{
    txt->Draw();

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
                    if(resources>=optionsMenu->getOpCost() && humanPop < humanMaxPop){ //if enough resources and population room
                        resources = resources - optionsMenu->getOpCost(); //remove resources
                        selectedBuilding->startCreating(1); //initiate creation of unit (10 sec, multiple units may be queued)
                    }else{
                        //alert insufficient funds
                    }
                    optionsMenu->buttonPressed = false;
                }
            } else { //orc towncenter
                if(optionsMenu->getWhatToMake() == 4){ //if orc villager selected
                    //make orc villager next to towncenter
                    if(orcResources>=optionsMenu->getOpCost()  && orcPop < orcMaxPop){
                        orcResources = orcResources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(2);
                    }else{
                        //alert insufficient funds
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
                    if(resources>=optionsMenu->getOpCost() && humanPop < humanMaxPop){
                        resources = resources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(1);
                    }else{
                        //alert insufficient funds
                    }
                    optionsMenu->buttonPressed = false;
                }else if(optionsMenu->getWhatToMake() == 7){
                    //make champion next to barracks
                    if(resources>=optionsMenu->getOpCost() && humanPop < humanMaxPop){
                        resources = resources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(3);
                    }else{
                        //alert insufficient funds
                    }
                    optionsMenu->buttonPressed = false;
                }
            } else { //orc barracks
                if(optionsMenu->getWhatToMake() == 6){
                    //make orc militia next to barracks
                    if(orcResources>=optionsMenu->getOpCost() && orcPop < orcMaxPop){
                        orcResources = orcResources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(2);
                    }else{
                        //alert insufficient funds
                    }
                    optionsMenu->buttonPressed = false;
                }else if(optionsMenu->getWhatToMake() == 8){
                    //make champion next to barracks
                    if(orcResources>=optionsMenu->getOpCost()  && orcPop < orcMaxPop){
                        orcResources = orcResources - optionsMenu->getOpCost();
                        selectedBuilding->startCreating(4);
                    }else{
                        //alert insufficient funds
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
                    }
                } else {
                    if(orcResources >= optionsMenu->getOpCost()){
                        buildings.push_back(new House(sdl_setup, "images/collision_rectangle.png", *MouseX-50, *MouseY-50, 50, 50, 2, this));
                        orcResources = orcResources - optionsMenu->getOpCost();
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
    return false;
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




