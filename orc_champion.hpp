#ifndef orc_champion_hpp
#define orc_champion_hpp


#include "character.hpp"
#include "environment.hpp"

class Environment;

class OrcChampion : public Character
{
public:
    OrcChampion(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment);
    OrcChampion() {}
    ~OrcChampion();
    void Update();
};
#endif /* orc_champion_hpp */
