#ifndef TOWNCENTER_H
#define TOWNCENTER_H
#include "building.hpp"


class TownCenter: public Building
{
    public:
        TownCenter(SDL_Setup* sdl_setup, std::string FilePath, int x, int y, int size_x, int size_y, int passed_team);
        TownCenter() {}
        ~TownCenter();
        void Update();
        void startCreating(Environment* passed_environment, int unit_to_create);
    private:
        int timecheck;
};

#endif // TOWNCENTER_H
