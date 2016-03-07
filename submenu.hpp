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
    int getY();
    bool opSelected;
    bool buttonPressed;

private:

    int *MouseX;
    int *MouseY;
    int type;
    std::vector<MenuOption> mainOptions;//options presented with nothing selected
    std::vector<MenuOption> houseOptions;//options presented with a house selected
    std::vector<MenuOption> villagerOptions;//options presented with a character selected
    std::vector<MenuOption> TownCenterOptions;//options presented with a town center selected
    std::vector<MenuOption> barracksOptions;//options presented with a barracks selected
    MenuOption newHouse; //option to build a new house
    MenuOption newVillager;
    MenuOption newOrcVillager;
    MenuOption newChampion;
    MenuOption newOrcChampion;
    MenuOption newMilitia;
    MenuOption newOrcMilitia;
    MenuOption newBarracks;
    std::vector<MenuOption> options; //the options
    std::vector<Sprite*> displayed;
    std::vector<Sprite*> main;
    std::vector<Sprite*> house;
    std::vector<Sprite*> barracks;
    std::vector<Sprite*> villager;
    std::vector<Sprite*> townCenter;
    SDL_Setup* sdl_setup;
    Sprite* bar;
    int selectedI;//index of selected option
    std::vector<Sprite*> newMenu(std::vector<MenuOption> passed_options);
};


#endif // SUBMENU_HPP
