#ifndef BARRACKS_HPP
#define BARRACKS_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "building.hpp"


class Barracks: public Building
{
    public:
        Barracks(SDL_Setup* sdl_setup, std::string FilePath, int x, int y);
        //Barracks();
        ~Barracks();
        void Update();
        int getStructureX();
        int getStructureY();
        int getStructureW();
        int getStructureH();
    private:
        Sprite* Structure;

};

#endif // BARRACKS_HPP
