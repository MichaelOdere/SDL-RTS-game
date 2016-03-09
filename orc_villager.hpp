#ifndef ORC_VILLAGER_HPP
#define ORC_VILLAGER_HPP

#include "character.hpp"
#include "environment.hpp"

class Environment;

class OrcVillager : public Character
{
    public:
        OrcVillager(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment);
        OrcVillager() {}
        ~OrcVillager();
        void Update();
        void setFollowPoint(int x, int y);
};

#endif // ORC_VILLAGER_HPP
