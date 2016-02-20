
#ifndef SUBMENU_HPP_INCLUDED
#define SUBMENU_HPP_INCLUDED
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include <math.h>
#include "building.hpp"
#include "menuoption.hpp"
#include <vector>

class SubMenu
{
public:
    SubMenu(SDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, int kind);
    ~SubMenu();

    void Update();
    void Draw();
    void DrawOptions();
    void UpdateType(int type);
    
    int getWhatToMake();
    
    bool opSelected;

private:

    int *MouseX;
    int *MouseY;

    int type;
    
    std::vector<MenuOption> mainOptions;
    std::vector<MenuOption> houseOptions;
    
    MenuOption newHouse;
    MenuOption newCharacter;

    std::vector<MenuOption> options;
    std::vector<Sprite*> sprites;

    SDL_Setup* sdl_setup;

    Sprite* bar;

    int selectedI;
    


};


#endif // CHARACTER_HPP_INCLUDED
