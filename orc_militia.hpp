#ifndef ORC_MILITIA_HPP
#define ORC_MILITIA_HPP

#include "character.hpp"
#include "environment.hpp"

class Environment;

class OrcMilitia : public Character
{
public:
    OrcMilitia(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment);
    OrcMilitia() {}
    ~OrcMilitia();
    void Update();
};
#endif // ORC_MILITIA_HPP
