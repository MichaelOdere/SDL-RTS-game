#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "character.hpp"
#include "environment.hpp"

class Main
{
public:
    Main();
    ~Main();

    void GameLoop();

    double GetDistance(int x1, int y1, int x2, int y2);

private:

    Character *unit;

    Environment* grassArea;
    bool quit;

    Sprite* grass[21][16];

    SDL_Setup* sdl_setup;

    int MouseX;
    int MouseY;
};


#endif // MAIN_HPP_INCLUDED
