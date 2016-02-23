#ifndef GOLD_HPP
#define GOLD_HPP
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

        int getGoldX();
        int getGoldY();
        int getGoldW();
        int getGoldH();

        void Update();

        void setSelected() { selected = true; }
        void unSelect() { selected = false; }

        bool selected;

    private:
        Sprite* Mine;
        float resources;
};

#endif // GOLD_HPP
