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

        bool Mining();

        float GetResources() { return resources; }

        Sprite* GetGold() { return Mine; }

    private:
        Sprite* Mine;
        float resources;
};

#endif // GOLD_HPP_INCLUDED
