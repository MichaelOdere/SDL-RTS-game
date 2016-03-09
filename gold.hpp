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
        Gold(SDL_Setup* sdl_setup, SDL_Texture* passed_image, int x, int y, Environment* passed_environment);
        ~Gold();

        void DrawGold();
        bool Mining();
        float GetResources() { return resources; }
        Sprite* GetGold() { return Mine; }
        int getGoldX();
        int getGoldY();
        int getGoldW();
        int getGoldH();
        bool isAlive() { return alive; }
        void Update();
        void setSelected() { selected = true; }
        void unSelect() { selected = false; }

        bool selected;

    private:
        Sprite* Mine;
        Environment* environment;
        float resources;
        float max_resources;
        bool alive;

};

#endif // GOLD_HPP
