#include "environment.hpp"

Environment::Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY)
{
    sdl_setup = passed_sdl_setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;

    showMenu = false;
    menuType = 1;

    resources = 100;

    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            grass[i][j] = new Sprite(sdl_setup->GetRenderer(), "images/grass.bmp", i*50, j*50, 50, 50, CollisionRectangle(0,0,0,0)); //map, currently tiled, will eventually be one big grass tile
        }
    }

    selectedCharacter = new Character(sdl_setup, "images/villager.png", 300, 150, MouseX, MouseY, this); //game begins with villager selected to avoid error of deselecting an unselected character below
    selectedCharacter->unSelect();
    characters.push_back(selectedCharacter);
    characters.push_back(new Character(sdl_setup, "images/villager.png", 350, 150, MouseX, MouseY, this)); // "this" is instance of current class

    selectedBuilding = new Building(sdl_setup, "images/house.png", 200, 200);
    selectedBuilding->unSelect();
    buildings.push_back(selectedBuilding);
    buildings.push_back(new Building(sdl_setup, "images/house.png", 300, 200));

    selectedGold = new Gold(sdl_setup, 50, 50);
    selectedGold->unSelect();
    goldMines.push_back(selectedGold);
    goldMines.push_back(new Gold(sdl_setup, 600, 200));
    goldMines.push_back(new Gold(sdl_setup, 550, 500));
    goldMines.push_back(new Gold(sdl_setup, 720, 100));



}

Environment::~Environment()
{
    for (int i = 0; i < 21; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            delete grass[i][j];
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

int Environment::getMenuType()
{
    return menuType;
}

bool Environment::shouldMenu()
{
    return showMenu;
}

void Environment::Update()
{

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

            for(std::vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); ++i){
                if(*MouseX >= ((*i)->getStructureX()) && *MouseX <= ((*i)->getStructureX()+(*i)->getStructureW()) && *MouseY >= ((*i)->getStructureY()) && *MouseY <= ((*i)->getStructureY()+(*i)->getStructureH()))
                {
                    selectedBuilding->unSelect(); //unselect previously selected
                    (*i)->setSelected();
                    selectedBuilding = (*i); //reassign selected building for future deselection
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
            //buildings.push_back(new Building(sdl_setup, "images/house.png", *MouseX-50, *MouseY-50)); //testing
            //characters.push_back(new Character(sdl_setup, "images/villager.png", MouseX, MouseY, this)); //testing
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


