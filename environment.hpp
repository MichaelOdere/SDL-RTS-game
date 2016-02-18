#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H
#include "imports.hpp"
#include <vector>
#include <list>

#include "sprite.hpp"
#include "sdl_setup.hpp"
#include "gold.hpp"
#include "building.hpp"
#include "character.hpp"

class Character; //avoids error because Environment includes Character and vice versa

class Environment
{
    public:
        Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY);
        ~Environment();

        void DrawBack();

        void Update();
        int getMenuType();
        bool shouldMenu();

        std::vector<Building*> getBuildings() { return buildings; }
        std::vector<Gold*> getGoldMines() { return goldMines; }

        void AddResources();

        void PrintResources() { std::cout << resources << std::endl; } //prints to command line, for testing only

        float resources;
        Character* selectedCharacter;

    private:

        int *MouseX;
        int *MouseY;

        int menuType;
        bool showMenu;

        SDL_Setup* sdl_setup;
        Sprite* grass[21][16];
        std::vector<Gold*> goldMines;
        std::vector<Building*> buildings;
        std::list<Character*> characters;

};

#endif // ENVIRONMENT_H
