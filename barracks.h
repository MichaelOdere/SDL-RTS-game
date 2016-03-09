#ifndef BARRACKS_H
#define BARRACKS_H
#include "building.hpp"

class Barracks: public Building
{
    public:
        Barracks(SDL_Setup* sdl_setup, SDL_Texture* passed_image, int x, int y, int size_x, int size_y, int passed_team, Environment* passed_environment);
        Barracks() {}
        ~Barracks();
        void Update();
        void startCreating(int unit_to_create);
        void constructing();
    private:
        int timecheck;
};

#endif // BARRACKS_H
