#include "TownCenter.h"


TownCenter::TownCenter(SDL_Setup* sdl_setup, std::string FilePath, int x, int y) : Building(sdl_setup, FilePath, x, y)
{
    std::cout << "Town Center created" << std::endl;
}
TownCenter::~TownCenter()
{
}
