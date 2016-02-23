#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "imports.hpp"
#include <vector>
#include <list>
#include "sprite.hpp"
#include "sdl_setup.hpp"
#include "gold.hpp"
#include "building.hpp"
#include "submenu.hpp"

class Character; //avoids error because Environment includes Character and vice versa

class Environment
{
    public:
        Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY, SubMenu* passed_menu);
        ~Environment();

        void DrawBack();

        void Update();

        int getMenuType();
        void updateWhatToMake(int what);
        void updateCost(int n);
        bool shouldMenu();

        std::vector<Building*> getBuildings() { return buildings; }
        std::vector<Gold*> getGoldMines() { return goldMines; }
        std::list<Character*> getCharacters() { return characters; }

        void AddResources();

        void PrintResources() { std::cout << resources << std::endl; } //prints to command line, for testing only

        float resources;
        Character* selectedCharacter;
        Building* selectedBuilding;
        Gold* selectedGold;

    private:

        SubMenu* optionsMenu;

        int *MouseX;
        int *MouseY;

        int menuType;
        int whatToMake;
        bool showMenu;

        SDL_Setup* sdl_setup;
        Sprite* grass[21][16];
        std::vector<Gold*> goldMines;
        std::vector<Building*> buildings;
        std::list<Character*> characters;

};

#endif // ENVIRONMENT_HPP
