#ifndef MILITIA_HPP
#define MILITIA_HPP

#include "character.hpp"
#include "environment.hpp"

class Environment;

class Militia : public Character
{
public:
    Militia(SDL_Setup* passed_SDL_Setup, std::string FilePath, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment);
    Militia() {}
    ~Militia();
    void Update();
};
#endif // MILITIA_HPP
