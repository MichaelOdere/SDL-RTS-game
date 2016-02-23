
#ifndef TOWNCENTER_H
#define TOWNCENTER_H
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"


class TownCenter: public Building
{
    public:
        TownCenter(SDL_Setup* sdl_setup, std::string FilePath, int x, int y);
        ~TownCenter();

    private:
        Sprite* Structure;

};

#endif // TOWNCENTER_H
