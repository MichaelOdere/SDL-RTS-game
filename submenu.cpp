#include "submenu.hpp"
#include "main.hpp"
#include "sprite.hpp"



SubMenu::SubMenu(SDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, int kind) //Constructor
{

    sdl_setup = passed_SDL_Setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    
    selectedI = 0;
    opSelected = false;
    
    newHouse = MenuOption(1,100, "images/house.png");
    newCharacter = MenuOption(2,20, "images/villager.png");
    
    mainOptions.push_back(newHouse);//this is how i plan to build different menus, create options above and then populate separate lists for any item that can be selected
    mainOptions.push_back(newHouse);
    mainOptions.push_back(newHouse);
    
    houseOptions.push_back(newCharacter);
    houseOptions.push_back(newHouse);
    houseOptions.push_back(newCharacter);

    bar = new Sprite(sdl_setup->GetRenderer(), "images/optionsmenu.png", 0, 400, 1024, 300, CollisionRectangle(0,0,1024,300));

    type = kind;
}

SubMenu::~SubMenu() //Destructor
{
    delete bar;
    delete sdl_setup;
    delete MouseX;
    delete MouseY;
    
    for(int i = 0; i < sprites.size(); i++){
        delete sprites[i];
    }
}

void SubMenu::Draw()
{
    bar->Draw();
    DrawOptions();
}

void SubMenu::DrawOptions(){
    for(int j = 0; j < options.size(); j++){
        sprites[j]->Draw();
        if(options[j].selected){
            sprites[j]->DisplayRectangle();
        }
    }
    
}

void SubMenu::UpdateType(int kind){
    if(type!=kind){
        type = kind;
        
        options.clear();
        sprites.clear();
        for(int i = 0; i < sprites.size(); i++){
            delete sprites[i];
        }
        
        if(type==1){//main menu?
            options = mainOptions;
        }else if(type ==2){// house selected
            options = houseOptions;
        }

        for( int i = 0; i < options.size(); i++){
            sprites.push_back(new Sprite(sdl_setup->GetRenderer(), options[i].getPic(), (i*300), 400, 300, 300, CollisionRectangle(0,0,300,300)));
        }
        
    }
}

int SubMenu::getType(){
    return type;
}

int SubMenu::getY(){
    return bar->GetY();
}

void SubMenu::Update()
{
    if (sdl_setup->GetEv()->type == SDL_MOUSEBUTTONDOWN) //mouse button clicked
    {
        if (sdl_setup->GetEv()->button.button == SDL_BUTTON_LEFT) //specifically, the left mouse button
        {
            for(int i = 0; i < options.size(); i++){
                if(*MouseX>sprites[i]->GetX() && *MouseX<(sprites[i]->GetX()+sprites[i]->GetWidth()) && *MouseY>sprites[i]->GetY() && *MouseY<(sprites[i]->GetY()+sprites[i]->GetHeight()))
                {
                    if(options[i].selected){
                        options[i].selected = false;
                        opSelected = false;
                    }else{
                        options[i].selected = true;
                        opSelected = true;
                        options[selectedI].selected = false;
                        selectedI = i;
                    }
                }
            }
        }
    }
}

int SubMenu::getWhatToMake(){
    if(opSelected){
        return options[selectedI].getType();
    }else{
        return 0;
    }
}

int SubMenu::getOpCost(){
    if(opSelected){
        return options[selectedI].getCost();
    }else{
        return 0;
    }
}

