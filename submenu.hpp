
#ifndef SUBMENU_HPP_INCLUDED
#define SUBMENU_HPP_INCLUDED
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include <math.h>
#include "building.hpp"
#include <vector>

class SubMenu
{
public:
    SubMenu(SDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, int kind);
    ~SubMenu();

    void Update(int kind);
    void Draw();
    void DrawOptions();
    void UpdateType(int type);

private:

    int *MouseX;
    int *MouseY;
    
    int type;
    
    std::vector<char> options;
    std::vector<Sprite*> sprites;

    SDL_Setup* sdl_setup;

    Sprite* bar;

    int timeCheck;


};


#endif // CHARACTER_HPP_INCLUDED
