#ifndef MAIN_HPP
#define MAIN_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "character.hpp"
#include "environment.hpp"
#include "submenu.hpp"
#include "ai.hpp"

class Environment;
class AI;

class Main
{
public:
    Main();
    ~Main();

    void GameLoop();
    double GetDistance(int x1, int y1, int x2, int y2);
    void endGame(int loser);

private:

    Character *unit;
    Environment* gameMap;
    SubMenu *optionsMenu;
    bool quit;
    bool start;
    bool quitEarly;
    AI* ai;
    Sprite* grass;
    Sprite* orcVictory;
    Sprite* humanVictory;
    bool showMenu;
    int menuType;
    SDL_Setup* sdl_setup;
    int MouseX;
    int MouseY;
};


#endif // MAIN_HPP
