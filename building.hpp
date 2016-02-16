#ifndef BUILDING_HPP_INCLUDED
#define BUILDING_HPP_INCLUDED
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"

class Building
{
    public:
        Building(SDL_Setup* sdl_setup, int x, int y);
        ~Building();

        void DrawBuilding();

    private:
        Sprite* Structure;
};

#endif // BUILDING_HPP_INCLUDED
