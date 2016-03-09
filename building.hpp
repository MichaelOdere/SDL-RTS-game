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
        Building(SDL_Setup* sdl_setup, SDL_Texture* passed_image, int x, int y, int size_x, int size_y, int passed_team, Environment* passed_environment);
        Building() {}
        ~Building();

        Sprite* GetBuilding() { return Structure; }
        void SetBuilding();
        virtual void Update();
        virtual void startCreating(int unit_to_create) {}
        virtual void constructing();
        void DrawBuilding();
        int getMenuType() {return menuType;}
        int getTeam() { return team; }
        void Select();
        int getStructureX();
        int getStructureY();
        int getStructureW();
        int getStructureH();
        void attacked(float attacker_attack);
        void setSelected() { selected = true; }
        void unSelect() { selected = false; }
        bool isAlive() { return alive; }
        bool Creating() { return creating; }
        int getType() { return type; }
        bool isConstructed() { return constructed; }

        bool constructed;
        bool selected;
        int menuType;
        bool creating;

    protected:

        Environment* environment;
        int team;
        Building* target;
        float health;
        float max_health;
        bool alive;
        int unit;
        int type;
        float previous_health;
        Sprite* Structure;

};

#endif // BUILDING_HPP
