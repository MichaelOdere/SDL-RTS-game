#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "sprite.hpp"
#include "sdl_setup.hpp"

//currently not used
class Environment
{
    public:
        Environment(SDL_Setup* sdl_setup);
        ~Environment();

        void DrawBack(); //to be implemented
        void DrawFront(); //to be implemented

    private:
        Sprite* grass[21][16];
};

#endif // ENVIRONMENT_H
