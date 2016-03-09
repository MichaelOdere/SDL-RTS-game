#ifndef AI_HPP
#define AI_HPP
#include "imports.hpp"
#include "building.hpp"
#include "character.hpp"
#include "gold.hpp"
#include "menuoption.hpp"
#include "sprite.hpp"
#include "sdl_setup.hpp"
#include <vector>
#include <list>
#include <algorithm>

class Environment;
class Character;
class Building;
class Gold;

class AI
{
    public:
        AI();
        ~AI();

        void updateCharacter(Character* character);
        void updateBuilding(Building* building);
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
        void goldMineDepleted(int gold_x, int gold_y);
        void buildingNotConstructing(int structure_x, int structure_y);
        void addEnemy(Character* enemy) { if(std::find(enemies.begin(), enemies.end(), enemy) == enemies.end()) { enemies.push_back(enemy); } }

    private:
        int team;
        int villagerPop;
        int militiaPop;
        int championPop;
        int buildX;
        int buildY;
        int houses;
        int barracks;
        int idle_x;
        int idle_y;
        bool buildingHouse;
        bool buildingBarracks;
        Environment* environment;
        void setBuildArea();
        bool notConstructing1;
        bool notConstructing2;
        bool barracksConstructionInitiated;
        int struct_x;
        int struct_y;
        int militiaCreations;
        std::vector<Character*> enemies;
        Character* enemy_target;
        Character* villagerDefender;

};

#endif // AI_HPP
