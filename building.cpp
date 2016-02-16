#include "building.hpp"

Building::Building(SDL_Setup* sdl_setup, int x, int y)
{
    Structure = new Sprite(sdl_setup->GetRenderer(), "images/house.bmp", x, y, 50, 50); //map

}

Building::~Building()
{
    delete Structure;
}

void Building::DrawBuilding()
{
    Structure->Draw();
}
