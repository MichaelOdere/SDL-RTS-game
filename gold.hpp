#ifndef GOLD_HPP
#define GOLD_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "environment.hpp"

class Environment;

class Gold
{
    public:
        Gold(SDL_Setup* sdl_setup, int x, int y, Environment* passed_environment);
        ~Gold();

        void DrawGold();

        bool Mining();

        float GetResources() { return resources; }

        Sprite* GetGold() { return Mine; }

        int getGoldX();
        int getGoldY();
        int getGoldW();
        int getGoldH();

        bool alive;

        bool Alive() { return alive; }

        void Update();

        void setSelected() { selected = true; }
        void unSelect() { selected = false; }

        bool selected;

        float resources;
        float max_resources;

    private:
        Sprite* Mine;
        Environment* environment;

};

#endif // GOLD_HPP
