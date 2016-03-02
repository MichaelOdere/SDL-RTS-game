#ifndef BARRACKS_H
#define BARRACKS_H
#include "building.hpp"

class Barracks: public Building
{
    public:
        Barracks(SDL_Setup* sdl_setup, std::string FilePath, int x, int y, int size_x, int size_y, int passed_team);
        Barracks() {}
        ~Barracks();
        void Update();
        void startCreating(Environment* passed_environment, int unit_to_create);
        void constructing();
    private:
        int timecheck;
};

#endif // BARRACKS_H
