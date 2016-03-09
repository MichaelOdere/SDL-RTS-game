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
    buttonPressed = false;

    //Buttons
    newHouse = MenuOption(1,100, "images/house.png", false);
    newBarracks = MenuOption(2,250, "images/barracks.png", false);
    newVillager = MenuOption(3, 50, "images/villagerButton.png", true);
    newMilitia = MenuOption(5, 50, "images/militiaButton.png", true);
    newChampion = MenuOption(7, 150, "images/championButton.png", true);

    //Menu Options
    villagerOptions.push_back(newHouse);
    villagerOptions.push_back(newBarracks);
    TownCenterOptions.push_back(newVillager);
    barracksOptions.push_back(newMilitia);
    barracksOptions.push_back(newChampion);

    bar = new Sprite(sdl_setup->GetRenderer(), "images/optionsmenu.png", 0, 675, 1024, 100, CollisionRectangle(0,0,1024,100));

    //Sprite menus
    main = newMenu(mainOptions);
    house = newMenu(houseOptions);
    barracks = newMenu(barracksOptions);
    villager = newMenu(villagerOptions);
    townCenter = newMenu(TownCenterOptions);
    displayed = main;

    type = kind;
}

SubMenu::~SubMenu() //Destructor
{
    delete bar;
    delete MouseX;
    delete MouseY;

    for(int i = 0; i < main.size(); i++){
        delete main[i];
    }
    main.clear();
    for(int i = 0; i < house.size(); i++){
        delete house[i];
    }
    house.clear();
    for(int i = 0; i < townCenter.size(); i++){
        delete townCenter[i];
    }
    townCenter.clear();
    for(int i = 0; i < villager.size(); i++){
        delete villager[i];
    }
    villager.clear();
    for(int i = 0; i < barracks.size(); i++){
        delete barracks[i];
    }
    barracks.clear();
    for(int i = 0; i < displayed.size(); i++){
        delete displayed[i];
    }
    displayed.clear();
}

void SubMenu::Draw() //display menu bar and buttons
{
    bar->Draw();
    DrawOptions();
}

void SubMenu::DrawOptions(){ //display each button in menu
    for(int j = 0; j < options.size(); j++){
        displayed[j]->Draw();
    }

}

void SubMenu::UpdateType(int kind){// if different item is selected, a different menu is displayed
    if(type!=kind){
        type = kind;
        opSelected = false;

        if(type==1){//main menu
            options = mainOptions;
            displayed = main;
        }else if(type ==2){// house selected
            options = houseOptions;
            displayed = house;
        }else if(type ==3){
            options = villagerOptions; //villager selected
            displayed = villager;
        }else if(type == 4){
            options = TownCenterOptions; //town center selected
            displayed = townCenter;
        } else if(type == 5) {
            options = barracksOptions; //barracks selected
            displayed = barracks;
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
                if(*MouseX>displayed[i]->GetX() && *MouseX<(displayed[i]->GetX()+displayed[i]->GetWidth()) && *MouseY>displayed[i]->GetY() && *MouseY<(displayed[i]->GetY()+displayed[i]->GetHeight()))
                {
                    if(options[i].selected){
                        options[i].selected = false;
                        opSelected = false;
                    }else{
                        options[i].selected = true;
                        opSelected = true;
                        options[selectedI].selected = false;
                        selectedI = i;
                        if(options[i].isButton){
                            buttonPressed = true;
                        }
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

std::vector<Sprite*> SubMenu::newMenu(std::vector<MenuOption> passed_options) //create vector of sprites for each menu
{
    std::vector<Sprite*> result;
    for( int i = 0; i < passed_options.size(); i++){
        result.push_back(new Sprite(sdl_setup->GetRenderer(), passed_options[i].getPic(), (i*100), 675, 100, 100, CollisionRectangle(0,0,100,100)));
    }
    return result;
}
