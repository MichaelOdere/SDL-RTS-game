#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "building.hpp"
#include <math.h>

class Environment; //avoids error because Environment includes Character and vice versa
class Building;

class Character
{
    public:
        Character(SDL_Setup* passed_SDL_Setup, std::string FilePath, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment);
        Character() {}
        ~Character();

        int type;
        int getType() { return type; }

        double GetDistance(int x1, int y1, int x2, int y2);

        virtual void Update();
        void Draw();

        bool hasTask;
        void setNoTask() { hasTask = false; }
        bool ifHasTask() { return hasTask; }

        Sprite* GetCharacter() { return unit; }
        int getTeam() { return team; }
        void Animate();
        void Select();
        void Move();
        virtual void setFollowPoint(int x, int y);

        int getMenuType() {return menuType;}

        Character* target;
        Character* follow_target;
        Building* buildingTarget;

        int prevX;
        int prevY;

        int getCharacterX();
        int getCharacterY();
        int getCharacterW();
        int getCharacterH();

        int team;
        float health;
        float max_health;
        float attack;
        float defense;

        void attacked(float attacker_attack);

        void setSelected() { selected = true; }
        void unSelect() { selected = false; }

        bool isAlive() { return alive; }

        bool Alive() { return alive; }

        bool selected;

        bool alive;

        int menuType;

        bool building;
        bool mining;
        bool follow;

        bool isMining() { return mining; }
        bool isBuilding() { return building; }
        bool isFollowing() { return follow; }

    protected:

        Environment* environment;

        int *MouseX;
        int *MouseY;

        SDL_Setup* sdl_setup;

        Sprite* unit;

        int timeCheck;

        int follow_point_x;
        int follow_point_y;

        bool character_target;

        float angle;

        float distance;
        bool stopAnimation;
};


#endif // CHARACTER_HPP_INCLUDED
