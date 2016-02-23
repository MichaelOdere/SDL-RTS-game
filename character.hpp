#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "building.hpp"
#include <math.h>

class Environment; //avoids error because Environment includes Character and vice versa

class Character
{
    public:
        Character(SDL_Setup* passed_SDL_Setup, std::string FilePath, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment);
        Character() {}
        ~Character();

        double GetDistance(int x1, int y1, int x2, int y2);

        virtual void Update();
        void Draw();

        Sprite* GetCharacter() { return unit; }
        int getTeam() { return team; }
        void Animate();
        void Select();
        void Move();

        Character* target;

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

        bool Alive() { return alive; }

        bool selected;

        bool alive;

    protected:

        Environment* environment;

        int *MouseX;
        int *MouseY;

        SDL_Setup* sdl_setup;

        Sprite* unit;

        int timeCheck;

        bool follow;
        int follow_point_x;
        int follow_point_y;

        float angle;

        float distance;
        bool stopAnimation;
};


#endif // CHARACTER_HPP_INCLUDED
