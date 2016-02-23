#include "environment.hpp"
#include "villager.hpp"
#include "militia.hpp"
#include "champion.hpp"
#include "TownCenter.h"
#include "barracks.h"

Environment::Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY, SubMenu* passed_menu)
{
    sdl_setup = passed_sdl_setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    optionsMenu = passed_menu;

    showMenu = false;//start with menu not displayed
    optionsMenu->UpdateType(1);// 1 is main menu

    resources = 100;

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            grass[i][j] = new Sprite(sdl_setup->GetRenderer(), "images/grass.bmp", i*50, j*50, 50, 50, CollisionRectangle(0,0,0,0)); //map, currently tiled, will eventually be one big grass tile
        }
    }


    selectedCharacter = new Militia(sdl_setup, "images/militia.png", 300, 150, MouseX, MouseY, this); //game begins with villager selected to avoid error of deselecting an unselected character below
    selectedCharacter->unSelect();
    characters.push_back(selectedCharacter);
    characters.push_back(new Champion(sdl_setup, "images/champion.png", 350, 150, MouseX, MouseY, this)); // "this" is instance of current class
    characters.push_back(new Villager(sdl_setup, "images/villager.png", 400, 150, MouseX, MouseY, this)); // "this" is instance of current class
    characters.push_back(new Villager(sdl_setup, "images/villager.png", 450, 150, MouseX, MouseY, this)); // "this" is instance of current class

    selectedBuilding = new Building(sdl_setup, "images/house.png", 200, 200);
    selectedBuilding->unSelect();
    buildings.push_back(selectedBuilding);
    buildings.push_back(new Building(sdl_setup, "images/house.png", 300, 200));
    buildings.push_back(new TownCenter(sdl_setup, "images/towncenter.png", 400, 400));
    buildings.push_back(new Barracks(sdl_setup, "images/barracks.png", 300, 300));


    selectedGold = new Gold(sdl_setup, 50, 50);
    selectedGold->unSelect();
    goldMines.push_back(selectedGold);
    goldMines.push_back(new Gold(sdl_setup, 600, 200));
    goldMines.push_back(new Gold(sdl_setup, 550, 500));
    goldMines.push_back(new Gold(sdl_setup, 720, 100));
}

Environment::~Environment()
{
    delete optionsMenu;

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            delete grass[i][j];
            //delete grass;
        }
    }
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
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            grass[i][j]->Draw();
        }
    }

    for (std::vector<Gold*>::iterator i = goldMines.begin(); i != goldMines.end(); ++i)
    {
        (*i)->DrawGold();
    }

    for (std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
        (*i)->DrawBuilding();
    }

        for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i)
    {
        (*i)->Draw();
    }
}

void Environment::AddResources()
{
    resources = resources + 0.005;
}

void Environment::Update()
{
    if(showMenu){
        optionsMenu->Draw();
        optionsMenu->Update();
    }

    for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i)
    {
        (*i)->Update();
    }

    for (std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i)
    {
        (*i)->Update();
    }

    for (std::vector<Gold*>::iterator i = goldMines.begin(); i != goldMines.end(); ++i)
    {
        (*i)->Update();
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

                    if(optionsMenu->getType() == 2){
                        optionsMenu->UpdateType(1);
                    }else{
                        optionsMenu->UpdateType(2);
                    }

                    break;
                }
                selectedBuilding->unSelect();
            }

            for(std::vector<Gold*>::iterator i = goldMines.begin(); i != goldMines.end(); ++i){
                if(*MouseX >= ((*i)->getGoldX()) && *MouseX <= ((*i)->getGoldX()+(*i)->getGoldW()) && *MouseY >= ((*i)->getGoldY()) && *MouseY <= ((*i)->getGoldY()+(*i)->getGoldH()))
                {
                    selectedGold->unSelect(); //unselect previously selected
                    (*i)->setSelected();
                    selectedGold = (*i); //reassign selected gold mine for future deselection
                    break;
                }
                selectedGold->unSelect();
            }

            for (std::list<Character*>::iterator i = characters.begin(); i != characters.end(); ++i) //character selection takes priority over buildings and gold mines
            {
                if(*MouseX >= ((*i)->getCharacterX()-15) && *MouseX <= ((*i)->getCharacterX()+(*i)->getCharacterW()-15) && *MouseY >= ((*i)->getCharacterY()-20) && *MouseY <= ((*i)->getCharacterY()+(*i)->getCharacterH()-20))
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

            //if((showMenu && (*MouseY > optionsMenu->getY())) || (showMenu == false)){

            if(optionsMenu->getWhatToMake()== 1){
                if(resources>=optionsMenu->getOpCost()){
                    PrintResources();
                    buildings.push_back(new Building(sdl_setup, "images/house.png", *MouseX-50, *MouseY-50));
                    resources = resources - optionsMenu->getOpCost();
                    PrintResources();
                }else{
                    //alert insufficient funds
                    PrintResources();
                }
            }else if(optionsMenu->getWhatToMake() == 2){
                if(resources>=optionsMenu->getOpCost()){
                    PrintResources();
                    characters.push_back(new Character(sdl_setup, "images/villager.png",*MouseX-50, *MouseY-50, MouseX, MouseY, this));
                    resources = resources - optionsMenu->getOpCost();
                    PrintResources();
                }else{
                    //alert insufficient funds
                }

            }
            }
        }
    }

    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){
       // if(sdl_setup->GetEv()->button.button == SDLK_SPACE){
            if(showMenu){
                showMenu = false;
            }else{
                showMenu = true;
            }
        //}
    }
}


