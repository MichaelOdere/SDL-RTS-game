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
class Character;
class Building;

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

        void setEnvironment(Environment* passed_environment);
        void notBuildingHouse() { buildingHouse = false; houses++; }
        void notBuildingBarracks() { buildingBarracks = false; barracks++;}
        void barracksDestroyed() { barracks--; }
        void addVillager() { villagerPop++; }
        void addMilitia() { militiaPop++; }
        void addChampion() { championPop++; }
        void removeVillager() { villagerPop--; }
        void removeMilitia() { militiaPop--; }
        void removeChampion() { championPop--; }

    private:
        int team;
        int villagerPop;
        int militiaPop;
        int championPop;
        int buildX;
        int buildY;
        int houses;
        int barracks;
        bool buildingHouse;
        bool buildingBarracks;
        Environment* environment;
        void setBuildArea();

};

#endif // AI_HPP
