#ifndef champion_hpp
#define champion_hpp


#include "character.hpp"
#include "environment.hpp"

class Environment;

class Champion : public Character
{
public:
    Champion(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment);
    Champion() {}
    ~Champion();
    void Update();
};
#endif /* champion_hpp */
