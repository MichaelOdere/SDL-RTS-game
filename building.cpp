#include "building.hpp"

Building::Building(SDL_Setup* sdl_setup, int x, int y)
{
    Structure = new Sprite(sdl_setup->GetRenderer(), "images/house.png", x, y, 100, 100, CollisionRectangle(13, 30, 73, 70));

}

Building::~Building()
{
    delete Structure;
}

void Building::DrawBuilding()
{
    Structure->Draw();
}
