#ifndef BARRACKS_H
#define BARRACKS_H
#include "building.hpp"




class Barracks: public Building
{
    public:
        Barracks(SDL_Setup* sdl_setup, std::string FilePath, int x, int y);
        Barracks() {}
        ~Barracks();

};

#endif // BARRACKS_H
