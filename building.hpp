#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
//#include <math.h>

class Building
{
    public:
        Building(SDL_Setup* sdl_setup, std::string FilePath, int x, int y);
        Building() {}
        ~Building();

        Sprite* GetBuilding() { return Structure; }
        void SetBuilding();

        virtual void Update();
        void DrawBuilding();

        int getTeam() { return team; }
        void Select();

        Building* target;

        int getStructureX();
        int getStructureY();
        int getStructureW();
        int getStructureH();

        int team;
        float health;
        float max_health;
        float attack;

        void attacked(float attacker_attack);

        void setSelected() { selected = true; }
        void unSelect() { selected = false; }

        bool isAlive() { return alive; }

        bool Alive() { return alive; }

        bool selected;

        bool alive;

    private:
        Sprite* Structure;
};

#endif // BUILDING_HPP
