#ifndef TOWNCENTER_H
#define TOWNCENTER_H
#include "building.hpp"


class TownCenter: public Building
{
    public:
        TownCenter(SDL_Setup* sdl_setup, SDL_Texture* passed_image, int x, int y, int size_x, int size_y, int passed_team, Environment* passed_environment);
        TownCenter() {}
        ~TownCenter();
        void Update();
        void startCreating(int unit_to_create);
    private:
        int timecheck;
};

#endif // TOWNCENTER_H
