#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "character.hpp"
#include "environment.hpp"
#include "submenu.hpp"

class Main
{
public:
    Main();
    ~Main();

    void GameLoop();

    double GetDistance(int x1, int y1, int x2, int y2);

private:

    Character *unit;

    Environment* gameMap;
    SubMenu *optionsMenu;
    bool quit;
    bool showMenu;

    int menuType;

    Sprite* grass[21][16];

    SDL_Setup* sdl_setup;

    int MouseX;
    int MouseY;
};


#endif // MAIN_HPP_INCLUDED
