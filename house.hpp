#ifndef HOUSE_HPP
#define HOUSE_HPP

#include "building.hpp"

class House : public Building
{
    public:
        House(SDL_Setup* sdl_setup, std::string FilePath, int x, int y);
        House() {}
        ~House();
        void Update();

};

#endif // HOUSE_HPP
