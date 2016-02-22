#ifndef SUBMENU_HPP
#define SUBMENU_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
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

    int getType();
    int getWhatToMake();
    int getOpCost();

    bool opSelected;

private:

    int *MouseX;
    int *MouseY;

    int type;

    std::vector<MenuOption> mainOptions;//options presented with nothing selected
    std::vector<MenuOption> houseOptions;//options presented with a house selected

    MenuOption newHouse; //option to build a new house
    MenuOption newCharacter; // option to build a new character

    std::vector<MenuOption> options; //the options
    std::vector<Sprite*> sprites; //corresponding sprites for options

    SDL_Setup* sdl_setup;

    Sprite* bar;

    int selectedI;//index of selected option



};


#endif // SUBMENU_HPP
