#ifndef VILLAGER_HPP
#define VILLAGER_HPP

#include "character.hpp"

class Environment;

class Villager : public Character
{
    public:
        Villager(SDL_Setup* passed_SDL_Setup, std::string FilePath, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment);
        Villager() {}
        ~Villager();

};

#endif // VILLAGER_HPP
