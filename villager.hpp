#ifndef VILLAGER_HPP
#define VILLAGER_HPP

#include "character.hpp"
#include "environment.hpp"

class Environment;

class Villager : public Character
{
    public:
        Villager(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment);
        Villager() {}
        ~Villager();
        void Update();
};

#endif // VILLAGER_HPP
