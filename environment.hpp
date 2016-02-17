#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "imports.hpp"
#include <vector>

#include "sprite.hpp"
#include "sdl_setup.hpp"
#include "gold.hpp"
#include "building.hpp"


class Environment
{
    public:
        Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY);
        ~Environment();

        void DrawBack();

        void Update();

        std::vector<Building*> getBuildings() { return buildings; }
        std::vector<Gold*> getGoldMines() { return goldMines; }

    private:

        int *MouseX;
        int *MouseY;

        SDL_Setup* sdl_setup;
        Sprite* grass[21][16];
        std::vector<Gold*> goldMines;
        std::vector<Building*> buildings;
};

#endif // ENVIRONMENT_H
