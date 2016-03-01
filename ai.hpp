#ifndef AI_HPP
#define AI_HPP
#include "imports.hpp"
//#include "environment.hpp"
#include "building.hpp"
#include "character.hpp"
#include "gold.hpp"
#include "menuoption.hpp"
#include "sprite.hpp"
#include "sdl_setup.hpp"
#include <vector>
#include <list>

class Environment;

class AI
{
    public:
        AI();
        ~AI();

        void updateCharacter(Character* character);
        void updateBuilding(Building* building);

        std::list<Character*> characters;
        std::vector<Building*> buildings;
        std::vector<Gold*> goldMines;

    private:
        int team;
        Environment* environment;

};

#endif // AI_HPP
