#ifndef GOLD_HPP_INCLUDED
#define GOLD_HPP_INCLUDED
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"

class Gold
{
    public:
        Gold(SDL_Setup* sdl_setup, int x, int y);
        ~Gold();

        void DrawGold();

    private:
        Sprite* Rock;
};

#endif // GOLD_HPP_INCLUDED
