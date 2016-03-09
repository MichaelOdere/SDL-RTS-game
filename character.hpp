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
        Character(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment);
        Character() {}
        ~Character();

        int getType() { return type; }
        double GetDistance(int x1, int y1, int x2, int y2);
        virtual void Update();
        void Draw();
        void setNoTask() { hasTask = false; }
        bool ifHasTask() { return hasTask; }
        Sprite* GetCharacter() { return unit; }
        int getTeam() { return team; }
        void Animate();
        void Select();
        void Move();
        virtual void setFollowPoint(int x, int y);
        int getMenuType() {return menuType;}
        int getCharacterX();
        int getCharacterY();
        int getCharacterW();
        int getCharacterH();
        void attacked(float attacker_attack);
        void setSelected() { selected = true; }
        void unSelect() { selected = false; }
        bool isAlive() { return alive; }
        bool isMining() { return mining; }
        bool isBuilding() { return building; }
        bool isFollowing() { return follow; }
        bool isAttacking() { return attacking; }
        bool isTargeted() { return targeted; }
        void Target(Character* passed_attacker);
        Character* getEnemy() { return enemy; }
        void setEnemy(Character* passed_enemy) { enemy = passed_enemy; }

        bool selected;

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
        Character* attacker;
        Character* enemy;
        bool alive;
        int menuType;
        bool building;
        bool mining;
        bool follow;
        bool attacking;
        bool targeted;
        int team;
        float health;
        float max_health;
        float attack;
        float defense;
        Character* target;
        Character* follow_target;
        Building* buildingTarget;
        int prevX;
        int prevY;
        int type;
        bool hasTask;
};


#endif // CHARACTER_HPP_INCLUDED
