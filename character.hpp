
#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include <math.h>

class Character
{
public:
    Character(SDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY);
    ~Character();

    double GetDistance(int x1, int y1, int x2, int y2);

    void Update();
    void Draw();

private:

    int *MouseX;
    int *MouseY;

    SDL_Setup* sdl_setup;

    Sprite* unit;

    int timeCheck;

    bool follow;
    int follow_point_x;
    int follow_point_y;

    float angle;

    float distance;
    bool stopAnimation;

};


#endif // CHARACTER_HPP_INCLUDED
