#ifndef BUILDING_HPP
#define BUILDING_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "environment.hpp"

class Environment;

class Building
{
    public:
        Building(SDL_Setup* sdl_setup, std::string FilePath, int x, int y, int size_x, int size_y, int passed_team, Environment* passed_environment);
        Building() {}
        ~Building();

        Sprite* GetBuilding() { return Structure; }
        void SetBuilding();

        virtual void Update();
        void DrawBuilding();

        int team;

        int getMenuType() {return menuType;}
        int getTeam() { return team; }
        void Select();

        Building* target;

        int getStructureX();
        int getStructureY();
        int getStructureW();
        int getStructureH();

        float health;
        float max_health;
        float attack;

        void attacked(float attacker_attack);

        void setSelected() { selected = true; }
        void unSelect() { selected = false; }

        bool Alive() { return alive; }

        bool selected;

        bool alive;

        int menuType;

        bool creating;
        virtual void startCreating(int unit_to_create) {}
        bool Creating() { return creating; }
        Environment* environment;

        int unit;

        int type;

        int getType() { return type; }

        float previous_health;

        bool constructed;

        bool isConstructed() { return constructed; }

        virtual void constructing();

        Sprite* Structure;

};

#endif // BUILDING_HPP
