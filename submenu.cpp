#include "submenu.hpp"
#include "main.hpp"
#include <math.h>
#include "sprite.hpp"



SubMenu::SubMenu(SDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, int kind) //Constructor
{

    sdl_setup = passed_SDL_Setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;


    bar = new Sprite(sdl_setup->GetRenderer(), "images/optionsmenu.png", 0, 400, 1024, 300, CollisionRectangle(0,0,1024,300));

    timeCheck = SDL_GetTicks();
    type = kind;
}

SubMenu::~SubMenu() //Destructor
{
    delete bar;
}

void SubMenu::Draw()
{
    bar->Draw();
    DrawOptions();
}

void SubMenu::DrawOptions(){
    for(int j = 0; j < sprites.size(); j++){
        sprites[j]->Draw();
    }
}

void SubMenu::UpdateType(int kind){
    if(type!=kind){
        type = kind;

        if(type==1){//barracks
            options.push_back('c');//will push Option type soon
            options.push_back('a');
            options.push_back('c');
        }

        for( int i = 0; i < options.size(); i++){
            if(options[i] == 'c'){
                sprites.push_back(new Sprite(sdl_setup->GetRenderer(), "images/house.png", (i*300), 400, 300, 300, CollisionRectangle(0,0,300,300)));
            }else if(options[i] == 'a'){
                sprites.push_back(new Sprite(sdl_setup->GetRenderer(), "images/villager.png", (i*300), 400, 300, 300, CollisionRectangle(0,0,300,300)));
            }
        }
    }
}

void SubMenu::Update(int kind)
{
    if (sdl_setup->GetEv()->type == SDL_MOUSEBUTTONDOWN) //mouse button clicked
    {
        if (sdl_setup->GetEv()->button.button == SDL_BUTTON_LEFT) //specifically, the left mouse button
        {

        }
    }
}
